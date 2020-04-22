#pragma once

namespace Honey {

	class Timestamp {

	public:

		Timestamp(float time = 0.0f) : _time(time) {}

		operator float() const { return _time; }

		Timestamp operator +=(float amount) { _time += amount; }
		Timestamp operator -=(float amount) { _time -= amount; }

		float GetSeconds() const { return _time; }
		float GetMilliseconds() const { return _time * 1000.0f; }

	private:

		float _time;
	};

}