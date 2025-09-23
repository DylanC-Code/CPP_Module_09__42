/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:34:50 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 11:12:13 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <deque>

class RPN
{
private:
	static std::deque<long> _operands;
	static long _res;

	static bool _isOperator(char c);
	static void _compute(char op);
	static void _checkSyntax(const std::string &input);

public:
	static const std::string operators;

	static long calculate(const std::string &input);

	class SegmentTooLongException : public std::exception
	{
		const char *what() const throw();
	};

	class InvalidSymbolException : public std::exception
	{
	public:
		InvalidSymbolException(const char c);
		virtual ~InvalidSymbolException() throw();
		virtual const char *what() const throw();

	private:
		std::string _msg;
	};

	class InputEmptyException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class OperatorRequiredException : public std::exception
	{
	private:
		std::string _msg;

	public:
		OperatorRequiredException();
		virtual ~OperatorRequiredException() throw();
		virtual const char *what() const throw();
	};

	class OperandRequiredException : public std::exception
	{
	private:
		std::string _msg;

	public:
		OperandRequiredException(const char c);
		virtual ~OperandRequiredException() throw();
		virtual const char *what() const throw();
	};

	class ZeroedDivisionException : public std::exception
	{
		virtual const char *what() const throw();
	};

	friend class OperatorRequiredException;
};
