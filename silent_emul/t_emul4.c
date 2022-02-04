#include "../t_emul.h"

void	ft_rx(t_emul *t, t_aorb aorb)
{
	if (aorb == A)
		ft_ra(t);
	else
		ft_rb(t);
}

void	ft_rrx(t_emul *t, t_aorb aorb)
{
	if (aorb == A)
		ft_rra(t);
	else
		ft_rrb(t);
}

t_emul	ft_mk_emul(t_destack *a, t_destack *b)
{
	t_emul	t;

	t.a = a;
	t.b = b;
	return (t);
}

void	ft_op_ofline(t_emul *t, char *line, int *ec)
{
	if (!ft_strncmp(line, "pa\n", 3))
		ft_pa(t);
	else if (!ft_strncmp(line, "pb\n", 3))
		ft_pb(t);
	else if (!ft_strncmp(line, "sa\n", 3))
		ft_sa(t);
	else if (!ft_strncmp(line, "sb\n", 3))
		ft_sb(t);
	else if (!ft_strncmp(line, "ss\n", 3))
		ft_ss(t);
	else if (!ft_strncmp(line, "ra\n", 3))
		ft_ra(t);
	else if (!ft_strncmp(line, "rb\n", 3))
		ft_rb(t);
	else if (!ft_strncmp(line, "rr\n", 3))
		ft_rr(t);
	else if (!ft_strncmp(line, "rra\n", 4))
		ft_rra(t);
	else if (!ft_strncmp(line, "rrb\n", 4))
		ft_rrb(t);
	else if (!ft_strncmp(line, "rrr\n", 4))
		ft_rrr(t);
	else
		*ec = -1;
}
