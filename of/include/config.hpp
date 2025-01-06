#include "main.h"




extern double track_width;


extern double t_wheel_diameter;
extern double wheel_diatemeter;










extern pros::MotorGroup intake_chain;
extern pros::MotorGroup intake_stage1;

extern pros::MotorGroup lady_brown_arm ;

extern pros::adi::DigitalOut pneumatic_mogo_grabber;
// extension arm to move corner rings
extern pros::adi::DigitalOut pneumatic_robot_extension;





/**
 * =-
 * SENSORS 
 * =-
 */
extern pros::Imu imu;

extern pros::Rotation rotation_horizontal ;
extern pros::Rotation rotation_vertical ;





extern pros::Rotation rotation_arm;
extern pros::Vision vision_sensor;
extern pros::Distance distance_sensor;
/**
 * =-
 * SENSORS END 
 * =-
 */



extern pros::MotorGroup right_motors;   // left motors on ports 1, 2, 3
extern pros::MotorGroup left_motors; // right motors on ports 4, 5, 6





