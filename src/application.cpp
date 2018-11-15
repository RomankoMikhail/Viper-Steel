#include "application.h"

#include "global_objects.h"
#include "js_methods.h"

namespace game
{

void application::run()
{
	for(std::string str : m_args)
	{
		LOG_DEBUG << str;
	}


	duk_context* ctx = duk_create_heap_default();

	js_setup_context(ctx, 101);
	ships[1] = ship(20);
	duk_eval_string(ctx, "log('Hello from ' + 1 + ' :3 ');move(-1, 1);");

	duk_destroy_heap(ctx);

	while(m_window.isOpen())
	{
		sf::Event event;

		while(m_window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}

		m_window.clear();
		m_window.display();
	}
}

application::application(int argc, char* argv[])
{
	LOG_INFO << "---====== Starting up =======---";
	for(int i = 0; i < argc; i++)
	{
		m_args.push_back(argv[i]);
	}
	sf::Image icon;

	if(icon.loadFromFile("images/debug_16.png") == false)
	{
		LOG_ERROR << "File images/debug_16.png not found";
	}

	m_window.setIcon(icon.getSize().x, icon.getSize().x, icon.getPixelsPtr());
	m_window.create(sf::VideoMode(640, 480), "Viper Steel");
	m_window.setVerticalSyncEnabled(true);
}

application::~application()
{
	LOG_INFO << "---====== Shutting down =======---";
}

} /* namespace game */
