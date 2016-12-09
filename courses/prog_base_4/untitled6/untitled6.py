from model import *

csrf = CsrfProtect()
app = Flask(__name__)
app.secret_key = "B59A94B829FDD9C7375FC2F32E21A"
app.config["MAX_CONTENT_LENGTH"] = 2 * 1024 * 1024 * 1024
# csrf.init_app(app)
address = "http://127.0.0.1"
port = 27015
full_address = address + ":" + str(port)

login_manager = LoginManager()

login_manager.init_app(app)

ALLOWED_IMAGE_TYPES = ['PNG', 'BMP', 'JPEG', 'JPG']

# region Classes


class UserFieldEnum(Enum):
    none = int(0)
    login = int(2)
    username = int(4)
    email = int(8)


class RegistrationForm(Form):
    login = StringField('Login', [validators.length(min=6, max=15, message="Length of login must be 6 to 15")])
    username = StringField('Username', [validators.length(min=4, max=20, message="Length of login must be 4 to 20")])
    password = PasswordField('New Password', [
        validators.DataRequired(),
        validators.EqualTo('confirm', message='Passwords must match')
    ])
    confirm = PasswordField('Repeat Password')
    email = StringField('Email', [validators.Email(message="invalid email format")])

    def is_unique(self):
        res = UserFieldEnum.none.value
        if user_field_unique("login", self.login.data): res |= UserFieldEnum.login.value
        if user_field_unique("username", self.username.data): res |= UserFieldEnum.username.value
        if user_field_unique("email", self.email.data): res |= UserFieldEnum.email.value
        return res


class ProfileForm(Form):
    username = StringField('Username', [validators.length(min=6, max=15, message="Length of login must be 8 to 15")])


class LoginForm(Form):
    login = StringField('Login', [validators.length(min=6, max=15, message="Length of login must be 8 to 15")])
    password = PasswordField('Password', [validators.length(min=8, max=35, message="Length of password must be 8 to 35")])

# endregion REG

# region Functions


def dated_url_for(endpoint, **values):
    if endpoint == 'static':
        filename = values.get('filename', None)
        if filename:
            file_path = os.path.join(app.root_path, endpoint, filename)
            values['q'] = int(os.stat(file_path).st_mtime)
    return url_for(endpoint, **values)

# endregion

# region context


@app.before_request
def csrf_protect():
    validate_csrf(request.data)

# app.jinja_env.globals['_csrf_token'] = generate_csrf


@login_manager.user_loader
def user_loader(user_id):
    return get_user_by_id(user_id)


@app.context_processor
def url_for_override():
    return dict(
        url_for=dated_url_for,
        full_address=full_address,
        csrf_token=generate_csrf,
        session=session,
        os=os
    )

# endregion

# region Routes


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/profile/json/')
@app.route('/profile/<username>/json/')
def profile_data(username=None):
    if username is None and User(user_id=session.get("ID")).exists():
        user = User(user_id=session.get("ID"))
        return json.dumps(dict(username=user["username"], status=user["status"], age=user["years old"]))
    if User(username=username).exists():
        user = User(username=username)
        return json.dumps(dict(username=user["username"], status=user["status"], age=user["years old"]))
    return Response(status=404)


@app.route('/profile/')
@app.route('/profile/<username>')
def profile(username=None):
    if session.get("authenticated") is not True:
        return redirect(url_for('login'))
    if username is None:
        return render_template('profile.html', user=User(username=session.get("username")))
    if User(username=username).exists():
        return render_template('profile.html', user=User(username=username))
    else:
        return redirect(url_for('index'))


@app.route('/profile/status/', methods=['GET', 'POST'])
@app.route('/profile/<username>/status/', methods=['GET'])
def status(username=None):
    if request.method == "GET":
        if username is None and User(user_id=session.get("ID")).exists():
            return json.dumps(dict(status=User(user_id=session.get("ID"))["status"]))
        if User(username=username).exists():
            return json.dumps(dict(status=User(username=username)["status"]))
        return Response(status=404)

    if username is None and User(user_id=session.get("ID")).exists():
        User(user_id=session.get("ID"))["status"] = request.form["status"]
        if request.form["submit"]:
            return redirect(url_for('profile'))
        return Response(status=200)
    Response(status=403)


@app.route('/profile/age/', methods=['GET', 'POST'])
@app.route('/profile/<username>/age/', methods=['GET'])
def age(username=None):
    if request.method == "GET":
        if username is None and User(user_id=session.get("ID")).exists():
            return json.dumps(dict(age=User(user_id=session.get("ID"))["years old"]))
        if User(username=username).exists():
            return json.dumps(dict(age=User(username=username)["years old"]))
        return Response(status=404)

    if username is None and User(user_id=session.get("ID")).exists():
        yo = request.form["age"]
        try:
            yo = int(yo)
            User(user_id=session.get("ID"))["years old"] = yo
        except ValueError:
            return json.dumps(dict(error="invalid age"))
        if request.form["submit"]:
            return redirect(url_for('profile'))
        return Response(status=200)
    Response(status=403)


@app.route('/register/', methods=["GET", "POST"], strict_slashes=False)
def register():
    form = RegistrationForm(request.form)
    if request.method == "POST":
        if form.validate():
            field_bools = form.is_unique()
            if (field_bools & UserFieldEnum.login.value) is not UserFieldEnum.none.value:
                flash("Login is already in use")
            if (field_bools & UserFieldEnum.username.value) is not UserFieldEnum.none.value:
                flash("Username is already in use")
            if (field_bools & UserFieldEnum.email.value) is not UserFieldEnum.none.value:
                flash("Email is already in use")
            if field_bools != UserFieldEnum.none.value: return render_template('register.html', form=form)

            user_create(form.login.data, form.username.data, form.password.data, form.email.data)
            flash('Thanks for registering')
            return redirect(url_for('login'))
        else:
            flash('Validation failed')
            return render_template('register.html', form=form)
    return render_template('register.html', form=form)


@app.route('/login/', methods=['GET', 'POST'])
def login():
    form = LoginForm(request.form)
    if session.get("authenticated"):
        redirect(url_for("index"))
    if request.method == "POST":
        if form.validate():
            user = User(login=form.login.data, password=form.password.data)
            if user.exists():
                session["authenticated"] = True
                session["username"] = user["username"]
                session["ID"] = user["ID"]
                return render_template('index.html')
            else:
                flash("Invalid login or password")
                return render_template('login.html', form=form)
        else:
            flash("Invalid length login or password")
            return render_template('login.html', form=form)
    return render_template('login.html', form=form)


@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index'))


# endregion

if __name__ == '__main__':
    app.run(port=port)
