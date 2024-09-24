/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:59:51 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/16 19:36:41 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <glfw3.h>
#include <string>

namespace gl42
{
	class Window
	{
		private:
			GLFWwindow* win_ptr;
			const std::string &title;
			int width;
			int height;
		public:
			Window(int width, int height, const std::string &title, GLFWmonitor *monitor, GLFWwindow *share);
			~Window();
		public:
			GLFWwindow* getWinPtr() const;
			int getWidth() const;
			int getHeight() const;
		public:
			bool shouldClose();
			void setShouldClose();
		public:
			static void setWindowHint(int hint, int value);
	};
}
