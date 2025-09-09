/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:22:24 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/08 16:50:57 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	std::ifstream database_file("data.csv", std::ifstream::in);
	std::ifstream input_file(argv[1], std::ifstream::in);

	if (argc != 2 || !database_file || !input_file)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange btc(database_file);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
