#include <cstdio>
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "lemlib/pid.hpp"
#include "pros/adi.h"
#include "pros/distance.hpp"
#include "pros/vision.hpp"


#include "config.hpp"



// double track_width = 12.375 * 2.54;
double track_width = 12.375;


// double t_wheel_diameter = lemlib::Omniwheel::NEW_2 * 2.54 - 0.24;
// double t_wheel_diameter = lemlib::Omniwheel::NEW_2 - (0.24 / 2.54);
double t_wheel_diameter = lemlib::Omniwheel::NEW_2;
// double wheel_diatemeter = lemlib::Omniwheel::NEW_325 * 2.54;
double wheel_diatemeter = lemlib::Omniwheel::NEW_325;


double horizontal_tw_offset = -1.0;
double vertical_tw_offset = 1.0;


pros::MotorGroup intake_chain ({14});
pros::MotorGroup intake_stage1({13});

pros::MotorGroup lady_brown_arm ({-15});

pros::adi::DigitalOut pneumatic_mogo_grabber('B', LOW);
// extension arm to move corner rings
pros::adi::DigitalOut pneumatic_robot_extension('D', LOW);

pros::MotorGroup right_motors({-5, -7, 8}, pros::MotorGearset::blue);   // left motors on ports 1, 2, 3
pros::MotorGroup left_motors({19, -17, 16}, pros::MotorGearset::blue); // right motors on ports 4, 5, 6



/**
 * =-
 * SENSORS 
 * =-
 */
pros::Imu imu(4);

// pros::Rotation rotation_horizontal (9);
pros::Rotation rotation_vertical (9);


// lemlib::TrackingWheel tw_horizontal(&rotation_horizontal, t_wheel_diameter, horizontal_tw_offset);
lemlib::TrackingWheel tw_vertical(&rotation_vertical, t_wheel_diameter - 0.1, vertical_tw_offset);

lemlib::TrackingWheel tw_left_motors(&left_motors, lemlib::Omniwheel::NEW_325 + 0.06, -6.2125, 450);
lemlib::TrackingWheel tw_right_motors(&right_motors, lemlib::Omniwheel::NEW_325 + 0.06, 6.2125, 450);


// lemlib::OdomSensors sensors(&tw_vertical, nullptr, &tw_horizontal, nullptr, &imu);
lemlib::OdomSensors sensors(&tw_vertical, nullptr, nullptr, nullptr, &imu);
// lemlib::OdomSensors sensors(&tw_left_motors, &tw_right_motors, &tw_horizontal, nullptr, &imu);




pros::Rotation rotation_arm(3);
pros::Optical optical_sensor (17);
pros::Distance distance_sensor (18);
/**
 * =-
 * SENSORS END 
 * =-
 */

lemlib::Drivetrain drivetrain(&left_motors, &right_motors, track_width, wheel_diatemeter, 450, 2);


lemlib::ControllerSettings lateral_controller(10,  // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              6,   // derivative gain (kD)
                                              0,   // anti windup
                                              1, // * 2.54   // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3,   // large error range, in inches
                                              200, // large error range timeout, in milliseconds
                                              40   // maximum acceleration (slew)
);
lemlib::ControllerSettings angular_controller(2,   // proportional gain (kP)
                                              0,   // integral gain (kI)
                                              10.8,  // derivative gain (kD)
                                              0,   // anti windup
                                              3,   // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              6,   // large error range, in degrees
                                              200, // large error range timeout, in milliseconds
                                              0    // maximum acceleration (slew)
);




lemlib::ExpoDriveCurve steer_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);


lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors, &throttle_curve, &steer_curve);
pros::Controller master(pros::E_CONTROLLER_MASTER);



