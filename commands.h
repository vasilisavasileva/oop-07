#pragma once
#include"canvas.h"
#include"command.h"


struct add_command : command {
public:
	add_command();
	add_command(canvas* canvas_);
	void undo() override;

	canvas* canvas_p;
};

struct remove_command : command {
public:
	remove_command() {}
	void undo() override;
	remove_command(canvas* canvas_, int id_, std::unique_ptr<figure> figure_);

	std::unique_ptr<figure> fig;
	int id;
	canvas* canvas_p;
};