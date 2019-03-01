
#pragma once

//Represents the height we want to climb to
enum ClimbHeight {
	MEDIUM, HIGH
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