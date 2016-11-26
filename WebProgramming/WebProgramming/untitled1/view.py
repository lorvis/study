from model import *

csrf = CsrfProtect()
app = Flask(__name__)
app.secret_key = "B59A94B829FDD9C7375FC2F32E21A"
app.config["MAX_CONTENT_LENGTH"] = 2 * 1024 * 1024 * 1024
csrf.init_app(app)
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


def generate_os_tree_html(root):
    html = ''
    for root, dirs, files in os.walk(root):
        level = root.replace(root, '').count(os.se)
        indent = ' ' * 4 * level
        html += '<pre>' + indent
        html += os.path.basename(root) + '</pre>'
        subindent = ' ' * 4 * (level + 1)
        for f in files:
            html += '<pre>' + subindent
            html += f + '</pre>'
    return html

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
        acctypes=acctypes,
        freespace_max=freespace_max,
        os=os
    )

# endregion

# region Routes


@app.route('/')
def index():
    return render_template('index.html')


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


@app.route('/profile/avatar/', methods=["POST"])
@app.route('/profile/avatar/<uid>',  methods=["POST"])
def avatar(uid=None):
    if session.get("type") != acctypes.index("owner") and (uid and session.get("ID") != uid):
        return Response(status=403)

    if "avatar" not in request.files:
        flash('No sent avatar')
        return redirect(url_for('profile'))

    ava = request.files["avatar"]

    if ava.filename == '':
        flash("No selected avatar")
        return redirect(url_for('profile'))

    if len(ava.read()) > 16 * 1024 * 1024:
        flash("Max avatar size is 16MB")
        return redirect(url_for('profile'))

    img = Image.open(ava)
    width, height = img.size
    if ava and img.format in ALLOWED_IMAGE_TYPES and width < 1024 and height < 4096:
        user = User(user_id=session.get("ID"))["avatar"] = base64.b64encode(ava.read())
        return redirect(url_for('profile'))


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


@app.route('/drive', methods=['GET', 'POST'])
def drive():
    if request.method == "GET":
        if User(user_id=session.get("ID")).exists():
            root = drive_root + str(session.get("ID")) + "\\"
            return render_template('drive.html', tree=generate_os_tree_html(root))
        else:
            return Response(status=403)


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
                session["acctype"] = user["type"]
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
