/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:04 by najacque          #+#    #+#             */
/*   Updated: 2021/12/15 18:08:32 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"

void	ft_putstr_endl(char const *s)
{
	while (*s)
		write(1, s++, 1);
	write (1, "\n", 1);
}

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (n != 0 && *s1)
	{
		if (*s1 != *s2)
			return ((t_uchar)(*s1) - (t_uchar)(*s2));
		++s1;
		++s2;
		--n;
	}
	if (n != 0)
		return ((t_uchar)(*s1) - (t_uchar)(*s2));
	else
		return (0);
}
