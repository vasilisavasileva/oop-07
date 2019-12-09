#pragma once
#include<fstream>
#include<iostream>
#include<vector>
#include<memory>
#include"figures.h"

struct loader {
private:
	std::string fig_name;
	std::array<vertex, 5> vertices_p;
	std::array<vertex, 6> vertices_h;
	std::array<vertex, 8> vertices_o;

public:
	~loader() = default;
	std::vector<std::unique_ptr<figure>> load(std::ifstream& is);
};