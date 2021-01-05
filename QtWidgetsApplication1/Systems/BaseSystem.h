#pragma once
#include <entt/entity/registry.hpp>

class BaseSystem
{
public:
	virtual ~BaseSystem() = default;
	virtual void init(entt::registry & registry) {}
	virtual void update(entt::registry & registry) {}
};
