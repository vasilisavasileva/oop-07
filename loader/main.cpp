#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include<string>

#include "sdl.h"
#include "imgui.h"
#include "figures.h"
#include "builder.h"
#include "loader.h"
#include "canvas.h"



	int main() {
		canvas canvas;
		sdl::renderer renderer("Editor");
		bool quit = false;
		std::unique_ptr<builder> active_builder = nullptr;
		const int32_t file_name_length = 128;
		char file_name[file_name_length] = "";
		int32_t remove_id = 0;
		while (!quit) {
			renderer.set_color(0, 0, 0);
			renderer.clear();

			sdl::event event;

			while (sdl::event::poll(event)) {
				sdl::quit_event quit_event;
				sdl::mouse_button_event mouse_button_event;
				if (event.extract(quit_event)) {
					quit = true;
					break;
				}
				else if (event.extract(mouse_button_event)) {
					if (active_builder && mouse_button_event.button() == sdl::mouse_button_event::left &&
						mouse_button_event.type() == sdl::mouse_button_event::down) {
						std::unique_ptr<figure> figure =
							active_builder->add_vertex(vertex{ mouse_button_event.x(), mouse_button_event.y() });
						if (figure) {
							canvas.add_figure(std::move(figure));
							active_builder = nullptr;
						}
					}
				}
			}

			for (const std::unique_ptr<figure>& figure : canvas.figures) {
				if(figure)
				figure->render(renderer);
			}

			ImGui::Begin("Menu");
			if (ImGui::Button("New canvas")) {
				canvas.figures.clear();
			}
			ImGui::InputText("File name", file_name, file_name_length - 1);
			if (ImGui::Button("Save")) {
				std::ofstream os(file_name);
				if (os) {
					for (const std::unique_ptr<figure>& figure : canvas.figures) {
						figure->save(os);
					}
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Load")) {
				std::ifstream is(file_name);
				if (is) {
					loader loader;
					canvas.figures = loader.load(is);
				}
			}
			if (ImGui::Button("Pentagon")) {
				active_builder = std::make_unique<pentagon_builder>();
			}
			if (ImGui::Button("Hexagon")) {
				active_builder = std::make_unique<hexagon_builder>();
			}
			if (ImGui::Button("Octagon")) {
				active_builder = std::make_unique<octagon_builder>();
			}
			ImGui::InputInt("Remove id", &remove_id);
			if (ImGui::Button("Remove")) {
				if(remove_id< canvas.figures.size())
				canvas.remove_figure(remove_id);
			}

			if (ImGui::Button("Undo")) {
				canvas.undo();
			}
			ImGui::End();

			renderer.present();
		}
	}

