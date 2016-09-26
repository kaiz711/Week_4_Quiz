#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <stdbool.h>

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

bool checkCursor(double xpos, double ypos, int r, const int& i0, const int& j0)
{
	// 커서가 원 안에 들어가있는지 확인하는 작업
	// 2주차에 사용했던 몬테카를로 시뮬레이션 기법 응용

	if ((xpos - (double)i0) * (xpos - (double)i0) + (ypos - (double)j0) * (ypos - (double)j0) < (double)r * (double)r)
		return true;
	else
		return false;
}

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	// 수직선을 그을 경우 에러 방지

	if (i0 == i1)
	{
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}

	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawCircle(int r, const int& i0, const int& j0, const float& red, const float& green, const float& blue)
{
	for (int i = i0 - r; i < i0 + r; i++)
	{
		for (int j = j0 - r; j < j0 + r; j++)
		{
			int a = (i - i0) * (i - i0) + (j - j0) * (j - j0) - r * r;
			int b = (i - i0) * (i - i0) + (j - j0) * (j - j0) - (r - 1) * (r - 1) + 2 * r - 1;

			if (a < 0 && b > 0)
				drawPixel(i, j, red, green, blue);
		}
	}
}


void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background
													/*	for (int i = 0; i<width*height; i++) {
													pixels[i * 3 + 0] = 1.0f; // red
													pixels[i * 3 + 1] = 1.0f; // green
													pixels[i * 3 + 2] = 1.0f; // blue
													}*/

													//const int i = rand() % width, j = rand() % height;
													//drawPixel(i, j, 0.0f, 0.0f, 0.0f);

													// drawing a line
													//TODO: anti-aliasing

	// Bold Line

	drawCircle(50, 100, 350, 1.0f, 0.0f, 0.0f);
	drawLine(75, 325, 125, 375, 1.0f, 0.0f, 0.0f);
	drawLine(75, 326, 124, 375, 1.0f, 0.0f, 0.0f);
	drawLine(76, 325, 125, 374, 1.0f, 0.0f, 0.0f);

	// Bold Circle

	drawCircle(50, 210, 350, 1.0f, 0.0f, 0.0f);
	drawCircle(20, 210, 350, 1.0f, 0.0f, 0.0f);
	drawCircle(21, 210, 350, 1.0f, 0.0f, 0.0f);
	drawCircle(22, 210, 350, 1.0f, 0.0f, 0.0f);
	drawCircle(23, 210, 350, 1.0f, 0.0f, 0.0f);
	drawCircle(24, 210, 350, 1.0f, 0.0f, 0.0f);

	// Empty Square

	drawCircle(50, 320, 350, 1.0f, 0.0f, 0.0f);
	drawLine(295, 325, 345, 325, 1.0f, 0.0f, 0.0f);
	drawLine(295, 375, 345, 375, 1.0f, 0.0f, 0.0f);
	drawLine(295, 325, 295, 375, 1.0f, 0.0f, 0.0f);
	drawLine(345, 325, 345, 375, 1.0f, 0.0f, 0.0f);

	// Cross Line

	drawCircle(50, 430, 350, 1.0f, 0.0f, 0.0f);
	drawLine(405, 325, 455, 375, 1.0f, 0.0f, 0.0f);
	drawLine(405, 375, 455, 325, 1.0f, 0.0f, 0.0f);

	// Down Arrow

	drawCircle(50, 540, 350, 1.0f, 0.0f, 0.0f);
	drawLine(540, 325, 540, 375, 1.0f, 0.0f, 0.0f);
	drawLine(520, 345, 540, 325, 1.0f, 0.0f, 0.0f);
	drawLine(540, 325, 560, 345, 1.0f, 0.0f, 0.0f);

	// Right Arrow

	drawCircle(50, 100, 150, 1.0f, 0.0f, 0.0f);
	drawLine(75, 150, 125, 150, 1.0f, 0.0f, 0.0f);
	drawLine(105, 130, 125, 150, 1.0f, 0.0f, 0.0f);
	drawLine(105, 170, 125, 150, 1.0f, 0.0f, 0.0f);

	// A Shape

	drawCircle(50, 210, 150, 1.0f, 0.0f, 0.0f);
	drawLine(185, 130, 210, 180, 1.0f, 0.0f, 0.0f);
	drawLine(210, 180, 235, 130, 1.0f, 0.0f, 0.0f);
	drawLine(195, 150, 225, 150, 1.0f, 0.0f, 0.0f);
	drawLine(195, 151, 225, 151, 1.0f, 0.0f, 0.0f);

	for (int i = 185; i < 210; i++) // 기울기가 45도가 아닌 선은 흐릿하게 만들어지므로 두껍게 만들어주기 위한 작업
	{
		const int j = 50 * (i - 185) / 25 + 130;

		drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		drawPixel(i, j - 1, 1.0f, 0.0f, 0.0f);
		drawPixel(i, j + 1, 1.0f, 0.0f, 0.0f);
	}

	for (int i = 210; i < 235; i++)
	{
		const int j = -50 * (i - 210) / 25 + 180;

		drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		drawPixel(i, j - 1, 1.0f, 0.0f, 0.0f);
		drawPixel(i, j + 1, 1.0f, 0.0f, 0.0f);
	}

	// Vertical

	drawCircle(50, 320, 150, 1.0f, 0.0f, 0.0f);
	drawLine(320, 125, 320, 175, 1.0f, 0.0f, 0.0f);

	// Left Arrow

	drawCircle(50, 430, 150, 1.0f, 0.0f, 0.0f);
	drawLine(405, 150, 455, 150, 1.0f, 0.0f, 0.0f);
	drawLine(405, 150, 425, 130, 1.0f, 0.0f, 0.0f);
	drawLine(405, 150, 425, 170, 1.0f, 0.0f, 0.0f);

	// Up Arrow

	drawCircle(50, 540, 150, 1.0f, 0.0f, 0.0f);
	drawLine(540, 125, 540, 175, 1.0f, 0.0f, 0.0f);
	drawLine(520, 155, 540, 175, 1.0f, 0.0f, 0.0f);
	drawLine(540, 175, 560, 155, 1.0f, 0.0f, 0.0f);
}

int main(void)
{
	GLFWwindow* window;

	double xpos, ypos;

	/* Initialize the library */

	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */

	window = glfwCreateWindow(width, height, "Week 4 Quiz", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */

	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		//glClear(GL_COLOR_BUFFER_BIT);

		glfwGetCursorPos(window, &xpos, &ypos);

		drawOnPixelBuffer();

		// 커서가 원 안으로 들어갈 경우 원의 색이 파랑색이 되도록 만들어주는 작업

		if (checkCursor(xpos, ypos, 50, 100, 130) == true)
			drawCircle(50, 100, 350, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 210, 130) == true)
			drawCircle(50, 210, 350, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 320, 130) == true)
			drawCircle(50, 320, 350, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 430, 130) == true)
			drawCircle(50, 430, 350, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 540, 130) == true)
			drawCircle(50, 540, 350, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 100, 330) == true)
			drawCircle(50, 100, 150, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 210, 330) == true)
			drawCircle(50, 210, 150, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 320, 330) == true)
			drawCircle(50, 320, 150, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 430, 330) == true)
			drawCircle(50, 430, 150, 0.0f, 0.0f, 1.0f);
		if (checkCursor(xpos, ypos, 50, 540, 330) == true)
			drawCircle(50, 540, 150, 0.0f, 0.0f, 1.0f);

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */

		glfwSwapBuffers(window);

		/* Poll for and process events */

		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
