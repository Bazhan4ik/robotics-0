#include "pros/rtos.hpp"
#include "utils/pose.hpp"
#include "config.hpp"
#include "utils/utils.hpp"
#include <cstddef>


Pose position (0,0,0);
Pose speed (0,0,0);
Pose localSpeed (0,0,0);



float ema(float current, float previous, float smooth) {
  return (current * smooth) + (previous * (1 - smooth));
}
Pose getPose() {
  return position;
}


float prevVertical = 0;
float prevImu = 0;

void update() {
  float verticalRaw = (float(rotation_vertical.get_position()) * t_wheel_diameter * M_PI / 36000);
  float imuRaw = degToRad(imu.get_rotation());


  float deltaVertical = verticalRaw - prevVertical;
  float deltaImu = imuRaw - prevImu;
  float heading = position.orientation += deltaImu;


  float deltaHeading = heading - position.orientation;
  float avgHeading = position.orientation + deltaHeading / 2;


  prevVertical = verticalRaw;
  prevImu = imuRaw;


  float localVertical = 2 * sin(deltaHeading / 2) * (deltaVertical / deltaHeading);

  Pose prevPose = position;

  position.x = localVertical * sin(avgHeading);
  position.y = localVertical * cos(avgHeading);
  position.orientation = heading;

  speed.x = ema((position.x - prevPose.x) / 0.01, speed.x, 0.95);
  speed.y = ema((position.y - prevPose.y) / 0.01, speed.y, 0.95);
  speed.orientation = ema((position.orientation - prevPose.orientation) / 0.01, speed.orientation, 0.95);

 
}




pros::Task* trackingTask = nullptr;
void init() {
    if (trackingTask == nullptr) {
        trackingTask = new pros::Task {[=] {
            while (true) {
                update();
                pros::delay(10);
            }
        }};
    }
}

