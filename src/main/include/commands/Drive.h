
#pragma once

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "AHRS.h"

namespace frc2019 {

class Drive : public frc::Command {
public:
	Drive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	void SetAlignDriver();
	void SetFODDriver();
private:
	double y, x, rot, angle;
};


}//frc2019