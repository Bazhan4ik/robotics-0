#pragma once

#include "utils/chassis.hpp"
#include "utils/odometry.hpp"


Pose Chassis::getPose() {
  return odometry::getPose();
}
