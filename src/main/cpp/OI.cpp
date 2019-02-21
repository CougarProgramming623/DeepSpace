#include "OI.h"
#include "commands/VisionDrive.h"
	
	namespace frc2019 {
	
	OI::OI() {
		driverJoystick.reset(new frc::Joystick(0));
		buttonBoard.reset(new frc::Joystick(1));
	
		intakeButton.reset(new frc::JoystickButton(buttonBoard.get(), INTAKE_BUTTON));
		expungeButton.reset(new frc::JoystickButton(buttonBoard.get(), EXPUNGE_BUTTON));
		toggleSliderControl.reset(new frc::JoystickButton(buttonBoard.get(), TOGGLE_SLIDER_BUTTON));
		releaseShaftButton.reset(new frc::JoystickButton(buttonBoard.get(), RELEASE_SHAFT_BUTTON));
		releaseRampButton.reset(new frc::JoystickButton(buttonBoard.get(), RELEASE_RAMP_BUTTON)); //FIXME maybe i dunno
		togglePot.reset(new frc::JoystickButton(buttonBoard.get(), TOGGLE_POT_BUTTON));
	
		endgameOverride.reset(new frc::JoystickButton(buttonBoard.get(), ENDGAME_OVERRIDE_BUTTON));
		climb.reset(new frc::JoystickButton(buttonBoard.get(), CLIMB_BUTTON));
		potRezeroLift.reset(new frc::JoystickButton(buttonBoard.get(), POT_REZERO_BUTTON));

		releaseRampButton.get()->WhenPressed(new VisionDrive());
	}
	
	
	void OI::Update() {
	
	}

	bool OI::GetVision(){
		return buttonBoard->GetRawButton(9);
	}

	
	
	
	
	std::shared_ptr<frc::Joystick> OI::GetDriverJoystick() {
		return driverJoystick;
	}
	
	std::shared_ptr<frc::Joystick> OI::GetButtonBoard() {
		return buttonBoard;
	}
	
	}//namespace
