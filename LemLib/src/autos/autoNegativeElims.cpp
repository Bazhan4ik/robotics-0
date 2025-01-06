#include "config.hpp"
#include "intake.hpp"
#include "autos.hpp"
#include "lady-brown2.hpp"






// negative corner
// no alliance stake
// mogo: preload + 3 rings
// variation 1: touch the bar
// variation 2: clear the negative corner  






void touchTheBar() {
  // turn to the bar
  chassis.turnToHeading(140, 2000);
  chassis.waitUntilDone();
  // make sure ring doesnt go into lady brown
  pros::delay(500);

  // move to the bar
  chassis.moveToPoint(-11, -40, 2000, { .maxSpeed=70 });
  lb.move(4);

  pros::delay(1000);
  intake.stop();
}


void autoNegativeElims() {


  // grab the mogo
  chassis.moveToPoint(0, -31, 2000, { .forwards=false, .maxSpeed=70 });

  // turn to the first of two rings
  chassis.turnToPoint(-21.4, -37.2, 1000);
  intake.run_auto();
  // move to the first of the two rings
  chassis.moveToPoint(-21.4, -37.2, 1700, { .maxSpeed=50 });

  // turn to the second of double rings
  chassis.turnToPoint(-35, -35, 1000);
  chassis.moveToPoint(-35, -32, 1500, { .maxSpeed=50 });
  // turn to the last rings
  chassis.turnToPoint(-21.6, -24, 1000);
  chassis.moveToPoint(-21.6, -24, 1500, { .maxSpeed=50 });
  

  touchTheBar();
}
