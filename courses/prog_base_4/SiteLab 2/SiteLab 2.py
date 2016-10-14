from flask import Flask, render_template, url_for, send_from_directory, send_file, json
import json
import os

app = Flask(__name__)


@app.context_processor
def utility_processor():

    f = open(os.path.dirname(os.path.abspath(__file__)) + "\\static\\data.json")
    jtext = f.read()
    objlist = json.loads(jtext)

    # def get_from_json(index, key):
    #     return objlist[index].get(key)

    return dict(obj_amount=11, objlist=objlist, url_for=dated_url_for)


def dated_url_for(endpoint, **values):
    if endpoint == 'static':
        filename = values.get('filename', None)
        if filename:
            file_path = os.path.join(app.root_path, endpoint, filename)
            values['q'] = int(os.stat(file_path).st_mtime)
    return url_for(endpoint, **values)


@app.route('/')
def index():
    return render_template("index.html")


@app.route('/objects/')
def objects():
    return render_template("objects.html")


@app.route('/objects/<int:obj_id>')
def curr_object(obj_id):
    return render_template("curr_obj.html", obj_id=obj_id)


if __name__ == '__main__':
    app.run(debug=True)
