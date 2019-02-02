/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once

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
    y = table->GetEntry("location/y")
    rotation = table->GetEntry("location/rotation")
    mainArmRotation = table->GetEntry("arm/main-arm/rotation")
    wristRotation = table->GetEntry("arm/wrist/rotation")
    wristVacuum = table->GetEntry("arm/wrist/vacuum")
    isSandstorm = table->GetEntry("robot/is-sandstorm")
    isTeleop = table->GetEntry("robot/is-teleop")
    isEnabled = table->GetEntry("robot/is-enabled")
    timeLeft = table->GetEntry("fms/time-left")
    isRed = table->GetEntry("fms/is-red")
}

void Cob::PushX(double x){
    this.x.SetDouble(x);
}
void Cob::PushY(double y){
    this.y.SetDouble(y);
}
void Cob::PushRotation(double rotation){
    this.rotation.SetDouble(rotation);    
}
void Cob::PushMainArmRotation(double rotation){
    this.mainArmRotation.SetDouble(rotation);
}
void Cob::PushWristRotation(double rotation){
    this.wristRotation.SetDouble(rotation);
}
void Cob::PushWristVacuum(bool vacuum){
    this.wristVacuum.SetBool(vacuum);
}
void Cob::PushIsSandstorm(bool isSandstorm){
    this.isSandstorm.SetBool(isSandstorm);
}
void Cob::PushIsTeleop(bool isTeleop){
    this.isTeleop.SetBool(isTeleop);
}
void Cob::PushIsEnabled(bool isEnabled){
    this.isEnabled.SetBool(isEnabled);
}
void Cob::PushTimeLeft(double timeLeft){
    this.timeLeft.SetDouble(timeLeft);
}
void Cob::PushAlianceColor(bool isRed){
    this.isRed.setDouble(isRed);
}