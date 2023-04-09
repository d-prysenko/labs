import socket

ADDR = "127.0.0.1"
PORT = 777
BUFFER_LENGTH = 1024

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    print(">> ", end='')
    message = str.encode(input())
    sock.sendto(message, (ADDR, PORT))
    buffer, addr = sock.recvfrom(BUFFER_LENGTH)
    print("Response: " + buffer.decode("utf-8"))