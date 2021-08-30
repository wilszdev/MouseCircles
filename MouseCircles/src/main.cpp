#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cmath>
#include <iostream>
#include <chrono>

int main()
{
	// find center of screen
	RECT window;
	GetWindowRect(GetDesktopWindow(), &window);
	int cx = window.right / 2;
	int cy = window.bottom / 2;
	// parameters for the circular path
	const float pi = 3.14159f;
	const double r = 250.0;
	float theta = 0.0f;
	// for delta time, to keep the angular velocity pretty much constant
	auto tp1 = std::chrono::high_resolution_clock::now();
	float dt = 0.0f;
	while (1)
	{
		// get dt in seconds
		auto tp = std::chrono::high_resolution_clock::now();
		dt = (tp - tp1).count() / 1000000000.0;
		tp1 = tp;
		// close on esc kepress
		if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
		{
			break;
		}
		// parametric equations for a circle
		// x(t) = r * cos(t)
		// y(t) = r * sin(t)
		if (!SetCursorPos(r * cos(theta) + cx, r * sin(theta) + cy))
		{
			break;
		}
		// increase theta by 60 degrees per second
		theta += pi / 3.0 * dt;
	}
	return 0;
}