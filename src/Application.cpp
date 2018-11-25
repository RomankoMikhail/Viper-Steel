#include "Application.h"

#include "GlobalObjects.h"
#include "JSMethods.h"

namespace Game
{

void Application::run()
{
	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}

		m_window.clear();
		m_window.draw(*ships[101].get());
		m_window.display();
	}
}

Application::Application(int argc, char* argv[])
{
	LOG_INFO << "---====== Starting up =======---";
	for (int i = 0; i < argc; i++)
	{
		m_args.push_back(argv[i]);
	}

	m_window.create(sf::VideoMode(640, 480), "Viper Steel");

	m_window.setVerticalSyncEnabled(true);
}

void Application::update()
{

}

Application::~Application()
{
	LOG_INFO << "---====== Shutting down =======---";
}

} /* namespace game */
