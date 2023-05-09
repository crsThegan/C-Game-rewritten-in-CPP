#pragma once

#include "board.hpp"

#include <vector>

// controls
#define RIGHT_KEY 'd'
#define LEFT_KEY 'a'
#define DOWN_KEY 's'
#define UP_KEY 'w'
#define SHOOT_KEY 'r'

enum Direction {
    up,
    down,
    right,
    left
};

class Entity {
protected:
    int x, y;
    Direction dir;
public:
    // basic getters
    int getX();
    int getY();
    Direction getDir();
};

class Player: public Entity {
    int ammo;
    int health;

    void moveOnBoard(element (*board)[HEIGHT]);
    void actionCheck(element (*board)[HEIGHT]);
public:
    Player(int x, int y, Direction dir);
    void hit(int damage);
    void shoot();
    static void actionCheckAll(element (*board)[HEIGHT]);
};

extern std::vector<Player> players;