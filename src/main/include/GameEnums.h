
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