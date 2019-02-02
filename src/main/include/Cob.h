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
  static void PushValue(double x);
  

  //entries

  static nt::NetworkTableEntry x;
};
