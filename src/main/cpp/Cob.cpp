/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "Cob.h"

namespace frc2019 {
std::shared_ptr<nt::NetworkTable> Cob::table;
std::map<std::string,nt::NetworkTableEntry> Cob::map;

Cob::Cob() {
   //never contruct
}

void Cob::InitBoard() {
    auto inst = nt::NetworkTableInstance::GetDefault();
    table = inst.GetTable("cob");
}


void Cob::InitValue(std::string str){
  if(map.count(str)==0) {
    map[str] = table->GetEntry(str);
  }
}

double Cob::GetValue(std::string str){
	Cob::InitValue(str)
	return map[str].GetDouble(-1.0);
}

}//frc2019
