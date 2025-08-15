#include "StateMachine.h"

StateMachine::StateMachine(){
  stateList = new LinkedList<State*>();
};

StateMachine::~StateMachine(){};

/*
 * Main execution of the machine occurs here in run
 * The current state is executed and it's transitions are evaluated
 * to determine the next state. 
 * 
 * By design, only one state is executed in one loop() cycle.
 */
void StateMachine::run(){
  //Serial.println("StateMachine::run()");
  // Early exit, no states are defined
  if(stateList->size() == 0) return;

  // Initial condition
  if(currentState == -1){
    currentState = 0;
  }
  
  // Execute state logic and return transitioned
  // to state number. Remember the current state then check
  // if it wasnt't changed in state logic. If it was, we 
  // should ignore predefined transitions.
  int initialState = currentState;

  if (initialState != lastState && lastState != -1){
    stateList->get(lastState)->executeExit();
  }
  if (initialState != lastState){
    stateList->get(initialState)->executeEnter();
  }
  lastState = initialState;

  int next = stateList->get(currentState)->execute();
  if(initialState == currentState){
    executeOnce = (currentState == next)?false:true;
    currentState = next;
  }
}

/*
 * Adds a state to the machine
 * It adds the state in sequential order.
 */
State* StateMachine::addState(void (*fp_loop)(), void (*fp_enter)(), void (*fp_exit)()){
  int idx = stateList->size();
  State* s = new State(idx, fp_loop, fp_enter, fp_exit);
  stateList->add(s);
  return s;
}

/*
 * Jump to a state
 * given by a pointer to that state.
 */
State* StateMachine::transitionTo(State* s){
  this->currentState = s->getIndex();
  this->executeOnce = true;
  return s;
}

/*
 * Jump to a state
 * given by a state index number.
 */
int StateMachine::transitionTo(int i){
  if(i < stateList->size()){
	this->currentState = i;
	this->executeOnce = true;
	return i;
  }
  return currentState;
}