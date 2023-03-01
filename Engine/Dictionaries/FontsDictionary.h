#pragma once
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include "Dictionary.h"

namespace Engine {

	class FontsDictionary : public Dictionary<FontsDictionary, sf::Font>
	{
		friend Dictionary<FontsDictionary, sf::Font>;

		static const sf::Font& get_implementation(std::string name) {
			if (!elementExist(name)) {
				m_elements[name] = std::make_unique<sf::Font>();
				m_elements[name]->loadFromFile("Assets/Fonts/" + name);
			}

			return *m_elements[name].get();
		};
	};
}
