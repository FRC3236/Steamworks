#ifndef EnableCompressor_H
#define EnableCompressor_H

#include "../CommandBase.h"

class EnableCompressor : public CommandBase {
public:
	EnableCompressor();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // EnableCompressor_H
