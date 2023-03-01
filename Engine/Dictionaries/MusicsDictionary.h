#pragma once
#include <map>
#include <string>

#include <SFML/Audio.hpp>
#include "Dictionary.h"

namespace Engine {

	class MusicsDictionary : public Dictionary<MusicsDictionary, sf::Music>
	{
		static const sf::Music& get_implementation(std::string name) {
			{
			if (!elementExist(name)) {
				m_elements[name] = std::make_unique<sf::Music>();
				m_elements[name]->loadFromFile("Assets/Musics/" + name);
			}

			return m_elements[name];
		}
	};

}
