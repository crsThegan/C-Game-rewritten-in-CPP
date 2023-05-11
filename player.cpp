#include "player.hpp"
#include "board.hpp"
#include "bullet.hpp"

#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>

const int INITIAL_AMMO = 10;
const int INITIAL_HEALTH = 100;

std::vector<Player> players;

// Entity class getters
int Entity::getX() {
    return x;
}

int Entity::getY() {
    return y;
}

Direction Entity::getDir() {
    return dir;
}

// Player class methods
Player::Player(int x, int y, Direction dir) {
    this->x = x;
    this->y = y;
    this->dir = dir;
    this->ammo = INITIAL_AMMO;
    this->health = INITIAL_HEALTH;
}

void Player::shoot() {
    Bullet::create(this);
}

void Player::actionCheck(element (*board)[HEIGHT]) {
    if (_kbhit()) {
        switch(_getch()) {
        case RIGHT_KEY:
            dir = Direction::right;
            moveOnBoard(board);
            break;
        case LEFT_KEY:
            dir = Direction::left;
            moveOnBoard(board);
            break;
        case UP_KEY:
            dir = Direction::up;
            moveOnBoard(board);
            break;
        case DOWN_KEY:
            dir = Direction::down;
            moveOnBoard(board);
            break;
        case SHOOT_KEY:
            shoot();
            break;
        }
    }
}

void Player::moveOnBoard(element (*board)[HEIGHT]) {
    switch (dir) {
    case Direction::right:
        if (board[x + 1][y] == BLANK_SPACE) x++;
        break;
    case Direction::left:
        if (board[x - 1][y] == BLANK_SPACE) x--;
        break;
    case Direction::up:
        if (board[x][y + 1] == BLANK_SPACE) y++;
        break;
    case Direction::down:
        if (board[x][y - 1] == BLANK_SPACE) y--;
        break;
    }
}

void Player::actionCheckAll(element (*board)[HEIGHT]) {
    while (1) {
        for (auto &player: players) player.actionCheck(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(GAME_TICK * 2));
    }
}