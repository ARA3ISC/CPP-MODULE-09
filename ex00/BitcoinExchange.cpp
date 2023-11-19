/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:42:20 by maneddam          #+#    #+#             */
/*   Updated: 2023/11/19 16:44:31 by maneddam         ###   ########.fr       */
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

void insertLineIntoDB(std::string year, std::string month, std::string day, std::string value, std::map<unsigned long, double>& mydb)
{
	std::string key = year + month + day;
	char *end;
	char *end1;
	double v1;
	double v2;

	v1 = std::strtod(key.c_str(), &end);
	v2 = std::strtod(value.c_str(), &end1);


	// std::cout << v2 << std::endl;
	mydb.insert(std::pair<unsigned long, double>(static_cast<unsigned long>(v1), static_cast<double>(v2)));
	
	
	// std::cout << mydb.begin()->second << std::endl;
	// exit(0);
}

void insertIntoDB(std::map<unsigned long, double>& mydb, std::string line)
{
	int i = 0;
	int dashes = 0;
	std::string year;
	std::string month;
	std::string day;
	std::string value;

	
	while (line[i] && line[i] != ',')
	{
		if (line[i] != '-' && dashes == 0)
			year += line[i];
		else if (line[i] != '-' && dashes == 1)
			month += line[i];
		else if (line[i] != '-' && dashes == 2)
			day += line[i]; 
		else
			dashes++;
		i++;
	}
	while (line[i])
		value += line[++i];


	
	// std::cout << year << "-" << month << "-" << day << "," << value << "\n";
	// (void)mydb;
	insertLineIntoDB(year, month, day, value, mydb);
}

void loadData(std::map<unsigned long, double>& mydb)
{
	std::fstream obj;
	std::string line;
	obj.open("data.csv", std::ios::in);
	if (obj.is_open())
	{
		getline(obj, line);
		while (1)
		{
			if (getline(obj, line).eof())
			{
				insertIntoDB(mydb, line);
				break; 
			}
			insertIntoDB(mydb, line);
		}
		for (std::map<unsigned long, double>::iterator it = mydb.begin(); it != mydb.end() ; ++it) 
		{
			std::cout << it->first << "," << it->second << std::endl;
		}
	}
	else
		throw std::runtime_error("Error: could not open file.");

	(void)mydb;

}