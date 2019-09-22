/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_bin_frac_part.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:27:13 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/20 16:26:34 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

uint64_t       *convert_fraction(char *s_frac, uint64_t *buf,  t_qualfrs *fmt_feature)
{
    uint64_t res[2000];
    uint64_t  buf_2n[2001];
    int prec;

    buf[0] = 1;
    buf[1]= 0;
   prec = fmt_feature->prcs;

   if (fmt_feature->typs == 'e' && fmt_feature->ld->iflg == 0 )
   {
       prec = fmt_feature->prcs + fmt_feature->ld->count_0;
   }
    convert_string(buf, s_frac);
   if (buf[0] == 1 && buf[1] == 0)
	   return (buf);

   /* printf("buf_1:\n");
    for (unsigned n = buf[0]; n >= 1; n--)
    {
        printf("_%llu_",buf[n]);
    }
    printf("\n");*/
   pow_of_num(buf_2n, 63 - fmt_feature->ld->exp, 2);
   div_mod_l(buf, buf_2n, res);
	//i = prec;
	prec += 7;
    while (prec > 0) // *10 - явные числа после зпт
    {
         mul_s(buf, 10);
         prec--;
    }

    div_mod_l(buf, buf_2n, res);

    copy_buf_ull(res, buf);
    return (buf);
}

void pow_of_num(uint64_t *buf_n, uint64_t  exp, unsigned num)
{
    buf_n[0] = 1;
    buf_n[1] = 1;

    while (exp > 0)
    {
        mul_s(buf_n, num);
        exp--;
    }
}

unsigned skip_first_last_zeros(char *s_part, long long  *maxpow)
{
    char                *start_s; // пропустить нули в начале строки(для дробной части)
    int            i;

    i = 0;
    start_s = s_part;
    while(s_part[(*maxpow) - i] == '0')//пропустить младшие "0"
    {
		if (i == (*maxpow))
			return (-1);
        i++;
    }
    while (*(start_s) != '1')//пропустить старшие "0"
    {
        start_s++;
        (*maxpow)--;
    }
    return (i);
}

void convert_string(uint64_t *buf, char *s_part)
{
	long long            maxpow;
    int            i;
    uint64_t       buf_2n[2000];
    long long           maxindx;

    buf[0] = 1;
    buf[1] = 0;
    maxindx = ft_strlen(s_part) - 1;
    if(maxindx < 0)
	{
    	return;
    }

    maxpow = maxindx;
    i = skip_first_last_zeros(s_part, &maxpow);
    if (i == -1)
    	return ;
    pow_of_two(buf_2n, i);//сохраняю начальную степень 2
    while(i <= maxpow) //перевод в десятичный массив
    {
        if (i == 0)
            buf[1] = 0;
        if (s_part[maxindx - i] == '1')
            add(buf, buf_2n);
        mul_s(buf_2n, 2);
        i++;
    }
}

unsigned start_index(char *s_part)
{
    unsigned start_i;

    start_i = 1;
    while (*s_part == '0')
    {
        start_i++;
        s_part++;
    }
    //printf("\nstart_index = %u\n", start_i);
    return(start_i);
}


void    copy_buf_ull(const uint64_t *src, uint64_t *dst)
{
    int i;

    i = src[0];
    while (i >= 0)
    {
        dst[i] = src[i];
        i--;
    }
}