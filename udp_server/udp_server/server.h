#pragma once
#include <string>
#include "graphics.h"
using namespace std;
class Command {
public:
    void (*f) (int, INT16[], INT16[], std::string);
    std::string name[99];
    int nameCount = 0;
    int reqParamNum = 0;
    Command(void(*f_0)(int, INT16[], INT16[], std::string), int paramNum, int count, const char* text, ...) {
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
void clearDisplay(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawPixel(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawLine(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawRect(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void fillRect(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawEllipse(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void fillEllipse(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawCircle(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void fillCircle(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawRoundRect(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void fillRoundRect(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawText(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void drawImage(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void setOrientation(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void getHeight(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void getWidth(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void getHelp(int paramCount, INT16 parameters[], INT16 color[], std::string text);
void clearConsole(int paramCount, INT16 parameters[], INT16 color[], std::string text);
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