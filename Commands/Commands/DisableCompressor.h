#ifndef DisableCompressor_H
#define DisableCompressor_H

#include "../../CommandBase.h"

class DisableCompressor : public CommandBase {
public:
	DisableCompressor();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DisableCompressor_H
