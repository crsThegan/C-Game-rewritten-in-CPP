#pragma once

#include "player.hpp"
#include "board.hpp"
#include "bullet.hpp"

#include <vector>

class Cannon: public Entity {
    Cannon(int x, int y, Direction dir);
    void shoot(element (*board)[HEIGHT]);
public:
    static const int RELOAD_TIME = 500;
    static void create(int x, int y, Direction dir);
    static void fireAll(element (*board)[HEIGHT]);
};

extern std::vector<Cannon> cannons;