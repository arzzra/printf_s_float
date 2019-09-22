/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:27:42 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/20 13:50:04 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char 		*fill_res_f(char* res_str, char *s_full, t_qualfrs *fmt)
{
    long long 	tmp;
    char	*p;

        p = &(res_str[fmt->ld->totallen - 1]);

	if (fmt->flg->minus && (tmp = fmt->ld->delta) > 0)
	{
		while (tmp-- > 0)
		{
			p--;
			*p = ' ';
		}
	}
	while (fmt->ld->ovrld-- > 0)
	{
		p--;
		*p = '0';
	}
	tmp = (long long)ft_strlen(s_full) - 1;
	while (tmp >= 0)
	{
		p--;
		*p = s_full[tmp];
		tmp--;
	}
    //printf("sf_%s*\n", p);

    return(&(res_str[0]));
}

char 		*fill_res_e(char* res_str,  t_qualfrs *fmt)
{
    long long 	tmp;
    char	*p;

	p = &(res_str[fmt->ld->totallen - 1]);
    if (fmt->flg->minus && (tmp = fmt->ld->delta) > 0)
    {
        while (tmp-- > 0)
        {
            p--;
            *p = ' ';
        }
    }

  /*  tmp = ft_strlen(s_full) - 1;
    while (tmp >= 0)
    {
        p--;
        *p = s_full[tmp];
        tmp--;
    }*/
  //  printf("pe_%s*\n", p);
    return(p);
}
