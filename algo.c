#include "t_emul.h"
#include "t_destack.h"
#include "algo.h"

/****** DEBUG ****/
#include <stdio.h>
void print_stack(t_destack *t)
{
	t_node *it = t->top;

	while (it)
	{
		//printf("%d_", it->x);
		it = it->down;
	}
	//printf("\n");
}
/*	END DEBUG */

// opt masks
#define Revo 1
#define AtBot 2

int	ft_less(int x, int y, int rev)
{
	if (rev)
		return (x > y);
	else 
		return (x < y);
}
// TODO file for these funs
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

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	else 
		return (x);
}

/* maybe todo : improve to not compute the size */
void	ft_smart_rotate(t_emul *t, t_aorb aorb, int shift)
{
	int			rshift;
	t_destack	*u;

	//printf("shift : %d\n", shift);
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
		{
			//printf("sr : shift %d\n", shift);
			ft_rx(t, aorb);
		}
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
		//printf("bouh\n");
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
 * if (opt & Revo) sort in reverse order 
 * if (opt & AtBot) place them at the bottom
 * before rotating to the desired place this function implements the 
 * following table:
 * perm : ops - final layout (where | is the rest of the list)
 * 1 2 3 : / - 1 2 3 |
 * 1 3 2 : rx sx - 2 3 | 1
 * 2 1 3 : sx - 1 2 3 |
 * 2 3 1 : rx sx rrx sx - 1 2 3 |
 * 3 1 2 : sx rx sx - 2 3 | 1
 * 3 2 1 : sx rx sx rrx sx - 1 2 3 | */
static void	ft_sort_topmost3max(t_emul *t, t_aorb aorb, size_t n, int opt)
{
	t_destack	*u;
	int			rot;

	u = ft_getaorb(t, aorb);
	if (!ft_atleast_n(u, 4))
	{
		ft_sort3orless(t, aorb, (opt & Revo));
		return ;
	}
	rot = 0;
	if (n < 3)
	{
		if (n == 2 && ft_less(ft_nth(u, 1), ft_nth(u, 0), (opt & Revo)))
			ft_sx(t, aorb);
	}
	else 
		rot = ft_sorttop_helper(t, aorb, 0, (opt & Revo));
	if (opt & AtBot)
		ft_smart_rotate(t, aorb, n - rot);
	else 
		ft_smart_rotate(t, aorb, 0 - rot);
}
		
/*static void	ft_sort2orless(t_emul *t, t_aorb aorb, size_t n, int opt)
{
	t_destack	*u;
	
	u = ft_getaorb(t, aorb);
	if (n == 1 && (opt & AtBot))
		ft_rx(t, aorb);
	if (n == 0 || n == 1)
		return;
	if (ft_less(ft_nth(u, 1), ft_nth(u, 0), (opt & Revo)))
			ft_sx(t, aorb);
	if (opt & AtBot)
	{
		ft_rx(t, aorb);
		ft_rx(t, aorb);
	}
}
*/

// TODO file for these 5 fun
static void	ft_split(t_emul *t, t_aorb aorb, size_t n)
{
	n /= 2;
	while (n)
	{
		ft_px(t, ft_other(aorb));
		--n;
	}
}

static void	ft_merge_atbot(t_emul *t, t_aorb aorb, size_t naorb, size_t nbora, int rev)
{
	//printf("merge at bot \n");
	t_destack	*taorb;
	t_destack	*tbora;

	if (naorb == 0 && nbora == 0)
		return ;
	taorb = ft_getaorb(t, aorb);
	tbora = ft_getaorb(t, ft_other(aorb));
	if (naorb == 0 || (nbora != 0 
			&& ft_less(ft_nth(tbora, 0), ft_nth(taorb, 0), rev)))
	{
		ft_px(t, aorb);
		--nbora;
	}
	else 
		--naorb;
	ft_rx(t, aorb);
	ft_merge_atbot(t, aorb, naorb, nbora, rev);
}

static void	ft_merge_attop(t_emul *t, t_aorb aorb, size_t naorb, size_t nbora, int rev)
{
	//printf("merge at top\n");
	t_destack	*taorb;
	t_destack	*tbora;

	if (naorb == 0 && nbora == 0)
		return ;
	taorb = ft_getaorb(t, aorb);
	tbora = ft_getaorb(t, ft_other(aorb));
	if (naorb == 0 || (nbora != 0 
				&& ft_less(ft_rnth(taorb, 0), ft_nth(tbora, 0), rev)))
	{
		ft_px(t, aorb);
		--nbora;
	}
	else
	{
		ft_rrx(t, aorb);
		--naorb;
	}
	ft_merge_attop(t, aorb, naorb, nbora, rev);
}

void	ft_subpb_szs(size_t *buff, size_t n)
{
	buff[0] = n / 4;
	buff[1] = n / 4;
	buff[2] = n / 2;
	n -= buff[0] + buff[1] + buff[2];
	if (n >= 1)
		++(buff[1]);
	if (n == 2)
		++(buff[2]);
}	

/* Merging must happen according to the following table.
 * (eg to get (opt 0) in stack a, after splitting
 * the half in a must be sorted using opt AtBot
 * and the half in b using opt Revo)
 * table :
 * opt 			to : from
 * (0)			->| : |->, <-|
 * Revo			<-| : |<-, ->|
 * AtBot		|-> : ->|, ->|
 * Revo | AtBot	|<- : <-|, <-| */

/* sort the n topmost element of the stack a or b 
 * expects n to be no greater than the size of the 
 * stack a or b 
 * and a valid t_emul struct */
void	ft_merge_sort(t_emul *t, t_aorb aorb, size_t n, int opt)
{
	//printf("sorting %zu in %c with opt %u:\n", n, (aorb == A)? 'a' : 'b', opt);
	//print_stack(ft_getaorb(t, A));
	//print_stack(ft_getaorb(t, B));
	size_t	szs[3];
	int		rev_bora;

	ft_subpb_szs(szs, n);
	////printf("%zu\n", szs[1]);
	//if (ft_nfstsorted(ft_getaorb(t, aorb), n))
	//	return ;
	if (n <= 3)
	{
		ft_sort_topmost3max(t, aorb, n, opt);
		return ;
	}
	if (opt & AtBot)
		rev_bora = (opt & Revo);
	else 
		rev_bora = (~opt & Revo);
	ft_split(t, aorb, szs[0] + szs[1]);
	ft_merge_sort(t, ft_other(aorb), szs[0], AtBot | rev_bora);
	ft_merge_sort(t, aorb, szs[1], (~rev_bora & Revo));
	ft_merge_attop(t, ft_other(aorb), szs[0], szs[1], rev_bora);
	ft_merge_sort(t, aorb, szs[2], (~opt & AtBot) | (opt & Revo));
	if (opt & AtBot)
		ft_merge_atbot(t, aorb, szs[2], szs[0] + szs[1], (opt & Revo));
	else 
		ft_merge_attop(t, aorb, szs[2], szs[0] + szs[1], (opt & Revo));
	//printf("out :\n");
	//print_stack(ft_getaorb(t, A));
	//print_stack(ft_getaorb(t, B));
}
