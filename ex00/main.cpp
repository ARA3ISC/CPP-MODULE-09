/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:52:36 by maneddam          #+#    #+#             */
/*   Updated: 2023/11/19 16:07:57 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    std::map<unsigned long, double> mydb;
    try
    {
        if (ac == 2)
        {
            (void)av;
            loadData(mydb);
            // parseTheFile(av[1]);
        }
        else
            std::cout << "Error: could not open file." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}