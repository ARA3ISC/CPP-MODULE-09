/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:06:55 by maneddam          #+#    #+#             */
/*   Updated: 2023/11/21 11:06:55 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void parseArguments(char **av)
{
	char *end;
	long int n;

	int i = 1;
	while (av[i])
	{
		n = std::strtol(av[i] , &end, 10);
		if (*end || n > INT_MAX)
			throw std::invalid_argument("Error: Invalid argument");
		else {
			if (n < 0)
				throw std::invalid_argument("Error: Number not positive");
		}
		i++;
	}
}
