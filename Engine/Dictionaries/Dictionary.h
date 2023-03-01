#pragma once
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace Engine {

	template<class Child, typename Type>
	class Dictionary
	{

	protected:

		static std::map<std::string, std::unique_ptr<Type>> m_elements;
		static bool elementExist(std::string name);


	public:
		static const Type& get(std::string name) {
			return Child::get_implementation(name);
		};

		virtual ~Dictionary() {
			m_elements.clear();
		}
	};


	template<class Child, typename Type>
	std::map<std::string, std::unique_ptr<Type>> Dictionary<Child, Type>::m_elements;

	template<class Child, typename Type>
	inline bool Dictionary<Child, Type>::elementExist(std::string name)
	{
		return m_elements.find(name) != m_elements.end();
	}

}