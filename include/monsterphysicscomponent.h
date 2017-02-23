#ifndef MONSTERPHYSICSCOMPONENT_H
#define MONSTERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "gameobject.h"
#include "tile.h"
#include <vector>

class MonsterPhysicsComponent : public PhysicsComponent
{
private:
    int velocity;
    int newx,newy;
    std::vector<std::vector<Tile*>> Tilesmap;
    int width_of_tile,height_of_tile,screenWidth,screenHeight;
public:
    MonsterPhysicsComponent(std::vector<std::vector<Tile*>> &Tilesmap, int theight, int twidth, int sheight, int swidth);
    virtual ~MonsterPhysicsComponent() {}
    void update(GameObject &ob);
};

#endif // MONSTERPHYSICSCOMPONENT_H
