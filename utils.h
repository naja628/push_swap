/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:09 by najacque          #+#    #+#             */
/*   Updated: 2021/12/14 15:48:09 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

typedef unsigned char	t_uchar;

void	ft_putstr_endl(char const *s);
int		ft_atoi_errcode(char const *s, int *errcode);
int		ft_abs(int n);
int		ft_less(int x, int y, int rev);
// only used by checker :
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
