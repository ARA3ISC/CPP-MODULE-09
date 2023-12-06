/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:07:56 by maneddam          #+#    #+#             */
/*   Updated: 2023/11/21 11:07:56 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


int main(int ac, char **av)
{
	std::vector<long int> v;
	// std::deque<int> d;
	try
	{
		if (ac == 1)
			throw std::invalid_argument("Error: Invalid arguments");
		parseArguments(av);
		load(av, v);

		// ? print container elements before sorting
		std::cout << "before: ";
		printContainer(v);


		sorting(v);
		// load(av, d);
		// sorting();


		// ? print container elements before sorting
		std::cout << "after:  ";
		printContainer(v);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
