/**
 * @file Entity.h
*/

#pragma once

#include <entt.hpp>

#include <Honey/Core/Assertion.h>
#include <Honey/Scene/Scene.h>

namespace Honey {

	/**
	 * @brief ECS Entity
	 * Easily deal with entities.
	*/
	class Entity {

	public:

		/**
		 * @brief Entity default constructor.
		*/
		Entity() = default;
		Entity(entt::entity entity, Scene* scene) : _scene(scene), _entityID(entity) {}
		Entity(const Entity& entity) = default;

		/**
		 * @brief Add component to entity.
		 * @tparam T Component type.
		 * @tparam ...Args Don't mind this, it's deduced automatically.
		 * @param ...args Argument to use to construct component.
		 * @return Reference to the component just added.
		*/
		template <typename T, typename... Args>
		T& addComponent(Args&&... args) 
		{
			// Entity cannot have components of the same type.
			HNY_CORE_ASSERT(!hasComponent<T>(), "Entity already has component!");

			// Add component.
			return _scene->_registry.emplace<T>(_entityID, std::forward<Args>(args)...);
		}

		/**
		 * @brief Remove component from entity.
		 * @tparam T Component type.
		*/
		template <typename T>
		void removeComponent() 
		{ 
			// It is not possible to remove non-existent components.
			HNY_CORE_ASSERT(hasComponent<T>(), "Entity does not have component!");

			// Remove component.
			return _scene->_registry.remove<T>(_entityID);
		}

		/**
		 * @brief Get component from entity.
		 * @tparam T Component type.
		 * @return A reference to the specified component.
		*/
		template <typename T>
		T& getComponent()
		{ 
			// It is not possible to retrieve non existent components.
			HNY_CORE_ASSERT(hasComponent<T>(), "Entity does not have component!");

			// Get component.
			return _scene->_registry.get<T>(_entityID);
		}

		/**
		 * @brief Get component if it is attached to entity.
		 * @tparam T Component type.
		 * @return A pointer to the component if it exists, a null pointer otherwise.
		*/
		template <typename T>
		T* getComponentIfPresent()
		{
			return _scene->_registry.try_get<T>(_entityID);
		}

		/**
		 * @brief Check if entity already has a component.
		 * @tparam T Component type.
		*/
		template <typename T>
		bool hasComponent() { return _scene->_registry.has<T>(_entityID); }

		/**
		 * @brief Convert entity to entt::entity.
		*/
		operator entt::entity() const { return _entityID; }

		/**
		 * @brief Convert entity to bool (true if not null)
		*/
		operator bool() const { return _entityID != entt::null; }

		/**
		 * @brief Check if two entities are equal to each other.
		 * @param other The other entity.
		*/
		bool operator ==(const Entity& other) const { return _scene == other._scene && _entityID == other._entityID; }

		/**
		 * @brief Check if two entities differ from each other.
		 * @param other The other entity.
		*/
		bool operator !=(const Entity& other) const { return !(*this == other); }

	private:

		Scene* _scene = nullptr;
		entt::entity _entityID { entt::null };

	};

}
