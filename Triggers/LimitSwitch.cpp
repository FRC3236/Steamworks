 #include "LimitSwitch.h"
#include "../CommandBase.h"

using namespace frc;

LimitSwitch::LimitSwitch() {

}

bool LimitSwitch::Get() const {
	return CommandBase::gearsystem->LimitSwitch->Get();
}

