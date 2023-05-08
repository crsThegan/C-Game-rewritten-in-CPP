#pragma once

#include "board.hpp"
#include "player.hpp"
#include "type_flags.hpp"

#include <vector>

class Bullet {
    int x, y;
    Direction dir;
    int distLeft;

    Bullet(Entity &shooter);
    fly(element (*board)[HEIGHT]);
public:
    // static void create(Entity &shooter);
    static void flyAll(element (*board)[HEIGHT]);
    static void create(Entity &shooter);
    // getters & setters
    // int getX() {
    //     return x;
    // }

    // void setX(int x) {
    //     this->x = x;
    // }

    // int getY() {
    //     return y;
    // }

    // void setY(int y) {
    //     this->y = y;
    // }

    // Direction getDir() {
    //     return dir;
    // }

    // void setDir(Direction dir) {
    //     this->dir = dir;
    // }

    // int getDist() {
    //     return distLeft;
    // }

    // void setDist(int distLeft) {
    //     this->distLeft = distLeft;
    // }
};

extern std::vector<Bullet> bullets;