#pragma once
#include "Scribble2D/Core/KeyCode.h"
#include "Scribble2D/Core/MouseCode.h"

#include <glm/glm.hpp>
#include <utility>
#include <memory>

namespace Scribble {

	class Input
	{
	protected:
		Input() = default;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImp(key); }
		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImp(button); }

		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImp(); }
		static float GetMouseX() { return s_Instance->GetMouseXImp(); }
		static float GetMouseY() { return s_Instance->GetMouseXImp(); }

	protected:
		virtual bool IsKeyPressedImp(int keycode) = 0;

		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImp() = 0;
		virtual float GetMouseXImp() = 0;
		virtual float GetMouseYImp() = 0;

	private:
		static std::unique_ptr<Input> s_Instance;
	};

}

