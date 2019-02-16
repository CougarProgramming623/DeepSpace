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
frc::PIDController* VisionDrive::xPID;
frc::PIDController* VisionDrive::yPID;
frc::PIDController* VisionDrive::zPID;
geoffrey VisionDrive::geoff;
jacques VisionDrive::jacque;
dummyOutput VisionDrive::zOutput;
dummierOutput VisionDrive::yOutput;
double VisionDrive::targetWidth;

double geoffrey::PIDGet(){
  //DriverStation::ReportError("val:" + std::to_string(VisionDrive::getPower()));
  return -(VisionDrive::getCenterX() - 960/2) / (960 / 2);
}
double jacques::PIDGet(){
  //change this for the Y - axis PID
  //DriverStation::ReportError("TargetWidth: " + std::to_string(VisionDrive::targetWidth));
  return -(VisionDrive::targetWidth - VisionDrive::getTargetWidth())/VisionDrive::targetWidth; 
}
void dummyOutput::PIDWrite(double output){
  VisionDrive::zPower = output;
}
void dummierOutput::PIDWrite(double output){
  //DriverStation::ReportError("yPower writing: "+std::to_string(output));
  VisionDrive::yPower = output;
}

VisionDrive::VisionDrive() : frc::Command(), frc::PIDOutput(){
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::driveTrain.get());
  visionTable = start_networkTable();
  
  DriverStation::ReportError("Enabled");
  xPower = zPower = yPower = 0;
  correctIndex = 0;
  prefs = Preferences::GetInstance();
  xP = prefs->GetDouble("xP", .03f);
  xI = prefs->GetDouble("xI", 0.002f);
  xD = prefs->GetDouble("xD", .03f);
  yP = prefs->GetDouble("yP", .03f); //not tuned
  yI = prefs->GetDouble("yI", 0.002f); //not tuned
  yD = prefs->GetDouble("yD", .03f); //not tuned
  zP = prefs->GetDouble("zP", 0.03f);
  zI = prefs->GetDouble("zI", 0.002f);
  zD = prefs->GetDouble("zD", 0.03f);

  prefs->PutDouble("xP", xP);
  prefs->PutDouble("xI", xI);
  prefs->PutDouble("xD", xD);
  prefs->PutDouble("yP", yP);
  prefs->PutDouble("yI", yI);
  prefs->PutDouble("yD", yD);
  prefs->PutDouble("zP", zP);
  prefs->PutDouble("zI", zI);
  prefs->PutDouble("zD", zD);
}


// Called just before this Command runs the first time
void VisionDrive::Initialize() {
  correctIndex = 0;
  std::vector<double> defaultVal;
  
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
  arrAngle = visionTable->GetNumberArray("angle", defaultVal); 
  arrWidth = visionTable->GetNumberArray("width", defaultVal);
  arrHeight = visionTable->GetNumberArray("height", defaultVal);

  DriverStation::ReportError("size:" + std::to_string(arrAngle.size()));

  xPID = new frc::PIDController(xP, xI, xD, &geoff, this);
  yPID = new frc::PIDController(yP, yI, yD, &jacque, &yOutput);
  zPID = new frc::PIDController(zP, zI, zD, Robot::navx, &zOutput);/*
  DriverStation::ReportError("xP: " + std::to_string(xP));
  DriverStation::ReportError("xI: " + std::to_string(xI));
  DriverStation::ReportError("xD: " + std::to_string(xD));
  DriverStation::ReportError("zP: " + std::to_string(zP));
  DriverStation::ReportError("zI: " + std::to_string(zI));
  DriverStation::ReportError("zD: " + std::to_string(zD));*/
  if(arrAngle[correctIndex] > -50)
    VisionDrive::targetWidth = 120.0;
  else VisionDrive::targetWidth = 50.0;

  rotationRate = 0.0;
  SetTimeout(5); 
  xPID->SetInputRange(-1.0f, 1.0f);
  yPID->SetInputRange(-1.0f, 1.0f);
  zPID->SetInputRange(-180.0f, 180.0f);

  xPID->SetOutputRange(-1.0, 1.0);
  yPID->SetOutputRange(-1.0, 1.0);
  zPID->SetOutputRange(-1.0, 1.0);

  xPID->SetPercentTolerance(2.0f);
  yPID->SetPercentTolerance(2.0f);
  zPID->SetAbsoluteTolerance(1.0f);

  xPID->SetSetpoint(0.0f);
  yPID->SetSetpoint(0.0f);
  zPID->SetSetpoint(0.0f);

  xPID->SetContinuous(false);
  yPID->SetContinuous(false);
  zPID->SetContinuous(true);
  if(!somethingWrong()){
    xPID->Enable();
    yPID->Enable();
    zPID->Enable();
  }
}



// Called repeatedly when this Command is scheduled to run
void VisionDrive::Execute() {
  //Robot::driveTrain->FODDrive(0, xPower/1.5, zPower/1.5, 0);
 // Robot::driveTrain->FODDrive(0, 0, rotationRate, 0);
  //getCenterX();
  //getZPower();



  Robot::driveTrain->RODrive(yPower,xPower,zPower);

  

  //DriverStation::ReportError("xPower: " + std::to_string(xPower));
  DriverStation::ReportError("yPower: " + std::to_string(yPower));
  //DriverStation::ReportError("zPower: " + std::to_string(zPower));

  //DriverStation::ReportError("xP: " + std::to_string(xP));
  //DriverStation::ReportError("xI: " + std::to_string(xI));
  //DriverStation::ReportError("xD: " + std::to_string(xD));
  //DriverStation::ReportError("zP: " + std::to_string(zP));
  //DriverStation::ReportError("zI: " + std::to_string(zI));
  //DriverStation::ReportError("zD: " + std::to_string(zD));
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() { 
  //return xPower == 0 && zPower == 0 && !somethingWrong();
  //if(xPID->OnTarget() && zPID->OnTarget() || IsTimedOut())
    //DriverStation::ReportError("is finished");
  //return xPID->OnTarget() && zPID->OnTarget() || IsTimedOut();
  return somethingWrong() || (xPID->OnTarget() && 
    //change this later when yPID works
    yPID->OnTarget() &&
    zPID->OnTarget()) || IsTimedOut() || !frc2019::Robot::oi->GetVision();
}

// Called once after isFinished returns true
void VisionDrive::End() {
  DriverStation::ReportError("PID Disabled");
  xPID->Disable();
  yPID->Disable();
  zPID->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionDrive::Interrupted() {}

std::shared_ptr<nt::NetworkTable> VisionDrive::start_networkTable(){
  auto inst =  nt::NetworkTableInstance::GetDefault();
  return inst.GetTable("vision");
}

bool VisionDrive::somethingWrong(){
  if (arrAngle.size() == 0)
    return true;
  while(correctIndex < arrAngle.size()){
    if(arrAngle[correctIndex] > -100 && arrAngle[correctIndex] < -50){
      return false;
    }
    correctIndex++;
  }
  DriverStation::ReportError("no left targets found");
  return true;
}


double VisionDrive::getCenterX() {
  std::vector<double> defaultVal{0};
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
 // DriverStation::ReportError("Width: " + std::to_string(arrCenterX[correctIndex]));
  return arrCenterX[correctIndex];
  
	//DriverStation::ReportError("CenterX is :" + std::to_string(arrCenterX[correctIndex]));
  /*
  xPower = double(leftCenter - 960/2)/(960/2);
	if(abs(xPower) < 0.03)
    xPower = 0;
  else if (xPower > 0)
    xPower += .3;
  else
    xPower -= .3;
    */
}

double VisionDrive::getTargetWidth(){
  std::vector<double> defaultVal{0};
  arrWidth = visionTable->GetNumberArray("width", defaultVal); 
  //DriverStation::ReportError("Width: " + std::to_string(arrWidth[correctIndex]));
  return arrWidth[correctIndex];
}

//never called lol
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
  xPower = output;
  //DriverStation::ReportError("Output:" + std::to_string(output));
}
}//namespace