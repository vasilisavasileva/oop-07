#pragma once
#include<vector>
#include<stack>
#include<memory>
#include"figures.h"
#include"command.h"
struct canvas {
public:
	std::vector<std::unique_ptr<figure>> figures;
	std::stack<std::unique_ptr<command>> commands;

	void add_figure(std::unique_ptr<figure> fig);
	void remove_figure(int id);
	void undo();

};


