/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:21:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 10:16:57 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <iostream>
#include <map>

class BitcoinExchange
{
private:
	std::map<std::string, double> _data;

	// Members functions
	static std::string parseDate(const std::string &raw);
	static double parseExchangeRate(const std::string &raw);
	static float parseValue(const std::string &raw);
	static double findExchangeRate(const std::string &date, const std::map<std::string, double> &data);

public:
	BitcoinExchange(std::ifstream &exchange_data_file);

	void convert_and_display_input_file(std::ifstream &bitcoin_input_stream) const;
};
