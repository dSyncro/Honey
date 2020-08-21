#pragma once

#include "Entity.h"

namespace Honey {

	class Behaviour {

	public:

		virtual ~Behaviour() = default;

		virtual void OnCreate() {}
		virtual void OnUpdate() {}
		virtual void OnDestroy() {}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return _entity->AddComponent<T>(std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent() { return _entity->RemoveComponent<T>(_entityID); }

		template <typename T>
		T& GetComponent() 
		{
			return _entity->GetComponent<T>();
		}

		template <typename T>
		bool HasComponent() { return _entity->HasComponent<T>(_entityID); }

		Entity& GetEntity() { return *_entity; }

	private:

		Entity* _entity = nullptr;

		friend class Scene;
	};
}
