#include <vector>
#include <fstream>
#include <iostream>
#include <memory>


#include"loader.h"
#include"figures.h"

	
std::vector<std::unique_ptr<figure>> loader::load(std::ifstream & is) {
		std::vector<std::unique_ptr<figure>> figures;
		while (is >> fig_name) {
			if (fig_name == "pentagon") {
				for (int i = 0; i < 5; i++) {
					is >> vertices_p[i].x >> vertices_p[i].y;
				}
				figures.emplace_back(std::make_unique<pentagon>(vertices_p));
			}
			else if (fig_name == "hexagon") {
				for (int i = 0; i < 6; i++) {
					is >> vertices_h[i].x >> vertices_h[i].y;
				}
				figures.emplace_back(std::make_unique<hexagon>(vertices_h));
			}
			else if (fig_name == "octagon") {
				for (int i = 0; i < 8; i++) {
					is >> vertices_o[i].x >> vertices_o[i].y;
				}
				figures.emplace_back(std::make_unique<octagon>(vertices_o));
			}
		}
		return figures;
	}