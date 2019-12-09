#pragma once
struct command {
public:
	virtual void undo() = 0;
};