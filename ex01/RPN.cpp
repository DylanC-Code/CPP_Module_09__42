/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:36:06 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 11:12:40 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

const std::string RPN::operators = "*/+-";
std::deque<long> RPN::_operands;
long RPN::_res = 0;

bool RPN::_isOperator(char c)
{
	return (RPN::operators.find(c) != std::string::npos);
}

void RPN::_compute(char op)
{
	if (_operands.size() < 2)
		throw RPN::OperandRequiredException(op);

	long a = _operands[_operands.size() - 2];
	long b = _operands[_operands.size() - 1];

	_operands.pop_back();
	_operands.pop_back();

	long tmp;

	switch (op)
	{
	case '-':
		tmp = a - b;
		break;
	case '+':
		tmp = a + b;
		break;
	case '*':
		tmp = a * b;
		break;
	case '/':
		if (b == 0)
			throw ZeroedDivisionException();
		tmp = a / b;
		break;
	default:
		throw InvalidSymbolException(op);
	};

	_operands.push_back(tmp);
}

void RPN::_checkSyntax(const std::string &input)
{
	int segment_len;
	bool isEmpty;

	isEmpty = true;
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
		if (isdigit(input[i]) || RPN::_isOperator(input[i]))
			continue;
		throw RPN::InvalidSymbolException(input[i]);
	}
	if (isEmpty)
		throw RPN::InputEmptyException();
}

long RPN::calculate(const std::string &input)
{
	_operands.clear();

	RPN::_checkSyntax(input);

	for (size_t i = 0; i < input.size(); i++)
	{
		if (isspace(input[i]))
			continue;
		if (isdigit(input[i]))
			_operands.push_back(input[i] - '0');
		else if (_isOperator(input[i]))
			_compute(input[i]);
	}
	if (_operands.size() != 1)
		throw RPN::OperatorRequiredException();
	return (*_operands.rbegin());
}

// longernal Exceptions

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
	return ("input empty.");
}

RPN::OperatorRequiredException::OperatorRequiredException()
{
	_msg = "operator required.";
}
RPN::OperatorRequiredException::~OperatorRequiredException() throw() {};

const char *RPN::OperatorRequiredException::what() const throw()
{
	return this->_msg.c_str();
}

RPN::OperandRequiredException::OperandRequiredException(const char c)
{
	_msg = "the symbol '";
	_msg += c;
	_msg += "' should be an operand.";
}

RPN::OperandRequiredException::~OperandRequiredException() throw() {};

const char *RPN::OperandRequiredException::what() const throw()
{
	return this->_msg.c_str();
}

const char *RPN::ZeroedDivisionException::what() const throw()
{
	return "division by zero.";
}
