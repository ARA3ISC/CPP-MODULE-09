/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:42:20 by maneddam          #+#    #+#             */
/*   Updated: 2023/11/19 15:29:40 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool countPipesDashes(std::string line)
{
    int pipes = 0;
    int dashes = 0;

    pipes = std::count(line.begin(), line.end(), '|');
    dashes = std::count(line.begin(), line.end(), '-');
    if (pipes != 1 || dashes != 2)
        return true;
    return false;
}

void parseLine(std::string line)
{
    std::string year;
    std::string month;
    std::string day;
    // std::cout << line << "\n";
    if (countPipesDashes(line))
        std::cout << "Error: bad input => " << line << std::endl;
    else
    {
        
    }
}

void parseTheFile(std::string toOpen)
{
    std::fstream obj;
    std::string line;

    obj.open(toOpen.c_str(), std::ios::in);
    if (obj.is_open())
    {
        getline(obj, line);
        while (line.empty())
            getline(obj, line);

        if (line != "date | value")
            throw std::runtime_error("Invalid header line");
        else
        {
            while (1)
            {
                if (getline(obj, line).eof())
                    break; 
                parseLine(line);
            }
        }
    }
    else
        throw std::runtime_error("Error: could not open file.");
}

void insertIntoDB(std::map<unsigned long, unsigned int>& mydb, std::string line)
{
    
}

void loadData(std::map<unsigned long, unsigned int>& mydb)
{
    std::fstream obj;
    std::string line;
    obj.open("data.csv", std::ios::in);
    if (obj.is_open())
    {
        getline(obj, line);
        while (getline(obj, line).eof())
        {
            insertIntoDB(mydb, line);
        }
    }
    else
        throw std::runtime_error("Error: could not open file.");

    (void)mydb;

}