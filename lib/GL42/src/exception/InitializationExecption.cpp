/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitializationExecption.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:26 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/11 18:53:39 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>

#include "InitializationExecption.hpp"

const char *gl42::InitializationExecption::what() const noexcept
{
	return "Deneme";
}
