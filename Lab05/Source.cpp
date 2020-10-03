#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void erase_ship(int x, int y)
{
    gotoxy(x, y);
    setcolor(0, 0);
    printf("     ");
}
void erase_bullet(int x, int y)
{
    gotoxy(x, y);
    setcolor(0, 0);
    printf(" ");
}
void draw_bullet(int x, int y)
{

    setcolor(4, 6);
    gotoxy(x, y); printf("|");
}
void draw_ship(int x, int y)
{

    setcolor(2, 4);
    gotoxy(x, y); printf("<-0->");
}
int main()
{
    setcursor(0);
    int stateship = 0;//0 == stop , 1 == left , 2== right
    int i, state = 0;
    int bullet = 0;
    int shoot[5] = { 0 }, ax[5] = { 0 }, ay[5] = { 0 };

    char ch = '.';
    int x = 38, y = 20;
    int x1 = 38, y1 = 20;
    draw_ship(x, y);
    do {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'a') { stateship = 1; }
            if (ch == 'd') { stateship = 2; }
            if (ch == 's') { stateship = 0; }
            if (ch == ' ')
            {
                for (i = 0; i < 5; i++) {
                    if (shoot[i] == 0) {
                        shoot[i] = 1;
                        ax[i] = x + 2;
                        ay[i] = y - 1;
                        break;
                    }
                }
            }
            fflush(stdin);
        }
        if (stateship == 1 && x > 0) { erase_ship(x, y); draw_ship(--x, y); }
        if (stateship == 2 && x < 75) { erase_ship(x, y); draw_ship(++x, y); }
        if (stateship == 0 && x < 75) { erase_ship(x, y); draw_ship(x, y); }
        for (i = 0; i < 5; i++) {
            if (shoot[i] == 1 && ay[i] > 0) {
                erase_bullet(ax[i], ay[i]); draw_bullet(ax[i], --ay[i]);
            }
            if (shoot[i] == 1 && ay[i] == 0) {
                erase_bullet(ax[i], ay[i]);
                shoot[i] = 0;
            }

        }
        Sleep(100);
    } while (ch != 'x');




    return 0;
}