/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_mantiss.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:27:20 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/21 15:33:21 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"


char    *lead_zeros(long long exp, char *_part, char flag)
{
    if (flag == 'f')
    {
        while (exp >= 0)
        {
            *_part = '0';
            _part++;
            exp--;
        }
        return (&(*_part));
    }
    if (flag == 'i')
    {
        while (exp >= 0)
        {
            *_part = '0';
            _part++;
            exp--;
        }
        *_part = '\0';
    }
    return (_part) ;
}

void frac_to_str(void *src, char *frac_part, int i,int k, t_qualfrs *fmt)
{
    unsigned char    *s;
    unsigned char    bit;
    size_t        zeros;
    size_t        l;

    l = i * 8 + k;

    s = (unsigned char*)src;
    k == 0 ? k = 7 : k--;
    zeros = 0;
    //  i_start = 64 + exp - (i) * 8 - k - 1;//64 + exp - last(сколько бит осталось в мантиссе)

    while (i >= 0)
    {
        while (k >= 0)
        {
            bit = (s[i] >> k) & 1;
            bit == 0 ? zeros++ : 1;
            *frac_part = bit + '0';
            frac_part++;
            k--;
        }
        k = 7;
        i--;
    }
    *frac_part = '\0';
    //printf("frac_part_%s", frac_part);

    if (zeros == l)
        fmt->ld->fflg = 1;
}

void    replace_bit_min(void *src, char *frac_part, size_t size, long long exp)
{
    unsigned char    *s;
    unsigned char    bit;
    int              i;
    int              k;

    s = (unsigned char*)src;
    i = size - 1;
    k = 7;

    if (exp != 0)
        frac_part = lead_zeros(exp, &(*frac_part),'f');
    while (i >= 0 )
    {
        while (k >= 0 )
        {
            bit = (s[i] >> k) & 1;
            *frac_part = bit + '0';
            frac_part++;
            //exp--;
            k--;
        }
        k = 7;
        i--;
    }
    *frac_part = '\0';
}

void replace_bit_max(void *src, char *int_part, char *frac_part, size_t size, t_qualfrs *fmt )//число, строка, размер числа,кол-во бит
{
    unsigned char    *s;
    unsigned char    bit;
    int              i;
    int              k;
    long long       exp;

    exp = fmt->ld->exp;
    s = (unsigned char*)src;
    i = size - 1;
    k = 7;
    while (i >= 0 && exp >= 0)
    {
        while (k >= 0 && exp >= 0)
        {
            bit = (s[i] >> k) & 1;
            *int_part = bit + '0';
            int_part++;
            if(exp == 0)
                frac_to_str(src, frac_part, i, k, fmt);
            exp--;
            k--;
        }
        k = 7;
        i--;
    }
    if (exp >= 0)
        lead_zeros(exp, &(*int_part),'i');
    else
        *int_part = '\0';
}