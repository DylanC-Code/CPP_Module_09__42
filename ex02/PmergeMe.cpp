/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:35:20 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 16:06:21 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

double PmergeMe::now()
{
	return static_cast<double>(clock()) / CLOCKS_PER_SEC * 1000000.0; // µs
}

template <typename Container>
void PmergeMe::printContainer(const Container &c)
{
	typename Container::const_iterator it = c.begin();
	while (it != c.end())
	{
		std::cout << *it;
		++it;
		if (it != c.end())
			std::cout << " ";
	}
	std::cout << std::endl;
}

std::vector<int> PmergeMe::parseInput(int argc, char **argv)
{
	std::vector<int> numbers;
	for (int i = 1; i < argc; i++)
	{
		std::istringstream iss(argv[i]);
		long val;
		if (!(iss >> val) || val < 0 || val > INT_MAX)
			throw std::runtime_error("Error");

		int n = static_cast<int>(val);

		if (std::find(numbers.begin(), numbers.end(), n) != numbers.end())
			throw std::runtime_error("Error: duplicate number");

		numbers.push_back(n);
	}
	return numbers;
}

template <typename Container>
void PmergeMe::fordJohnson(Container &c)
{
	if (c.size() <= 1)
		return;

	Container bigs, smalls;
	typename Container::iterator it = c.begin();
	while (it != c.end())
	{
		typename Container::iterator next = it;
		++next;
		if (next != c.end())
		{
			if (*it < *next)
			{
				bigs.push_back(*next);
				smalls.push_back(*it);
			}
			else
			{
				bigs.push_back(*it);
				smalls.push_back(*next);
			}
			++it;
		}
		else
		{
			bigs.push_back(*it);
		}
		++it;
	}

	fordJohnson(bigs);

	for (typename Container::iterator sit = smalls.begin(); sit != smalls.end(); ++sit)
	{
		typename Container::iterator pos =
			std::lower_bound(bigs.begin(), bigs.end(), *sit);
		bigs.insert(pos, *sit);
	}

	c = bigs;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &v)
{
	fordJohnson(v);
}

void PmergeMe::fordJohnsonList(std::list<int> &l)
{
	fordJohnson(l);
}

void PmergeMe::run(int argc, char **argv)
{
	std::vector<int> input = parseInput(argc, argv);

	std::cout << "Before: ";
	printContainer(input);

	// VECTOR
	std::vector<int> v(input.begin(), input.end());
	double t1 = now();
	fordJohnsonVector(v);
	double t2 = now();

	std::cout << "After:  ";
	printContainer(v);

	// LIST
	std::list<int> l(input.begin(), input.end());
	double t3 = now();
	fordJohnsonList(l);
	double t4 = now();

	std::cout << "Time to process a range of " << input.size()
			  << " elements with std::vector : "
			  << std::fixed << std::setprecision(5) << (t2 - t1) << " us" << std::endl;

	std::cout << "Time to process a range of " << input.size()
			  << " elements with std::list   : "
			  << std::fixed << std::setprecision(5) << (t4 - t3) << " us" << std::endl;
}
