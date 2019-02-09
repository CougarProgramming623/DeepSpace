
#pragma once

#include <frc/commands/Command.h>

namespace frc2019 {

class Drive : public frc::Command {
public:
	Drive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

}//frc2019