/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/WPILib.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTableEntry.h>



namespace frc2019 {
class Lights {
 public:
  Lights();
  static void InitLights();
  static void PushAllianceColor(frc::DriverStation::Alliance color);
  static std::shared_ptr<nt::NetworkTable> lightsTable;
  static nt::NetworkTableEntry colorEntry;
};
}
