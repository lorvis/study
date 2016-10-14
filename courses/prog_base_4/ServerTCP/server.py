import socket
import threading
import json
import re


class Client:

    def __init__(self, conn, addr, t):
        self.socket = conn
        self.ip = addr[0]
        self.port = addr[1]
        self.thread = t

    def close(self):
        self.socket.close()


def create_response(msg, jtext):
    jstruct = json.loads(jtext)
    msg = str(msg).strip()
    if msg == "-q" or msg == "quit":
        print("Client disconnected")
        return "q"
    if msg == "-h" or msg == "-help":
        return "TCP Client commands: \n" + \
              "-h/-help help\n" + \
              "-q/-quit to shut down client and server\n" + \
              "-json to get whole json file\n" + \
              "-filter to get filtered json, request format '-filter <object type>'\n" + \
              "-clientlist to get list of clients connected to server\n"
    if msg == "-json":
        return jtext
    if msg == "-clientlist" or msg == "-cl":
        return "cl"
    if msg.find("-filter") == 0:

        msg_args = re.split("( )", msg)
        msg_args = list(filter(" ".__ne__, msg_args))
        msg_args.remove("-filter")
        jstruct = list(filter(lambda a: dict(a).get("Type") == msg_args[0], jstruct))
        jtext = json.dumps(jstruct, indent=4)
        return jtext
    return "You have typed {0}".format(msg)


def thread_serve(client, clients):
    print("Connected to {0}:{1}".format(client.ip, client.port))
    f = open("data.json", "r")
    jtext = f.read()
    while True:
        try:
            msg = client.socket.recv(20000).decode('utf-8')
            print("{0} << {1}:{2}".format(msg, client.ip, client.port))
            resp = create_response(msg, jtext)

            if resp == "cl":
                resp = "Connected clients:\n"
                for i in range(0, len(clients)):
                    resp += "\n" + "{0}. ".format(i) + clients[i].ip + ":" + str(clients[i].port)

            if resp == "q":
                for i in range(0, len(clients)):
                    if clients[i].socket == client.socket:
                        clients[i].close()
                        del clients[i]
                        resp = "Disconnected by client"
                        break

            print("{0}  >> {1}:{2}\n".format(resp, client.ip, client.port))
            client.socket.send(resp.encode('utf-8'))
            if resp == "Disconnected by client":
                break

        except socket.error as e:
            print("{0}:{1} >> ".format(client.ip, client.port) + "Socket error {0}".format(e))
            break
        except Exception as e:
            print("{0}:{1} >> ".format(client.ip, client.port) + "Exception on messaging>> {0}".format(e))
            break


def main():
    HOST = ""
    PORT = 8000
    clients = []

    while True:
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.bind((HOST, PORT))
            s.listen()
        except socket.error as se:
            print("Socket binding error {0}".format(se))
            continue
        except Exception as e:
            print("Exception on deploying>> {0}".format(e))
            continue
        print("Listening on port %s" % PORT)
        break

    while True:
        try:
            conn, addr = s.accept()
            t = " "
            c = Client(conn, addr, t)
            c.thread = threading.Thread(target=thread_serve, args=(c, clients))
            clients.append(c)
            clients[len(clients)-1].thread.start()
        except socket.error as e:
            print("Socket error {0}".format(e))
        except Exception as e:
            print("Exception on connecting>> {0}".format(e))
    s.close()

main()
