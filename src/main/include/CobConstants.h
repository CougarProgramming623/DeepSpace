#pragma once

#define COB_X "location/x"
#define COB_Y "location/y"
#define COB_ROTATION "location/rotation"
#define COB_X_VEL "location/xVel"
#define COB_Y_VEL "location/yVel"
#define COB_LEFT_DISTANCE "location/left-distance"
#define COB_RIGHT_DISTANCE "location/right-distance"
#define COB_MAIN_ARM_ROTATION "arm/main-arm/rotation"
#define COB_WRIST_ROTATION "arm/wrist/rotation"
#define COB_VACUUM "arm/wrist/vacuum"
#define COB_HATCH "arm/wrist/is-hatch"
#define COB_SANDSTORM "robot/is-sandstorm"
#define COB_TELEOP "robot/is-teleop"
#define COB_ENDGAME "robot/is-endgame"
#define COB_ENABLED "robot/is-enabled"
#define COB_ALLIANCE_COLOR "robot/alliance-color"
#define COB_FIELD_ORIENTED "robot/is-field-oriented"
#define COB_TIME "fms/time-left"
#define COB_RED "fms/is-red" 

#define COB_ARM_CARGO_ROCKET_HIGH "arm-position/rocket-high"
#define COB_ARM_CARGO_ROCKERT_MID "arm-position/rocket-mid"
#define COB_ARM_CARGO_ROCKET_LOW "arm-position/rocket-low"
#define COB_ARM_CARGO_GROUND "arm-position/cargo/ground"
#define COB_ARM_CARGO_SHIP "arm-position/cargo/ship"
#define COB_ARM_HATCH_LOW "arm-position/hatch/low"
#define COB_ARM_HATCH_MID "arm-position/hatch/mid"
#define COB_ARM_HATCH_HIGH  "arm-position/hatch/high"
#define COB_ARM_SECURE "arm-position/secure"
#define COB_ARM_ALLEYOOP "arm-position/alley-oop"


//wrist
#define COB_WRIST_CARGO_ROCKET_HIGH "wrist-position/rocket-high"
#define COB_WRIST_CARGO_ROCKET_MID "wrist-position/rocket-mid"
#define COB_WRIST_CARGO_ROCKET_LOW "wrist-position/rocket-low"
#define COB_WRIST_CARGO_GROUND "wrist-position/cargo/ground"
#define COB_WRIST_CARGO_SHIP "wrist-position/cargo/ship"
#define COB_WRIST_HATCH_LOW "wrist-position/hatch/low"
#define COB_WRIST_HATCH_MID "wrist-position/hatch/mid"
#define COB_WRIST_HATCH_HIGH "wrist-position/hatch/high"
#define COB_WRIST_SECURE "wrist-position/secure"
#define COB_WRIST_ALLEYOOP "wrist-position/alley-oop"

#define COB_FORK_PICKUP "fork/setpoints/floor-pickup"
#define COB_FORK_SCOOP "fork/setpoints/scoop"
#define COB_FORK_CARGO_HOLD "fork/setpoints/cargo-hold"
#define COB_FORK_VERTICAL "fork/setpoints/vertical"
#define COB_FORK_STOW "fork/setpoints/stow"

#define COB_PULL_ARM_SETPOINTS "pull-setpoints"
#define COB_SAVE_ARM_SETPOINTS "save-setpoints"

#define COB_PULL_FORK_SETPOINTS "fork/pull-setpoints"
#define COB_SAVE_FORK_SETPOINTS "fork/save-setpoints"

#define COB_ARM_OFFSET "arm-position/offset"
#define COB_WRIST_OFFSET "wrist-position/offset"
#define COB_FORK_OFFSET "fork/offset"

#define COB_IS_HOLDING "ak/is-pressed"

#define COB_SHUTDOWN_BEAGLEBONE "beaglebone/is-shutdown"


const std::string COB_DRIVE_P = "drive/p";
const std::string COB_DRIVE_I = "drive/i";
const std::string COB_DRIVE_D = "drive/d";
