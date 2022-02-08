/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:55 by najacque          #+#    #+#             */
/*   Updated: 2022/02/08 16:55:56 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "t_destack.h"
#include "t_emul.h"
#include "utils.h"
#include <stdlib.h>
#include "ft_strsplit.h"
#include "check_exec.h"

/* int sorting algo since, bc we don't have access
 * to lookup table, sorting is the "best" way to
 * check for duplicates with a reasonable time complexity
 * (ie whatever the complexity of the sorting algo) */
static void	ft_int_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* in place quicksort */
static void	ft_sort_int_tab(int *tab, int size)
{
	int	*pivot_ptr;
	int	*greater_ptr;

	if (!tab || size == 1 || size == 0)
	{
		return ;
	}
	pivot_ptr = tab;
	greater_ptr = tab + size - 1;
	while (pivot_ptr != greater_ptr)
	{
		if (*(pivot_ptr + 1) < *pivot_ptr)
		{
			ft_int_swap(pivot_ptr, pivot_ptr + 1);
			++pivot_ptr;
		}
		else
		{
			ft_int_swap(pivot_ptr + 1, greater_ptr--);
		}
	}
	ft_sort_int_tab(tab, pivot_ptr - tab);
	ft_sort_int_tab(pivot_ptr + 1, size - (pivot_ptr - tab) - 1);
}

/* return -1 if input is invalid or bad alloc happens
 * 0 otherwise
 * and fill a and xs with the input */
static int	ft_validate_input(int *xs, char **strs, t_destack *a, int sz)
{
	int	errc;
	int	i;

	errc = 0;
	i = sz - 1;
	while (errc == 0 && i >= 0)
	{
		xs[i] = ft_atoi_errcode(strs[i], &errc);
		if (ft_push(a, xs[i--]) == -1)
			errc = -1;
	}
	if (errc == -1)
		return (-1);
	ft_sort_int_tab(xs, sz);
	i = 0;
	while (++i < sz)
		if (xs[i - 1] == xs[i])
			return (-1);
	return (0);
}

static void	ft_check_and_cleanup(t_destack *a)
{
	t_destack	b;
	t_emul		t;

	b = ft_newstack();
	t = ft_mk_emul(a, &b);
	ft_check_exec_stdin(&t);
	ft_clear(t.a);
	ft_clear(t.b);
}

int	main(int ac, char **av)
{
	t_destack	a;
	int			*xs;
	char		**strargs;

	if (ac == 1)
		return (0);
	strargs = av + 1;
	if (ac == 2)
		strargs = ft_strsplit(av[1], ' ', &ac);
	a = ft_newstack();
	xs = malloc(sizeof(int) * (ac - 1));
	if (!xs || ft_validate_input(xs, strargs, &a, ac - 1) == -1)
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	free(xs);
	if (strargs != av + 1)
	{
		free(*strargs);
		free(strargs);
	}
	ft_check_and_cleanup(&a);
	return (0);
}
