/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:34:04 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 11:43:45 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <climits>

class PmergeMe
{
public:
	static void run(int argc, char **argv);

private:
	// parsing
	static std::vector<int> parseInput(int argc, char **argv);

	static void fordJohnsonVector(std::vector<int> &v);
	static void fordJohnsonList(std::list<int> &l);

	template <typename Container>
	static void fordJohnson(Container &c);

	template <typename Container>
	static void printContainer(const Container &c);

	static double now();
};
