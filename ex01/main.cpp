/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:27:08 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 10:29:04 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "RPN.hpp"

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: invalid args number." << std::endl;
		exit(1);
	}

	try
	{
		const long res = RPN::calculate(argv[1]);
		std::cout << res << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		exit(2);
	}

	return 0;
}
