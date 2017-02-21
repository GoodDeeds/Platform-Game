#ifndef HUMANINPUTCOMPONENT_H
#define HUMANINPUTCOMPONENT_H

#include "inputcomponent.h"
#include "state.h"
#include "gameobject.h"
#include <QEvent>
#include <Qt>
#include <set>

class HumanInputComponent : public InputComponent
{
    std::set<Qt::Key> keysPressed;
public:
    HumanInputComponent();
    virtual ~HumanInputComponent() {}
    virtual void update(GameObject &);
    void event(QEvent *);
};

#endif // HUMANINPUTCOMPONENT_H
