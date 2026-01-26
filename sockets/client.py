import socket

host = '127.0.0.1'
port = 65432
sentence = "Hello, World!"

# Create a socket object using IPv4 (AF_INET) and TCP (SOCK_STREAM)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server at the specified host and port
# You need to know these; host is a string eg “127.0.0.1”, port an int
client_socket.connect((host, port))

# Send the sentence to the server
print(f"Sending: {sentence}")
client_socket.send(sentence.encode())

# Receive the reversed sentence from the server
data = client_socket.recv(1024)

# Decode the received bytes to a string and print it
print(f"Received: {data.decode()}")

# Ensure the client socket is closed when done
client_socket.close()