
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
<<<<<<< HEAD
frc::PIDController* VisionDrive::xRot;
frc::PIDController* VisionDrive::zRot;
geoffrey VisionDrive::geoff;
FakePIDOutput VisionDrive::rotOutput;


=======
frc::PIDController* VisionDrive::xPID;
frc::PIDController* VisionDrive::zPID;
geoffrey VisionDrive::geoff;
dummyOutput VisionDrive::zOutput;

double geoffrey::PIDGet(){
  //DriverStation::ReportError("val:" + std::to_string(VisionDrive::getPower()));
  return -(VisionDrive::getCenterX() - 960/2) / (960 / 2);
}

void dummyOutput::PIDWrite(double output){
  VisionDrive::zPower = output;
}
>>>>>>> 6432a4025c5d4949a00fd10a9bd93a1f841c8876

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

<<<<<<< HEAD
double geoffrey::PIDGet(){
  VisionDrive::getXPower();
  //DriverStation::ReportError("val:" + std::to_string(VisionDrive::getPower()));
  return -(VisionDrive::getPower() - 960/2) / (960 / 2);
}
double VisionDrive::getPower(){
  return xPower;
}
=======
>>>>>>> 6432a4025c5d4949a00fd10a9bd93a1f841c8876

// Called just before this Command runs the first time
void VisionDrive::Initialize() {
  std::vector<double> defaultVal{0};
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
  arrAngle = visionTable->GetNumberArray("angle", defaultVal); 
  arrWidth = visionTable->GetNumberArray("width", defaultVal);
  arrHeight = visionTable->GetNumberArray("height", defaultVal);
<<<<<<< HEAD
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

=======
  xPID = new frc::PIDController(1.0f, 0.00f, .8f, &geoff, this);
  zPID = new frc::PIDController(.05, 0.005, .03, Robot::navx, &zOutput);
  rotationRate = 0.0;
  SetTimeout(5); 
  xPID->SetInputRange(-1.0f, 1.0f);
  zPID->SetInputRange(-180.0f, 180.0f);
  xPID->SetOutputRange(-1.0, 1.0);
  zPID->SetOutputRange(-1.0, 1.0);
  xPID->SetPercentTolerance(5.0f);
  xPID->SetPercentTolerance(5.0f);
  xPID->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
  xPID->SetSetpoint(0.0f);
  zPID->SetSetpoint(0.0f);
  xPID->SetContinuous(false);
  zPID->SetContinuous(true);
  xPID->Enable();
  zPID->Enable();
>>>>>>> 6432a4025c5d4949a00fd10a9bd93a1f841c8876
}



// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {
  //Robot::driveTrain->FODDrive(0, xPower/1.5, zPower/1.5, 0);
 // Robot::driveTrain->FODDrive(0, 0, rotationRate, 0);

<<<<<<< HEAD
  Robot::driveTrain->FODDrive(0, xDisplacement, 0, Robot::navx->GetYaw());
  //DriverStation::ReportError("Rotation Rate: " + std::to_string(rotationRate));
  //DriverStation::ReportError("Current Angle: " + std::to_string(Robot::navx->GetYaw()));
=======
  Robot::driveTrain->RODrive(0,xPower, zPower);
  DriverStation::ReportError("xPower: " + std::to_string(xPower));
  DriverStation::ReportError("zPower: " + std::to_string(zPower));
>>>>>>> 6432a4025c5d4949a00fd10a9bd93a1f841c8876
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() { 
  //return xPower == 0 && zPower == 0 && !somethingWrong();
<<<<<<< HEAD
  if(xRot->OnTarget() || IsTimedOut())
    DriverStation::ReportError("is finished");
  return xRot->OnTarget() || IsTimedOut();
=======
  //if(xPID->OnTarget() && zPID->OnTarget() || IsTimedOut())
    //DriverStation::ReportError("is finished");
  //return xPID->OnTarget() && zPID->OnTarget() || IsTimedOut();
  return xPID->OnTarget() || IsTimedOut();
>>>>>>> 6432a4025c5d4949a00fd10a9bd93a1f841c8876
  }

// Called once after isFinished returns true
void VisionDrive::End() {
  DriverStation::ReportError("PID Disabled");
<<<<<<< HEAD
  xRot->Disable();
  zRot->Disable();
=======
  xPID->Disable();
  zPID->Disable();
>>>>>>> 6432a4025c5d4949a00fd10a9bd93a1f841c8876
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


double VisionDrive::getCenterX() {
  std::vector<double> defaultVal{0};
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
  return arrCenterX[correctIndex];
  
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
<<<<<<< HEAD
  xDisplacement = output;
=======
  xPower = output;
>>>>>>> 6432a4025c5d4949a00fd10a9bd93a1f841c8876
  DriverStation::ReportError("Output:" + std::to_string(output));
}
}//namespace
