/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:51:03 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 10:24:02 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <stdexcept>

// Helpers

static std::string trim(const std::string &s)
{
	std::string::size_type a = 0, b = s.size();
	while (a < b && std::isspace(static_cast<unsigned char>(s[a])))
		++a;
	while (b > a && std::isspace(static_cast<unsigned char>(s[b - 1])))
		--b;
	return s.substr(a, b - a);
}

static bool isLeap(int y) { return (y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0)); }

static int daysInMonth(int y, int m)
{
	static const int d[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (m == 2)
		return d[1] + (isLeap(y) ? 1 : 0);
	return (m >= 1 && m <= 12) ? d[m - 1] : 0;
}

// ************************* //
// Private Members functions //
// ************************* //

std::string BitcoinExchange::parseDate(const std::string &raw)
{
	std::string s = trim(raw);
	if (s.size() != 10 || s[4] != '-' || s[7] != '-')
		throw std::runtime_error("Invalid date");
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			throw std::runtime_error("Invalid date");
	}

	int y = 0, m = 0, d = 0;
	{
		std::istringstream yy(s.substr(0, 4));
		yy >> y;
		if (!yy || !yy.eof())
			throw std::runtime_error("Invalid date");
		std::istringstream mm(s.substr(5, 2));
		mm >> m;
		if (!mm || !mm.eof())
			throw std::runtime_error("Invalid date");
		std::istringstream dd(s.substr(8, 2));
		dd >> d;
		if (!dd || !dd.eof())
			throw std::runtime_error("Invalid date");
	}

	if (m < 1 || m > 12)
		throw std::runtime_error("Invalid date");
	int mdays = daysInMonth(y, m);
	if (d < 1 || d > mdays)
		throw std::runtime_error("Invalid date");

	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(4) << y << "-"
		<< std::setw(2) << m << "-" << std::setw(2) << d;
	return oss.str();
}

double BitcoinExchange::parseExchangeRate(const std::string &raw)
{
	std::string s = trim(raw);
	double v = 0.0;

	if (s.empty())
		throw std::runtime_error("Empty value");
	if (s[0] == '-')
		throw std::runtime_error("Value must be positive");
	std::istringstream iss(s);
	iss >> v;

	if (!iss || !iss.eof())
		throw std::runtime_error("Invalid value");

	if (v < 0.0)
		throw std::runtime_error("Negative value");
	return v;
}

float BitcoinExchange::parseValue(const std::string &raw)
{
	std::string s = trim(raw);
	float v = 0.0;

	if (s.empty())
		throw std::runtime_error("bad input");
	if (s[0] == '-')
		throw std::runtime_error("not a positive number");
	std::istringstream iss(s);
	iss >> v;
	if (!iss || !iss.eof())
		throw std::runtime_error("bad input");
	if (v < 0.0)
		throw std::runtime_error("not a positive number");
	if (v > 1000)
		throw std::runtime_error("too large a number");
	return v;
}

double BitcoinExchange::findExchangeRate(const std::string &date, const std::map<std::string, double> &data)
{
	std::map<std::string, double>::const_iterator it = data.find(date);
	if (it != data.end())
		return it->second;
	it = data.lower_bound(date);
	if (it == data.begin())
		throw std::runtime_error("No exchange rate available");
	--it;
	return it->second;
}

// Constructors

BitcoinExchange::BitcoinExchange(std::ifstream &input_file)
{
	std::string line;

	if (std::getline(input_file, line))
	{
		if (line != "date,exchange_rate")
			throw std::runtime_error("Invalid header");
	}
	else
		throw std::runtime_error("Empty file");
	while (std::getline(input_file, line))
	{
		std::string::size_type commaPosition = line.find(',');
		if (commaPosition == std::string::npos)
			throw std::runtime_error("Missing ',' separator");
		std::string date = BitcoinExchange::parseDate(line.substr(0, commaPosition));
		this->_data[date] = BitcoinExchange::parseExchangeRate(line.substr(commaPosition + 1));
	}
}

// Public Member Functions

void BitcoinExchange::convert_and_display_input_file(std::ifstream &bitcoin_input_stream) const
{
	std::string line;

	if (std::getline(bitcoin_input_stream, line))
	{
		if (line != "date | value")
			throw std::runtime_error("Invalid bitcoin input streaam header");
		while (std::getline(bitcoin_input_stream, line))
		{
			try
			{

				std::string::size_type barPosition = line.find('|');
				if (barPosition == std::string::npos)
					throw std::runtime_error("Missing '|' separator");
				std::string date = BitcoinExchange::parseDate(line.substr(0, barPosition));
				float value = BitcoinExchange::parseValue(line.substr(barPosition + 1));
				double exchange_rate = BitcoinExchange::findExchangeRate(date, this->_data);
				std::cout << date << " => " << value << " = " << value * exchange_rate << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cout << "Error: " << e.what() << std::endl;
			}
		}
	}
}
