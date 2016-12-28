from model import *
from flask import request, render_template, url_for, flash, redirect, session, abort, Response, send_from_directory, send_file, after_this_request
from flask_bootstrap import Bootstrap
from navbar import *
from shutil import rmtree
from mimetypes import guess_type
from markupsafe import escape

csrf = CsrfProtect()
app = Flask(__name__)
app.secret_key = "B59A94B829FDD9C7375FC2F32E21A"
app.config["MAX_CONTENT_LENGTH"] = 2 * 1024 * 1024 * 1024
csrf.init_app(app)
address = "http://127.0.0.1"
port = 27015
full_address = address + ":" + str(port)
Bootstrap(app)
login_manager = LoginManager()
login_manager.init_app(app)
server_root = os.getcwd()
drive_root = os.getcwd() + "\\user files\\storage\\"

ALLOWED_IMAGE_TYPES = ['PNG', 'BMP', 'JPEG', 'JPG']

# region Classes


class TreeObj:
    def __init__(self, id, name, path, size, type):
        self.id = id
        self.name = name
        self.path = path
        self.size = size
        self.type = type


class UserFieldEnum(Enum):
    none = int(0)
    login = int(2)
    username = int(4)
    email = int(8)


nav.init_app(app)


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
    cur_dir_level = 0
    for root, dirs, files in os.walk(root):
        level = root.replace(drive_root, '').count(os.sep)
        if level == 0:
            html += '<div class="directory">Drive</div><div class="dircontent">'
            continue
        else:
            if level > cur_dir_level:
                html += '<div class="dircontent">'
                cur_dir_level += 1
            elif level < cur_dir_level:
                html += '</div>'
                cur_dir_level -= 1
            dirname = os.path.basename(root)
            roothash = saltyhash(root)
        html += '<div><a onclick="updateTreeRepr(\'' + roothash +'\')"' +\
                'ondblclick=contentChangeHiddenState("' + roothash + '")>' +\
                '<span class="directory" id="' + roothash + '" style="margin-left: ' + str(level * 30) + 'px">' + \
                dirname + \
                '</span>' + \
                "<label class=\"btn btn-default btn-file\">" + \
                "Upload" + \
                "<input type=\"file\" name=\"file\" style=\"display: none;\">" + \
                "</label>" + \
                '</div>' + \
                '<div class="dircontent">'
        if root[len(root)-1] != os.sep:
            root += os.sep
        for f in files:
            level = root.replace(drive_root, '').count(os.sep)
            # html += '<a href="' + url_for('download', file_id=saltyhash(root+f)) + '"><div>' + '<span class="file"  id="' + saltyhash(root+f) + '" style="margin-left: ' + str(level * 30) + 'px">'
            # html += f + '</span>' + '</div></a>'
            filehash = saltyhash(root+f)
            html += '<div><a id="' + f + '" onclick="updateTreeRepr(\'' + filehash +'\')" ondblclick="downloadTreeFile(\''+ filehash +'\')"><span class="file"  id="' \
                    + filehash \
                    + '" style="margin-left: ' + str(level * 30) + 'px">'
            html += f + '</span>' + '</a></div>'
        html += "</div>"
    html += "</div></div>"
    return html


def send_file_from_hashtree(root, hash):
    for root, dirs, files in os.walk(root):
        if root[len(root)-1] != os.sep:
            root += os.sep
        for f in files:
            if hash == saltyhash(root+f):
                result = send_from_directory(directory=root, filename=f)
                result.headers["Content-Disposition"] = "inline; filename=\"" + f + "\""
                result.headers["Content-type"] = "application/octet-stream"
                result.headers["Cache-Control"] = "no-cache"
                result.headers["Pragma"] = "no-cache"
                return result
    return redirect(url_for('drive'))


def get_file_to_hashtree(root, hash, file):
    for root, dirs, files in os.walk(root):
        if hash == saltyhash(root):
            file.save(root, file.filename)
            return Response(status=200)
        if root[len(root)-1] != os.sep:
            root += os.sep
        for f in files:
            pass
    return Response(status=404)


def get_file_by_id(id, root):
    for root, dirs, files in os.walk(root):
        if root[len(root)-1] != os.sep:
            root += os.sep
        for f in files:
            if hash == saltyhash(root+f):
                return f, os.stat(root+f).st_size
    return redirect(url_for('drive'))


def get_treeobj_by_id(obj_id, user_id):
    base_root = drive_root + str(user_id)
    for root, dirs, files in os.walk(base_root):
        if obj_id == saltyhash(root):
            root += os.sep
            return TreeObj(obj_id, os.path.dirname(root), root, None, "d")
        if root[len(root)-1] != os.sep:
            root += os.sep
        for f in files:
            if obj_id == saltyhash(root+f):
                stat = os.stat(root+f)
                return TreeObj(obj_id, f, root + f, stat.st_size, "f")
    return None


def tree_get_path(obj_id, user_id):
    base_root = drive_root + str(user_id)
    for root, dirs, files in os.walk(base_root):
        if obj_id == saltyhash(root):
            root += os.sep
            return root
        if root[len(root)-1] != os.sep:
            root += os.sep
        for f in files:
            if obj_id == saltyhash(root+f):
                stat = os.stat(root+f)
                return root+f
    return None
# endregion

# region context


@app.before_request
def csrf_protect():
    validate_csrf(request.data)

# app.jinja_env.globals['_csrf_token'] = generate_csrf


@app.context_processor
def url_for_override():
    return dict(
        url_for=dated_url_for,
        full_address=full_address,
        csrf_token=generate_csrf,
        session=session,
        acctypes=acctypes,
        freespace_max=freespace_max,
        os=os,
        nav=nav,
    )

# endregion

# region Routes


@app.route('/drive/ajax/tree-repr/<id>')
def ajax_repr(id=None):
    @after_this_request
    def content_type_to_html(response):
        response.headers["Content-type"] = 'text/html'
        return response

    if not id or not session.get("ID"):
        return "AJAX NULL ERROR"

    treeobj = get_treeobj_by_id(id, session.get("ID"))

    if treeobj:
        return render_template('ajax/repr.html', treeobj=treeobj)
    else:
        return "FOUND NOTHING"


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
            root = drive_root + str(session.get("ID"))
            return render_template('drive.html', tree=generate_os_tree_html(root))
    return None


@app.route('/drive/download/<file_id>')
def download(file_id):
    root = drive_root + str(session.get("ID")) + "\\"
    result = send_file_from_hashtree(root, file_id)
    if result:
        return result
    else:
        return redirect('drive')


@app.route('/drive/delete/<obj_id>')
def delete(obj_id):
    user = User(user_id=session.get("ID"))
    if user.exists():
        path = tree_get_path(obj_id, user["ID"])

        if os.path.isfile(path):
            os.remove(path)

        if os.path.isdir(path):
            rmtree(path)

    return redirect(url_for('drive'))


@app.route('/drive/upload/<directory_id>', methods=["POST"])
def upload(directory_id):
    root = drive_root + str(session.get("ID")) + "\\"
    if 'file' not in request.files:
        flash('No file part')
        return Response(status=400)
    file = request.files['file']
    if file.filename == '':
        return Response(status=400)
    get_file_to_hashtree(root, directory_id, file)
    return redirect(url_for('drive'))


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
