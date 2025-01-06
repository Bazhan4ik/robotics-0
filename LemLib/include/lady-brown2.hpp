#include "pros/rtos.hpp"




class LadyBrown {

public:

  void move(int position);

  void reset();

  void init();

  bool isFinished();

  void waitUntilDone();

private:
  int current_position;
  int current_target;

  bool finished;

  pros::Task* task;
};


extern LadyBrown lb;


