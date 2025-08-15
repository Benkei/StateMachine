#include <LinkedList.h>
#include "State.h"

#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

class StateMachine
{
  public:
    // Methods
    
    StateMachine();
    ~StateMachine();
    void init();
    void run();

    // When a stated is added we pass the function that represents 
    // that state logic
    State* addState(void (*fp_loop)(), void (*fp_enter)() = NULL, void (*fp_exit)() = NULL);
    State* transitionTo(State* s);
    int transitionTo(int i);

  private:
    // Attributes
    LinkedList<State*> *stateList;
    bool executeOnce = true; // Indicates that a transition to a different state has occurred
    int currentState = -1;   // Indicates the current state number
    int lastState = -1;      // Indicates the last state number
};



#endif
