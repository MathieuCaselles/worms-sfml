#pragma once

class PhysicsWorld
{
public:
	// World objects density table : https://www.thoughtco.com/table-of-densities-of-common-substances-603976
	inline static constexpr float MinDensity = 0.534f; // Lithium density
	inline static constexpr float MaxDensity = 22.6f; // Iridium density
};