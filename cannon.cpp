#include "cannon.hpp"
#include "board.hpp"
#include "bullet.hpp"

#include <vector>
#include <thread>
#include <chrono>

std::vector<Cannon> cannons;

Cannon::Cannon(int x, int y, Direction dir) {
    this->x = x;
    this->y = y;
    this->dir = dir;
}

void Cannon::shoot(element (*board)[HEIGHT]) {
    Bullet::create(this);
}

void Cannon::create(int x, int y, Direction dir) {
    cannons.push_back(Cannon(x, y, dir));
}

void Cannon::fireAll(element (*board)[HEIGHT]) {
    while (true) {
        for (auto &cannon: cannons) cannon.shoot(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(RELOAD_TIME));
    }
}