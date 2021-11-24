#pragma once
#define PORT 7777 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#pragma comment ( lib, "ws2_32.lib" )
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include "graphics.h"
#include <vector>
using namespace std;

extern int height, width;

class Command {
public:
    const char* (*f) (Command[], int, INT16[], INT16[], std::string);
    std::string name[99];
    int nameCount = 0;
    int reqParamNum = 0;
    Command(const char* (*f_0)(Command[], int, INT16[], INT16[], std::string), int paramNum, int count, const char* text, ...) {
        const char** s = &text;
        for (size_t i = 0; i < count; i++, s++)
        {
            name[i] = (*s);
        }
        nameCount = count;
        reqParamNum = paramNum;
        f = f_0;

    }
};

class myObject {
public:
    int x = 0;
    int y = 0;
    int color;
    myObject(int _x, int _y, int _c) {
        x = _x;
        y = _y;
        color = _c;
    }
    void print() {
        setcolor(color);
        rectangle(x, y, x + 10, y + 10);
    }
    bool collide(myObject obj) {
        return ((x - 10 <= obj.x && x + 10 >= obj.x) && (y - 10 <= obj.y && y + 10 >= obj.y));
    }
    void getRandCords() {
        x = 30 + rand() % (((height - 100) + 1) - 30);
        y = 30 + rand() % (((width - 100) + 1) - 30);
    }
};

const char* clearDisplay(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawPixel(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawLine(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* fillRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawEllipse(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* fillEllipse(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawCircle(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* fillCircle(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawRoundRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* fillRoundRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawText(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* drawImage(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* setOrientation(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* getHeight(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* getWidth(Command commands[], int paramCount, INT16 parameters[], INT16 color[], std::string text);
const char* parseCommand(char buff[], int bsize);
const char* startSnake(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);
const char* createImgFile(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

const char* pinFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

const char* aruinoDrawPixFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);
const char* arduinoClear(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

const char* aruinoGameStartFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);
const char* aruinoGameStopFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

const char* snakeLeftFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);
const char* snakeRightFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);
const char* snakeUpFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);
const char* snakeDownFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

const char* AdrawChar(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);
const char* AdrawText(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

const char* animTextFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

const char* tempFunc(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text);

string StartServer();
string getCommandsName(int i);
int getCommandsLen();
