#pragma once

#include <Honey/Input/Input.h>

namespace Honey{

	class GlfwPlatformsInput final : public Input {

	protected:

		virtual bool IsKeyPressedImpl(Keycode keycode) override;
		virtual bool IsMouseButtonPressedImpl(MouseButton button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}