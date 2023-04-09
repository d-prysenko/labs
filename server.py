import socket
import datetime

PORT = 777
BUFFER_LENGTH = 1024

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('', PORT))

print(f"UDP server started on port {PORT}")

while True:
    buffer, addr = sock.recvfrom(BUFFER_LENGTH)
    recv_str = buffer.decode("utf-8")

    time = datetime.datetime.now().strftime("%d-%m-%Y %H:%M")

    print(f"Received message: {recv_str}")
    print(f"Sending time({time}) to client {addr}..")
    
    sock.sendto(str.encode(time), addr)