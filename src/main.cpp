/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:46 by buozcan           #+#    #+#             */
/*   Updated: 2024/10/01 01:49:45 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <gl42.hpp>

//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	(void)scancode;
//	(void)mods;
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
//		std::cout << "Q Released" << std::endl;
//}

int main()
{
	if (!glfwInit())
		return (1);
	try
	{
		gl42::Window win = gl42::Window(800, 600, "GL42", nullptr, nullptr);
		if (win.getWinPtr() == nullptr)
			return (1);
		//vertex array
		GLfloat vertices[12] = {
			-1.0f, +1.0f,
			+1.0f, +1.0f,
			+1.0f, -1.0f,
			-1.0f, -1.0f
		};
		//index array
		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};
		glEnable(GL_DEBUG_OUTPUT);
		//Must be generated for Core Profile. Compatibility profile does not require this.
		unsigned int vertex_array_id;
		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		//Generate generic type of buffer and assing it to buffer_id.
		unsigned int buffer_id;
		glGenBuffers(1, &buffer_id);
		//Bind buffer to array buffer. Array buffer is a type of buffer that stores vertex data.
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		//Copy data to buffer. GL_STATIC_DRAW is a type of draw that tells OpenGL that we are not going to change the data.
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);
		//Modify vertex attribute array. 0 is the index of the attribute.
		//2 is the size of the attribute as count. GL_FLOAT is the type of the attribute.
		//GL_FALSE is the normalization of the attribute. 2 * sizeof(float) is the stride of the attribute.
		//0 is the offset of the attribute inside single vertex.
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
		//Enables the vertex attribute array.
		glEnableVertexAttribArray(0);
		
		unsigned int index_buffer_id;
		glGenBuffers(1, &index_buffer_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		gl42::Shader shader = gl42::Shader("res/shaders/test.glsl");
		//Use after linking. Add to Shader Class.
		unsigned int loc = glGetUniformLocation(shader.getShaderId(), "time");
		shader.use();
		//Sets Callback function for key events.
		//glfwSetKeyCallback(win.getWinPtr(), key_callback);
		//Main Rendering loop.
		float i = 0;
		float inc = 0.01f;
		while(!win.shouldClose())
		{
			//Clear Buffer memory to remove garbage values
			glClear(GL_COLOR_BUFFER_BIT);
			//Draws the buffer. GL_TRIANGLES is a type of draw that tells OpenGL to draw triangles.
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			//Draws from index buffer.
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			//Swaps front and back buffer. OpenGL deafult is two buffer. One for back one for front.
			//Polls events. Like key events.
			//Access and modify uniform inside shader via location.
			glUniform1f(loc, i);
			win.updateWindow();
			i += inc;
			if (i > 1 || i < 0)
				inc = -inc;
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
