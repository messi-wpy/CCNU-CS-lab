#include <iostream>

using namespace std;

typedef struct p {
    int x;
    int y;
} point;
static point defaultPoint[2];

bool checkSlant_1(char position[16][16], int x, int y, int flag, point *p = defaultPoint);

bool checkSlant_2(char position[16][16], int x, int y, int flag, point *p = defaultPoint);

bool checkHorizontal(char position[16][16], int x, int y, int flag, point *p = defaultPoint);

bool checkVertical(char position[16][16], int x, int y, int flag, point *p = defaultPoint);

bool isSuccess(char position[16][16], int x, int y, int flag);

void printBoard(char position[16][16]);

bool isBound(point p);

bool isBound(int x, int y);

bool findNext(point p, char a[16][16], point *nullLocation, int *length);

void input(char(*a)[16], point *p);

bool checkfull(char chessboard[16][16]);


//水平方向检查
bool findHorizontal(char position[16][16], int x, int y, int flag, point *p);

bool findSlant_1(char position[16][16], int x, int y, int flag, point *p);

bool findSlant_2(char position[16][16], int x, int y, int flag, point *p);

//垂直方向检查
bool findVertical(char position[16][16], int x, int y, int flag, point *p);

void printBoard(char position[16][16]) {
    system("clear");
    printf("     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
    for (int i = 1; i <= 15; i++) {
        printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
        printf("%3d|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|%3c|\n", i, position[i][1], position[i][2],
               position[i][3], position[i][4], position[i][5], position[i][6], position[i][7], position[i][8],
               position[i][9], position[i][10], position[i][11], position[i][12], position[i][13], position[i][14],
               position[i][15]);
    }
    printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
}

bool computerAttack(int length, point *nullLocations, char(*a)[16], int flag, point *computer) {
    for (int j = 0; j < length; j++) {
        a[nullLocations[j].x][nullLocations[j].y] = '*';
        if (isSuccess(a, nullLocations[j].x, nullLocations[j].y, flag)) {
            computer->x = nullLocations[j].x;
            computer->y = nullLocations[j].y;
            return true;
        } else
            a[nullLocations[j].x][nullLocations[j].y] = ' ';
    }
    return false;


}

bool computerDefend(int len, char(*a)[16], const point *human, point *points, point *computer, int flag) {
    point useless[8];
    int temp = 0;

    for (int k = len - 1; k >= 0; --k) {
        if (checkHorizontal(a, human[k].x, human[k].y, flag, points) ||
            checkSlant_1(a, human[k].x, human[k].y, flag, points) ||
            checkSlant_2(a, human[k].x, human[k].y, flag, points) ||
            checkVertical(a, human[k].x, human[k].y, flag, points)) {
            if (a[points[0].x][points[0].y] == ' ') {
                if (a[points[1].x][points[1].y] == ' ') {
                    if (findNext(points[0], a, useless, &temp)) {
                        a[points[0].x][points[0].y] = '*';
                        computer->x = points[0].x;
                        computer->y = points[0].y;
                        return true;
                    } else {
                        a[points[1].x][points[1].y] = '*';
                        computer->x = points[1].x;
                        computer->y = points[1].y;
                        return true;
                    }
                } else {
                    a[points[0].x][points[0].y] = '*';
                    computer->x = points[0].x;
                    computer->y = points[0].y;
                    return true;
                }
            } else if (a[points[1].x][points[1].y] == ' ') {
                a[points[1].x][points[1].y] = '*';
                computer->x = points[1].x;
                computer->y = points[1].y;
                return true;
            } else {
                continue;
            }
        }
    }

    for (int k = len - 1; k >= 0; --k) {
        if (findHorizontal(a, human[k].x, human[k].y, flag, points) ||
            findSlant_1(a, human[k].x, human[k].y, flag, points) ||
            findSlant_2(a, human[k].x, human[k].y, flag, points) ||
            findVertical(a, human[k].x, human[k].y, flag, points)) {
            if (a[points[0].x][points[0].y] == ' ') {
                if (a[points[1].x][points[1].y] == ' ') {
                    if (findNext(points[0], a, useless, &temp)) {
                        a[points[0].x][points[0].y] = '*';
                        computer->x = points[0].x;
                        computer->y = points[0].y;
                        return true;
                    } else {
                        a[points[1].x][points[1].y] = '*';
                        computer->x = points[1].x;
                        computer->y = points[1].y;
                        return true;
                    }
                } else {
                    a[points[0].x][points[0].y] = '*';
                    computer->x = points[0].x;
                    computer->y = points[0].y;
                    return true;
                }
            } else if (a[points[1].x][points[1].y] == ' ') {
                a[points[1].x][points[1].y] = '*';
                computer->x = points[1].x;
                computer->y = points[1].y;
                return true;
            } else {
                continue;
            }
        }
    }
    return false;

}

//计算出电脑的下一步
void computerRun(point *human, int len, char(*a)[16], point *computer) {
    point points[2];
    point nullLocations[8] = {{0, 0}};
    int length = 0;

    findNext(*computer, a, nullLocations, &length);
    //computer 5
    if (computerAttack(length, nullLocations, a, 5, computer)) return;

    for (int l = 4; l >= 2; l--) {

        if (computerDefend(len, a, human, points, computer, l)) return;
        if (computerAttack(length, nullLocations, a, l, computer))return;
    }


}


//判断在棋盘边界内
bool isBound(point p) {
    return p.x > 0 && p.x < 16 && p.y > 0 && p.y < 16;
}

bool isBound(int x, int y) {
    return x > 0 && x < 16 && y > 0 && y < 16;
}

bool findNext(point p, char a[16][16], point *nullLocation, int *length) {
    int x = p.x - 1;
    int y = p.y - 1;
    int index = 0;
    bool isBetter = false;
    for (int i = 0; i < 3; i++) {
        if (isBound(x + i, y)) {
            if (a[x + i][y] == ' ') {
                nullLocation[index].x = x + i;
                nullLocation[index].y = y;
                index++;
            }
            if (a[x + i][y] == '*')
                isBetter = true;
        }
    }
    x += 2;
    for (int i = 1; i < 3; i++) {
        if (isBound(x, y + i)) {
            if (a[x][y + i] == ' ') {
                nullLocation[index].x = x;
                nullLocation[index].y = y + i;
                index++;
            }
            if (a[x][y + i] == '*')
                isBetter = true;
        }
    }
    y += 2;
    for (int i = 1; i < 3; i++) {
        if (isBound(x - i, y)) {
            if (a[x - i][y] == ' ') {
                nullLocation[index].x = x - i;
                nullLocation[index].y = y;
                index++;
            }
            if (a[x - i][y] == '*')
                isBetter = true;
        }
    }
    x -= 2;
    for (int i = 1; i < 2; i++) {
        if (isBound(x, y - i)) {
            if (a[x][y - i] == ' ') {
                nullLocation[index].x = x;
                nullLocation[index].y = y - i;
                index++;
            }
            if (a[x][y - i] == '*')
                isBetter = true;
        }
    }
    *length = index;
    return isBetter;
}

void input(char(*a)[16], point *p) {
    int x, y;
    cin >> x >> y;
    if (a[x][y] == ' ') {
        a[x][y] = 'o';
        p->x = x;
        p->y = y;
    } else {
        cout << "Wrong! There is alreadly a point here. Please enter another one.";
        return input(a, p);
    }

}

bool findSlant_1(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempX, tempY;
    //斜向检查
    tempX = x;
    tempY = y;
    while ((tempX - 1) > 0 && (tempY - 1) > 0 && (position[tempX - 1][tempY - 1] == position[tempX][tempY] ||
                                                  ((tempX - 2) > 0 && (tempY - 2) > 0 &&
                                                   position[tempX - 2][tempY - 2] == position[tempX][tempY] &&
                                                   position[tempX - 1][tempY - 1] != '*'))) {
        num++;
        tempX--;
        tempY--;
    }
    p[0].x = tempX - 1;
    p[0].y = tempY - 1;
    tempX = x;
    tempY = y;
    while ((tempX + 1) < 16 && (tempY + 1) < 16 && (position[tempX + 1][tempY + 1] == position[tempX][tempY] ||
                                                    ((tempX + 2) < 16 && (tempY + 2) < 16 &&
                                                     position[tempX + 2][tempY + 2] == position[tempX][tempY] &&
                                                     position[tempX + 1][tempY + 1] != '*'))) {
        num++;
        tempX++;
        tempY++;
    }
    p[1].x = tempX + 1;
    p[1].y = tempY + 1;
    if ((position[p[0].x][p[0].y] == '*' || position[p[1].x][p[1].y] == '*'))
        return false;
    return num >= flag;
}

bool findSlant_2(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempX, tempY;
    //斜向检查
    tempX = x;
    tempY = y;
    while ((tempX + 1) < 16 && (tempY - 1) > 0 && (position[tempX + 1][tempY - 1] == position[tempX][tempY] ||
                                                   ((tempX + 2) < 16 && (tempY - 2) > 0 &&
                                                    position[tempX + 2][tempY - 2] == position[tempX][tempY] &&
                                                    position[tempX + 1][tempY - 1] != '*'))) {
        num++;
        tempX++;
        tempY--;
    }
    p[0].x = tempX + 1;
    p[0].y = tempY - 1;
    tempX = x;
    tempY = y;
    while ((tempX - 1) > 0 && (tempY + 1) < 16 && (position[tempX - 1][tempY + 1] == position[tempX][tempY] ||
                                                   ((tempX - 2) > 0 && (tempY + 2) < 16 &&
                                                    position[tempX - 2][tempY + 2] == position[tempX][tempY] &&
                                                    position[tempX - 1][tempY + 1] != '*'))) {
        num++;
        tempX--;
        tempY++;
    }
    p[1].x = tempX - 1;
    p[1].y = tempY + 1;
    if ((position[p[0].x][p[0].y] == '*' || position[p[1].x][p[1].y] == '*') )
        return false;
    return num >= flag;
}

//水平方向检查
bool findHorizontal(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempX;
    tempX = x;
    while ((tempX - 1) > 0 && (position[tempX - 1][y] == position[tempX][y] ||
                               ((tempX - 2) > 0 && position[tempX - 2][y] == position[tempX][y] &&
                                position[tempX - 1][y] != '*'))) {
        num++;
        tempX--;
    }
    p[0].x = tempX - 1;
    p[0].y = y;
    tempX = x;
    while ((tempX + 1) < 16 && (position[tempX + 1][y] == position[tempX][y] ||
                                ((tempX + 2) < 16 && position[tempX + 2][y] == position[tempX][y] &&
                                 position[tempX + 1][y] != '*'))) {
        num++;
        tempX++;
    }
    p[1].x = tempX + 1;
    p[1].y = y;
    if ((position[p[0].x][p[0].y] == '*' || position[p[1].x][p[1].y] == '*'))
        return false;
    return num >= flag;

}

//垂直方向检查
bool findVertical(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempY = y;
    while ((tempY - 1) > 0 && (position[x][tempY - 1] == position[x][tempY] ||
                               ((tempY - 2) > 0 && position[x][tempY - 2] == position[x][tempY] &&
                                position[x][tempY - 1] != '*'))) {
        num++;
        tempY--;
    }
    p[0].x = x;
    p[0].y = tempY - 1;
    tempY = y;
    while ((tempY + 1) < 16 && (position[x][tempY + 1] == position[x][tempY] ||
                                ((tempY + 2) < 16 && position[x][tempY + 2] == position[x][tempY] &&
                                 position[x][tempY + 1] != '*'))) {
        num++;
        tempY++;
    }
    p[1].x = x;
    p[1].y = tempY + 1;
    if ((position[p[0].x][p[0].y] == '*' || position[p[1].x][p[1].y] == '*') )
        return false;
    return num >= flag;
}

//斜向检查
bool checkSlant_1(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempX, tempY;
    //斜向检查
    tempX = x;
    tempY = y;
    while ((tempX - 1) > 0 && (tempY - 1) > 0 && position[tempX - 1][tempY - 1] == position[tempX][tempY]) {
        num++;
        tempX--;
        tempY--;
    }
    p[0].x = tempX - 1;
    p[0].y = tempY - 1;
    tempX = x;
    tempY = y;
    while ((tempX + 1) < 16 && (tempY + 1) < 160 && position[tempX + 1][tempY + 1] == position[tempX][tempY]) {
        num++;
        tempX++;
        tempY++;
    }
    p[1].x = tempX + 1;
    p[1].y = tempY + 1;
    return num >= flag;
}

bool checkSlant_2(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempX, tempY;
    //斜向检查
    tempX = x;
    tempY = y;
    while ((tempX + 1) < 16 && (tempY - 1) > 0 && position[tempX + 1][tempY - 1] == position[tempX][tempY]) {
        num++;
        tempX++;
        tempY--;
    }
    p[0].x = tempX + 1;
    p[0].y = tempY - 1;
    tempX = x;
    tempY = y;
    while ((tempX - 1) > 0 && (tempY + 1) < 16 && position[tempX - 1][tempY + 1] == position[tempX][tempY]) {
        num++;
        tempX--;
        tempY++;
    }
    p[1].x = tempX - 1;
    p[1].y = tempY + 1;
    return num >= flag;
}

//水平方向检查
bool checkHorizontal(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempX;
    tempX = x;
    while ((tempX - 1) > 0 && position[tempX - 1][y] == position[tempX][y]) {
        num++;
        tempX--;
    }
    p[0].x = tempX - 1;
    p[0].y = y;
    tempX = x;
    while ((tempX + 1) < 16 && position[tempX + 1][y] == position[tempX][y]) {
        num++;
        tempX++;
    }
    p[1].x = tempX + 1;
    p[1].y = y;
    return num >= flag;

}

//垂直方向检查
bool checkVertical(char position[16][16], int x, int y, int flag, point *p) {
    int num = 1;
    int tempY = y;
    while ((tempY - 1) > 0 && position[x][tempY - 1] == position[x][tempY]) {
        num++;
        tempY--;
    }
    p[0].x = x;
    p[0].y = tempY - 1;
    tempY = y;
    while ((tempY + 1) < 16 && position[x][tempY + 1] == position[x][tempY]) {
        num++;
        tempY++;
    }
    p[1].x = x;
    p[1].y = tempY + 1;
    return num >= flag ? true : false;
}

bool isSuccess(char position[16][16], int x, int y, int flag = 5) {
    return checkSlant_1(position, x, y, flag) || checkSlant_2(position, x, y, flag) ||
           checkHorizontal(position, x, y, flag) || checkVertical(position, x, y, flag);
}

bool checkfull(char chessboard[16][16]) {
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 15; j++)
            if (chessboard[i][j] == ' ')
                return false;
    return true;
}


int main() {

    char chessboard[16][16];
    point humanLast[5];
    point computerLast;
    int index = 1;
    int len = 1;
    //初始化
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 15; j++)
            chessboard[i][j] = ' ';
    printBoard(chessboard);
    cout << "* represent computer,o represent you." << endl;
    cout << "Start!Please enter start point (x,y)：　" << endl;
    input(chessboard, &humanLast[0]);
    computerLast.x = humanLast[0].x - 1;
    computerLast.y = humanLast[0].y;
    chessboard[computerLast.x][computerLast.y] = '*';
    printBoard(chessboard);
    while (!checkfull(chessboard)) {
        cout << "Please enter next point: ";
        input(chessboard, &humanLast[index]);
        printBoard(chessboard);
        if (isSuccess(chessboard, humanLast[index].x, humanLast[index].y, 5)) {
            cout << "Congratulation! You win!" << endl;
            break;
        }
        index++;
        if (len < 5) len = index;

        computerRun(humanLast, len, chessboard, &computerLast);
        printBoard(chessboard);
        if (isSuccess(chessboard, computerLast.x, computerLast.y, 5)) {
            cout << "You failed! computer win!" << endl;
            break;
        }
        if (index == 5) index = 0;
    }

    return 0;
}
