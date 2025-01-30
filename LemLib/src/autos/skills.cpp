#include "intake.hpp"
#include "config.hpp"
#include "autos.hpp"
#include "mogo-grabber.hpp"
#include "lady-brown2.hpp"
#include "pros/motors.h"



void align() {
  right_motors.move(60);
  
  pros::delay(250);
  right_motors.brake();
  left_motors.move(60);

  pros::delay(250);
  left_motors.brake();
  right_motors.move(60);

  pros::delay(250);
  right_motors.brake();
  left_motors.move(60);

  pros::delay(250);
  left_motors.brake();
  right_motors.move(60);

  pros::delay(150);
  right_motors.brake();
  left_motors.brake();
}



void skills() {
  chassis.setPose(0,0, 90);


  intake.run_auto();
  pros::delay(500);
  intake.stop();


  chassis.moveToPoint(12.5, 0, 1000, { .maxSpeed=60 });
  chassis.turnToHeading(180, 1000);

  chassis.moveToPoint(12.5, 20, 1000, { .forwards=false, .maxSpeed=70 });
  chassis.turnToHeading(90, 1000);

  intake.run_auto();

  chassis.moveToPoint(34.3, 20.4, 1000);
  chassis.turnToHeading(0, 1000);
  chassis.moveToPoint(35, 42.5, 1000);
  chassis.turnToHeading(-90, 1000);
  // move close to wall
  chassis.moveToPoint(5, 42.5, 3000, { .maxSpeed=80 });
  chassis.waitUntilDone();
  // doesn't hit the wall + picks up last ring

  chassis.moveToPoint(15, 42.5, 1000, { .forwards=false });
  chassis.turnToHeading(0, 1000);
  // turns to the last corner ring, hits it a little
  chassis.moveToPoint(15, 52, 1000);
  
  // go to corner
  chassis.turnToPoint(7, 56.5, 1000, { .forwards=false });
  // doesn't hit the wall
  chassis.moveToPoint(7, 56.5, 1000, { .forwards=false });
  // doesn't hit the wall with the mogo
  mogo_ungrab();
  grab = false;

  // move away from the corner
  chassis.moveToPoint(12, 50, 1000);
  chassis.turnToHeading(0, 1000);

  // second mogo grab
  chassis.moveToPoint(11, -13, 3000, { .forwards=false, .minSpeed=100, .earlyExitRange=13 });
  chassis.moveToPoint(11, -22, 4000, { .forwards=false, .maxSpeed=30 });
  // slows down at the end, grabs the mogo
  grab = true;

  chassis.turnToHeading(90, 1000);
  // turns looking exactly at the ring

  chassis.moveToPoint(35, -22.5, 1000);
  chassis.turnToHeading(180, 1000);

  chassis.moveToPoint(35, -43, 1000);
  chassis.turnToHeading(-90, 1000);

  chassis.moveToPoint(2, -44, 2000, { .maxSpeed=80 });
  // doesnt hit the wall, touches the last ring??
  chassis.moveToPoint(11, -44, 1000, { .forwards=false });
  chassis.turnToHeading(180, 1000);
  // aligns with the last ring??

  chassis.moveToPoint(13.5, -53, 1000);
  chassis.waitUntilDone();

  // put mogo in corner
  chassis.turnToPoint(5, -56.5, 1000, { .forwards=false });
  chassis.moveToPoint(5, -56.5, 1000, { .forwards=false });
  mogo_ungrab();
  grab = false;

  // align with the high stake
  chassis.moveToPoint(55.7, -38.5, 3000, { .maxSpeed=70 });
  intake.stop();
  chassis.turnToHeading(180, 1000);
  
  // move closer to the high stake
  chassis.moveToPoint(59, -61.5, 3000, { .maxSpeed=35 });
  lb.move(1);
  max_speed = 90;
  intake.run_auto();

  chassis.waitUntilDone();

  align();

  chassis.setPose(0,0, chassis.getPose().theta);
  chassis.moveToPoint(0, 2.5, 1000, { .forwards=false, .maxSpeed=60, });
  chassis.waitUntilDone();

  max_speed = 40;
  intake.reverse();
  lb.move(4);
  intake.stop();

  lb.waitUntilDone();
  lb.move(0);

  chassis.moveToPoint(0, 12, 1000, { .forwards=false, });
  chassis.turnToHeading(90, 1000);

  chassis.moveToPoint(21, 14, 1000);
  max_speed = 70;
  intake.run_time(500);
  chassis.turnToPoint(24, 33, 1000);
  chassis.moveToPoint(24, 33, 1000);
  intake.stop();
  intake.run_auto_wheels();

  chassis.turnToPoint(44, 57, 2000, { .forwards=false });
  chassis.moveToPoint(44, 57, 2000, { .forwards=false, .maxSpeed=40 });
  grab = true;
  

  // chassis.moveToPoint();
  // intake.run_auto();
  intake.stop();
  max_speed = 127;
  intake.run_auto();

  chassis.turnToPoint(21.5, 80.5, 2000);
  chassis.moveToPoint(21.5, 80.5, 2000);

  chassis.turnToHeading(0, 1000);

  chassis.moveToPoint(21, 102, 1000);


  chassis.waitUntilDone();
  pros::delay(2000);
  intake.stop();
  mogo_ungrab();
}
