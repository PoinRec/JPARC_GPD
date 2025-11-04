#include "Action.hh"
#include "Run.hh"

MyActionInitialization::MyActionInitialization() {
}

MyActionInitialization::~MyActionInitialization() {
}

void MyActionInitialization::Build() const {
  MyGenerator *generator = new MyGenerator();
  SetUserAction(generator);
  
  MyRunAction *runAction = new MyRunAction();
  SetUserAction(runAction);
}
