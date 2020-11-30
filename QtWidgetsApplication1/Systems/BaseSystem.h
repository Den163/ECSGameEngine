#pragma once

class BaseSystem
{
public:
	virtual ~BaseSystem() = default;
	virtual void init() = 0;
	virtual void update() = 0;
};
