// PLOG library
#include <plog/Log.h>

#ifdef _WIN32
#define _fileno(F) ((F)->_file)
#endif
#include <plog/Appenders/ConsoleAppender.h>

// Standard C++ library
#include <iostream>

// SFML library
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GridDrawer.h"
#include "Templates.hpp"

#include <duktape.h>

int main() {
	// Initialize logging library for both text and console logging
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);

	LOG_INFO << "Application started";
	// Main code begins here

	duk_context *ctx = duk_create_heap_default();
	duk_eval_string(ctx, "1+2");
	printf("1+2=%d\n", (int) duk_get_int(ctx, -1));
	duk_destroy_heap(ctx);

	sf::Texture gridTexture;
	if (!gridTexture.loadFromFile("imgs/grid.png")) {
		LOGE << "Texture file not loaded";
		return 0;
	}
	gridTexture.setSmooth(true);

	Game::GridDrawer grid(gridTexture, sf::Vector2u(16, 16));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Viper Steel",
			sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	sf::Vector2f cameraSpeed;

	while (window.isOpen() == true) {
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::Closed) {
				window.close();
			}
			if (windowEvent.type == sf::Event::MouseMoved) {

				sf::Vector2i mm = sf::Mouse::getPosition(window);
				sf::Vector2u windowSize = window.getSize();

				if (withinDelta(mm.x, 0, 32)) {
					cameraSpeed.x = -1;
				} else if (withinDelta(mm.x, windowSize.x, 32)) {
					cameraSpeed.x = 1;
				} else {
					cameraSpeed.x = 0;
				}

				if (withinDelta(mm.y, 0, 32)) {
					cameraSpeed.y = -1;
				} else if (withinDelta(mm.y, windowSize.y, 32)) {
					cameraSpeed.y = 1;
				} else {
					cameraSpeed.y = 0;
				}
			}
			if (windowEvent.type == sf::Event::MouseWheelScrolled) {
				sf::View newView = window.getView();
				sf::Vector2f size = newView.getSize();
				float delta = windowEvent.mouseWheelScroll.delta;

				if ((newView.getSize().x > 320 && sgn(delta) == -1)
						|| sgn(delta) != -1) {

					int w, h;
					w = size.x / gcd(size.x, size.y) * 10;
					h = size.y / gcd(size.x, size.y) * 10;

					newView.setSize(size.x + w * sgn(delta),
							size.y + h * sgn(delta));

					window.setView(newView);
				}
			}
		}

		sf::View newView = window.getView();
		newView.move(cameraSpeed * 4.f);
		window.setView(newView);

		window.clear();
		window.draw(grid);
		window.display();
	}

	// Main code ends here
	LOG_INFO << "Application shuting down";
	return 0;
}
