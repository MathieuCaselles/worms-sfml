#pragma once
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include "Dictionary.h"

namespace Engine {

	class TextureDictionary : public Dictionary<TextureDictionary, sf::Texture>
	{

		static const sf::Texture* get_implementation(std::string name) {
		{
			if (!elementExist(name)) {
				m_elements[name] = std::make_unique<sf::Texture>();
				m_elements[name]->loadFromFile("Assets/Textures/" + name);
			}

			return m_elements[name];
		}
	};
}
