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
//MEMBER DECLARATIONS:
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

frc::Preferences* VisionDrive::prefs;

centerX_Source VisionDrive::xSource;
width_Source VisionDrive::ySource;

xOutput VisionDrive::xOut;
yOutput VisionDrive::yOut;
zOutput VisionDrive::zOut;

double VisionDrive::targetWidth;

//***********DUMMY CLASSES FOR PID:***********

//Fake PIDSource classes
double centerX_Source::PIDGet(){
  if(VisionDrive::correctIndex == -1)
    return 0;
  return -(VisionDrive::getCenterX() - 480) / (480);
}

double width_Source::PIDGet(){
  if(VisionDrive::correctIndex == -1)
    return 0;
  return -(VisionDrive::targetWidth - VisionDrive::getWidth())/VisionDrive::targetWidth; 
}

//fake PIDOutput classes
void xOutput::PIDWrite(double output){
  VisionDrive::xPower = output;
}
void yOutput::PIDWrite(double output){
  VisionDrive::yPower = output;
}

void zOutput::PIDWrite(double output){
  VisionDrive::zPower = -output;
}
//***********************************

//***********VISION DRIVE:***********

VisionDrive::VisionDrive() : frc::Command() {
  Requires(Robot::driveTrain.get());
  visionTable = start_networkTable();
  
  DriverStation::ReportError("Enabled");
  xPower = zPower = yPower = 0;
  correctIndex = 0;

  //Preferences Table + x, y, z PID default values
  prefs = Preferences::GetInstance();
  xP = prefs->GetDouble("xP", .7);
  xI = prefs->GetDouble("xI", 0.0);
  xD = prefs->GetDouble("xD", .4);
  yP = prefs->GetDouble("yP", .8); 
  yI = prefs->GetDouble("yI", 0.0); 
  yD = prefs->GetDouble("yD", .4); 
  zP = prefs->GetDouble("zP", 0.02);
  zI = prefs->GetDouble("zI", 0.0);
  zD = prefs->GetDouble("zD", 0.0175);

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

//startup the command; create PIDs and PID settings
void VisionDrive::Initialize() {
  correctIndex = -1;  
  targetWidth = 40;

  xPID = new frc::PIDController(xP, xI, xD, &xSource, &xOut);
  yPID = new frc::PIDController(yP, yI, yD, &ySource, &yOut);
  zPID = new frc::PIDController(zP, zI, zD, Robot::navx.get(), &zOut);

  SetTimeout(5); 
  xPID->SetInputRange(-1.0f, 1.0f);
  yPID->SetInputRange(-1.0f, 1.0f);
  zPID->SetInputRange(-180.0f, 180.0f);

  xPID->SetOutputRange(-1.0, 1.0);
  yPID->SetOutputRange(-1.0, 1.0);
  zPID->SetOutputRange(-1.0, 1.0);

  xPID->SetPercentTolerance(2.0f);
  yPID->SetPercentTolerance(1.5f);
  zPID->SetAbsoluteTolerance(1.0f);

  xPID->SetSetpoint(0.0f);
  yPID->SetSetpoint(0.0f);
  zPID->SetSetpoint(getClosestTargetAngle());

  xPID->SetContinuous(false);
  yPID->SetContinuous(false);
  zPID->SetContinuous(true);

  findLeftSignature();
  //Only proceed if signature picks up a target
  if(correctIndex != -1){
    xPID->Enable();
    yPID->Enable();
    zPID->Enable();
  }

}

//Drive the robot according to PID output
void VisionDrive::Execute() {
  findLeftSignature();
  DriverStation::ReportError("xPower:   " + std::to_string(xPower));
  DriverStation::ReportError("   yPower:      " + std::to_string(yPower));
  DriverStation::ReportError("      zPower:         " + std::to_string(zPower));
  Robot::driveTrain->CartesianDrive(yPower, zPower, xPower, 0);
}
//Finish if all 3 PIDs are on target, if no target found, or if robot reaches timeout
bool VisionDrive::IsFinished() { 
  return correctIndex == -1 || 
  (xPID->OnTarget() && yPID->OnTarget() && zPID->OnTarget()) ||
  IsTimedOut() ||
  !frc2019::Robot::oi->IsVisionActive();
}

//Disables PID at the end of the command
void VisionDrive::End() {
  DriverStation::ReportError("PID Disabled");
  xPID->Disable();
  yPID->Disable();
  zPID->Disable();
}

void VisionDrive::Interrupted() {}

//returns the network table
std::shared_ptr<nt::NetworkTable> VisionDrive::start_networkTable(){
  auto inst =  nt::NetworkTableInstance::GetDefault();
  return inst.GetTable("vision");
}

//finds the closes left signature to the robot
void VisionDrive::findLeftSignature(){
  std::vector<double> defaultVal{0};
  arrAngle = visionTable->GetNumberArray("angle", defaultVal); //array of angles
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); //array of the center X positions of contours
  double pixelsToCenter = 480.0; //reference point to X
  for(int i = 0; i < arrAngle.size(); i++){ //cycle through all contours
    if(arrAngle[i] < -50.0 && abs(arrCenterX[i] - 480.0) < pixelsToCenter){ //if contour is a left contour and is closest left target to robot
      //set new best values for indexing and center distance
      correctIndex = i;
      pixelsToCenter = abs(arrCenterX[i] - 480.0);
    }
  }
  DriverStation::ReportError("correctIndex: " + std::to_string(correctIndex));
  //found no targets
  if(correctIndex == -1)
    DriverStation::ReportError("No left targets found");
}

//finds the center X value of left target closest to robot
double VisionDrive::getCenterX() {
  std::vector<double> defaultVal{0};
  arrCenterX = visionTable->GetNumberArray("centerX", defaultVal); 
  return arrCenterX[VisionDrive::correctIndex];
}

//finds the width value of left target closest to robot
double VisionDrive::getWidth(){
  std::vector<double> defaultVal{0};
  arrWidth = visionTable->GetNumberArray("width", defaultVal); 
  return arrWidth[VisionDrive::correctIndex];
}

double VisionDrive::getClosestTargetAngle(){
  double targets[] = {0.0, 90.0, -90.0, 30.0, -30.0, 150.0, -150.0};
  int min = 0;
  double currentHeading = Robot::navx->GetYaw();
  double minError = abs(currentHeading - targets[0]);
  for(int i = 1; i < 7; i++){
    if(abs(currentHeading - targets[i]) < minError){
      min = i;
      minError = abs(currentHeading - targets[i]);
    }
  }
  DriverStation::ReportError("Target Angle:" + std::to_string(targets[min]));
  return targets[min];
}

}//namespace