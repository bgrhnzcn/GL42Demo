/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:46 by buozcan           #+#    #+#             */
/*   Updated: 2024/11/19 21:00:55 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl42.hpp"
#include <cstdlib>
#include <iostream>

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
	gl42::Window win(WIDTH, HEIGHT, "GL42");
	if (win.getWinPtr() == nullptr)
		return (1);
	glfwMakeContextCurrent(win.getWinPtr());
	//vertex array
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	gl42::ObjAsset asset("..\\res\\models\\test.obj");
	asset.printAsset();
	//Must be generated for Core Profile. Compatibility profile does not require this.
	gl42::VertexArray va;
	gl42::VertexBuffer model(asset);
	//Generate generic type of buffer and assing it to buffer_id.
	//Modify vertex attribute array. 0 is the index of the attribute.
	//2 is the size of the attribute as count. GL_FLOAT is the type of the attribute.
	//GL_FALSE is the normalization of the attribute. 2 * sizeof(float) is the stride of the attribute.
	//0 is the offset of the attribute inside single vertex.
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gl42::Vertex), 0));
	//Enables the vertex attribute array.
	glEnableVertexAttribArray(0);
	gl42::Shader shader("..\\res\\shaders\\vertex\\v_test.glsl", "..\\res\\shaders\\fragment\\f_test.glsl");
	//Use after linking. Add to Shader Class.
	unsigned int loc = glGetUniformLocation(shader.getShaderId(), "time");
	shader.use();
	//Sets Callback function for key events.
	glfwSetKeyCallback(win.getWinPtr(), &key_callback);
	//Main Rendering loop.
	float i = 0;
	while(!win.shouldClose())
	{
		//Clear Buffer memory to remove garbage values
		glClear(GL_COLOR_BUFFER_BIT);
		//Draws the buffer. GL_TRIANGLES is a type of draw that tells OpenGL to draw triangles.
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//Draws from index buffer.
		GLCall(glDrawArrays(GL_TRIANGLES, 0, (GLsizei)asset.vertices.size() / 3));
		//Swaps front and back buffer. OpenGL deafult is two buffer. One for back one for front.
		//Polls events. Like key events.
		//Access and modify uniform inside shader via location.
		glUniform1f(loc, (gl42::Math::sin(i) / 2) + 0.5f);
		win.updateWindow();
		i += 0.001f;
	}
}
