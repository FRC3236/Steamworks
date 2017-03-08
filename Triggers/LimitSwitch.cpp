#include "LimitSwitch.h"

LimitSwitch::LimitSwitch() {
}

bool LimitSwitch::Get() const {
	return CommandBase::gearsystem->LimitSwitch->Get();
}

