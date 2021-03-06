#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <plog/Log.h>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define UPDATE_FREQ 30

namespace Game
{
namespace Core
{
/*!
 * \brief Class representing main application
 * \ingroup core
 *
 * \details Game::Application is a class, that contain variables related to
 * application such as video resolution, audio level settings and etc.
 */
class Application
{
	std::vector<std::string> m_args;
	std::map<sf::String, sf::Texture> m_textures;
	sf::RenderWindow m_window;

	const sf::Time timePerUpdate;

	void event();
	void update(sf::Time delta);
	void render();
public:
	/*!
	 * \brief Application starts working from here
	 */
	void run();

	/*!
	 * \brief game::application constructor.
	 *
	 * \param argc number of arguments
	 * \param argv the arguments
	 */
	explicit Application(int argc, char* argv[]);
	~Application();
};

} /* namespace Core */
} /* namespace Game */



#endif /* APPLICATION_H_ */
