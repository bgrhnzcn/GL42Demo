/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitializationExecption.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:26 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/11 18:59:28 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>

namespace gl42
{
	class InitializationExecption : public std::exception
	{
		public:
			virtual const char *what() const noexcept override;
	};
}
