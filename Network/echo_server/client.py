from socket import *

HOST = '127.0.0.1'
PORT = 8000

bufsize = 1024
ADDR = (HOST, PORT)

while True:
    data = input('>')
    if not data:
        break
    tcpclient = socket(AF_INET, SOCK_STREAM)
    tcpclient.connect(ADDR)
    tcpclient.send(data.encode())
    data = tcpclient.recv(bufsize).decode()
    print(data)
    tcpclient.close()
