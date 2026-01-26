import socket

host = '127.0.0.1'
port = 8000

# Create a socket object using IPv4 (AF_INET) and TCP (SOCK_STREAM)
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the specified host and port
server_socket.bind((host, port))
# Start listening for incoming connections
server_socket.listen()
print(f"Server listening on {host}:{port}")

while True:
    # Accept an incoming connection – return new socket
    conn, addr = server_socket.accept()
    print(f"Connected by {addr}")

    # Receive data from the client
    # The buffer size (1024) determines how much data to read at once
    data = conn.recv(1024)
    # Should do error checking here - decode the received bytes to string
    received_sentence = data.decode()
    print(f"Received: {received_sentence}")
    # Reverse the sentence
    reversed_sentence = received_sentence[::-1]
    print(f"Reversed: {reversed_sentence}")
    # Send the reversed sentence back to the client
    conn.send(reversed_sentence.encode())
    # Close the connection to the client
    conn.close()


server_socket.close()