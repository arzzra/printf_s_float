/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_frac_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:28:34 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/21 12:03:21 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void replace_dig(char *s_base_i, short *f)
{
	if (*s_base_i - 48 < 9)
	{
		*s_base_i += 1;
		*f = 0;
	}
	else
	{
		*s_base_i = '0';
		*f = 1;
	}
}


int check_last_dig(char *s)
{
    char		*snum;
    size_t 		len;


    snum = s;
   // printf("_snum_%s*\n", snum);

   len = ft_strlen(snum);

    if (s[0] == '0' || len == 0)
        return (0);
    s[8] = '\0';
    len = ft_strlen(snum);
    snum = ft_itoa(ft_atoi(s) + 1);

    if (ft_strlen(snum) > len || snum[0] > '5')
    {
        return (1);
    }
    if (snum[0] == '5')
    {
        if(ft_atoi(&(snum[1])) > 0)
            return (1);
    }
    return (0);
}

void		round_line(char *s_full, t_qualfrs *fmt)
{
	long long	i;
	short		f;



   i = fmt->ld->realprec ;


    //printf("_s[i]_%c*\n", s_full[i]);

	if(check_last_dig(&(s_full[i])))
	{
	    if (i >= 1)
	        replace_dig(&(s_full[i-1]), &f);
	    else
	        f = 1;
		while (f == 1)
		{
			if (i - 1 <= 0)
			{
				fmt->ld->carry = 1;
				break;
			}
			i--;
			replace_dig(&(s_full[i - 1]), &f);
		}
	}
	s_full[fmt->ld->realprec] = '\0';

    //printf("\nAAAAround_s_%s*\n\n", s_full);
}


void fill_prec(char *s_full, uint64_t *buf, t_qualfrs *fmt)
{
	if (buf[0] == 1 && buf[1] == 0)
	{
		ft_memset(s_full, '0', fmt->ld->realprec);
		s_full[fmt->ld->realprec] = '\0';
		return;
	}
	buf_to_str(buf, s_full);

}


static long long	get_start_index(char *s_full, uint64_t *buf, t_qualfrs *fmt)
{
	long long	i;
	char		*s_base;

	i = fmt->ld->realprec - fmt->ld->count_0;
	if (i <= 0)
	{
		ft_memset(s_full, '0', fmt->ld->realprec);
		if (i == -1)
		{
			s_base = ft_itoa_base_ll(buf[buf[0]], 10);
			if (s_base[0] - 48 >= 5)
				s_full[fmt->ld->realprec] = '1';
		}
		s_full[fmt->ld->realprec] = '\0';
		return (-1);
	}
	else
	{
		ft_memset(s_full, '0', fmt->ld->count_0);
		s_full[fmt->ld->count_0] = '0';
		return (fmt->ld->count_0);
	}
}

char		*save_frac_part(char *res_str, uint64_t *p_frac,uint64_t *p_int, t_qualfrs *fmt)
{
	char			s_full[fmt->ld->realprec + 2 + 8 ]; //+ '.' +'\0' + lead_zeros
	long long		i;
    char            *new;

	i = (long long)p_frac[0] * BASELEN + fmt->ld->count_0 + 2;
	fmt->ld->carry = 0;
	if(fmt->ld->realprec == 0)
	{
		zero_prec(&(s_full[0]), p_frac, fmt);
	}
	else
	{
		s_full[0] = '.';
		i = get_start_index(&(s_full[1]), p_frac, fmt) + 1;
		if (i == 0 && s_full[fmt->ld->count_0 + 1] == '0')
            return (fill_res_f(res_str,&(s_full[0]),fmt));
		fill_prec(&(s_full[fmt->ld->count_0  + 1]), p_frac, fmt);
        round_line(&(s_full[1]), fmt);
		if (fmt->ld->count_0 > 0 && fmt->ld->carry == 1)
		{
            s_full[i - 1] = '1';
            fmt->ld->carry = 0;

        }
	}
   /* printf("p_int1:\n");
    for (unsigned n = p_int[0]; n >= 1; n--)
    {
        printf("_%llu_",p_int[n]);
    }
    printf("\n");*/
	if (fmt->ld->carry == 1)
    {
        add_s(p_int, 1);
	    if(fmt->ld->intlen < get_buflen(p_int)) //9.9999
        {
	        fmt->ld->newmem = 1;
	        free(res_str);
            fmt->ld->totallen += 1;
	        new = (char*)malloc(fmt->ld->totallen * sizeof(char));
            new[fmt->ld->totallen] = '\0';
            return (fill_res_f(new,&(s_full[0]),fmt));
        }
    }
	return (fill_res_f(res_str,&(s_full[0]),fmt));
}

void zero_prec(char *s_full, uint64_t *buf, t_qualfrs *fmt)
{
	char		*s_base;
	//unsigned	i;

	if (fmt->flg->sharp == 1)
		s_full[0] = '.';

	if (buf[buf[0]] != 0)
	{
		if(fmt->ld->count_0 > 0)
			return ;
		s_base = ft_itoa_base_ll(buf[buf[0]],10);
		if(((s_base[0] - 48) > 5 ) || ((s_base[0] - 48) == 5 && s_base[1] - 48 > 0))
			fmt->ld->carry = 1;
	}
	s_full[1] = '\0';
}
