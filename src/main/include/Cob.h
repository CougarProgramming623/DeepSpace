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
#include "CobConstants.h"

#include <string>
#include <map>

namespace frc2019 {
class Cob {
 public:
  static std::shared_ptr<NetworkTable> table;
  Cob();
  static void InitBoard();

  template<typename T>
  static void PushValue(std::string str,T t);

// private:
  static std::map<std::string,nt::NetworkTableEntry> map;
  private:
    static void InitValue(std::string str);
};


template<>
inline void Cob::PushValue<double>(std::string str, double t){
  InitValue(str);
  map.at(str).SetDouble(t);
}

template<>
inline void Cob::PushValue<float>(std::string str, float t){
  Cob::PushValue(str,(double)t);
}

template<>
inline void Cob::PushValue<bool>(std::string str, bool t){
  InitValue(str);
  map.at(str).SetBoolean(t);
}

template<>
inline void Cob::PushValue<int>(std::string str, int t){
  Cob::PushValue(str,(double)t);
}

template<>
inline void Cob::PushValue<std::string>(std::string str, std::string val) {
  InitValue(str);
  map.at(str).SetString(val);
}
}


