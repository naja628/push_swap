/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:07:39 by najacque          #+#    #+#             */
/*   Updated: 2021/10/12 14:09:01 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else 
		return (0);
}

int	ft_atoi(const char *s)
{
	int	sign;
	int	acc;

	while (('\t' <= *s && *s <= '\r') || *s == ' ')
		++s;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		++s;
	}
	acc = 0;
	while (ft_isdigit(*s))
	{
		acc *= 10;
		acc += *s - '0';
		++s;
	}
	return (sign * acc);
}
