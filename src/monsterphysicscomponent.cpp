#include "monsterphysicscomponent.h"
#include <QGraphicsItem>

MonsterPhysicsComponent::MonsterPhysicsComponent(std::vector<std::vector<Tile*>> &Tilesmap, int theight, int twidth, int sheight, int swidth)
{
    velocity = 1;
    this->Tilesmap = Tilesmap;
    width_of_tile = twidth;
    height_of_tile = theight;
    screenHeight = sheight;
    screenWidth = swidth;
}

void MonsterPhysicsComponent::update(GameObject & ob)
{
    int newx,newy,height,width;
    std::vector<qreal> details(4);
    details = ob.graphicsComponent->getSizePositionOfObject();
    newx = details[0];
    newy = details[1];
    width = details[2];
    height = details[3];
    enumerator::State state_index =  ((ob.state)->type());
    enumerator::JumpingState jumping_state_index =  ((ob.jumpingState)->type());

    if(!((Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[newy/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() ))
    {
        if(newx<=0)
        {
            newx=0;
        }
        else if ( newx + width > screenWidth-width_of_tile )
        {
            newx= screenWidth - width_of_tile - width;
        }
        ob.graphicsComponent->setPos(newx,newy);
    }


    if(state_index == enumerator::State::MOVING_RIGHT)
    {
        newx+=width_of_tile;
    }
    else if(state_index == enumerator::State::MOVING_LEFT)
    {
        newx-=width_of_tile;
    }

    if(newx<=0)
    {
        newx=0;
    }
    else if (newx > screenWidth-width_of_tile)
    {
        newx= screenWidth - width_of_tile;
    }

    if(!(Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle())
    {
        ob.graphicsComponent->setOffset(newx,newy);
    }

}
