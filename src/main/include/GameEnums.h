
#pragma once

#include <string>

namespace frc2019 {

//For indexing the array in OI

#define ARM_MECHANISM_TYPE_COUNT 2
enum ArmMechanismType {
	MAIN_ARM = 0, WRIST = 1
};

#define CARGO_OR_HATCH_COUNT 2
enum CargoOrHatch {
	HATCH = 0, CARGO = 1
};

#define DIAL_POSITION_COUNT 6
enum DialPosition {
	ALL_IN, PICKUP, LOW, SHIP, MEDIUM, HIGH, INVALID
};

const constexpr char * const DIAL_POSITION_NAMES[] = {"all-in", "pickup", "low", "cargo-ship", "medium", "high"};

//Represents the what the sliders control

}//namespace

enum SliderStatus {
	DIAL_CONTROL, //The sliders do nothing
	MANUAL_PID_CONTROL, //The sliders map to position values [0, 1]
	VELOCITY_CONTROL //The sliders control the velocity [-1, 1]
};

enum TalonData {
	SENSOR_POSITION, SENSOR_VELOCITY, TARGET, ERROR, PERCENT_OUTPUT
};

enum DriveTalon {
	LEFT_FRONT, LEFT_REAR, RIGHT_FRONT, RIGHT_REAR
};

/*enum RocketHeight {
	LOW, MEDIUM, HIGH, SHIP, ALL_IN
};
*/