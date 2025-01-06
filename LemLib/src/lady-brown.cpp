#include "lady-brown.hpp"
#include "config.hpp"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include <cstdlib>



bool lady_brown_allowed = true;
bool running_lady_brown = false;


int lb_dist_1 = 2700;
int lb_dist_2 = 3000;


pros::Task* get_ready_task = nullptr;


void lb_get_ready_task(int target) {
  if(running_lady_brown) {
    return;
  }

  pros::lcd::print(7, "%d", target);

  double maxSpeed = 35;

  // start PID
  lady_brown_allowed = true;
  running_lady_brown = true;

  // constants
  double kP = 1;
  double kD = 5;

  double prevError = 0;


  // reset rotation positions
  rotation_arm.reset();
  rotation_arm.reset_position();

  pros::lcd::print(4, "INITIAL VALUE: %d", rotation_arm.get_position());


  while(lady_brown_allowed) {


    int ticks = rotation_arm.get_position();

    int error = target - std::abs(ticks);
    int derivative = error - prevError;

    double lateralMotorPower = std::abs((error * kP) + (derivative * kD));

    if(lateralMotorPower > maxSpeed) {
      lateralMotorPower = maxSpeed;
    }
    if(lateralMotorPower < -maxSpeed) {
      lateralMotorPower = -maxSpeed;
    }


    // CHECK ALL THE NUMBERS
    if(abs(error) < 150) {
      // STOP ALL THE MOTORS
      
      lady_brown_arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      lady_brown_arm.brake();

      break;
    } else {
      // KEEP SPINNING
      lady_brown_arm.move(lateralMotorPower);
    }


    prevError = error;

    pros::delay(20);
  }

  running_lady_brown = false;
  get_ready_task = nullptr;
}
void lb_move_down_task() {
  lady_brown_allowed = false;
  running_lady_brown = true;
  lady_brown_arm.move(-127);
  pros::delay(500);
  lady_brown_arm.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lady_brown_arm.brake();
  running_lady_brown = false;
}
void lb_move_up_task() {
  running_lady_brown = true;
  lady_brown_arm.move(127);
  pros::delay(700);
  lady_brown_arm.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lady_brown_arm.brake();
  running_lady_brown = false;
}


void lb_get_ready(int target) {
  if(lady_brown_allowed) {
    get_ready_task = new pros::Task {[=] {
      lb_get_ready_task(target);
    }};
  }
}
void lb_move_down() {
  pros::Task task(lb_move_down_task);
}
void lb_move_up() {
  pros::Task task(lb_move_up_task);
}