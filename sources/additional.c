/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdemetra <cdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 14:21:22 by cdemetra          #+#    #+#             */
/*   Updated: 2019/09/21 18:02:14 by cdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_without_typs(t_qualfrs *ql)
{
	t_flag *fl;

	fl = ql->flg;
	if (fl->minus)
	{
		ql->countchr += write(1, &(ql->sformat)[0], 1);
		ft_print_space(ql->width - 1, ql);
	}
	else
	{
		ft_print_space(ql->width - 1, ql);
		ql->countchr += write(1, &(ql->sformat)[0], 1);
	}
	ql->sformat++;
}

void	ft_print_percent(t_qualfrs *ql)
{
	t_flag *fl;

	fl = ql->flg;
	if (ql->width > 1)
	{
		if (fl->minus)
		{
			ql->countchr += write(1, &(TYPES)[13], 1);
			ft_print_space(ql->width - 1, ql);
		}
		else
		{
			if (fl->zero)
				ft_print_zero(ql->width - 1, ql);
			else
				ft_print_space(ql->width - 1, ql);
			ql->countchr += write(1, &(TYPES)[13], 1);
		}
	}
	else
		ql->countchr += write(1, &(TYPES)[13], 1);
}

int		ft_zd(char *frm, t_qualfrs *ql)
{
	if (*frm == 'z' || *frm == 'j')
	{
		ql->len->l = 2;
		return (1);
	}
	else
		return (0);
}

void	ft_print_str_uni(t_qualfrs *ql)
{
	char			wr;
	unsigned char	c2;
	int				i;

	if (ql->typs == TYPES[1])
		ql->countchr += write(1, ql->num, ql->countnum);
	else if (ql->typs == TYPES[15])
	{
		i = -1;
		while (++i < ql->countnum)
		{
			c2 = (unsigned char)ql->num[i];
			if (c2 < 0)
				continue ;
			else if (c2 > 0x7F)
			{
				wr = (c2 >> 6) | 0xC0;
				ql->countchr += write(1, &wr, 1);
				wr = c2 & 0xbf;
				ql->countchr += write(1, &wr, 1);
			}
			else
				ql->countchr += write(1, &c2, 1);
		}
	}
}
