import socket
PORT = 1234


def main():
    port = 1234

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind host address and port together
    server_socket.bind(("10.0.0.19", port))
    server_socket.listen(1)
    while True:
        conn, address = server_socket.accept()  # accept new connection
        print(address)
        data = conn.recv(1024 * 8).decode()
        open("logFiles/" + address[0], "w").write(data)
        print("Updated " + address[0] + " log file!")

        conn.close()


if __name__ == "__main__":
    main()
