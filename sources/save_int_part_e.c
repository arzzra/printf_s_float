/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_int_part_e.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:28:42 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/20 13:50:04 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_printf.h"


char     *save_int_part_e(char *res_str, t_qualfrs *fmt)
{
    char        *p;
   // uint64_t    num;

    p = res_str;
    p += fill_left_part(res_str, fmt);

    if(fmt->ld->iflg == 0 && fmt->ld->fflg == 0)
    {
        *p = '0';
        //00.000
    }
    else
    {
        if (fmt->ld->tmp == '9')
            fmt->ld->tmp = '1';
        *p = fmt->ld->tmp;
    }

    if ( fmt->ld->realprec > 0 || fmt->flg->sharp == 1)
        *(++p) = '.';

    /*printf("res_str_%s*\n", res_str);
    printf("p_%s*\n\n", p);*/

    return(res_str);
}

long     fill_left_part(char *res_str, t_qualfrs *fmt)
{
    char	*p;

    p = res_str;
    if (fmt->flg->zero && !fmt->flg->minus)
    {
        if(fmt->flg->plus != 0 || fmt->flg->space == 1)
            put_first_simbol(&p, fmt);
        if(fmt->ld->delta > 0)
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
    if (fmt->flg->plus != 0 || fmt->flg->space == 1)
        put_first_simbol(&p, fmt);

    return(p - res_str);

}

