#include "pros/rtos.hpp"


extern int max_speed;

class LadyBrown {

public:

  void move(int position);

  void reset();

  void init();

  bool isFinished();

  void waitUntilDone();

  int current_target;

private:
  int current_position;

  bool finished;

  pros::Task* task;
};


extern LadyBrown lb;


