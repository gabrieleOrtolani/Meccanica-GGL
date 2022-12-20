#this program writes the data received by WEMOS D1 via UDP protocol into a file
#AUTHOR: gabrieleOrtolani
#DATE: 20/11/2022

import socket


msgFromClient       = "ACK"

bytesToSend         = str.encode(msgFromClient)

serverAddressPort   = ("192.168.1.105", 1234)

bufferSize          = 1024

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

with open("dati.txt", "w") as f:
# Send to server using created UDP socket
    while 1:
        UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)
        
        print(msgFromServer[0])

        f.write(str(msgFromServer[0])+"\n")

f.close()





 
