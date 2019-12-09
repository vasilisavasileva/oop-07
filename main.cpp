#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include<string>

#include "sdl.h"
#include "imgui.h"

struct figure {
  virtual void render(const sdl::renderer& renderer) const = 0;
  virtual void save(std::ostream& os) const = 0;
  virtual ~figure() = default;

};

struct vertex {
  int32_t x, y;

};

struct pentagon : figure {
  pentagon(const std::array<vertex, 5>& vertices): vertices_(vertices) {}

  void render(const sdl::renderer& renderer) const override {
    renderer.set_color(255, 0, 0);
    for(int32_t i = 0; i < 5; ++i){
      renderer.draw_line(vertices_[i].x, vertices_[i].y,
          vertices_[(i + 1) % 5].x, vertices_[(i + 1) % 5].y);
    }
  }

  void save(std::ostream& os) const override {
    os << "pentagon\n";
    for(int32_t i = 0; i < 5; ++i){
      os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
    }
  }

private:
  std::array<vertex, 5> vertices_;

};

struct hexagon : figure {
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

private:
	std::array<vertex, 6> vertices_;

};

struct octagon : figure {
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

private:
	std::array<vertex, 8> vertices_;

};



struct loader {
private:
	std::string fig_name;
	std::array<vertex, 5> vertices_p;
	std::array<vertex, 6> vertices_h;
	std::array<vertex, 8> vertices_o;

public:
	~loader() = default;
	std::vector<std::unique_ptr<figure>> load(std::ifstream& is) {
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
	
	};

	struct builder {
		virtual std::unique_ptr<figure> add_vertex(const vertex& v) = 0;

		virtual ~builder() = default;

	};

	struct pentagon_builder : builder {
		std::unique_ptr<figure> add_vertex(const vertex& v) {
			vertices_[n_] = v;
			n_ += 1;
			if (n_ != 5) {
				return nullptr;
			}
			return std::make_unique<pentagon>(vertices_);
		}

	private:
		int32_t n_ = 0;
		std::array<vertex, 5> vertices_;

	};

	struct hexagon_builder : builder {
		std::unique_ptr<figure> add_vertex(const vertex& v) {
			vertices_[n_] = v;
			n_ += 1;
			if (n_ != 6) {
				return nullptr;
			}
			return std::make_unique<hexagon>(vertices_);
		}

	private:
		int32_t n_ = 0;
		std::array<vertex, 6> vertices_;

	};

	struct octagon_builder : builder {
		std::unique_ptr<figure> add_vertex(const vertex& v) {
			vertices_[n_] = v;
			n_ += 1;
			if (n_ != 8) {
				return nullptr;
			}
			return std::make_unique<octagon>(vertices_);
		}

	private:
		int32_t n_ = 0;
		std::array<vertex, 8> vertices_;

	};

	int main() {
		sdl::renderer renderer("Editor");
		bool quit = false;
		std::vector<std::unique_ptr<figure>> figures;
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
							figures.emplace_back(std::move(figure));
							active_builder = nullptr;
						}
					}
				}
			}

			for (const std::unique_ptr<figure>& figure : figures) {
				figure->render(renderer);
			}

			ImGui::Begin("Menu");
			if (ImGui::Button("New canvas")) {
				figures.clear();
			}
			ImGui::InputText("File name", file_name, file_name_length - 1);
			if (ImGui::Button("Save")) {
				std::ofstream os(file_name);
				if (os) {
					for (const std::unique_ptr<figure>& figure : figures) {
						figure->save(os);
					}
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Load")) {
				std::ifstream is(file_name);
				if (is) {
					loader loader;
					figures = loader.load(is);
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
				if(remove_id< figures.size())
				figures.erase(figures.begin() + remove_id);
			}
			ImGui::End();

			renderer.present();
		}
	}

