
#pragma once


class Pose {
  public:
    float x;
    float y;
    float orientation;

    Pose(float x, float y, float orientation = 0);

    float distance(Pose target) const;

    float angle(Pose target) const;
};