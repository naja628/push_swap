#include "t_destack.h"
#include "t_emul.h"
#include "utils.h"
#include <stdlib.h>
#include "get_next_line.h"

/* int sorting algo since, bc we don't have access
 * to lookup table, sorting is the "best" way to 
 * check for duplicates with a reasonable time complexity
 * (ie whatever the complexity of the sorting algo) */
static void    ft_int_swap(int *a, int *b)
{
        int     tmp;

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
		return;
	}
	pivot_ptr = tab;
	greater_ptr = tab + size - 1;
	while (pivot_ptr != greater_ptr)
	{
		if (*(pivot_ptr + 1) < *pivot_ptr )
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
	int i;

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

static void 	ft_check_exec_stdin(t_emul *t)
{
	char *line;
	int ec;

	line = get_next_line(0);
	ec = 0;
	while (ec == 0 && line)
	{
		ft_op_ofline(t, line, &ec);
		free(line);
		line = get_next_line(0);
	}
	if (ec == -1)
		ft_putstr_endl("Error.");
	else if (ft_issorted(t->a))
		ft_putstr_endl("ok");
	else 
		ft_putstr_endl("KO");
}

int main(int ac, char **av)
{
	t_destack	a;
	t_destack	b;
	t_emul		t;
	int			*xs;

	a = ft_newstack();
	xs = malloc(sizeof(int) * (ac - 1));
	if (!xs || ft_validate_input(xs, av + 1, &a, ac - 1) == -1)
	{
		ft_putstr_endl("Error.");
		return (-1);
	}
	free(xs);
	b = ft_newstack();
	t = ft_mk_emul(&a, &b);
	ft_check_exec_stdin(&t);
	ft_clear(t.a);
	ft_clear(t.b);
	return (0);
}
