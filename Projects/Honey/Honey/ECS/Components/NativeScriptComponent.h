// Warning! This is absolutely unfinished and unstable.
// TODO: Make it way more stable.

#pragma once

#include <Honey/ECS/Behaviour.h>

namespace Honey {

	/**
	 * @brief Native Script Component.
	 * It manages native scripts attached to entity.
	*/
	class NativeScriptComponent {

	public:

		NativeScriptComponent(const Entity& entity) : entity(entity) {};
		NativeScriptComponent(const NativeScriptComponent&) = default;
		~NativeScriptComponent() = default;

		/**
		 * @brief Target entity.
		*/
		Entity entity;

		/**
		 * @brief Behaviours attached to entity.
		*/
		std::vector<Behaviour*> behaviours;

		/**
		 * @brief Called when NSC is attached to entity.
		*/
		void onCreate()
		{
			// Instance creation for each behaviour attached.
			for (Behaviour* behaviour : behaviours)
				behaviour->onCreate();
		}

		/**
		 * @brief Update scripts.
		*/
		void onUpdate()
		{
			for (Behaviour* behaviour : behaviours)
				behaviour->onUpdate();
		}

		/**
		 * @brief Called when NSC is destroyed.
		*/
		void onDestroy()
		{
			// Instance destruction to each behaviour.
			for (Behaviour* behaviour : behaviours)
				behaviour->onDestroy();
		}

		/**
		 * @brief Add behaviour to script manager.
		 * @tparam T Behaviour type.
		*/
		template <typename T>
		void addBehaviour() 
		{
			T& component = entity.addComponent<T>();
			behaviours.push_back(&component);
		}

		/**
		 * @brief Attach native scripting to entity.
		 * @param entity Target entity.
		 * @return A reference to the newly attached NSC.
		*/
		static NativeScriptComponent& attach(Entity& entity)
		{
			return entity.addComponent<NativeScriptComponent>(entity);
		}

		friend class Scene;
	};

}
