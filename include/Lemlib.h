#include "pros/misc.hpp"
#include "lemlib/api.hpp"
#include "pros/motors.h"
#include "pros/rotation.hpp"

pros::Motor front_left_motor(-1, pros::E_MOTOR_GEARSET_06); // left_motor_group
pros::Motor middle_left_motor(-2, pros::E_MOTOR_GEARSET_06); // left_motor_group
pros::Motor back_left_motor(-3, pros::E_MOTOR_GEARSET_06); // left_motor_group
pros::Motor front_right_motor(4, pros::E_MOTOR_GEARSET_06); // right_motor_group
pros::Motor middle_right_motor(5, pros::E_MOTOR_GEARSET_06); // right_motor_group
pros::Motor back_right_motor(6, pros::E_MOTOR_GEARSET_06); // right_motor_group

// left motor group
pros::MotorGroup left_motor_group({ front_left_motor, middle_left_motor, back_left_motor });
// right motor group
pros::MotorGroup right_motor_group({ front_right_motor, middle_right_motor, back_right_motor });

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(10);
// horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(20);
// vertical tracking wheel encoder
pros::Rotation vertical_encoder(21);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);