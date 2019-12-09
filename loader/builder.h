#pragma once
#include<fstream>
#include<iostream>
#include<vector>
#include<memory>
#include"figures.h"

struct builder {
	virtual std::unique_ptr<figure> add_vertex(const vertex& v) = 0;

	virtual ~builder() = default;

};

struct pentagon_builder : builder {
	std::unique_ptr<figure> add_vertex(const vertex& v);

private:
	int32_t n_ = 0;
	std::array<vertex, 5> vertices_;

};

struct hexagon_builder : builder {
	std::unique_ptr<figure> add_vertex(const vertex& v);

private:
	int32_t n_ = 0;
	std::array<vertex, 6> vertices_;

};

struct octagon_builder : builder {
	std::unique_ptr<figure> add_vertex(const vertex& v);

private:
	int32_t n_ = 0;
	std::array<vertex, 8> vertices_;

};
