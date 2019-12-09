#include<fstream>
#include<iostream>
#include<vector>
#include<memory>
#include"builder.h"
#include"figures.h"

std::unique_ptr<figure> pentagon_builder::add_vertex(const vertex& v) {
		vertices_[n_] = v;
		n_ += 1;
		if (n_ != 5) {
			return nullptr;
		}
		return std::make_unique<pentagon>(vertices_);
}


std::unique_ptr<figure> hexagon_builder::add_vertex(const vertex& v) {
		vertices_[n_] = v;
		n_ += 1;
		if (n_ != 6) {
			return nullptr;
		}
		return std::make_unique<hexagon>(vertices_);
}


std::unique_ptr<figure> octagon_builder::add_vertex(const vertex& v) {
		vertices_[n_] = v;
		n_ += 1;
		if (n_ != 8) {
			return nullptr;
		}
		return std::make_unique<octagon>(vertices_);
}
