#include "lady-brown2.hpp"
#include "config.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rotation.h"
#include "pros/rtos.hpp"



LadyBrown lb;
uint32_t timer = pros::millis();


int max_speed = 80;

void LadyBrown::move(int position) {
  if(position == 1) {
    max_speed = 50;
    current_target = 4300;
  } else if(position == 2) {
    max_speed = 50;
    current_target = 6000;
  } else if(position == 3) {
    current_target = 12000;
  } else if(position == 4) {
    // max_speed = 80;
    max_speed = 0;
    current_target = 18000;
  } else if(position == 0) {
    current_target = 0;
    max_speed = 80;
  }

  timer = pros::millis();
  finished = false;
}

void LadyBrown::reset() {
  current_position = 0;
  rotation_arm.reset();
  rotation_arm.reset_position();
}
void LadyBrown::waitUntilDone() {
  while(true) {
    pros::delay(20);
    if(finished) {
      return;
    }
  }
}


void LadyBrown::init() {
  lady_brown_arm.move(-127);
  pros::delay(300);
  lady_brown_arm.brake();
  reset();
  finished = true;
  
  task = new pros::Task{[=, this] {

    float kP = 0.031;
    float kD = 0.055;

    int previous_error = 0;

    bool timerDone = false;

    while(true) {
      pros::delay(20);

      if(finished || max_speed == 0) {
        timer = pros::millis();
        continue;
      }

      timerDone = pros::millis() > timer + 1000;

      int current_position = -rotation_arm.get_position();

      int error = current_target - current_position;
      int derivative = error - previous_error;

      double motor_power = float(error) * kP + float(derivative) * kD;



      previous_error = error;

      printf("LADYBROWN REPORT motorpower: %f  ::: error: %d  ::: currentposition: %d", motor_power, error, current_position);

      pros::lcd::print(5, "error: %d", error);
      pros::lcd::print(6, "motorpower: %f", motor_power);
      pros::lcd::print(7, "currentposition: %d", current_position);


      if(motor_power > max_speed) {
        motor_power = max_speed;
      } else if(motor_power < -max_speed) {
        motor_power = -max_speed;
      }

      if(abs(error) < 150 || timer + 1500 < pros::millis()) {

        if(current_target == 0) {
          lady_brown_arm.move(-50);
          pros::delay(200);
          reset();
        }

        lady_brown_arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        lady_brown_arm.brake();

        finished = true;
        previous_error = 0;

        continue;
      }

      lady_brown_arm.move(motor_power);
    }
  }};
}

bool LadyBrown::isFinished() {
  return finished;
}

