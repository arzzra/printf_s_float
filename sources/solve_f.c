/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:28:55 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/21 14:57:36 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"



long long get_totallen_f(uint64_t *p_int, t_qualfrs *fmt)
{
    long long		totallen;
    int 			dt;

    fmt->ld->intlen = get_buflen(p_int);
    totallen = fmt->ld->intlen + 1 + fmt->ld->ovrld + fmt->ld->realprec ;// int part's length + '\0'+ overload(prec > 16383)

    if(fmt->ld->realprec > 0 || fmt->flg->sharp)
    {
        totallen++; // + '.'
    }
    if(fmt->flg->plus != 0 || fmt->flg->space == 1)
    {
        totallen++; //+ sign
    }

    (dt = fmt->width - totallen + 1) > 0 ? totallen += dt : 1;
    fmt->ld->delta = dt;
    fmt->ld->totallen = totallen;
    return (totallen);

}

char *solve_f(uint64_t *p_int, uint64_t *p_frac, char **res_str, t_qualfrs *fmt)

{
    char			*si;
    char			*pnt;
    long long		totallen;


   totallen = get_totallen_f(p_int,fmt);

	*res_str = (char*)malloc(totallen * sizeof(char));
	(*res_str)[totallen - 1] = '\0';
    pnt = save_frac_part(*res_str, p_frac, p_int, fmt);
    //printf("pnt_%s*\n", pnt);
	si = save_int_part(pnt, p_int, fmt);
  //  printf("si_%s*\n", pnt);

    if (fmt->ld->realprec > 0 || fmt->flg->sharp)
    {
        si[ft_strlen(si)] = '.';
    }
    else if (fmt->flg->minus && (fmt->ld->delta) > 0) {
        si[ft_strlen(si)] = ' ';
    }
	write(1,pnt, fmt->ld->totallen - 1);
	return (NULL);
}

void	put_first_simbol(char **p, t_qualfrs *fmt)
{
 	if (fmt->flg->plus > 0)
		**p = '+';
	else if(fmt->flg->plus < 0)
		**p = '-';
	else if(fmt->flg->space)
	{
		**p = ' ';
	}
	else
		return;
    (*p)++;

}

char    *save_int_part(char *res_str, uint64_t *buf, t_qualfrs *fmt)
{
	char	*p;

	p = res_str;
		if (fmt->flg->zero && !fmt->flg->minus)
		{
            if(fmt->flg->plus != 0 || fmt->flg->space == 1)
                put_first_simbol(&p, fmt);
            if(fmt->ld->delta > 0 && fmt->flg->zero)
			{
				ft_memset(p, '0', fmt->ld->delta);
				p += fmt->ld->delta;
			}
		}
		else if (!fmt->flg->zero && !fmt->flg->minus)
		{
			if(fmt->ld->delta > 0)
			{
				ft_memset(p, ' ', fmt->ld->delta);
				p += fmt->ld->delta;
			}
			put_first_simbol(&(p), fmt);
		}
		else
		    if(fmt->flg->plus != 0 || fmt->flg->space == 1)
                 put_first_simbol(&p, fmt);
		buf_to_str(buf, p);
    	return(res_str);
}

long long	get_buflen(uint64_t *buf)
{
	unsigned long	last_el;
	long long		buflen;

	buflen = 0;
	last_el = buf[buf[0]];
	buflen = (buf[0] - 1) * BASELEN;
	if (buf[0] == 1 && buf[1] == 0)
		return (1);
	while (last_el)
	{
		last_el /= 10;
		(buflen)++;
	}
	return (buflen);
}