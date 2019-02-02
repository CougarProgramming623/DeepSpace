/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "Robot.h"

class Cob {
 public:
  static std::shared_ptr<NetworkTable> table;
  Cob();
  static void InitBoard();

  //set values
  static void PushX(double x);
  static void PushY(double y);
  static void PushRotation(double rotation);
  static void PushMainArmRotation(double rotation);
  static void PushWristRotation(double rotation);
  static void PushWristVacuum(bool isOn);
  static void PushIsSandstorm(bool isSandstorm);
  static void PushIsTeleop(bool isTeleop);
  static void PushIsEnabled(bool isEnabled);
  static void PushTimeLeft(double timeLeft);
  static void PushAlianceColor(bool isRed);

  //entries

  static nt::NetworkTableEntry x;
  static nt::NetworkTableEntry y;
  static nt::NetworkTableEntry rotation;
  static nt::NetworkTableEntry mainArmRotation;
  static nt::NetworkTableEntry wristRotation;
  static nt::NetworkTableEntry wristVacuum;
  static nt::NetworkTableEntry isSandstorm;
  static nt::NetworkTableEntry isTeleop;
  static nt::NetworkTableEntry isEnabled;
  static nt::NetworkTableEntry timeLeft;
  static nt::NetworkTableEntry isRed;
};
