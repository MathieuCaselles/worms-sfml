#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

template<typename Type, std::string fodlerName, std::string fileExtension>
class Dictionary
{
public:
	static const Type& getResource(const std::string resourceName);


private:
	static std::map<std::string, Type> m_resources;

	static bool resourceExist(const std::string resourceName);
};



template<typename Type, std::string fodlerName, std::string fileExtension>
static std::map<std::string, Type> Dictionary<Type, fodlerName, fileExtension>::m_resources;


template<typename Type, std::string fodlerName, std::string fileExtension>
inline const Type& Dictionary<Type, fodlerName, fileExtension>::getResource(const std::string resourceName)
{
	if (!resourceExist(resourceName))
	{
		m_resources[resourceName].loadFromFile("Assets/" + fodlerName + "/" + resourceName + "." + fileExtension);
	}
	return m_resources[resourceName];
}

template<typename Type, std::string fodlerName, std::string fileExtension>
inline bool Dictionary<Type, fodlerName, fileExtension>::resourceExist(const std::string resourceName)
{
	return  m_resources.find(textureName) != m_resources.end();
}



using TextureDictionary = Dictionary<sf::Texture, "Textures", "png">;
using FontDictionary = Dictionary<sf::Font, "Fonts", "ttf">;
using TextureDictionary = Dictionary<sf::Music, "Musics", "wav">;
using TextureDictionary = Dictionary<sf::SoundBuffer, "Sounds", "wav">;
