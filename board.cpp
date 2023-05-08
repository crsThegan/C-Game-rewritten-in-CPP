#include "board.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "cannon.hpp"

#include <stdio.h>
#include <thread>
#include <chrono>
#include <vector>

element board[WIDTH][HEIGHT];

std::vector<std::thread> threads;
const int GAME_TICK = 40;

int main() {
    setup(board);

    while (true) {
        changeBoard(board);
        drawBoard(board);

        std::this_thread::sleep_for(std::chrono::milliseconds(GAME_TICK));
        system("cls");
    }

    terminate();
    system("pause");
    return 0;    
}

void setup(element (*board)[HEIGHT]) {
    threads.push_back(std::thread(Bullet::flyAll, board));    // bullet thread
    threads.push_back(std::thread(Cannon::shootAll, board));  // cannon thread
    threads.push_back(std::thread(player.actionCheck, board));// player thread

    for (int i = 0; i < 5; i++) Cannon::create(WIDTH, HEIGHT / 2 + i, LEFT);

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) board[x][y] = WALL;
            else board[x][y] = BLANK_SPACE;
        }
    }
}

void changeBoard(element (*board)[HEIGHT]) {
    for (int x = 1; x < WIDTH - 1; x++) {
        for (int y = 1; y < HEIGHT - 1; y++) {
            board[x][y] = BLANK_SPACE;
            if (x == player.x && y == player.y) {
                switch (player.dir) {
                case RIGHT:
                    board[x][y] = PLAYER_RIGHT;
                    break;
                case LEFT:
                    board[x][y] = PLAYER_LEFT;
                    break;
                case UP:
                    board[x][y] = PLAYER_UP;
                    break;
                case DOWN:
                    board[x][y] = PLAYER_DOWN;
                    break;
                }
            }
            else if (board[x][y] == BLANK_SPACE) {
                for (int i = 0; i < cannons.size(); i++) {
                    if (x == cannons[i].x && y == cannons[i].y) {
                        if (cannons[i].dir == UP || cannons[i].dir == DOWN) board[x][y] = CANNON_VERTICAL;
                        else board[x][y] = CANNON_HORIZONTAL;
                    }
                }
            }
            else if (board[x][y] == BLANK_SPACE) {
                for (int i = 0; i < bullets.size(); i++) {
                    if (x == bullets[i].x && y == bullets[i].y) board[x][y] = BULLET;
                }
            }
        }
    }
}

void drawBoard(element (*board)[HEIGHT]) {
    char boardStr[HEIGHT][WIDTH + 1] = {0};
    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) boardStr[y][x] = board[x][y];
        puts(boardStr[y]);
    }
}

void terminate() {
    for (auto thread: threads) thread.join();
}