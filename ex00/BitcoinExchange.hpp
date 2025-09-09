/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:21:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/08 16:44:51 by dcastor          ###   ########.fr       */
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

public:
	BitcoinExchange(std::ifstream &input_file);
};
