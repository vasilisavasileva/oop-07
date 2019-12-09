#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include<array>
#include"sdl.h"
#include"figure.h"



struct pentagon : figure {
private:
	std::array<vertex, 5> vertices_;
	public:
	pentagon(const std::array<vertex, 5>& vertices) : vertices_(vertices) {}
	void render(const sdl::renderer& renderer) const override {
		renderer.set_color(255, 0, 0);
		for (int32_t i = 0; i < 5; ++i) {
			renderer.draw_line(vertices_[i].x, vertices_[i].y,
				vertices_[(i + 1) % 5].x, vertices_[(i + 1) % 5].y);
		}
	}
	void save(std::ostream& os) const override {
		os << "pentagon\n";
		for (int32_t i = 0; i < 5; ++i) {
			os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
		}
	}
};

struct hexagon : figure {

private:
	std::array<vertex, 6> vertices_;
public:
	hexagon(const std::array<vertex, 6>& vertices) : vertices_(vertices) {}

	void render(const sdl::renderer& renderer) const override {
		renderer.set_color(255, 0, 0);
		for (int32_t i = 0; i < 6; ++i) {
			renderer.draw_line(vertices_[i].x, vertices_[i].y,
				vertices_[(i + 1) % 6].x, vertices_[(i + 1) % 6].y);
		}
	}

	void save(std::ostream& os) const override {
		os << "hexagon\n";
		for (int32_t i = 0; i < 6; ++i) {
			os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
		}
	}

};

struct octagon : figure {
private:
	std::array<vertex, 8> vertices_;
public:
	octagon(const std::array<vertex, 8>& vertices) : vertices_(vertices) {}
	void render(const sdl::renderer& renderer) const override {
		renderer.set_color(255, 0, 0);
		for (int32_t i = 0; i < 8; ++i) {
			renderer.draw_line(vertices_[i].x, vertices_[i].y,
				vertices_[(i + 1) % 8].x, vertices_[(i + 1) % 8].y);
		}
	}
	void save(std::ostream& os) const override {
		os << "octagon\n";
		for (int32_t i = 0; i < 8; ++i) {
			os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
		}
	}

};