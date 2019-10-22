/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Turn.h"
#include "Robot.h"
#include "AHRS.h"

namespace frc2019 {
Turn::Turn(double angle, bool relative) : frc::Command("Turn") , frc::PIDOutput() {
	Requires(Robot::driveTrain.get()); //dependent on the Drivetrain subsystem
	rotateToAngleRate = 0.0;
	m_angle = angle + (relative ? Robot::navx.get()->GetAngle() : 0.0);
	//used Robot Preferences table to set P, I, and D values for the PID Controller
	prefs = frc::Preferences::GetInstance();
	kP = prefs->GetDouble("Turn kP", 0.051);
	kI = prefs->GetDouble("Turn kI", 0.0);
	kD = prefs->GetDouble("Turn kD", 0.022);
	prefs->PutDouble("Turn kP", kP);
	prefs->PutDouble("Turn kI", kI);
	prefs->PutDouble("Turn kD", kD);
	SetTimeout(2); //sets how long the command is allowed to run for
} //Turn()

void Turn::Initialize() {
	turnController = new PIDController(kP, kI, kD, Robot::navx.get(), this); //initializes a PIDController with a kP, kI, kD, PIDSource, and PIDOuput
	turnController->SetInputRange(-180.0f, 180.0f); //sets input range to an angle
	turnController->SetOutputRange(-1.0, 1.0); //sets output range to a motor power
	turnController->SetAbsoluteTolerance(2.0f); //makes it so the robot ends at most 2 degrees of its target angle
	turnController->SetSetpoint(m_angle); //sets target angle
	turnController->SetContinuous(true);
	turnController->Enable();
} //Initialize()

void Turn::Execute() {
	frc::DriverStation::ReportError(std::to_string(Robot::navx->GetYaw()));
	Robot::driveTrain->CartesianDrive(0, 0, rotateToAngleRate / 2, Robot::navx.get()->GetYaw()); //rotate the robot
} //Execute()

bool Turn::IsFinished() { 
	return IsTimedOut(); //command ends when timeout is reached
} //IsFinished()

void Turn::End() {
	DriverStation::ReportError("Finished turn");
} //End()

void Turn::Interrupted() {

} //Interrupted()

void Turn::PIDWrite(double output)
{
	rotateToAngleRate = output; //sets rotateToAngleRate to output from the PID loop running in the background
} //PIDWrite()
} //frc2019
