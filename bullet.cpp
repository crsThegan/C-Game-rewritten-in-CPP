#include "bullet.hpp"
#include "player.hpp"
#include "board.hpp"
#include "cannon.hpp"
#include "type_flags.hpp"

#include <vector>
#include <mutex>
#include <chrono>

const int BULLET_RANGE = 5;

std::vector<Bullet> bullets;

std::mutex bulletMutex; // needed to make sure that the 'bullets' vector is not being modified by
                        // multiple threads simultaneously

void Bullet::Bullet(Entity &shooter) {
    try {
        shooter = dynamic_cast<Player &>(shooter);
        x = shooter.x;
        y = shooter.y;
        dir = shooter.dir;
        distLeft = BULLET_RANGE;

        shooter.ammo--;
    } catch (std::bad_cast &ex) {
        shooter = dynamic_cast<Cannon &>(shooter);
        x = shooter.x;
        y = shooter.y;
        dir = shooter.dir;
        distLeft = BULLET_RANGE;

        std::this_thread::sleep_for(std::chrono::milliseconds(CANNON_RELOAD_TIME));
    }
}

void Bullet::fly(element (*board)[HEIGHT]) {
    std::lock_guard<std::mutex> lock(bulletMutex);

    switch (dir) {
    case Direction::right:
        if (board[x + 1][y] == BLANK_SPACE && distLeft > 0) x++;
        else bullets.erase(this);
        break;
    case Direction::left:
        if (board[x - 1][y] == BLANK_SPACE && distLeft > 0) x--;
        else bullets.erase(this);
        break;
    case Direction::up:
        if (board[x][y + 1] == BLANK_SPACE && distLeft > 0) y++;
        else bullets.erase(this);
        break;
    case Direction::down:
        if (board[x][y - 1] == BLANK_SPACE && distLeft > 0) y--;
        else bullets.erase(this);
        break;
    }
}

void Bullet::flyAll(element (*board)[HEIGHT]) {
    while (true) {
        for (Bullet &bullet: bullets) {
            bullet.fly(board);
            --bullet.distLeft;
        }
    }
}

void Bullet::create(Entity &shooter) {
    std::lock_guard<std::mutex> lock(bulletMutex);
    
    bullets.push_back(Bullet(shooter));
}