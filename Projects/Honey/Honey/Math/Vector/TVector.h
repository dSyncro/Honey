#pragma once

namespace Honey::Math {

	template <typename T, int size>
	struct TVector {

		T Components[size];

	};

	template <typename T>
	struct TVector2 : public TVector<T, 2> {

		T& X() { return Components[0]; }
		T& Y() { return Components[1]; }

	};

	template <typename T>
	struct TVector3 : public TVector<T, 3> {

		T& X() { return Components[0]; }
		T& Y() { return Components[1]; }
		T& Z() { return Components[2]; }

	};

	template <typename T>
	struct TVector4 : public TVector<T, 4> {

		T& X() { return Components[0]; }
		T& Y() { return Components[1]; }
		T& Z() { return Components[2]; }
		T& W() { return Components[3]; }

	};

}
