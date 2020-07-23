#pragma once

#include <entt.hpp>

#include <Honey/Core/Assertion.h>
#include <Honey/Scene/Scene.h>

namespace Honey {

	class Entity {

	public:

		Entity() = default;
		Entity(entt::entity entity, Scene* scene) : _scene(scene), _entityID(entity) {}
		Entity(const Entity& entity) = default;

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args) 
		{
			HNY_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return _scene->_registry.emplace<T>(_entityID, std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent() 
		{ 
			HNY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return _scene->_registry.remove<T>(_entityID, std::forward<Args>(args));
		}

		template <typename T>
		T& GetComponent() 
		{ 
			HNY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return _scene->_registry.get<T>(_entityID);
		}

		template <typename T>
		bool HasComponent() { return _scene->_registry.has<T>(_entityID); }

		operator entt::entity&() { return _entityID; }
		operator const entt::entity&() const { return _entityID; }

		operator bool() const { return _entityID != (entt::entity)0; }

	private:

		Scene* _scene = nullptr;
		entt::entity _entityID {0};

	};

}