#pragma once

#include <Honey/ECS/ScriptableEntity.h>

namespace Honey {

	struct NativeScriptComponent {

		NativeScriptComponent() = default;
		~NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent&) = default;

		ScriptableEntity* Instance = nullptr;

		template <typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { Instance = new T(); };
			DeleteInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* instance) { reinterpret_cast<T*>(instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) { reinterpret_cast<T*>(instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance) { reinterpret_cast<T*>(instance)->OnUpdate(); };
		}

		std::function<void()> InstantiateFunction;
		std::function<void()> DeleteInstanceFunction;
		std::function<void(ScriptableEntity*)> OnCreateFunction;
		std::function<void(ScriptableEntity*)> OnDestroyFunction;
		std::function<void(ScriptableEntity*)> OnUpdateFunction;

		friend class Scene;
	};

}
