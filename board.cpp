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

char tempbuf[256] = {0};

int main() {
    setup(board);

    while (true) {
        changeBoard(board);
        drawBoard(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(GAME_TICK));
        system("cls");
    }

    terminateProgram();
    system("pause");
    return 0;    
}

void setup(element (*board)[HEIGHT]) {
    players.push_back(Player(1, 1, Direction::right));             // new player

    threads.push_back(std::thread(Bullet::flyAll, board));         // bullet thread
    threads.push_back(std::thread(Cannon::fireAll, board));        // cannon thread
    threads.push_back(std::thread(Player::actionCheckAll, board)); // player thread

    for (int i = 0; i < 6; i++) Cannon::create(WIDTH - 2, HEIGHT / 2 + i, Direction::left);

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
            for (auto &player: players) {
                if (x == player.getX() && y == player.getY()) {
                    switch (player.getDir()) {
                    case Direction::right:
                        board[x][y] = PLAYER_RIGHT;
                        break;
                    case Direction::left:
                        board[x][y] = PLAYER_LEFT;
                        break;
                    case Direction::up:
                        board[x][y] = PLAYER_UP;
                        break;
                    case Direction::down:
                        board[x][y] = PLAYER_DOWN;
                        break;
                    }
                }
            }
            if (board[x][y] == BLANK_SPACE) {
                for (auto &cannon: cannons) {
                    if (x == cannon.getX() && y == cannon.getY()) {
                        if (cannon.getDir() == Direction::up || cannon.getDir() == Direction::down) board[x][y] = CANNON_VERTICAL;
                        else board[x][y] = CANNON_HORIZONTAL;
                    }
                }
            }
            for (auto *bullet: bullets) {
                if (x == bullet->getX() && y == bullet->getY()) board[x][y] = BULLET;
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

    if (bullets.size() > 0) sprintf(tempbuf, "%d %d %d", bullets.size(), bullets[0]->getX(), bullets[0]->getY());
    puts(tempbuf);
}

void terminateProgram() {
    for (std::thread &thread: threads) thread.join();
}