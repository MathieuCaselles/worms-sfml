#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

template<typename Type, const char* folderName, const char* fileExtension>
class Dictionary
{
public:
	static const Type& getResource(const std::string resourceName);


private:
	static std::map<std::string, Type> m_resources;

	static bool resourceExist(const std::string resourceName);
};



template<typename Type, const char* folderName, const char* fileExtension>
std::map<std::string, Type> Dictionary<Type, folderName, fileExtension>::m_resources;

template<typename Type, const char* folderName, const char* fileExtension>
inline const Type& Dictionary<Type, folderName, fileExtension>::getResource(const std::string resourceName)
{
	if (!resourceExist(resourceName))
	{
		m_resources[resourceName].loadFromFile("Assets/" + std::string(folderName) + "/" + resourceName + "." + std::string(fileExtension));
	}
	return m_resources[resourceName];
}

template<typename Type, const char* folderName, const char* fileExtension>
inline bool Dictionary<Type, folderName, fileExtension>::resourceExist(const std::string resourceName)
{
	return  m_resources.find(resourceName) != m_resources.end();
}


using TextureDictionary = Dictionary<sf::Texture, "Textures", "png">;
using FontDictionary = Dictionary<sf::Font, "Fonts", "ttf">;
using MusicDictionary = Dictionary<sf::Music, "Musics", "wav">;
using SoundBufferDictionary = Dictionary<sf::SoundBuffer, "Sounds", "wav">;