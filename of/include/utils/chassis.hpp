
#include "pros/motor_group.hpp"
#include "utils/pose.hpp"





class Drivetrain {
  public:
    Drivetrain(pros::MotorGroup* leftMotors, pros::MotorGroup* rightMotors, float trackWidth, float wheelDiameter, float rpm, float horizontalDrift);

    pros::MotorGroup* leftMotors;
    pros::MotorGroup* rightMotors;

    float trackWidth;
    float wheelDiameter;
    float rpm;
    float horizontalDrift;


};





class Chassis {
  public:
    Chassis(Drivetrain drivetrain);
    Pose getPose();

    
};