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

string StartServer();
string getCommandsName(int i);
int getCommandsLen();
/*
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
*/