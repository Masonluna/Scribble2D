#pragma once
#include <cstdint>


namespace Scribble {

	enum MouseCode : uint16_t
	{
		MouseButton1 = 0,
		MouseButton2 = 1,
		MouseButton3 = 2,
		MouseButton4 = 3,
		MouseButton5 = 4,
		MouseButton6 = 5,
		MouseButton7 = 6,
		MouseButton8 = 7,

		MouseButtonLast   = MouseButton8,
		MouseButtonLeft   = MouseButton1,
		MouseButtonRight  = MouseButton2,
		MouseButtonMiddle = MouseButton3


	};

}