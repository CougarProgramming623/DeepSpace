
#pragma once

#include <string>

namespace frc2019 {

//For indexing the array in OI

#define ARM_MECHANISM_TYPE_COUNT 2
enum ArmMechanismType {
	MAIN_ARM, WRIST
};

//Represents the what the sliders control
enum SliderStatus {
	DIAL_CONTROL, MANUAL_PID_CONTROL, VELOCITY_CONTROL
};

enum TalonData {
	SENSOR_POSITION, SENSOR_VELOCITY, TARGET, ERROR, PERCENT_OUTPUT
};

enum DriveTalon {
	LEFT_FRONT, LEFT_REAR, RIGHT_FRONT, RIGHT_REAR
};

enum RocketHeight {
	LOW_HATCH, MEDIUM_HATCH, HIGH_HATCH, LOW_CARGO, MEDIUM_CARGO, HIGH_CARGO
};