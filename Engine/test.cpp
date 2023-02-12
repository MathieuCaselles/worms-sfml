#include "test.h"

namespace engine {
    sf::RenderWindow getWindow(std::string name) {
	return sf::RenderWindow(sf::VideoMode(1200, 500), name);

    }
}
