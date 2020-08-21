#pragma once

#include <Honey/ECS/Behaviour.h>

namespace Honey {

	class NativeScriptComponent {

	public:

		NativeScriptComponent(const Entity& entity) : TargetEntity(entity) {};
		NativeScriptComponent(const NativeScriptComponent&) = default;
		~NativeScriptComponent() = default;

		Entity TargetEntity;
		std::vector<Behaviour*> Behaviours;

		void OnCreate()
		{
			for (Behaviour* behaviour : Behaviours)
				behaviour->OnCreate();
		}

		void OnUpdate()
		{
			for (Behaviour* behaviour : Behaviours)
				behaviour->OnUpdate();
		}

		void OnDestroy()
		{
			for (Behaviour* behaviour : Behaviours)
				behaviour->OnDestroy();
		}

		template <typename T>
		void AddBehaviour() 
		{
			T& component = TargetEntity.AddComponent<T>();
			Behaviours.push_back(&component);
		}

		static NativeScriptComponent& Attach(Honey::Entity& entity)
		{
			return entity.AddComponent<NativeScriptComponent>(entity);
		}

		friend class Scene;
	};

}
