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
	int last;
	int b_last;
	int result;

	last = myStack.top();
	myStack.pop();
	b_last = myStack.top();
	myStack.pop();
	if (op == '*')
		result = b_last * last;
	else if (op == '+')
		result = b_last + last;
	else if (op == '/')
		result = b_last / last;
	else if (op == '-')
		result = b_last - last;

	myStack.push(result);
}

void startManupilating(std::string exp)
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
			throw std::runtime_error("Error");
		else if (exp[i] == '*' || exp[i] == '+' || exp[i] == '/' || exp[i] == '-')
			calculate(myStack, exp[i]);
		i++;
	}
	if (myStack.size() != 1)
		std::cout << "Error\n";
	else
		std::cout << "result : " << myStack.top() << std::endl;
}
