/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_emul.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:08 by najacque          #+#    #+#             */
/*   Updated: 2021/12/17 14:42:10 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EMUL_H
# define T_EMUL_H
# include "t_destack.h"
# include "utils.h"

typedef struct s_emul
{
	t_destack	*a;
	t_destack	*b;
}	t_emul;

typedef enum e_aorb {B = 0, A = 1}	t_aorb;

t_emul		ft_mk_emul(t_destack *a, t_destack *b);
t_aorb		ft_other(t_aorb aorb);
t_destack	*ft_getaorb(t_emul *t, t_aorb aorb);
void		ft_sx(t_emul *t, t_aorb aorb);
void		ft_px(t_emul *t, t_aorb aorb);
void		ft_rx(t_emul *t, t_aorb aorb);
void		ft_rrx(t_emul *t, t_aorb aorb);
void		ft_sa(t_emul *t);
void		ft_sb(t_emul *t);
void		ft_ss(t_emul *t);
void		ft_pa(t_emul *t);
void		ft_pb(t_emul *t);
void		ft_ra(t_emul *t);
void		ft_rb(t_emul *t);
void		ft_rr(t_emul *t);
void		ft_rra(t_emul *t);
void		ft_rrb(t_emul *t);
void		ft_rrr(t_emul *t);
//only defined in silent version :
void		ft_op_ofline(t_emul *t, char *line, int *ec);

#endif
