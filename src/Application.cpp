#include "Application.h"

namespace Game
{
namespace Core
{

int i = 0;

void Application::run()
{
	//sf::Thread updateThread(&Application::updateCycle, this);
	//updateThread.launch();
	sf::Clock clock;
	sf::Time timeSinceLastCycle;

	while (m_window.isOpen())
	{
		event();
		timeSinceLastCycle += clock.restart();
		while (timeSinceLastCycle > timePerUpdate)
		{
			timeSinceLastCycle -= timePerUpdate;
			update(timePerUpdate);
		}
		render();
	}
	//updateThread.terminate();
}

Application::Application(int argc, char* argv[]) :
		timePerUpdate(sf::seconds(1.f / UPDATE_FREQ))
{
	LOG_INFO << "---====== Starting up =======---";
	for (int i = 0; i < argc; i++)
	{
		m_args.push_back(argv[i]);
	}

	m_window.create(sf::VideoMode(640, 480), "Viper Steel");

	m_window.setVerticalSyncEnabled(true);
}

void Application::update(sf::Time delta)
{
	static sf::Time jsRun;

	i++;
	if (i > 15)
		i = 0;
}

void Application::event()
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
}

void Application::render()
{
	m_window.clear(sf::Color(i * 16, 0, 0));

	m_window.display();
}

Application::~Application()
{
	LOG_INFO << "---====== Shutting down =======---";
}

} /* namespace Core */
} /* namespace Game */
