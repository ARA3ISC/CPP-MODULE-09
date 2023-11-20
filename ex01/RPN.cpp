/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:33:09 by maneddam          #+#    #+#             */
/*   Updated: 2023/11/20 18:33:09 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void calculate(std::stack<int>& myStack, char op)
{
	(void)myStack;
	switch (static_cast<int>(op))
	{
	case MULT:
		std::cout << "mult\n";
		break;
	case PLUS:
		std::cout << "plus\n";
		break;
	case SUBS:
		std::cout << "minus\n";
		break;
	case DIV:
		std::cout << "div\n";
		break;
	}
}

void startManupliationg(std::string exp)
{
	int i = 0;
	char *end;
	std::stack<int> myStack;
	std::string ops[4] = {"*", "/", "+", "-"};

	while (exp[i])
	{
		if (exp[i] == 32 || exp[i] == '\t')
		{
			i++;
			continue;
		}
		if (std::isdigit(exp[i]))
			myStack.push(static_cast<int>(std::strtod(&exp[i], &end)));
		if ((exp[i] == '*' || exp[i] == '+' || exp[i] == '/' || exp[i] == '-') && myStack.size() == 1)
			std::cout << "Error\n";
		else if (exp[i] == '*' || exp[i] == '+' || exp[i] == '/' || exp[i] == '-')
			calculate(myStack, exp[i]);

		i++;
	}

	// std::cout << "Stack\n";
	// while (!myStack.empty())
	// {
	// 	std::cout << myStack.top() << std::endl;
	// 	myStack.pop();
	// }


}
