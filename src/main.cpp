/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:46 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/27 01:24:49 by bgrhnzcn         ###   ########.fr       */
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

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		std::cerr << "Shader compilation failed." << std::endl;
	}

	return (id);
}

static unsigned int	CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	//Attaches the shaders to the program.
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	//Links the program.
	glLinkProgram(program);
	//Validates the program.
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return (program);
}

int main()
{
	if (!glfwInit())
		return (1);
	try
	{
		gl42::Window win = gl42::Window(800, 600, "GL42", nullptr, nullptr);
		if (win.getWinPtr() == nullptr)
		{
			std::cout << "Window Error" << std::endl;
			glfwTerminate();
			return (1);
		}
		glfwMakeContextCurrent(win.getWinPtr());
		//buffer id for opengl. OpenGL gives id for every object uses memory segments. Like buffers or arrays.

		GLfloat vertices[6] = {
			-0.5f, -0.8f,
			+0.0f, +0.5f,
			+0.5f, -0.5f
		};
		
		//Generate generic type of buffer and assing it to buffer_id.
		unsigned int buffer_id;
		glGenBuffers(1, &buffer_id);
		//Bind buffer to array buffer. Array buffer is a type of buffer that stores vertex data.
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		//Copy data to buffer. GL_STATIC_DRAW is a type of draw that tells OpenGL that we are not going to change the data.
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
		//Modify vertex attribute array. 0 is the index of the attribute.
		//2 is the size of the attribute as count. GL_FLOAT is the type of the attribute.
		//GL_FALSE is the normalization of the attribute. 2 * sizeof(float) is the stride of the attribute.
		//0 is the offset of the attribute inside single vertex.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		//Enables the vertex attribute array.
		glEnableVertexAttribArray(0);
		
		//Vertex Shader
		std::string ver = 
			"#version 330 core\n"
			"\n"
			"layout(location = 0) in vec4 position;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = position;\n"
			"}\n";
		//Fragment Shader
		std::string frag = 
			"#version 330 core\n"
			"\n"
			"layout(location = 0) out vec4 color;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	color = vec4(1, 0, 1, 1);\n"
			"}\n";

		unsigned int shader = CreateShader(ver, frag);
		glUseProgram(shader);
		//Sets Callback function for key events.
		glfwSetKeyCallback(win.getWinPtr(), key_callback);
		//Main Rendering loop.
		while(!win.shouldClose())
		{
			//Clear Buffer memeory to remove garbage values
			glClear(GL_COLOR_BUFFER_BIT);
			//Draws the buffer. GL_TRIANGLES is a type of draw that tells OpenGL to draw triangles.
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//Swaps front and back buffer. OpenGL deafult is two buffer. One for back one for front.
			glfwSwapBuffers(win.getWinPtr());
			//Polls events. Like key events.
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
