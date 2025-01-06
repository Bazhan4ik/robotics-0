#include "config.hpp"
#include "intake.hpp"
#include "lemlib/pose.hpp"

#include "autos.hpp"






void autoRedTwoRings() {
  chassis.setPose(0, 0, 180);

  chassis.moveToPoint(0, -14.5, 2000, { .maxSpeed=40 });
  chassis.turnToHeading(-90, 1500, { .maxSpeed=80 });
  chassis.moveToPoint(4.2, chassis.getPose().y, 1300, { .forwards=false, .maxSpeed=50 });
  chassis.waitUntilDone();
  
  intake.run_auto();

  pros::delay(600);

  intake.stop();

  chassis.moveToPoint(-3, chassis.getPose().y, 1000);
  chassis.turnToHeading(135, 1000);

  chassis.moveToPoint(-34.5, 10.5, 1500, { .forwards=false, .maxSpeed=55 });
  chassis.turnToHeading(-54, 1000);

  intake.run_auto();

  chassis.moveToPoint(-47, 24, 2000, { .maxSpeed=70 });
  


}