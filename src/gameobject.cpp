#include "gameobject.h"
#include <QCoreApplication>

GameObject::GameObject(InputComponent *input_component, Keys input_keys, const int &max_jump_count) : keys(input_keys), maxJumpCount(max_jump_count)
{
    inputComponent = input_component;
    inputComponent->setParent(this);
}

bool GameObject::event(QEvent *input_event)
{
    return QCoreApplication::sendEvent(inputComponent,input_event);
}
