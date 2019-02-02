/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Cob.h"

std::shared_ptr<NetworkTable> Cob::table;

nt::NetworkTableEntry Cob::x;
nt::NetworkTableEntry Cob::y;
nt::NetworkTableEntry Cob::rotation;
nt::NetworkTableEntry Cob::mainArmRotation;
nt::NetworkTableEntry Cob::wristRotation;
nt::NetworkTableEntry Cob::wristVacuum;
nt::NetworkTableEntry Cob::isSandstorm;
nt::NetworkTableEntry Cob::isTeleop;
nt::NetworkTableEntry Cob::isEnabled;
nt::NetworkTableEntry Cob::timeLeft;
nt::NetworkTableEntry Cob::isRed;

Cob::Cob() {
   //never contruct
}

void Cob::InitBoard(){
    auto inst = nt::NetworkTableInstance::GetDefault();
    table = inst.GetTable("cob");
    x = table->GetEntry("location/x");
    y = table->GetEntry("location/y");
    rotation = table->GetEntry("location/rotation");
    mainArmRotation = table->GetEntry("arm/main-arm/rotation");
    wristRotation = table->GetEntry("arm/wrist/rotation");
    wristVacuum = table->GetEntry("arm/wrist/vacuum");
    isSandstorm = table->GetEntry("robot/is-sandstorm");
    isTeleop = table->GetEntry("robot/is-teleop");
    isEnabled = table->GetEntry("robot/is-enabled");
    timeLeft = table->GetEntry("fms/time-left");
    isRed = table->GetEntry("fms/is-red");
}

void Cob::PushX(double x){
    Cob::x.SetDouble(x);
}
void Cob::PushY(double y){
    Cob::y.SetDouble(y);
}
void Cob::PushRotation(double rotation){
    Cob::rotation.SetDouble(rotation);    
}
void Cob::PushMainArmRotation(double rotation){
    Cob::mainArmRotation.SetDouble(rotation);
}
void Cob::PushWristRotation(double rotation){
    Cob::wristRotation.SetDouble(rotation);
}
void Cob::PushWristVacuum(bool vacuum){
    Cob::wristVacuum.SetBoolean(vacuum);
}
void Cob::PushIsSandstorm(bool isSandstorm){
    Cob::isSandstorm.SetBoolean(isSandstorm);
}
void Cob::PushIsTeleop(bool isTeleop){
    Cob::isTeleop.SetBoolean(isTeleop);
}
void Cob::PushIsEnabled(bool isEnabled){
    Cob::isEnabled.SetBoolean(isEnabled);
}
void Cob::PushTimeLeft(double timeLeft){
    Cob::timeLeft.SetDouble(timeLeft);
}
void Cob::PushAlianceColor(bool isRed){
    Cob::isRed.SetDouble(isRed);
}