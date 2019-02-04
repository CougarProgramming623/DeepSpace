/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionDrive.h"
#include "Math.h"
#include "networktables/NetworkTableInstance.h"
#include "Robot.h"
const double mid = 960/2.0;

namespace frc2019{
VisionDrive::VisionDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::driveTrain.get());
  visionTable = NetworkTable::GetTable("vision");
}

// Called just before this Command runs the first time
void VisionDrive::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
//get values
void VisionDrive::Execute() {
  nt::NetworkTableEntry centerX = visionTable->GetEntry("centerX");
	centerX.SetDoubleArray();

  if(arr.size() == 2){
    if(centerStraife(arr[0],arr[1]) > 10){
      Robot::driveTrain->fodDrive(-1,0,0,0);
    }
    else if (centerStraife(arr[0],arr[1]) < -10){
      Robot::driveTrain->fodDrive(1,0,0,0);
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDrive::IsFinished() {
  nt::NetworkTableEntry centerX = visionTable->GetEntry("centerX");
  centerX.SetDoubleArray();
  if(abs(centerStraife(arr[0],arr[1])) < 5) return true;

  return false; 
  }

// Called once after isFinished returns true
void VisionDrive::End() {
  Robot::driveTrain->fodDrive(0,0,0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionDrive::Interrupted() {}
double centerStraife(double leftContourCenterX, double rightContourCenterX){
  return (leftContourCenterX - mid) - (mid - rightContourCenterX);
}
}
