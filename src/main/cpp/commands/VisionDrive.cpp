/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionDrive.h"
#include "Robot.h"
#include "math.h"

#include "AnalogGyro.h"

namespace frc2019 {
VisionDrive::VisionDrive() : frc::Command(), frc::PIDOutput() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::driveTrain.get());
  visionTable = start_networkTable();
  
  DriverStation::ReportError("Enabled");
  xPower = zPower = yPower = 0;
  correctIndex = 0;
}

class VisionDrive::geoffrey {
  double PIDGet(){
    return arrCenterX[correctIndex];
  }
  
};
// Called just before this Command runs the first time
void VisionDrive::Initialize() {
  std::vector<double> defaultVal{0};
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
  arrAngle = visionTable->GetNumberArray("angle", defaultVal); 
  arrWidth = visionTable->GetNumberArray("width", defaultVal);
  arrHeight = visionTable->GetNumberArray("height", defaultVal);
  geoffrey geoff;
  geoff.PIDGet();
  turnController = new frc::PIDController(0.05f, 0.0f, 0.045f, Robot::navx, this);
  rotationRate = 0.0;
  SetTimeout(2);
  turnController->SetInputRange(-180.0f, 180.0f);
  turnController->SetOutputRange(-1.0, 1.0);
  turnController->SetAbsoluteTolerance(1.0f);
  turnController->SetSetpoint(90.0f);
  turnController->SetContinuous(true);
  turnController->Enable();
}



// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {
  somethingWrong();
  getXPower();
  getZPower();
  getYPower();
  Robot::driveTrain->FODDrive(0, xPower/1.5, zPower/1.5, 0);

  //Robot::driveTrain->FODDrive(0,0,rotationRate, Robot::navx->GetYaw());
  DriverStation::ReportError("Rotation Rate: " + std::to_string(rotationRate));
  DriverStation::ReportError("Current Angle: " + std::to_string(Robot::navx->GetYaw()));
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() { return xPower == 0 && zPower == 0 && !somethingWrong(); }

// Called once after isFinished returns true
void VisionDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionDrive::Interrupted() {}

std::shared_ptr<nt::NetworkTable> VisionDrive::start_networkTable(){
  auto inst =  nt::NetworkTableInstance::GetDefault();
  return inst.GetTable("vision");
}

bool VisionDrive::somethingWrong(){
  while(!arrAngle[correctIndex] > -100 && !arrAngle[correctIndex] < -50){
    correctIndex++;
    if(correctIndex > arrAngle.size()){
      DriverStation::ReportError("no left targets found");
      return true;
      correctIndex--;
    }
  }
  return false;
}

void VisionDrive::getXPower() {
  double leftCenter = arrCenterX[correctIndex];
  
	DriverStation::ReportError("CenterX is :" + std::to_string(arrCenterX[correctIndex]));
  xPower = double(leftCenter - 960/2)/(960/2);
	if(abs(xPower) < 0.03)
    xPower = 0;
  else if (xPower > 0)
    xPower += .3;
  else
    xPower -= .3;
}

void VisionDrive::getYPower(){
  
}

void VisionDrive::getZPower(){
  float angle = Robot::navx->GetYaw();
  zPower = (-angle)/90;
  if(abs(zPower) < 0.05)
    zPower = 0;
  else if (zPower > 0)
    zPower += .25;
  else
    zPower -= .25;
}

void VisionDrive::PIDWrite(double output) {
  rotationRate = output;
  DriverStation::ReportError("Output:" + std::to_string(output));
}
}//namespace