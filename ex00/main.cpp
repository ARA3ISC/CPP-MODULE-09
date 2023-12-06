/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:52:36 by maneddam          #+#    #+#             */
/*   Updated: 2023/12/05 18:06:34 by maneddam         ###   ########.fr       */
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
            loadData(mydb);
            parseTheFile(av[1], mydb);
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
