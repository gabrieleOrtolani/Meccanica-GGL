#this program writes the data received by WEMOS D1 via UDP protocol into a file
#AUTHOR: gabrieleOrtolani
#DATE: 20/11/2022

import socket


msgFromClient       = "ACK"

bytesToSend         = str.encode(msgFromClient)

serverAddressPort   = ("192.168.1.118", 8888)

bufferSize          = 128

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

UDPClientSocket.sendto(bytesToSend, serverAddressPort)

with open("dati.txt", "w") as f:
# Send to server using createsd UDP socket
    while 1:
        UDPClientSocket.sendto(bytesToSend, serverAddressPort)
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)
        
        print(msgFromServer[0].decode("utf-8"))
        

        f.write(msgFromServer[0].decode("utf-8")+"\n")

f.close()





 
