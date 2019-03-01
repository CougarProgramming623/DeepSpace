
#pragma once

#include <string>

namespace frc2019 {

//For indexing the array in OI

#define ARM_MEKANISM_TYPE_COUNT 2
enum ArmMekanismType {
	MAIN_ARM, WRIST
};

#define CARGO_OR_HATCH_COUNT 2
enum CargoOrHatch {
	HATCH, CARGO
};

#define DIAL_POSITION_COUNT 7
enum DialPosition {
	HIGH, MEDIUM, LOW, PICKUP, CARGO_SHIP, SECURE, ALLEY_OOP
};

const constexpr char * const DIAL_POSITION_NAMES[] = {"high", "medium", "low", "ground", "ship", "secure", "alley-oop"};

//Represents the what the sliders control
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

}//namespace