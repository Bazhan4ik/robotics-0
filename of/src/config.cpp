#include "main.h"


double track_width = 12.375;


double t_wheel_diameter = 2.125 - 0.1;
double wheel_diatemeter = 325;



pros::MotorGroup intake_chain ({8});
pros::MotorGroup intake_stage1({20});

pros::MotorGroup lady_brown_arm ({9});

pros::adi::DigitalOut pneumatic_mogo_grabber('B', LOW);
// extension arm to move corner rings
pros::adi::DigitalOut pneumatic_robot_extension('D', LOW);





/**
 * =-
 * SENSORS 
 * =-
 */
pros::Imu imu(3);

pros::Rotation rotation_horizontal (9);
pros::Rotation rotation_vertical (-16);





pros::Rotation rotation_arm(2);
pros::Vision vision_sensor (14);
pros::Distance distance_sensor (15);
/**
 * =-
 * SENSORS END 
 * =-
 */



pros::MotorGroup right_motors({12, -13, -14}, pros::MotorGearset::blue);   // left motors on ports 1, 2, 3
pros::MotorGroup left_motors({-17, 18, 19}, pros::MotorGearset::blue); // right motors on ports 4, 5, 6





