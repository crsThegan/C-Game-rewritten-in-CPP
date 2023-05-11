#pragma once

#include "board.hpp"
#include "player.hpp"

#include <vector>

class Bullet: public Entity {
    int distLeft;

    Bullet(Entity *shooter);
    void fly(element (*board)[HEIGHT]);
public:
    static void flyAll(element (*board)[HEIGHT]);
    static void create(Entity *shooter);

    bool operator==(const Bullet &right);
};

extern std::vector<Bullet *> bullets;