#pragma once
#include"sdl.h"
#include<iostream>
struct figure {
	virtual void render(const sdl::renderer& renderer) const = 0;
	virtual void save(std::ostream& os) const = 0;
	virtual ~figure() = default;
};

struct vertex {
	int32_t x, y;

};