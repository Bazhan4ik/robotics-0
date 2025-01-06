#include "utils/pose.hpp"
#include <cmath>


Pose::Pose(float x, float y, float orientation) {
  this->x = x;
  this->y = y;
  this->orientation = orientation;
} 

float Pose::distance(Pose target) const { return std::hypot(this->x - target.x, this->y - target.y ); }

float Pose::angle(Pose target) const { return std::atan2(target.y - this->y, target.x - this->x); }

