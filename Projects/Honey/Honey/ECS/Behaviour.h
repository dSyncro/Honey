/**
 * @file Behaviour.h
*/

#pragma once

#include "Entity.h"

namespace Honey {

	/**
	 * @brief Behavior is the main Honey scripting component.
	 * Behaviour is intended to be the main class of Honey
	 * scriptable entities. It provides a nice API for scripting
	 * and give you access to engine-integrated events.
	*/
	class Behaviour {

	public:

		virtual ~Behaviour() = default;

		/**
		 * @brief Called when entity is created.
		*/
		virtual void onCreate() {}

		/**
		 * @brief Called when scene is updated.
		*/
		virtual void onUpdate() {}

		/**
		 * @brief Called before entity is definitely destroyed.
		*/
		virtual void onDestroy() {}

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
			return _entity->addComponent<T>(std::forward<Args>(args)...);
		}

		/**
		 * @brief Remove component from entity.
		 * @tparam T Component type.
		*/
		template <typename T>
		void removeComponent() { return _entity->removeComponent<T>(); }

		/**
		 * @brief Get component from entity.
		 * @tparam T Component type.
		 * @return A reference to the specified component.
		*/
		template <typename T>
		T& getComponent() 
		{
			return _entity->getComponent<T>();
		}

		/**
		 * @brief Check if entity already has a component.
		 * @tparam T Component type.
		*/
		template <typename T>
		bool hasComponent() { return _entity->hasComponent<T>(); }

		/**
		 * @brief Get the entity this behaviour is attached to.
		 * @return The entity this behaviour is attached to.
		*/
		Entity& entity() { return *_entity; }

	private:

		Entity* _entity = nullptr;

		friend class Scene;
	};
}
