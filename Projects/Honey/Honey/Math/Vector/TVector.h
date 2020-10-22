// This code is not yet integrated with the engine.

#pragma once

#include <Honey/Core/TypeTraits.h>

namespace Honey::Math {

	template <typename T, UInt size>
	struct TVector {

		T Components[size];

	};

	template <typename T>
	struct TVector2 : public TVector<T, 2> {

		T& x() { return Components[0]; }
		T& y() { return Components[1]; }

	};

	template <typename T>
	struct TVector3 : public TVector<T, 3> {

		T& x() { return Components[0]; }
		T& y() { return Components[1]; }
		T& z() { return Components[2]; }

	};

	template <typename T>
	struct TVector4 : public TVector<T, 4> {

		T& x() { return Components[0]; }
		T& y() { return Components[1]; }
		T& z() { return Components[2]; }
		T& w() { return Components[3]; }

	};

}
