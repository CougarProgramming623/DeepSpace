
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionDrive.h"
#include "Robot.h"
#include "math.h"

namespace frc2019 {
std::vector<double> VisionDrive::arrCenterX;
std::vector<double> VisionDrive::arrAngle; 
std::vector<double> VisionDrive::arrWidth;
std::vector<double> VisionDrive::arrHeight;
int VisionDrive::correctIndex;
volatile double VisionDrive::xPower;
volatile double VisionDrive::yPower;
volatile double VisionDrive::zPower;
std::shared_ptr<nt::NetworkTable> VisionDrive::visionTable;
frc::PIDController* VisionDrive::xRot;
frc::PIDController* VisionDrive::zRot;
geoffrey VisionDrive::geoff;
FakePIDOutput VisionDrive::rotOutput;



VisionDrive::VisionDrive() : frc::Command(), frc::PIDOutput() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::driveTrain.get());
  visionTable = start_networkTable();
  
  DriverStation::ReportError("Enabled");
  xPower = zPower = yPower = 0;
  correctIndex = 0;
}
FakePIDOutput::FakePIDOutput(VisionDrive& drive) : visionDrive(drive){
  
}

double geoffrey::PIDGet(){
  VisionDrive::getXPower();
  //DriverStation::ReportError("val:" + std::to_string(VisionDrive::getPower()));
  return -(VisionDrive::getPower() - 960/2) / (960 / 2);
}
double VisionDrive::getPower(){
  return xPower;
}

// Called just before this Command runs the first time
void VisionDrive::Initialize() {
  std::vector<double> defaultVal{0};
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
  arrAngle = visionTable->GetNumberArray("angle", defaultVal); 
  arrWidth = visionTable->GetNumberArray("width", defaultVal);
  arrHeight = visionTable->GetNumberArray("height", defaultVal);
  rotOutput = frc::FakePIDOutput(visionDrive);
  xRot = new frc::PIDController(.7f, 0.05f, 0.1f, &geoff, this);
  zRot = new frc::PIDController(.7f, 0.05f, 0.1f, Robot::navx, &rotOutput);
  xDisplacement = 0.0;
  rotationRate = 0.0;
  SetTimeout(5); 

  xRot->SetInputRange(-1.0f, 1.0f);
  xRot->SetOutputRange(-1.0, 1.0);
  xRot->SetPercentTolerance(1.0f);
  xRot->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
  xRot->SetSetpoint(0.0f);
  xRot->SetContinuous(false);
  xRot->Enable();

  zRot->SetInputRange(-180.0f, 180.0f);
  zRot->SetOutputRange(-1.0, 1.0);
  zRot->SetPercentTolerance(2.0f);
  zRot->SetSetpoint(0.0f);
  zRot->SetContinuous(true);
  zRot->Enable();

}



// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {
  //Robot::driveTrain->FODDrive(0, xPower/1.5, zPower/1.5, 0);
 // Robot::driveTrain->FODDrive(0, 0, rotationRate, 0);
  getXPower();

  Robot::driveTrain->FODDrive(0, xDisplacement, 0, Robot::navx->GetYaw());
  //DriverStation::ReportError("Rotation Rate: " + std::to_string(rotationRate));
  //DriverStation::ReportError("Current Angle: " + std::to_string(Robot::navx->GetYaw()));
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() { 
  //return xPower == 0 && zPower == 0 && !somethingWrong();
  if(xRot->OnTarget() || IsTimedOut())
    DriverStation::ReportError("is finished");
  return xRot->OnTarget() || IsTimedOut();
  }

// Called once after isFinished returns true
void VisionDrive::End() {
  DriverStation::ReportError("PID Disabled");
  xRot->Disable();
  zRot->Disable();
}

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
  std::vector<double> defaultVal{0};
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
  xPower = arrCenterX[correctIndex];
  
	//DriverStation::ReportError("CenterX is :" + std::to_string(arrCenterX[correctIndex]));
  /*xPower = double(leftCenter - 960/2)/(960/2);
	if(abs(xPower) < 0.03)
    xPower = 0;
  else if (xPower > 0)
    xPower += .3;
  else
    xPower -= .3;*/
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

void FakePIDOutput::PIDWrite(double output){
  visionDrive.rotationRate = output;
  DriverStation::ReportError("Rotation Rate Output: " + std::to_string(output));
}
void VisionDrive::PIDWrite(double output) {
  xDisplacement = output;
  DriverStation::ReportError("Output:" + std::to_string(output));
}
}//namespace
