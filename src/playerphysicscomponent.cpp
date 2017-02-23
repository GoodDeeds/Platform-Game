#include "playerphysicscomponent.h"
#include <typeinfo>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "gem.h"

extern tile *** Tilesmap;
extern int score;

PlayerPhysicsComponent::PlayerPhysicsComponent()
{
    velocity = 0;
    acceleration = 1;
}

void PlayerPhysicsComponent::update(GameObject & ob)
{
    int newx,newy;
    newx=ob.graphicscomponent->x();
    newy=ob.graphicscomponent->y();
    enumerator::State state_index =  ((ob.state)->type());
    enumerator::JumpingState jumping_state_index =  ((ob.jumpingState)->type());
    newy-=width_of_tile;

    if(state_index == enumerator::State::MOVING_RIGHT)
    {
        newx+=width_of_tile;
    }
    else if(state_index == enumerator::State::MOVING_LEFT)
    {
        newx-=width_of_tile;
    }

    if(jumping_state_index == enumerator::JumpingState::IS_JUMPING)
    {
        newy=ob.graphicscomponent->y()-((0<velocity)-(velocity<0))*height_of_tile;
    }

    if(newx<=0)
    {
        newx=0;
    }
    else if (newx > screenWidth-width_of_tile)
    {
        newx= screenWidth - width_of_tile;
    }

    if (newy <= 0)
    {
        newy=0;
    }
    else if ( newy > screenHeight-height_of_tile)
    {
       newy= screenHeight-height_of_tile;
    }

    if(!(Tilesmap[newy/height_of_tile][newx/width_of_tile])->isObstacle)
    {
        ob.graphicscomponent->setOffset(newx,newy);
        QList<QGraphicsItem *> colliding_items = ob.graphicscomponent->collidingItems();
        for(int i = 0, n = colliding_items.size();i<n;i++) {
            if(typeid(*(colliding_items[i])) == typeid(gem)){
                score++;
                ob.scene->removeItem(colliding_items[i]);
                delete colliding_items[i];
            }
            if(typeid(*(colliding_items[i])) == typeid(GraphicsComponent)){
                if(((*colliding_items[i]).getIsMonster()) == TRUE ){
                    // getismonster() is a member of graphics component to check moster
                    if(state_index == enumerator::State::MOVING_RIGHT)
                    {
                        ob.setState(new DeadRight);
                    }
                    else
                    {
                        ob.setState(new DeadLeft);
                    }
                }
            }
        }
    }


}
