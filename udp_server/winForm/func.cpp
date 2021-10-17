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
    Command(drawImage, 4, 2, "draw", "image"), // 4
    Command(setOrientation, 1, 2, "set", "orientation"),
    Command(getWidth, 0, 2, "get", "width"),
    Command(getHeight, 0, 2, "get", "height"),
    Command(startSnake, 0, 1, "snake"),
    Command(createImgFile, 0, 1, "file")
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

vector< myObject > snakeBody = {
myObject(30, 30, COLOR(0, 255 ,0))
};
myObject apple = {
    myObject(height / 2, width / 2, COLOR(255, 255 ,0))
};
vector< myObject > enemy = {
};
void SpawnEnemy() {
    enemy.push_back(myObject(-30, -30, COLOR(255, 0, 0)));
    enemy[enemy.size() - 1].getRandCords();
}
int snakeDir = 1;
void inputSnake() {
    if (GetAsyncKeyState(VK_LEFT) && snakeDir != 1) {
        //snakeBody[0].x -= 15;
        snakeDir = 0;
    }
    if (GetAsyncKeyState(VK_RIGHT) && snakeDir != 0) {
        //snakeBody[0].x += 15;
        snakeDir = 1;
    }
    if (GetAsyncKeyState(VK_UP) && snakeDir != 3) {
        //snakeBody[0].y -= 15;
        snakeDir = 2;
    }
    if (GetAsyncKeyState(VK_DOWN) && snakeDir != 2) {
        //snakeBody[0].y += 15;
        snakeDir = 3;
    }

    if (snakeDir == 0) snakeBody[0].x -= 15;
    else if (snakeDir == 1) snakeBody[0].x += 15;
    else if (snakeDir == 2) snakeBody[0].y -= 15;
    else if (snakeDir == 3) snakeBody[0].y += 15;
}
void moveSnakeBody() {
    for (size_t i = snakeBody.size() - 1; i > 0; i--)
    {
        snakeBody[i].x = snakeBody[i - 1].x;
        snakeBody[i].y = snakeBody[i - 1].y;
    }
}
void snakeLimits() {
    if (snakeBody[0].x >= height - 10) {
        snakeBody[0].x = 1;
    }
    if (snakeBody[0].x <= 0) {
        snakeBody[0].x = height - 10;
    }
    if (snakeBody[0].y >= width - 10) {
        snakeBody[0].y = 1;
    }
    if (snakeBody[0].y <= 0) {
        snakeBody[0].y = width - 10;
    }
    /*
    for (size_t i = 1; i < snakeBody.size(); i++)
    {
        if (snakeBody[i].collide(snakeBody[0])) {
            snakeBody.clear();
        }
    }
    */
}
int score, gameSpeed, enemyDelay;
void loadSnakeGame() {
    snakeBody.clear();
    snakeBody.push_back(myObject(30, 30, COLOR(0, 255, 0)));
    apple = myObject(height / 2, width / 2, COLOR(255, 255, 0));
    enemy.clear();
    enemyDelay = 0;
    score = 0;
    gameSpeed = 100;
    snakeDir = 1;
}
const char* startSnake(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    loadSnakeGame();
    while (1) {
        cleardevice();
        char dataText[1024];
        sprintf(dataText, "Score > %d\n", score);
        setcolor(COLOR(255, 255, 0));
        outtextxy(10, 10, dataText);
        if (snakeBody.size() != 0) {
            moveSnakeBody();
            inputSnake();
            snakeLimits();
            if (snakeBody.size() != 0 && snakeBody[0].collide(apple)) {
                snakeBody.push_back(myObject(-30, -30, COLOR(0, 100, 0)));
                apple.getRandCords();
                score++;
                if (gameSpeed >= 50)
                    gameSpeed--;
            }
            for (size_t i = 0; i < enemy.size(); i++)
            {
                if (enemy[i].collide(snakeBody[0])) {
                    if (snakeBody.size() <= 3) {
                        snakeBody.clear();
                    }
                    for (size_t i = 0; i < snakeBody.size() / 1.5f; i++)
                    {
                        snakeBody.pop_back();
                    }
                    enemy.erase(enemy.begin() + i);
                }
            }
            if (score >= enemyDelay) {
                SpawnEnemy();
                enemyDelay += 3;
            }
            //Print
            for (size_t i = 0; i < snakeBody.size(); i++)
            {
                snakeBody[i].print();
            }
            apple.print();
            for (size_t i = 0; i < enemy.size(); i++)
            {
                enemy[i].print();
            }
        }
        else {
            string text = "you die :(\n your score > %d";
            sprintf(dataText, "You Die :( Your Score > %d", score);
            setcolor(COLOR(255, 255, 0));
            outtextxy(10, 10, dataText);
        }
        delay(gameSpeed);
        if (GetAsyncKeyState(0x52)) {
            loadSnakeGame();
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return "Game ended.\n";
        }
    }
    return "Game error!\n";
}

const char* createImgFile(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    writeimagefile("image.bmp");
    return "Command CreateFile\n";
}

const char* clearDisplay(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    cleardevice();
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
    rectangle(parameters[0], parameters[1], parameters[2] + parameters[0], parameters[3] + parameters[1]);
    return "Command draw Rectangle\n";
}
const char* fillRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    setcolor(COLOR(color[0], color[1], color[2]));
    setfillstyle(1, COLOR(color[0], color[1], color[2]));
    bar(parameters[0], parameters[1], parameters[2] + parameters[0], parameters[3] + parameters[1]);
    return "Command fill Rectangle\n";
}
const char* drawEllipse(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    setcolor(COLOR(color[0], color[1], color[2]));
    ellipse(parameters[0], parameters[1], 10, 10, parameters[2], parameters[3]);
    return "Command draw Ellipse\n";
}
const char* fillEllipse(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    setcolor(COLOR(color[0], color[1], color[2]));
    setfillstyle(1, COLOR(color[0], color[1], color[2]));
    fillellipse(parameters[0], parameters[1], parameters[2], parameters[3]);
    return "Command fill Ellipse\n";
}
const char* drawCircle(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    setcolor(COLOR(color[0], color[1], color[2]));
    circle(parameters[0], parameters[1], parameters[2]);
    return "Command draw Circle\n";
}
const char* fillCircle(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    setcolor(COLOR(color[0], color[1], color[2]));
    setfillstyle(1, COLOR(color[0], color[1], color[2]));
    fillellipse(parameters[0], parameters[1], parameters[2], parameters[2]);
    return "Command fill Circle\n";
}
const char* drawRoundRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    int x = parameters[0], y = parameters[1], w = parameters[2], h = parameters[3], r = parameters[4];
    setcolor(COLOR(255, 0, 0));
    arc(x, y, 180, 90, r);
    arc(x + w - r, y, 270, 90, r);
    arc(x + w - r, y + h - r, 0, 90, r);
    arc(x, y + h - r, 90, 90, r);
    return "Command draw rounded rectangle\n";
}
const char* fillRoundRect(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    return "Command fill rounded rectangle\n";
}
const char* drawText(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    settextstyle(parameters[2], 0, parameters[3]);
    char* cstr = &text[0];
    outtextxy(parameters[0], parameters[1], cstr);
    return "Command draw Text\n";
}
const char* drawImage(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    char* chText = &text[0];
    readimagefile(chText, parameters[0], parameters[1], parameters[2], parameters[3]);
    return "Command draw Image\n";
}
const char* setOrientation(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    settextstyle(0, parameters[0], 0);
    return "Command set Orientation\n";
}
const char* getWidth(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    char temp[1024];
    sprintf(temp, "Width > %d\n", getwindowwidth());
    return temp;
}
const char* getHeight(Command commands[], int paramCount, INT16 parameters[], INT16 color[], string text) {
    char temp[1024];
    sprintf(temp, "Height > %d\n", getwindowheight());
    return temp;
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
                if (stoi(wordArray[i]) > 300 || stoi(wordArray[i]) < 0) {
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
                return commands[i].f(commands, paramsCount, params, color, wordArray[w - 1]);
            }
            else {
                return "Need More Parameters!\n";
            }
        }
    }
    return "Command not found!\n";
}
