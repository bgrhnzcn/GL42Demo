/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:46 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/25 21:07:12 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <gl42.hpp>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		std::cout << "Q Released" << std::endl;
}

int main()
{
	if (!glfwInit())
		return (1);
	try
	{
		gl42::Window win = gl42::Window(1920, 1080, "GL42", nullptr, nullptr);
		if (win.getWinPtr() == nullptr)
		{
			std::cout << "Window Error" << std::endl;
			glfwTerminate();
			return (1);
		}
		glfwMakeContextCurrent(win.getWinPtr());
		//buffer id for opengl. OpenGL gives id for every object uses memory segments. Like buffers or arrays.
		unsigned int buffer_id;
		glCreateBuffers(1, &buffer_id);
		glGenBuffers(1, &buffer_id);
		while(!win.shouldClose())
		{
			//Clear Buffer memeory to remove garbage values
			glClear(GL_COLOR_BUFFER_BIT);
			//Legacy opengl version.
			glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, 0.5f);
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.5f, 0.5f);
			glEnd();
			//Swaps front and back buffer. OpenGL deafult is two buffer. One for back one for front.
			glfwSwapBuffers(win.getWinPtr());
			glfwSetKeyCallback(win.getWinPtr(), key_callback);
			glfwPollEvents();
		}
	}
	catch (gl42::InitializationExecption exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	catch (std::runtime_error exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
}
