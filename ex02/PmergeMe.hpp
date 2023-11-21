#pragma once

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <exception>
#include <vector>
#include <deque>
#include <limits.h>


void parseArguments(char **av);

template <typename T>
void load(char **av, T& container)
{
	char *end;
	long int nbr;
	int i = 1;
	while (av[i])
	{
		nbr = std::strtol(av[i], &end, 10);
		container.push_back(nbr);
		i++;
	}

	// std::cout << "vector :\n";
	// for (typename T::iterator it = container.begin(); it != container.end() ; it++)
	// 	std::cout << *it << " ";
}

template<typename T>
void merge(T& leftContainer, T& rightContainer, T& container)
{
	int leftsize = leftContainer.size();
	int rightsize = rightContainer.size();
	int i = 0;
	int l = 0;
	int r = 0;

	while (l < leftsize && r < rightsize)
	{
		if (leftContainer[l] < rightContainer[r])
		{
			container.push_back(leftContainer[l]);
			l++;
		}
		else
		{
			container.push_back(rightContainer[r]);
			r++;
		}
		i++;
	}
}

template<typename T>
void sorting(T& container)
{
	T leftContainer;
	T rightContainer;
	int half = container.size() / 2;
	int i = 0;

	if (container.size() == 1)
		return;

	for (; i < half; i++)
		leftContainer.push_back(container[i]);

	int size = container.size();
	for (; half < size; half++)
		rightContainer.push_back(container[half]);



	// ? print container elements
	// int size = leftContainer.size();
	// std::cout << "left : ";
	// for (i = 0; i < size; ++i)
	// 	std::cout << leftContainer[i] << " ";

	// std::cout << "\nright : ";
	//  size = rightContainer.size();
	// for (i = 0; i < size; ++i)
	// 	std::cout << rightContainer[i] <<  " ";
	// std::cout << "\n";


	sorting(leftContainer);
	sorting(rightContainer);

	merge(leftContainer, rightContainer, container);

}
