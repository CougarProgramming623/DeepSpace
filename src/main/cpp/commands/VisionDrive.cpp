
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionDrive.h"
#include "Robot.h"
#include "math.h"
#include "AHRS.h"

namespace frc2019 {
VisionDrive::VisionDrive() : frc::Command(), frc::PIDOutput() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::driveTrain.get());
  visionTable = start_networkTable();
  turnController = new frc::PIDController(0.05f, 0.0f, 0.045f, Robot::navx, this);
  rotationRate = 0.0; 
  SetTimeout(2);
  xPower = zPower = 0;
}

// Called just before this Command runs the first time
void VisionDrive::Initialize() {
    //Robot::navx->ZeroYaw();
  turnController->SetInputRange(-180.0f, 180.0f);
  turnController->SetOutputRange(-1.0, 1.0);
  turnController->SetAbsoluteTolerance(1.0f);
  turnController->SetSetpoint(90.0f);
  turnController->SetContinuous(true);
  turnController->Enable();
  DriverStation::ReportError("Enabled");
}

// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {
  getXPower();
  getZPower();
  Robot::driveTrain->FODDrive(0, xPower/2, zPower/2, 0);

  //Robot::driveTrain->FODDrive(0,0,rotationRate, Robot::navx->GetYaw());
  DriverStation::ReportError("Rotation Rate: " + std::to_string(rotationRate));
  DriverStation::ReportError("Current Angle: " + std::to_string(Robot::navx->GetYaw()));
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() { return xPower == 0 && zPower == 0; }

// Called once after isFinished returns true
void VisionDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionDrive::Interrupted() {}

std::shared_ptr<nt::NetworkTable> VisionDrive::start_networkTable(){
  auto inst =  nt::NetworkTableInstance::GetDefault();
  return inst.GetTable("vision");
}
/*
class VisionDrive::FakePIDSource{
  FakePIDSource::FakePIDSource(): frc::PIDSourceType(){
    fakePID = PIDSourceType::kDisplacement;
  }
  PIDSourceType FakePIdSource::GetPIDSourceType(){
    return PIDSourceType::kDisplacement;
  }
  double FakePIDSource::PIDGet(){
    return fakePID;
  }
  void FakePIDSource::setPIDSourceType(PIDSourceType pidSource){
    fakePID = pidSource;
  }
};
*/

void VisionDrive::getXPower() {
	//nt::NetworkTableEntry centerX = visionTable->GetEntry("centerX");
  //nt::NetworkTableEntry angle = visionTable->GetEntry("angle");
  std::vector<double> defaultVal{0};
  std::vector<double> arrX = visionTable->GetNumberArray("centerX", defaultVal); 
  std::vector<double> arrA = visionTable->GetNumberArray("angle", defaultVal); 
  int i = 0, leftCenter = 0;
  for(; i < arrX.size(); i++){
    if(arrA[i] > -100 && arrA[i] < -50)
      leftCenter = arrX[i];
  }
	DriverStation::ReportError("First CenterX is :" + std::to_string(arrX[0]) + " Second CenterX is :" + std::to_string(arrX[1]));
  DriverStation::ReportError("Located Left Center is" + std::to_string(arrX[i]));
  xPower = double(leftCenter - 960/2)/(960/2);
	if(abs(xPower) < 0.05)
    xPower = 0;
  else if (xPower > 0)
    xPower += .1;
  else
    xPower -= .1;
}

void VisionDrive::getZPower(){
  float angle = Robot::navx->GetYaw();
  zPower = (-angle)/90;
  if(abs(zPower) < 0.05)
    zPower = 0;
  else if (zPower > 0)
    zPower += .1;
  else
    zPower -= .1;
}

void VisionDrive::PIDWrite(double output) {
  rotationRate = output;
  DriverStation::ReportError("Output:" + std::to_string(output));
}
}//namespace
