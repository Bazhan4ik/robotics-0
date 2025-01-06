#include "intake.hpp"
#include "config.hpp"
#include "autos.hpp"
#include "mogo-grabber.hpp"
#include "lady-brown2.hpp"
#include "pros/motors.h"







void skills2() {
  // starting position: 0, 0, ~ 180  +- 2deg

  
  // REMOVE FOR FULL RUN
  // chassis.setPose(0, 0, 180);

  chassis.moveToPoint(0, 14, 1000, { .forwards=false, .maxSpeed=40, });
  chassis.turnToHeading(90, 1000);

  lb.move(1);
  intake.run_auto();

  chassis.moveToPoint(25.5, 12.5, 1500, { .maxSpeed=70 });
  chassis.turnToHeading(0, 1000);

  intake_speed = 127;

  pros::delay(350);

  intake.stop();
  intake.run_auto_wheels();

  lb.move(2);

  chassis.moveToPoint(25.5, 44, 1000, { .maxSpeed=60 });

  chassis.turnToHeading(-118, 1500, { .maxSpeed=70 });
  chassis.moveToPoint(48.1, 60, 1500, { .forwards=false, .maxSpeed=60 });
  grab = true;
  chassis.turnToHeading(-50, 1000);
  chassis.moveToPoint(24, 80, 1000, { .maxSpeed=60 });
  intake.stop();
  intake.run_auto();

  chassis.turnToHeading(0, 1000);


  // ring closest to the wall pick up
  chassis.moveToPoint(25, 104, 1000, { .maxSpeed=60 });
  // back up a little
  chassis.moveToPoint(22.5, 102, 1000, { .forwards=false, .maxSpeed=60 });
  chassis.turnToHeading(-90, 1000);
  // align with the high stake
  chassis.moveToPoint(1.6, 102, 2500, { .maxSpeed=50 });

  chassis.turnToHeading(0, 1500);

  chassis.moveToPose(1.6, 121, 0, 2100, { .maxSpeed=35 });
  chassis.waitUntilDone();

  left_motors.move(30);
  right_motors.move(18);
  pros::delay(300);
  left_motors.move(18);
  right_motors.move(30);
  pros::delay(300);
  left_motors.brake();
  right_motors.brake();

  lb.move(4);
  pros::delay(100);

  chassis.moveToPose(chassis.getPose().x, 113, 0, 2700, { .forwards=false, .maxSpeed=35 });
  chassis.turnToHeading(90, 1000);

  lb.move(0);


  pros::delay(2000);
  intake.stop();
  mogo_ungrab();
  grab = false;




}



void skills() {
  // skills2();

  // return;

  intake.run_auto();
  pros::delay(500);
  intake.stop();
  
  chassis.setPose(0,0, 90);

  chassis.moveToPose(11.2, 0, 90, 1000, { .maxSpeed=50 });
  chassis.turnToHeading(180, 1000);

  chassis.moveToPoint(11.2, 21, 1000, { .forwards=false, .maxSpeed=60 });
  chassis.turnToHeading(90, 1000);

  //=>
  //=> MOGO GRABBED
  //=>

  chassis.moveToPoint(35, 21, 1000, { .maxSpeed=60 });
  intake.run_auto();

  chassis.turnToHeading(0, 1000);
  chassis.moveToPoint(35.5, 45, 1000, { .maxSpeed=60 });

  chassis.turnToHeading(-90, 1000);
  chassis.moveToPoint(1.5, 47, 5000, { .maxSpeed=80 });
  chassis.turnToHeading(45, 1000);
  chassis.moveToPoint(11, 55, 1000);
  chassis.turnToHeading(120, 1000);
  chassis.moveToPoint(1.5, 60.5, 1000, { .forwards=false });
  mogo_ungrab();
  grab = false;
  chassis.moveToPoint(8, 52, 1000);
  intake.stop();


  //=>
  //=> PICK UP SECOND MOGO
  //=>

  chassis.turnToHeading(0, 1000, { .maxSpeed=60 });
  chassis.moveToPoint(8, -7, 2000, { .forwards=false, .minSpeed=80, .earlyExitRange=12 });
  chassis.moveToPoint(8, -23.5, 5000, { .forwards=false, .maxSpeed=40 });
  grab = true;

  //=>
  //=> SCORE FIRST RING ON SECOND MOGO 
  //=>

  chassis.turnToHeading(90, 1000);
  intake.run_auto();

  chassis.moveToPoint(32, -23, 1000);
  chassis.turnToHeading(180, 1000);
  chassis.moveToPoint(31, -44, 1000);

  //=>
  //=> PICK UP TWO RINGS
  //=>

  chassis.turnToHeading(-90, 1000);
  chassis.moveToPoint(2, -44, 2000);

  //=>
  //=> PICK UP LAST RING
  //=> 

  chassis.turnToHeading(135, 1000);
  chassis.moveToPoint(8, -54, 1000);

  chassis.turnToHeading(70, 1000);
  chassis.moveToPoint(1, -59.8, 1000, { .forwards=false });
  mogo_ungrab();
  grab = false;


  //=>
  //=> GO TO HIGH STAKE
  //=>

  chassis.moveToPoint(45, -47, 2000, { .minSpeed=80, .earlyExitRange=12 });
  intake.stop();
  chassis.moveToPoint(54.2, -43, 3000, { .maxSpeed=50 });
  chassis.turnToHeading(180, 1000, { .maxSpeed=50 });
  grab = true;
  

  //=>
  //=> MOVE CLOSER TO THE HIGH STAKE
  //=>

  lb.move(1);

  // all the way to the wall
  chassis.moveToPose(54.3, -66, 180, 2000, { .maxSpeed=33 });
  intake_speed=100;
  intake.run_auto();
  chassis.waitUntilDone();

  // make sure its properly lined up
  left_motors.move(40);
  right_motors.move(25);
  pros::delay(200);
  left_motors.move(25);
  right_motors.move(40);
  pros::delay(200);
  left_motors.brake();
  right_motors.brake();

  // reset position
  pros::delay(100);
  chassis.setPose(0, 0, chassis.getPose().theta);


  intake.stop();
  lb.move(4);
  pros::delay(300);

  skills2();
}