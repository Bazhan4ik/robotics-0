#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "config.hpp"
#include "intake.hpp"
#include "liblvgl/llemu.hpp"
#include "mogo-grabber.hpp"
#include "lady-brown.hpp"
#include "ui/ui.hpp"

#include "lady-brown2.hpp"
#include "autos.hpp"





void initialize() {
  // ui_init();
  pros::lcd::initialize();

  chassis.calibrate();

  mogo_ungrab();


  intake.set_team_alliance("red");
  pros::Task intake_task(intake.task);
  pros::Task grabber_task(mogo_grabber);

  lb.init();

  pros::Task screen_task([&]() {
    while (true) {
      // print robot location to the brain screen
      pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
      pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
      // delay to save resources
      pros::delay(40);
    }
  });
}

void disabled() {}

void competition_initialize() {}


void autonomous() {
  // autoRedTwoRings();
  // autoNegativeElims();
  
  skills();
}

void opcontrol() {

  while (true) {
    int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    chassis.tank(leftY, rightY);


    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      mogo_ungrab();
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) || master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      lb.move(1);
      // pros::Task my_task(lb_get_ready, "My Task Name");
    }
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !running_lady_brown) {
      lb.move(4);
    }
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      lb.move(0);
    }


    pros::delay(25);
  }

}
