#pragma once

#include "Entity.h"

namespace Honey {

	class ScriptableEntity {

	public:

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return _entity.AddComponent<T>(std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent() { return _entity.RemoveComponent<T>(); }

		template <typename T>
		T& GetComponent() { return _entity.GetComponent<T>(); }

		template <typename T>
		bool HasComponent() { return _entity.HasComponent<T>(); }

	private:

		Entity _entity;

		friend class Scene;
	};
}
