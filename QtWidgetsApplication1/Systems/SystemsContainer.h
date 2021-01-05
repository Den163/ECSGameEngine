#pragma once
#include <entt/entity/registry.hpp>

#include "BaseSystem.h"

class SystemsContainer
{
public:
	SystemsContainer(entt::registry & registry, std::vector<BaseSystem*> systems) :
		_systems(systems),
		_registry(registry)
	{}

	void init()
	{
		for (auto s : _systems)
		{
			s->init(_registry);
		}
	}
	
	void update()
	{
		for (auto s: _systems)
		{
			s->update(_registry);
		}
	}

private:
	std::vector<BaseSystem*> _systems;
	entt::registry & _registry;
};
