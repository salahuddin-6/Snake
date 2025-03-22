#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;
bool gameover;
int width = 20;
int height = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100]; // arrays for tail
int nTail;
char dir; // direction of snake 


void Setup() {
    srand(time(0)); // to display fruit and random places
    gameover = false;
    dir = 'S';
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}


void Display() {
    system("cls");
    cout << "Welcome to the Snake Game" << endl;
    cout << "Avoid hitting the walls or your own tail" << endl;
    cout << "Controls:\nW for Up\nA for Left\nS for Down\nD for Right\nX to end" << endl;
    for (int i = 0; i < width + 2; i++) {
        cout << "-";
    }
    cout << endl;//upperline

    //Both walls
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "|"; // left wall
            }
            if (i == y && j == x) { 
                cout << "O"; // snake head
            }
            else if (i == fruity && j == fruitx) {
                cout << "\u2022"; // display fruit
            }

            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o"; // tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // no tail 
            }
            if (j == width - 1)
                cout << "|"; // right wall
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-"; // bottom
    cout << endl;
    cout << "Score:" << score << endl;

}


void Input() {
    if (_kbhit()) { // check if any button is pressed
        switch (_getch()) { // check which button is pressed
        case 'a':
            dir = 'L';
            break;
        case 'd':
            dir = 'R';
            break;
        case 'w':
            dir = 'U';
            break;
        case 's':
            dir = 'D';
            break;
        case 'x':
            gameover = true;
            break;
        default:;
        }
    }
}


void Rules() {
    int prevx = tailx[0]; // tailx[0] is head of snake, prevx is temporary x coordinate of head position
    int prevy = taily[0]; // same as above
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch (dir) {
    case 'U':
        y--; // move the snake up (y--) because 0 is above 1
        break;
    case 'D':
        y++;
        break;
    case 'R':
        x++;
        break;
    case 'L':
        x--;
        break;
    default:
        break;
    }

    if (x > width || x < 0 || y > height || y < 0) { // check if snake hits boundary
        gameover = true;
    }
    for (int i = 0; i < nTail; i++) { // check if tail hits its own tail
        if (tailx[i] == x && taily[i] == y) {
            gameover = true;
        }
    }
    if (x == fruitx && y == fruity) { // if fruit is eaten
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail++;
        score += 10;
    }
}


int main() {
    Setup();
    while (!gameover) {
        Display();
        Input();
        Rules();
        Sleep(200); // to control speed
    }
    cout << "GAME OVER";
    return 0;
}