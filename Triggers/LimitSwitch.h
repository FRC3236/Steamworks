#ifndef LimitSwitch_H
#define LimitSwitch_H

#include <Buttons/Trigger.h>

class LimitSwitch : public frc::Trigger {
public:
	LimitSwitch();
	bool Get() const;
};

#endif  // LimitSwitch_H