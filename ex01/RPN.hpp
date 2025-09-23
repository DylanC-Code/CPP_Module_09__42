/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:34:50 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/23 10:04:55 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class RPN
{
private:
public:
	static const std::string operators;

	static void checkSyntax(const std::string &input);
	static bool isOperator(char c);

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
};
