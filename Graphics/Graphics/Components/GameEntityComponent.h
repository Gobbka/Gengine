#pragma once

namespace ECS {
	class Entity;
}

namespace Core
{
	struct GameEntityComponent
	{
		ECS::Entity* parent;

		GameEntityComponent(ECS::Entity* parent = nullptr) : parent(parent) {}
	};
}
