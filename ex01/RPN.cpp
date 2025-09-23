/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:36:06 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 10:06:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

const std::string RPN::operators = "*/+-";

bool RPN::isOperator(char c)
{
	return (RPN::operators.find(c) != std::string::npos);
}

void RPN::checkSyntax(const std::string &input)
{
	int segment_len;
	bool isEmpty = true;

	segment_len = 0;
	if (input.empty())
		throw RPN::InputEmptyException();
	for (size_t i = 0; i < input.size(); i++)
	{
		if (isspace(input[i]))
		{
			segment_len = 0;
			continue;
		}
		isEmpty = false;
		if (++segment_len > 1)
			throw RPN::SegmentTooLongException();
		if (isdigit(input[i]) || RPN::isOperator(input[i]))
			continue;
		throw RPN::InvalidSymbolException(input[i]);
	}
	if (isEmpty)
		throw RPN::InputEmptyException();
}

// Internal Exceptions

const char *RPN::SegmentTooLongException::what() const throw()
{
	return ("segment too long.");
}

RPN::InvalidSymbolException::InvalidSymbolException(const char c) : _msg("")
{
	std::string msg = "invalid symbol '";
	msg += c;
	msg += "'.";
	this->_msg = msg;
}

RPN::InvalidSymbolException::~InvalidSymbolException() throw() {};

const char *RPN::InvalidSymbolException::what() const throw()
{
	return (_msg.c_str());
};

const char *RPN::InputEmptyException::what() const throw()
{
	return "input empty.";
}
