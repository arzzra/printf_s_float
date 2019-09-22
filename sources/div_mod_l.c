/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_mod_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:15:54 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/20 14:07:59 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"


short get_borrow(long long temp2, long vJ, unsigned i, uint64_t *buf_a)
{
	if (temp2 < 0)
	{
		buf_a[vJ + i] = temp2 + BASE;
		return (-1);
	}
	else
	{
		buf_a[vJ + i] = temp2;
		return (0);
	}
}

long long buf_b_cicle(t_div_coef *divcoef, uint64_t *buf_a, uint64_t *buf_b)
{
	unsigned i;
	unsigned n;

	n = buf_b[0];
	i=0;
	while (i < n)
	{
		divcoef->temp1 = buf_b[i + 1 ] * divcoef->qGuess + divcoef->carry;
		divcoef->carry = divcoef->temp1 / BASE;
		divcoef->temp1 -= divcoef->carry*BASE;
		divcoef->temp2 = buf_a[divcoef->vJ + i] - divcoef->temp1 + divcoef->borrow;
		if (divcoef->temp2 < 0)
		{
			buf_a[divcoef->vJ + i] = divcoef->temp2 + BASE;
			divcoef->borrow = -1;
		}
		else
		{
			buf_a[divcoef->vJ + i] = divcoef->temp2;
			divcoef->borrow = 0;
		}
		i++;
	}
	divcoef->temp2 = buf_a[divcoef->vJ + i] - divcoef->carry + divcoef->borrow;
	return  (get_borrow(divcoef->temp2, divcoef->vJ, i, buf_a));
}

void check_borrow(t_div_coef *divcoef, uint64_t *buf_a, uint64_t *buf_b, uint64_t *res)
{
	if (divcoef->borrow == 0)
		res[divcoef->vJ] = divcoef->qGuess;
	else
	{
		res[divcoef->vJ] = divcoef->qGuess - 1;
		divcoef->carry = 0;
		divcoef->i = 1;
		while (divcoef->i <= divcoef->n)
		{
			divcoef->temp = buf_a[divcoef->vJ + divcoef->i] + buf_b[divcoef->i] + divcoef->carry;
			if (divcoef->temp >= BASE)
			{
				buf_a[divcoef->vJ + divcoef->i] = divcoef->temp - BASE;
				divcoef->carry = 1;
			}
			else
			{
				buf_a[divcoef->vJ + divcoef->i] = divcoef->temp;
				divcoef->carry = 0;
			}
			divcoef->i++;
		}
		buf_a[divcoef->vJ + divcoef->i] = buf_a[divcoef->vJ + divcoef->i] + divcoef->carry - BASE;
	}
}


void cicle_de_grandiozo(t_div_coef *divcoef, uint64_t *buf_a, uint64_t *buf_b, uint64_t *res)
{
	long i;

	divcoef->vJ = divcoef->m;
	divcoef->uJ=divcoef->n+divcoef->vJ;
	while ( divcoef->vJ > 0 )
	{
		divcoef->qGuess = (buf_a[divcoef->uJ] * BASE+ buf_a[divcoef->uJ - 1]) / buf_b[divcoef->n];
		divcoef->r = (buf_a[divcoef->uJ] * BASE + buf_a[divcoef->uJ - 1]) % buf_b[divcoef->n];
		guess_stabilization(&(divcoef->r), &(divcoef->qGuess), buf_a[divcoef->uJ - 2], buf_b);
		divcoef->carry = 0;
		divcoef->borrow = 0;
		divcoef->borrow = buf_b_cicle(divcoef, buf_a, buf_b);
		check_borrow(divcoef, buf_a, buf_b, res);
		i = buf_a[0] ;

		while ( (i>0) && (buf_a[i]==0) )
			i--;
		buf_a[0] = i;

		--divcoef->vJ;
		--divcoef->uJ;
	}
}

void    div_mod_l(uint64_t *buf_a, uint64_t *buf_b, uint64_t *res)
{
	uint64_t    tmp[2001];
	t_div_coef  divcoef;

	if (simple_case_div_mod(buf_a, buf_b, res))//перенести выше
		return ;
	buf_normalize(&(divcoef.scale),buf_a, buf_b );//перенести выше ??
	divcoef.n = (long)buf_b[0];
	divcoef.m=buf_a[0] - buf_b[0];
	get_zero_buf(res, divcoef.m);
	cicle_de_grandiozo(&divcoef,buf_a,buf_b, res);
	while ( (divcoef.m>0) && (tmp[divcoef.m]==0) )
		divcoef.m--;
	tmp[0] = divcoef.m+1;
	if (divcoef.scale > 1)
	{
		div_s( buf_b, divcoef.scale, tmp);
		div_s(buf_a, divcoef.scale, tmp);
	}
}