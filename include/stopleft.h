#ifndef STOPLEFT_H
#define STOPLEFT_H

#include "state.h"
class InputComponent;
class GameObject;

/*!
 * \brief The state in which the player is standing facing left
 * This also handles the responds to key press and key release inputs so as to change the state
 * of the GameObject
 */

class StopLeft : public State
{
public:
    /*!
     * \brief Destructor
     */
    virtual ~StopLeft() {}
    /*!
     * \brief Updates the state on the basis of the keys currently pressed
     * \param inputComponent the InputComponent of the GameObject whose state is being updated
     * \param key the set of keys currently pressed
     * \return the new state
     */
    virtual State* update(InputComponent *inputComponent, std::set<Qt::Key> key);
    /*!
     * \brief Provides the type of the State, i.e., DeadLeft
     * \return enumerator::State::STOP_LEFT
     */
    virtual enumerator::State type();
};

#endif // STOPLEFT_H
