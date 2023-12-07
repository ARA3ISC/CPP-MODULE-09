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
	std::deque<int> d;
	try
	{
		if (ac == 1)
			throw std::invalid_argument("Error: Invalid arguments");
		parseArguments(av);

		clock_t vector_start = clock();
		load(av, v);

		std::cout << "before: ";
		printContainer(v);

		sorting(v);
		clock_t vector_end = clock();

		clock_t deque_start = clock();
		load(av, d);
		sorting(d);
		clock_t deque_end = clock();

		std::cout << "after:  ";
		printContainer(v);

		double vector_f_time = static_cast<double>(vector_end - vector_start) / CLOCKS_PER_SEC;
		double deque_f_time = static_cast<double>(deque_end - deque_start) / CLOCKS_PER_SEC;
		std::cout<< std::fixed << std::setprecision(6) << "Time to process a range of " << v.size() << " with std::vector<int> : " << vector_f_time << " s" << std::endl;
		std::cout<< std::fixed << std::setprecision(6) << "Time to process a range of " << d.size() << " with std::deque<int>  : " << deque_f_time << " s" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
