#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <plog/Log.h>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace game
{

class application
{
	std::vector<std::string> m_args;
	std::map<sf::String, sf::Texture> m_textures;
	sf::RenderWindow m_window;
	void update();
public:
	/*!
	 * \brief Application starts working from here
	 */
	void run();

	/*!
	 * \brief game::application constructor.
	 *
	 * @param argc number of arguments
	 * @param argv the arguments
	 */
	explicit application(int argc, char* argv[]);
	~application();
};
/*!
 * \class game::application
 * \ingroup core
 *
 * game::application is a class, that contains variables related to
 * application such as video resolution, audio level settings and etc.
 *
 */

} /* namespace game */



#endif /* APPLICATION_H_ */
