#include "bullet.hpp"
#include "player.hpp"
#include "board.hpp"
#include "cannon.hpp"

#include <vector>
#include <mutex>
#include <algorithm>

const int BULLET_RANGE = 5;

std::vector<Bullet> bullets;
std::vector<Bullet *> bulletsToDestroy;

std::mutex bulletMutex; // needed to make sure that the 'bullets' vector is not being modified by
                        // multiple threads simultaneously

Bullet::Bullet(Entity *shooter) {
    x = shooter->getX();
    y = shooter->getY();
    dir = shooter->getDir();
    distLeft = BULLET_RANGE;
}

void Bullet::fly(element (*board)[HEIGHT]) {
    switch (dir) {
    case Direction::right:
        if (board[x + 1][y] == BLANK_SPACE && distLeft > 0) x++;
        else bulletsToDestroy.push_back(this);
        break;
    case Direction::left:
        if (board[x - 1][y] == BLANK_SPACE && distLeft > 0) x--;
        else bulletsToDestroy.push_back(this);
        break;
    case Direction::up:
        if (board[x][y + 1] == BLANK_SPACE && distLeft > 0) y++;
        else bulletsToDestroy.push_back(this);
        break;
    case Direction::down:
        if (board[x][y - 1] == BLANK_SPACE && distLeft > 0) y--;
        else bulletsToDestroy.push_back(this);
        break;
    }
}

void Bullet::flyAll(element (*board)[HEIGHT]) {
    std::lock_guard<std::mutex> lock(bulletMutex);

    while (true) {
        for (Bullet *bullet: bulletsToDestroy) bullets.erase(std::remove(bullets.begin(), bullets.end(), *bullet));
        for (Bullet &bullet: bullets) {
            bullet.fly(board);
            --bullet.distLeft;
        }
    }
}

void Bullet::create(Entity *shooter) {              // may be invoked by multiple threads
    std::lock_guard<std::mutex> lock(bulletMutex);

    bullets.push_back(Bullet(shooter));
}

bool Bullet::operator==(const Bullet &right) {
    return x == right.x && y == right.y &&
           dir == right.dir &&
           distLeft == right.distLeft;
}