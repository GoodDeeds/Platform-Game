
#include "include/gameobject.h"
#include "include/state.h"
#include <QEvent>
#include <QKeyEvent>
#include <Qt>
#include <set>

#include "include/humaninputcomponent.h"

HumanInputComponent::HumanInputComponent()
{
    keysPressed.clear();
}

void HumanInputComponent::update(GameObject &gameObject)
{
    State *new_state = gameObject.state->update(gameObject,keysPressed);
    if(new_state != NULL)
    {
        delete gameObject.state;
        gameObject.state = new_state;
    }

}

void HumanInputComponent::event(QEvent *event, GameObject &gameObject)
{
    QKeyEvent *key_event = dynamic_cast<QKeyEvent *>(event);
    if(key_event && key_event->type() == QKeyEvent::KeyPress && gameObject.keys.find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.insert(static_cast<Qt::Key>(key_event->key()));
    }
    else if(key_event && key_event->type() == QKeyEvent::KeyRelease && gameObject.keys.find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.erase(static_cast<Qt::Key>(key_event->key()));
    }
    update(gameObject);
}