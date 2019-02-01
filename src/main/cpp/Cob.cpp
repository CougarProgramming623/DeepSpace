/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Cob.h"

std::shared_ptr<NetworkTable> Cob::table;
nt::NetworkTableEntry Cob::x;

Cob::Cob() {
   //never contruct
}

void Cob::InitBoard(){
    auto inst = nt::NetworkTableInstance::GetDefault();
    table = inst.GetTable("cob");
    x = table->GetEntry("x");
}

void Cob::PushValue(double value){
    x.SetDouble(value);
    DriverStation::ReportWarning("Called Cob::Push Value");
}
