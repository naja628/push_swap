#include "t_emul.h"
#include "t_destack.h"
#include "utils.h"

void	ft_sa(t_emul *t)
{
	ft_putstr_endl("sa");
	ft_swap(t->a);
}

void	ft_sb(t_emul *t)
{
	ft_putstr_endl("sb");
	ft_swap(t->b);
}

void	ft_ss(t_emul *t)
{
	ft_putstr_endl("ss");
	ft_swap(t->b);
	ft_swap(t->a);
}

void	ft_pa(t_emul *t)
{
	int	x;

	ft_putstr_endl("pa");
	x = ft_pop(t->b);
	ft_push(t->a, x);
}

void 	ft_pb(t_emul *t)
{
	int x;

	ft_putstr_endl("pb");
	x = ft_pop(t->a);
	ft_push(t->b, x);
}

