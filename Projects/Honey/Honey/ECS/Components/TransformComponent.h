#pragma once

#include <Honey/Math/Transform.h>

namespace Honey {

	struct TransformComponent {

		TransformComponent() = default;
		~TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Honey::Transform& trasform)
			: Transform(trasform) { }

		Honey::Transform Transform;

		operator Honey::Transform&() { return Transform; }
		operator const Honey::Transform&() const { return Transform; }
	};

}
