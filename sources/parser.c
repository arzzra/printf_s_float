/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdemetra <cdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 14:45:01 by cdemetra          #+#    #+#             */
/*   Updated: 2019/09/16 15:04:08 by cdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_flags(char *format, t_qualfrs *ql)
{
	int		i;
	char	*fls;
	t_flag	*flag;

	flag = ql->flg;
	i = 0;
	while ((fls = ft_strchr(ALLFLG, format[i])))
	{
		flag->sharp = (*fls == ALLFLG[0]) ? 1 : flag->sharp;
		flag->zero = (*fls == ALLFLG[1]) ? 1 : flag->zero;
		flag->minus = (*fls == ALLFLG[2]) ? 1 : flag->minus;
		flag->plus = (*fls == ALLFLG[3]) ? 1 : flag->plus;
		flag->space = (*fls == ALLFLG[4]) ? 1 : flag->space;
		i++;
	}
	return (i);
}

int		ft_width(char *frm, t_qualfrs *ql)
{
	int		i;
	int		f;

	i = 0;
	if (*frm == '*')
	{
		ql->width = va_arg(ql->ap, int);
		ql->flg->minus = ql->width < 0 ? 1 : ql->flg->minus;
		ql->width *= ql->width < 0 ? -1 : 1;
		return (1);
	}
	else
	{
		if ((f = ft_atoi(frm)))
			ql->width = f;
		while (ql->width > 0 && frm[i] >= '0' && frm[i] <= '9')
			i++;
		return (i);
	}
}

int		ft_precision(char *frm, t_qualfrs *ql)
{
	int		i;

	i = 0;
	if (*frm == '.')
	{
		i++;
		ql->prcs = 0;
		if (frm[i] == '*')
		{
			ql->prcs = va_arg(ql->ap, int);
			ql->prcs = ql->prcs < 0 ? -1 : ql->prcs;
			return (2);
		}
		else
		{
			ql->prcs = ft_atoi(&(frm)[i]);
			while (ql->prcs > 0 && frm[i] >= '0' && frm[i] <= '9')
				i++;
			return (i);
		}
	}
	else
		return (i);
}

int		ft_length(char *frm, t_qualfrs *ql)
{
	t_length	*len;

	len = ql->len;
	if (*frm == 'l')
	{
		if (!len->h && !len->l && !len->L)
		{
			len->l = (frm[1] == 'l') ? len->l + 2 : 1;
			return (len->l);
		}
		return(1);
	}
	else if (*frm == 'h')
	{
		if (!len->h && !len->l && !len->L)
		{
			len->h = (frm[1] == 'h') ? len->h + 2 : 1;
			return (len->h);
		}
		return(1);
	}
	else if (*frm == 'L')
	{
		if (!len->h && !len->l && !len->L)
			len->L = 1;
		return (1);
	}
	else
		return (0);
}

char	*ft_types(char *frm, t_qualfrs *ql)
{
	char	*ser;

	if ((ser = ft_strchr(TYPES, *frm)))
	{
		ql->typs = *ser;
		return (ser);
	}
	else
		return (NULL);
}
