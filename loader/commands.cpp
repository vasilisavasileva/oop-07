#include"commands.h"
#include<memory>
#include"canvas.h"

add_command::add_command() {}
add_command::add_command(canvas* canvas_) {
	canvas_p = canvas_;
}

void add_command::undo() {
	(*canvas_p).figures.pop_back();
}

void remove_command::undo() {
	canvas_p->figures[id] = std::move(fig);
}

remove_command::remove_command(canvas* canvas_, int id_, std::unique_ptr<figure> figure_) {
	canvas_p = canvas_;
	fig = std::move(figure_);
	id = id_;
}