from pymongo import MongoClient, errors
from enum import Enum
from werkzeug.utils import secure_filename
from flask import Flask, request, render_template, url_for, flash, redirect, session, abort, Response
from flask_login import LoginManager
from wtforms import Form, BooleanField, StringField, PasswordField, validators
from flask_wtf.csrf import CsrfProtect, generate_csrf, validate_csrf
from bson.json_util import dumps
from PIL import Image
import random
import base64
import datetime
import bitmath
import hashlib
from io import BytesIO
import os

update_params = ["ADD", "UPDATE", "INCREMENT"]
modelerr = Enum('LOGIN_ALREADY_EXISTS', 'USERNAME_ALREADY_EXISTS')
body_private_fields = ["ID", "login", "password", "email"]
acctypes = ["owner", "admin", "moderator", "premium", "user"]
freespace_max = [bitmath.GiB(10), bitmath.GiB(5), bitmath.GiB(2), bitmath.GiB(1), bitmath.MiB(700)]
drive_root = os.getcwd() + "\\user files\\storage\\"

#region Classes


class User:

    def __init__(self, **kwargs):
        self.__body = None

        if kwargs.get('user_id'):
            self.__body = get_storage_collection('users').find_one({"ID": kwargs.get('user_id')})
            return
        if kwargs.get('username'):
            self.__body = get_storage_collection('users').find_one({"username": kwargs.get('username')})
            return

        if all((kwargs.get('login'), kwargs.get('password'))):
            self.__body = get_user(login=kwargs.get('login'), password=kwargs.get('password'))
            return

        if self.__body is not None:
            self.__body = dict(self.__body)

    def __getitem__(self, item):
        if self.__body is None:
            return None
        else:
            return self.__body[item]

    def __setitem__(self, key, value):
        if self.__body is None:
            return
        if key not in body_private_fields and key in dict(self.__body):
            self.__body[key] = value
            get_storage_collection('users').find_one_and_update(
                {"ID": self.__body["ID"]},
                {"$set": {key: value}}
            )

    def exists(self):
        return self.__body is not None

    def is_anonymous(self):
        return self.__body is None

    def is_active(self):
        return self.__body is not None and self.__body["active"] is True

    def get_id(self):
        if self.__body is None:
            return None
        else:
            return str(self.__body["ID"])

# endregion


def get_storage_collection(collname):
    client = MongoClient('localhost', 27017)
    db = client['FileStorageCourse']
    coll = db[collname]
    return coll


def saltyhash(password):
    m = hashlib.md5()
    m.update(bytes(str(password), encoding="UTF-8"))
    m.update(bytes("wX1n1tgwu9Wkee4I3djOr2J05TuUUr", encoding="UTF-8"))
    return str(m.digest())


def get_groups_by_login(login):
    users = get_storage_collection('users')
    try:
        groups = users.find_one({"login": login}, {"groups": True})
    except errors.CursorNotFound:
        print("Failed to found user " + login + " during logging out")
        return False
    return groups

# region user stuff


def user_create(login, username, password, email):
    users = get_storage_collection('users')
    server = get_storage_collection('server')
    user_count = dict(server.find_one({"SERVER_USER_ID_COUNTER": {"$exists": True}}))["SERVER_USER_ID_COUNTER"]
    if users.find_one({"login": login}) is not None:
        return modelerr.LOGIN_ALREADY_EXISTS

    post = {
        "ID": user_count,
        "login": login,
        "username": username,
        "password": saltyhash(password),
        "email": email,
        "session": None,
        "type": acctypes.index("user"),
        "register date": str(datetime.datetime.utcnow()),
        "memory used": 0,
        "files": 0,
        "directories": 0,
        "downloads": 0,
        "friends": None,
        "groups": None,
        "avatar": None,
        "active": True
    }

    server.find_one_and_update({"SERVER_USER_ID_COUNTER": {"$exists": True}}, {"$inc": {"SERVER_USER_ID_COUNTER": 1}})
    users.insert_one(post)
    os.mkdir(drive_root + str(user_count))


def get_user_id_by_login(login):
    users = get_storage_collection('users')
    return dict(users.find_one({"login": login}, {"ID": True}))["ID"]


def get_user_by_id(user_id):
    users = get_storage_collection('users')
    return users.find_one({"ID": int(user_id)})


def get_user(login, password):
    users = get_storage_collection('users')
    if password is not None:
        return users.find_one({"login": login, "password": saltyhash(password)})
    else:
        return users.find_one({"login": login})


def get_user(**kwargs):
    users = get_storage_collection('users')
    if kwargs.get('user_id'):
        return users.find_one({"ID": kwargs.get('user_id')})
    if kwargs.get('username'):
        return users.find_one({"username": kwargs.get('username')})
    if all((kwargs.get('login'), kwargs.get('password'))):
        return users.find_one({"login": kwargs.get('login'), "password": saltyhash(kwargs.get('password'))})
    return None


def get_user_kv(key, value):
    return get_storage_collection('users').find_one({key: value})


def user_exists(login):
    return get_storage_collection('users').find_one({"login": login}) is not None


def user_exists(username):
    return get_storage_collection('users').find_one({"username": username}) is not None


def user_exists(login, password):
    return get_storage_collection('users').find_one({"login": login, "password": password}) is not None


def user_field_unique(key, value):
    return get_storage_collection('users').find_one({key: value}) is not None

# endregion






