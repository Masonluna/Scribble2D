#pragma once

#include "Scribble2D/Core/Input.h"

namespace Scribble {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImp(int keycode) override;

		virtual bool IsMouseButtonPressedImp(int button) override;
		virtual std::pair<float, float> GetMousePositionImp() override;
		virtual float GetMouseXImp() override;
		virtual float GetMouseYImp() override;
	};

}