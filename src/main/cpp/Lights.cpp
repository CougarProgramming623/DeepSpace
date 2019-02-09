/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Lights.h"
#include <frc/WPILib.h>

namespace frc2019 {

std::shared_ptr<nt::NetworkTable> Lights::lightsTable;
nt::NetworkTableEntry Lights::colorEntry;
Lights::Lights() {

}

void Lights::InitLights() {
    auto inst = nt::NetworkTableInstance::GetDefault();
    lightsTable = inst.GetTable("lights");
    colorEntry = lightsTable->GetEntry("color");
    PushAllianceColor(frc::DriverStation::GetInstance().GetAlliance());
}

void Lights::PushAllianceColor(frc::DriverStation::Alliance color) {
   if(color == frc::DriverStation::Alliance::kRed) {
       colorEntry.SetString("red");
   } else if (color == frc::DriverStation::Alliance::kBlue) {
       colorEntry.SetString("blue");
   } else {
       colorEntry.SetString("INVALID COLOR. CHECK CODE");
   }
}
}
