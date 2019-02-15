
#pragma once


enum DialStatus {
	ROCKET_HIGH, ROCKET_MED, ROCKET_LOW, GROUND_PICKUP, SECURE, CARGO_SHIP
};

//Represents the what the sliders control
enum SliderStatus {
	DIAL_CONTROL, MANUAL_PID_CONTROL, VELOCITY_CONTROL
};
