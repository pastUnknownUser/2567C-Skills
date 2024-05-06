#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

extern pros::Motor front_left_motor;
extern pros::Motor middle_left_motor;
extern pros::Motor back_left_motor;
extern pros::Motor front_right_motor;
extern pros::Motor middle_right_motor;
extern pros::Motor back_right_motor;

extern pros::Motor_Group left_motor_group;
extern pros::Motor_Group right_motor_group;

extern lemlib::Drivetrain Drivetrain;

extern pros::Imu imu;

extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;

extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;

extern lemlib::OdomSensors sensors;

extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

extern lemlib::Chassis chassis;
