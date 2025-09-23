/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:27:08 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 09:43:40 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "RPN.hpp"

void check_args(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: invalid args number." << std::endl;
		exit(1);
	}
	try
	{
		RPN::checkSyntax(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		exit(2);
	}
}

int main(int argc, char const *argv[])
{
	check_args(argc, argv);
	return 0;
}
