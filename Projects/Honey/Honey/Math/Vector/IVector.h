#pragma once

namespace Honey::Math {

	template <typename T, unsigned int ComponentsCount>
	struct IVector {

	public:

		virtual ~IVector() = default;

		T operator [](unsigned int i)
		{
			return _components[i];
		}

	protected:

		T _components[ComponentsCount];
	};

}