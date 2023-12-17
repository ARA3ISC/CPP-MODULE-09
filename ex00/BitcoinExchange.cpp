/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:42:20 by maneddam          #+#    #+#             */
/*   Updated: 2023/12/17 13:22:09 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void retrieveData(std::string line, std::string& y, std::string& m, std::string& d, std::string& v)
{
	int i = 0;
	int dashes = 0;
	int pipe = 0;

	while (line[i] == 32 || line[i] == '\t')
		i++;
	while (line[i] && line[i] != ','&& line[i] != '|')
	{
		if (line[i] != '-' && dashes == 0)
			y += line[i];
		else if (line[i] != '-' && dashes == 1)
			m += line[i];
		else if (line[i] == '|')
			pipe++;
		else if (line[i] != '-' && dashes == 2 && pipe != 1 && line[i] != 32)
			d += line[i];
		if (line[i] == '-')
			dashes++;
		i++;
	}

	while (line[i])
		v += line[++i];
}

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

int is_leap_year(std::string year, std::string month, std::string day)
{
	char *end;

	double yr = std::strtod(year.c_str(), &end);
	double d = std::strtod(day.c_str(), &end);
	double m = std::strtod(month.c_str(), &end);
	(void)m;
	if (d < 1)
		throw 1;
	if (static_cast<int>(yr) % 4 == 0)
		return 1;
	return 0;
}

void parseDate(std::string toCheck, int field)
{
	char *end;
	double data;

	data = std::strtod(toCheck.c_str(), &end);
	if (field != 3)
		if (toCheck.find('.') != std::string::npos)
			throw 1;
	switch (field)
	{
		case 0:
			if (*end || data > 2022 || data < 2009)
				throw 1;
			break;
		case 1:
			if (*end || data > 12 || data <= 0 || toCheck.size() != 2)
				throw 1;
			break;
		case 2:
			if (*end || data > 31 || data <= 0 || toCheck.size() != 2)
				throw 1;
			break;
		case 3:
			if (*end || data > 1000 || data < 0)
			{
				if (data < 0)
					throw -1;
				else if (data > 1000)
					throw 999;
				throw 1;
			}
			break;
	}
}

void beginCalculation(std::string year, std::string month, std::string day, std::string value, std::map<unsigned long, double>& mydb)
{
	char *end1;
	char *end2;
	std::string key = year + month + day;
	double k = std::strtod(key.c_str(), &end1);
	double v = std::strtod(value.c_str(), &end2);

	if (mydb.find(k) != mydb.end())
	{
		float result = mydb.at(k) * v;
		std::cout << year << "-" << month << "-" << day << " => " << v << " = " << result << std::endl;
	}
	else
	{
		std::map<unsigned long, double>::iterator it = mydb.lower_bound(k);
		it--;
		std::cout << year << "-" << month << "-" << day << " => " << v << " = " << it->second * v << std::endl;
	}
}

void checkDaysOfMonth(std::string month, std::string day, bool leap)
{
	char *end;

	double m = std::strtod(month.c_str(), &end);
	double d = std::strtod(day.c_str(), &end);

	std::map<int, int> dayPerMonth;

	dayPerMonth[1] = 31;
	dayPerMonth[2] = 28;
	dayPerMonth[3] = 31;
	dayPerMonth[4] = 30;
	dayPerMonth[5] = 31;
	dayPerMonth[6] = 30;
	dayPerMonth[7] = 31;
	dayPerMonth[8] = 31;
	dayPerMonth[9] = 30;
	dayPerMonth[10] = 31;
	dayPerMonth[11] = 30;
	dayPerMonth[12] = 31;

	if (leap)
		dayPerMonth[2] = 29;
	if (d > dayPerMonth[m])
		throw 1;
}

void parseLine(std::string line, std::map<unsigned long, double>& mydb)
{
	std::string year;
	std::string month;
	std::string day;
	std::string value;
	if (line.empty())
		return ;
	if (countPipesDashes(line))
		std::cout << RED << "Error: bad input => "<< RESET << line  << std::endl;
	else
	{
		retrieveData(line, year, month, day, value);
		try
		{
			parseDate(year, 0);
			parseDate(month, 1);
			parseDate(day, 2);
			parseDate(value, 3);
			if (is_leap_year(year, month, day))
				checkDaysOfMonth( month, day, 1);
			else
				checkDaysOfMonth( month, day, 0);
			beginCalculation(year, month, day, value, mydb);
		}
		catch(int e)
		{
			if (e == -1)
				std::cerr << RED << "Error: not a positive number." << RESET << std::endl;
			else if (e == 1)
			{
				int i = 0;
				while (line[i] == 32 || line[i] == '\t')
					i++;
				std::cerr << RED << "Error: bad input => " << RESET << &line[i] << std::endl;
			}
			else
				std::cerr << RED << "Error: too large number." << RESET << std::endl;
		}
	}
}

void parseTheFile(std::string toOpen, std::map<unsigned long, double>& mydb)
{
	std::fstream obj;
	std::string line;

	obj.open(toOpen.c_str(), std::ios::in);
	if (obj.is_open())
	{
		getline(obj, line);
		while (line.empty())
		{
			if (getline(obj, line).eof())
				break;
		}

		if (line != "date | value")
			throw std::runtime_error("Invalid header line");
		else
		{
			while (1)
			{
				if (getline(obj, line).eof())
					break;
				parseLine(line, mydb);
			}
		}
		obj.close();
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

	mydb.insert(std::pair<unsigned long, double>(static_cast<unsigned long>(v1), v2));

}

void insertIntoDB(std::map<unsigned long, double>& mydb, std::string line)
{
	std::string year;
	std::string month;
	std::string day;
	std::string value;

	retrieveData(line, year, month, day, value);
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
				break;
			insertIntoDB(mydb, line);
		}
	}
	else
		throw std::runtime_error("Error: could not open file.");
}
