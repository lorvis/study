import os
import sys
import socket
import json
import re

def validate_ip(addr_ip):
    if isinstance(addr_ip, str):
        addr_ipset = re.split('[.]', addr_ip)
        if len(addr_ipset) != 4:
            return False
        else:
            ipvalid = 0
            for i in addr_ipset:
                if 0 <= int(i) <= 255:
                    ipvalid += 1
                    continue
                else:
                    ipvalid = -1
                    break
            if ipvalid == 4:
                return True
            else:
                return False


def validate_port(addr_port):
    if isinstance(addr_port, str):
        if 0 <= int(addr_port) <= 65535:
            return True
        else:
            return False


def main():
    # Connection attempting loop
    while True:

        try:
            addr_ip = input('Enter server IP address: ')
            addr_port = input('Enter server port: ')
        except KeyboardInterrupt:
            print("program aborted")
            sys.exit(1)
        except Exception as e:
            print('Address input exception>> {0}\n'.format(e))
            sys.exit(1)

        if not addr_ip or not addr_port:
            continue
        if not (validate_ip(addr_ip)):
            print("Incorrect IP format")
            continue
        if not (validate_port(addr_port)):
            print("Incorrect port format")
            continue

        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((addr_ip, int(addr_port)))
            break
        except socket.error as e:
            print("Socket error >> {0}".format(e))
            if s:
                s.close()
            continue
        except Exception as e:
            print("Connecting exception >> {0}".format(e))
    print("Connected to {0}:{1}".format(addr_ip, addr_port))
    print("For help type '-h' or '-help' ")

    # Messaging loop
    while True:

        try:
            msg = input("Enter your message: ")
            if not msg:
                continue
        except KeyboardInterrupt:
            print("program aborted")
            sys.exit(1)
        except Exception as e:
            print("Message input exception >> {0}".format(e))
            sys.exit(1)

        try:
            s.send(msg.encode('utf-8'))
            print("Sent >> \n {0}".format(msg))
            if msg == '-q':
                print("Disconnected by client")
                return
        except socket.error:
            print("Sending socket error")
            s.close()
            exit(1)

        try:
            response = (s.recv(20000)).decode('utf-8')
            print("Received << \n {0}".format(response))
        except socket.error:
            print("Receiving socket error")
            s.close()
            exit(1)
        except Exception as e:
            print("Receiving exception >> {0}".format(e))
            exit(1)


main()


