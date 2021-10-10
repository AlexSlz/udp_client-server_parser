#include "serverH.h"

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
    Command(getHeight, 0, 2, "get", "height")
};

string getCommandsName(int i) {
    string temp = "";
    for (size_t j = 0; j < commands[i].nameCount; j++)
    {
        temp += commands[i].name[j] + " ";
    }
    return temp;
}
int getCommandsLen() {
    return sizeof(commands) / sizeof(*commands);
}

const char* clearDisplay(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command clear\n";
}
const char* drawPixel(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    putpixel(parameters[0], parameters[1], COLOR(color[0], color[1], color[2]));
    return "Command draw Pixel\n";
}
const char* drawLine(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    setcolor(COLOR(color[0], color[1], color[2]));
    line(parameters[0], parameters[1], parameters[2], parameters[3]);
    return "Command draw Line\n";
}
const char* drawRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    setcolor(COLOR(color[0], color[1], color[2]));
    rectangle(parameters[0], parameters[1], parameters[2], parameters[3]);
    return "Command draw Rectangle\n";
}
const char* fillRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command fill Rectangle\n";
}
const char* drawEllipse(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command draw Ellipse\n";
}
const char* fillEllipse(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command fill Ellipse\n";
}
const char* drawCircle(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command draw Circle\n";
}
const char* fillCircle(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command fill Circle\n";
}
const char* drawRoundRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command draw rounded rectangle\n";
}
const char* fillRoundRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command fill rounded rectangle\n";
}
const char* drawText(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command draw Text\n";
}
const char* drawImage(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command draw Image\n";
}
const char* setOrientation(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command set Orientation\n";
}
const char* getWidth(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command get Width\n";
}
const char* getHeight(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command get Height\n";
}



const char* parseCommand(char buff[], int bsize) {
    if (bsize == 0)
        bsize = strlen(buff);
    string* wordArray = new string[99];
    int w = 0;

    INT16* params = new INT16[99];
    INT16* color = new INT16[99];
    int colorS = -1, colorE = -1;
    int colorC = 0;
    int paramsCount = 0;

    char n[] = { '\n', ' ', ',', '(', ')', ':' };
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
                if (stoi(wordArray[i]) > 280 || stoi(wordArray[i]) < 0) {
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
    for (size_t i = 0; i < getCommandsLen(); i++)
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
                return commands[i].f(commands, paramsCount, params, color, wordArray[w]);
            }
            else {
                return "Need More Parameters!\n";
            }
        }
    }
    return "Command not found!\n";
}
