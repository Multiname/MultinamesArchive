#include <iostream>

#include <fstream>
#include <streambuf>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{
    cout << "Trying to Send File Over Tcp!" << endl;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    int port = 27015;
    string ipAddress = "192.168.0.102";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    int connectRes = connect(sock, (sockaddr *)&hint, sizeof(hint));

    if (connectRes == -1)
    {
        return 1;
    }

    ifstream ifs("result.txt");
    string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

    int sendRes = send(sock, str.c_str(), str.size() + 1, 0);

    if (sendRes == -1)
    {
        cout << "Could not send to server! Whoops!\r\n";
    }

    else
    {
        cout << "The file \"output.csv\" has been successfully sent to the server.\r\n";
    }

    // Wait for response
    char buf[4096];

    memset(buf, 0, 4096);

    int bytesReceived = recv(sock, buf, 4096, 0);

    if (bytesReceived == -1)
    {
        cout << "There was an error getting response from server\r\n";
    }
    else
    {
        // Display response
        cout << "SERVER> Data received:\n"
             << string(buf, bytesReceived) << "\r\n";
    }
    // Close the socket
    close(sock);
    return 0;
}
