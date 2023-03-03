#pragma once


#include <Tools/DesignPatterns/Composite.h>
#include <Tools/DesignPatterns/Factory.h>

#include "../Components/InputComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/GraphicsComponent.h"
#include "Engine/Utility/RTTI.h"
#include <SFML/Graphics.hpp>

namespace Engine {
	class IScene;


	class IGameObject : public Tools::Composite<IGameObject>, public HasRTTI
	{
	public:
		DECLARE_RTTI(IGameObject, NoRTTIRoot)

	public:
		virtual ~IGameObject() {};

		virtual void onBeginPlay(IScene& scene) {};
		virtual void onEndPlay(IScene& scene) {};

		virtual void processInput(sf::Event& inputEvent, IScene& scene) = 0;
		virtual void update(const float& deltaTime, IScene& scene) = 0;
		virtual void render(sf::RenderWindow& window) = 0;

		virtual void destroy() { m_waitingToBeDestroyed = true; }

		inline void setIsActive(bool isActive) { m_isActive = isActive; }
		inline void setIsVisible(bool isVisible) { m_isVisible = isVisible; }

		inline bool isActive() const { return m_isActive; }
		inline bool isVisible() const { return m_isVisible; }
		inline bool isWaitingToBeDestroyed() const { return m_waitingToBeDestroyed; }

	protected:
		bool m_isActive = true;
		bool m_isVisible = true;
		bool m_waitingToBeDestroyed = false;
	};

	template<typename... MixinGameComponents>
	class GameObject : public IGameObject, public MixinGameComponents...
	{
	public:
		void processInput(sf::Event& inputEvent, IScene& scene) override
		{
			if (m_isActive)
				this->traverse([&](auto* gameObject) {
						static_cast<decltype(this)>(gameObject)->processInputImplementation(*this, inputEvent, scene);
					});

		}

		void update(const float& deltaTime, IScene& scene) override
		{
			if (m_isActive)
				this->traverse([&](auto* gameObject) {
					static_cast<decltype(this)>(gameObject)->updateImplementation(deltaTime, *this, scene);
				});
		}

		void render(sf::RenderWindow& window) override
		{
			if (m_isActive && m_isVisible)
				this->traverse([&](auto* gameObject) {
					static_cast<decltype(this)>(gameObject)->renderImplementation(*this, window);
				});
		}
	};

	using AvailableGameObjectsTypes = typelist<IGameObject>;
	using GameObjectFactory = Tools::Factory<AvailableGameObjectsTypes, true>;

}
