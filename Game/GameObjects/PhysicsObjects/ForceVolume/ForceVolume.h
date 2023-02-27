#pragma once

#include "Engine/GameObject/GameObject.h"

#include "Game/Components/GraphicsComponents/GCVoid.h"
#include "PCForceVolume.h"
#include "Game/Components/InputComponents/ICVoid.h"

class ForceVolume : public Engine::GameObject<PCForceVolume, GCVoid, ICVoid>
{
	friend PCForceVolume;

public:
	ForceVolume() = default;
	explicit ForceVolume(const std::vector<IRigidBody*>& rigidBodies);

	void addRigidBody(IRigidBody& rb);
	void removeRigidBody(IRigidBody& rb);

	virtual void setForce(const sf::Vector2f& force) { m_force = force; }

	[[nodiscard]] sf::Vector2f getForce() const { return m_force; }

protected:
	std::vector<IRigidBody*> m_rigidBodies;
	sf::Vector2f m_force { 0.f, 0.f };
};
