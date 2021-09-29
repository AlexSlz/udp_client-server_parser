#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#pragma comment ( lib, "ws2_32.lib" )
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>

#define PORT 7777    // порт сервера

using namespace std;

class Command {
public:
    void (*f) (int, INT16[], INT16[], string);
    string name[99];
    int nameCount = 0;
    int reqParamNum = 0;
    Command(void(*f_0)(int, INT16[], INT16[], string), int paramNum, int count, const char* text, ...) {
        const char ** s = &text;
        for (size_t i = 0; i < count; i++, s++)
        {
            name[i] = (*s);
        }
        nameCount = count;
        reqParamNum = paramNum;
        f = f_0;

    }
};
void displayParams(int count, INT16 params[], INT16 color[]) {
    cout << "Parameters\n";
    for (size_t i = 0; i < count; i++)
    {
        cout << params[i] << "\n";
    }
}
void clearDisplay(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command clear\n";
    displayParams(paramCount, parameters, color);
}
void drawPixel(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw Pixel\n";
    displayParams(paramCount, parameters, color);
}
void drawLine(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw Line\n";
    displayParams(paramCount, parameters, color);
}
void drawRect(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw Rectangle\n";
    displayParams(paramCount, parameters, color);
}
void fillRect(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command fill Rectangle\n";
    displayParams(paramCount, parameters, color);
}
void drawEllipse(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw Ellipse\n";
    displayParams(paramCount, parameters, color);
}
void fillEllipse(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command fill Ellipse\n";
    displayParams(paramCount, parameters, color);
}
void drawCircle(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw Circle\n";
    displayParams(paramCount, parameters, color);
}
void fillCircle(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command fill Circle\n";
    displayParams(paramCount, parameters, color);
}
void drawRoundRect(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw rounded rectangle\n";
    displayParams(paramCount, parameters, color);
}
void fillRoundRect(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command fill rounded rectangle\n";
    displayParams(paramCount, parameters, color);
}
void drawText(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw Text\n";
    displayParams(paramCount, parameters, color);
}
void drawImage(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command draw Image\n";
    displayParams(paramCount, parameters, color);
}
void setOrientation(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command set Orientation\n";
    displayParams(paramCount, parameters, color);
}
void getWidth(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command get Width\n";
}
void getHeight(int paramCount, INT16 parameters[], INT16 color[], string text) {
    cout << "Command get Height\n";
}
void getHelp(int paramCount, INT16 parameters[], INT16 color[], string text);
void clearConsole(int paramCount, INT16 parameters[], INT16 color[], string text) {
    system("CLS");
}
Command commands[] = {
    Command(clearDisplay, 0, 2, "clear", "display"),
    Command(drawPixel, 2, 2, "draw", "pixel"),
    Command(drawLine, 4, 2, "draw", "line"),
    Command(drawRect, 4, 2, "draw", "rectangle"),
    Command(fillRect, 4, 2, "fill", "rectangle"),
    Command(drawEllipse, 4, 2, "draw", "ellipse"),
    Command(fillEllipse, 4, 2, "fill", "ellipse"),
    Command(drawCircle, 3, 2, "draw", "circle"),
    Command(fillCircle, 3, 2, "fill", "circle"),
    Command(drawRoundRect, 5, 3, "draw", "rounded", "rectangle"),
    Command(fillRoundRect, 5, 3, "fill", "rounded", "rectangle"),
    Command(drawText, 4, 2, "draw", "text"),
    Command(drawImage, 4, 2, "draw", "image"),
    Command(setOrientation, 1, 2, "set", "orientation"),
    Command(getWidth, 0, 2, "get", "width"),
    Command(getHeight, 0, 2, "get", "height"),

    Command(getHelp, 0, 1, "help"),
    Command(clearConsole, 0, 1, "cls")
};
void getHelp(int paramCount, INT16 parameters[], INT16 color[], string text) {
    for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); i++)
    {
        for (size_t j = 0; j < commands[i].nameCount; j++)
        {
            cout << commands[i].name[j] << " ";
        }
        cout << "\n";
    }
}

SOCKET Socket;
sockaddr_in client_addr;

void sendToServer(const char * text) {
    sendto(Socket, text, strlen(text), 0, (sockaddr*)&client_addr, sizeof(client_addr));
}

const char * parseCommand(char buff[], int bsize) {
    
    if (bsize == 0)
        bsize = strlen(buff);
    string* wordArray = new string[99];
    int w = 0;

    INT16* params = new INT16[99];
    INT16* color = new INT16[99];
    int colorS = -1, colorE = -1;
    int colorC = 0;
    int paramsCount = 0;

    char n[] = { '\n', ' ', ',', '(', ')', ':'};
    for (size_t i = 0; i < bsize; i++)
    {
        bool o = false;
        for (size_t j = 0; j < sizeof(n) / sizeof(*n); j++)
        {
            if (n[j] == buff[i]) {
                o = true;
                w++;
                if (buff[i] == '(') {
                    colorS = w;
                }
                if (buff[i] == ')') {
                    colorE = w;
                }
                break;
            }
        }
        if (!o) {
            wordArray[w] += buff[i];
        }
    }
    for (int i = 0; i < w + 1; i++)
    {
        try
        {
            if (i >= colorS && i <= colorE) {
                if (stoi(wordArray[i]) > 255 || stoi(wordArray[i]) < 0) {
                    return "Exceeding limits!\n";
                }
                color[colorC] = stoi(wordArray[i]);
                colorC++;
            }
            else {
                if (stoi(wordArray[i]) > 100 || stoi(wordArray[i]) < 0) {
                    return "Exceeding limits!\n";
                }
                params[paramsCount] = stoi(wordArray[i]);
                paramsCount++;
            }
        }
        catch (const exception&)
        {
        }
    }
    for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); i++)
    {
        int t = 0;
        for (size_t n = 0; n < commands[i].nameCount; n++)
        {
            if (commands[i].name[n] == wordArray[n]) {
                t++;
            }
        }
        if (commands[i].nameCount == t) {
            if (paramsCount >= commands[i].reqParamNum) {
                    commands[i].f(paramsCount, params, color, wordArray[w]);
                return "Command Work!\n";
            }
            else {
                return "Need More Parameters!\n";
            }
        }
    }
    return "Command not found!\n";
}


int main(int argc, char* argv[])
{
    char buff[1024];
    if (WSAStartup(0x202, (WSADATA*)&buff[0]))
    {
        cout << "WSAStartup error: %d\n", WSAGetLastError();
        return -1;
    };

    Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket == INVALID_SOCKET)
    {
        cout << "Socket() error: %d\n", WSAGetLastError();
        WSACleanup();
        return -1;
    };
 
    sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(PORT);

    bind(Socket, (sockaddr*)&local_addr, sizeof(local_addr));

    while (1)
    {
        int client_addr_size = sizeof(client_addr);
        int bsize = recvfrom(Socket, &buff[0], sizeof(buff) - 1, 0, (sockaddr*)&client_addr, &client_addr_size);
        if (bsize == SOCKET_ERROR) {
            printf("recvfrom() error: %d\n", WSAGetLastError());
        }
        HOSTENT* hst;
        hst = gethostbyaddr((char*)&client_addr.sin_addr, 4, AF_INET);

        buff[bsize] = 0;

        const char * req = parseCommand(buff, bsize);
        sendToServer(req);


        printf("%s [%s:%d]: %s", (hst) ? hst->h_name : "Unknown host", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), &buff[0]);

    }
    return 0;
}