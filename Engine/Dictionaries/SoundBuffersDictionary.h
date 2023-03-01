#pragma once
#include <map>
#include <string>

#include <SFML/Audio.hpp>
#include "Dictionary.h"

namespace Engine {

	class SoundBuffersDictionary : public Dictionary<SoundBuffersDictionary, sf::SoundBuffer>
	{
		static const sf::SoundBuffer* get_implementation(std::string name) {
		{
			if (!elementExist(name)) {
				m_elements[name] = std::make_unique<sf::SoundBuffer>();
				m_elements[name]->loadFromFile("Assets/Sounds/" + name);
			}

			return m_elements[name];
		}
	};
}
