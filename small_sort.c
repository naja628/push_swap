#include "sort_utils.h"
#include "utils.h"

/* get the index of the maximum (min if rev)
 * of the 3 topmost vals of t */
static int	ft_imax3(t_destack *t, int rev)
{
	int	imax;

	if (ft_less(ft_nth(t, 1), ft_nth(t, 0), rev)
			&& ft_less(ft_nth(t, 2), ft_nth(t, 0), rev))
		imax = 0;
	else if (ft_less(ft_nth(t, 0), ft_nth(t, 1), rev) &&
			ft_less(ft_nth(t, 2), ft_nth(t, 1), rev))
		imax = 1;
	else 
		imax = 2;
	return (imax);
}


/* note : just the else part of the first if would suffice
 * (correctness wise)
 * but checking if the stack is small allows us to 
 * not temper with the time complexity of the whole algorithm...
 *
 * another solution would be to keep track of the size of the stacks
 */
static void	ft_smart_rotate(t_emul *t, t_aorb aorb, int shift)
{
	int			rshift;
	t_destack	*u;

	u = ft_getaorb(t, aorb);
	if (ft_atleast_n(u, 2 * ft_abs(shift)))
			rshift = -shift;
	else 
	{
		shift %= ft_stacksz(u);
		if (shift <= 0)
			shift += ft_stacksz(u);
		rshift = ft_stacksz(u) - shift;
	}
	if (rshift < 0 || (shift <= rshift && shift >= 0))
	{
		while (--shift + 1)
			ft_rx(t, aorb);
	}
	else
	{
		while (--rshift + 1)
			ft_rrx(t, aorb);
	}
}
	
/* sort the stack a or b when sz <= 3 
 * if rev == 1 sort in reverse order
 * note : ad hoc, non-general implementation
 * when sz = 3, this function implements the following table :
 * 1 2 3 : /
 * 1 3 2 : rrx sx
 * 2 1 3 : sx
 * 2 3 1 : rrx
 * 3 1 2 : rx
 * 3 2 1 : rx sx */
static void	ft_sort3orless(t_emul *t, t_aorb aorb, int rev)
{
	t_destack	*u;
	int			imax;

	u = ft_getaorb(t, aorb);
	if (ft_stacksz(u) == 2 && ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
		ft_sx(t, aorb);
	if (!(ft_stacksz(u) == 3))
		return ;
	imax = ft_imax3(u, rev);
	if (imax == 1)
		ft_rrx(t, aorb);
	if (imax == 0)
		ft_rx(t, aorb);
	if (ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
		ft_sx(t, aorb);
}

/* note : ad hoc, non-general implementation */
static int 	ft_sorttop_helper(t_emul *t, t_aorb aorb, int rot, int rev)
{
	t_destack *u;

	u = ft_getaorb(t, aorb);
	if (rot == 0 && ft_imax3(u, rev) == 1)
	{
		ft_rx(t, aorb);
		return (ft_sorttop_helper(t, aorb, 1 + rot, rev));
	}
	if (rot <= 1 && ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
	{
		ft_sx(t, aorb);
		return (ft_sorttop_helper(t, aorb, rot, rev));
	}
	if (rot == 1
		   	&& ft_less(ft_nth(u, 0), ft_nth(u, 1), rev)
			&& ft_less(ft_nth(u, 0), ft_rnth(u, 0), rev)
			&& ft_less(ft_rnth(u, 0), ft_nth(u, 1), rev))
	{
		ft_rrx(t, aorb);
		return (ft_sorttop_helper(t, aorb, rot - 1, rev));
	}
	return (rot);
}

/* sort the topmost 3 elements of the stack a or b 
 * (if there are less than 3 elems just sort it)
 * if (opt & REVO) sort in reverse order 
 * if (opt & ATBOT) place them at the bottom
 * before rotating to the desired place this function implements the 
 * following table:
 * perm : ops - final layout (where | is the rest of the list)
 * 1 2 3 : / - 1 2 3 |
 * 1 3 2 : rx sx - 2 3 | 1
 * 2 1 3 : sx - 1 2 3 |
 * 2 3 1 : rx sx rrx sx - 1 2 3 |
 * 3 1 2 : sx rx sx - 2 3 | 1
 * 3 2 1 : sx rx sx rrx sx - 1 2 3 | */
void	ft_sort_topmost3max(t_emul *t, t_aorb aorb, size_t n, int opt)
{
	t_destack	*u;
	int			rot;

	u = ft_getaorb(t, aorb);
	if (!ft_atleast_n(u, 4))
	{
		ft_sort3orless(t, aorb, (opt & REVO));
		return ;
	}
	rot = 0;
	if (n < 3)
	{
		if (n == 2 && ft_less(ft_nth(u, 1), ft_nth(u, 0), (opt & REVO)))
			ft_sx(t, aorb);
	}
	else 
		rot = ft_sorttop_helper(t, aorb, 0, (opt & REVO));
	if (opt & ATBOT)
		ft_smart_rotate(t, aorb, n - rot);
	else 
		ft_smart_rotate(t, aorb, 0 - rot);
}
