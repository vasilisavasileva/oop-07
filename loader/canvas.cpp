
#include<stack>
#include<vector>
#include<memory>
#include<stdio.h>
#include"canvas.h"
#include"figures.h"
#include"commands.h"

	/*canvas::canvas(std::vector<std::unique_ptr<figure>> figures_, std::stack<std::unique_ptr<command>> commands_) {
		figures = std::move(figures_);
		commands = std::move(commands_);
	}*/

	void  canvas::add_figure(std::unique_ptr<figure> fig) {
		figures.push_back(std::move(fig));
		commands.push(std::make_unique<add_command>(add_command(this)));
	}
	
	void canvas::remove_figure(int id) {
		commands.push(std::make_unique<remove_command>(remove_command(this, id, std::move(figures[id]))));
	}

	void canvas::undo() {
		if (commands.size()) {
			commands.top()->undo();
			commands.pop();
		}
	}
