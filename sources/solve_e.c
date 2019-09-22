/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:28:48 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/21 12:38:14 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long long number_pow(long long num)
{
    int i;
    long long d;

    d = num;
    if (d < 0)
        d *= -1;
    i = 0;
    while (d)
    {
        d /= 10;
        i++;
    }
   // printf("\nnumber_pow_e_%d\n", i);
    return (i);
}

long long get_totallen_e(uint64_t *p_int, t_qualfrs *fmt)
{
    long long   totallen;
    int         dt;
    long long   tmp;

    totallen = 4; // first_int + e+/- + '\0'
    fmt->ld->sf_index = 2;// e+/-

    if(fmt->ld->realprec > 0 || fmt->flg->sharp)
    {
        totallen++; // + '.'
        fmt->ld->sf_index++;

        totallen += fmt->ld->realprec;
        fmt->ld->sf_index += fmt->ld->realprec;
    }
    if(fmt->flg->plus != 0 || fmt->flg->space == 1) //sign
        totallen++;

    //=====================================
    //число после е
    fmt->ld->e = 0;
    if( fmt->ld->iflg == 0 &&  fmt->ld->fflg != 0 )
    {
        if (fmt->ld->carry == 1)
            fmt->ld->e = -fmt->ld->count_0;
        else
            fmt->ld->e = -fmt->ld->count_0 - 1;
    }
    else
    {
        fmt->ld->e = get_buflen(p_int) - 1;
    }
    //посчитать цифры после е+/-
    tmp = number_pow((size_t)fmt->ld->e);
    if(tmp <= 1)
        tmp = 2;
    totallen += tmp;
    fmt->ld->sf_index += tmp;
    //======================================
    (dt = fmt->width - totallen + 1) > 0 ? totallen += dt : 1;
    fmt->ld->delta = dt;
    fmt->ld->totallen = totallen;
    fmt->ld->sf_index = totallen - fmt->ld->sf_index  - 1;
    return (totallen);
}


char *solve_e(uint64_t *p_int, uint64_t *p_frac, char **res_str, t_qualfrs *fmt)
{
	char        *si;
	char        *sf;
	long long   totallen;

  totallen = get_totallen_e(p_int, fmt);

 if(!(*res_str = ft_memalloc(totallen + 8 * sizeof(char))))
     return(NULL);
  (*res_str)[totallen - 1] = '\0';
    si = *res_str;

    sf = &(si[fmt->ld->sf_index]);

    save_frac_part_e(sf, p_int,p_frac,fmt);
    si = save_int_part_e(si,  fmt);
    write(1,(*res_str), totallen - 1);
    return (*res_str);
}

char     *save_frac_part_e(char *sf, uint64_t *p_int, uint64_t *p_frac, t_qualfrs *fmt) {
    size_t len;
    char *p;

    sf[0] = '\0';
    fmt->ld->carry = 0;

    if (fmt->ld->iflg == 0 && fmt->ld->fflg == 0)
    {
        if (fmt->ld->realprec > 0 || fmt->flg->sharp == 1)
        {
            *sf = '.';
            sf++;
        }
        fmt->ld->e = 0;
        fill_e_end((sf), fmt);
        return (fill_res_e(sf, fmt));
        //00.000
    }
    if (fmt->ld->iflg == 1) //есть целая часть
    {
        if (p_int[0] * BASELEN > (uint64_t)fmt->ld->totallen)
        {
            p_int = cut_buf(p_int, fmt->ld->totallen + 7);
        }
        buf_to_str(p_int, sf);
    }
    len = ft_strlen(sf);
    if (fmt->ld->e >= 0) {
        ft_memset(&(sf[len]), '0', fmt->ld->count_0);
        len += fmt->ld->count_0;
    }
    buf_to_str(p_frac, &(sf[len]));

    len = ft_strlen(sf);
    long long dt = fmt->ld->realprec - len;//overload
    p = &(sf[len + dt]);
    while (dt >= 0)
    {
        *p = '0';
        p--;
        dt--;
    }

    //printf("s_full_1_%s*\n", sf);
    if (fmt->ld->realprec == 0)
    {
        if(check_last_dig(&(sf[1])))
        {
                fmt->ld->e++;
                sf[0] = '1';

        }

    }
    fmt->ld->tmp = sf[0]; // сохранить первую  значащую цифру


    if (fmt->ld->realprec > 0 || fmt->flg->sharp)
    {
        sf[0] = '.';
    }
    round_line(&(sf[1]), fmt);


    if (sf[0] == '9' && check_last_dig(&(sf[1])))
    {
        replace_dig(&(sf[0]), &(fmt->ld->carry));
        char *dup = ft_strdup(sf);

        fmt->ld->e++;
        sf[0] = '1';
        fmt->ld->tmp = sf[0];
        ft_strncpy(&(sf[1]), dup, ft_strlen(dup) - 1);
        free (dup);
    }

    //printf("s_full_before_round_%s*\n", sf);
   // printf("s_full_after__round_%s*\n", sf);

//*************************************************

    fill_e_end(sf, fmt);
     // printf("s_full_before_res_%s*\n", sf);
    return (fill_res_e(sf, fmt));
}

void    fill_e_end(char *s_full, t_qualfrs *fmt)
{
    char            *p;
    long long		i;

    p = (s_full);
    if(fmt->ld->iflg == 0 && fmt->ld->fflg == 0)
    {
        ft_memset(p, '0', fmt->ld->realprec);
        p += fmt->ld->realprec;
    }
    else if (fmt->ld->realprec > 0)
        p = &s_full[fmt->ld->realprec + 1];
    else
        p = &s_full[fmt->ld->realprec];


    //printf("sf_%s*\n\n", s_full);

    *(p) = 'e';
    p++;
    if (fmt->ld->e >= 0)
        *(p) = '+';
    else
        *(p) = '-';
    p++;
    if (fmt->ld->e < 0)
        fmt->ld->e *= -1;

    i = number_pow((long long) fmt->ld->e);
    if (i < 2)
    {
        i == 0 ? i++ : 1;
        *(p) = '0';
        p++;
    }

    p += i;
    *(p) = '\0';

   // printf("i_%lld*\n", i);
   if (fmt->ld->e == 0)
       *(--p) =  48;
    while (fmt->ld->e)
    {
        *(--p) = (fmt->ld->e % 10) + 48;
        fmt->ld->e /= 10;
    }
}


uint64_t *cut_buf(uint64_t *buf, long long len)
{
    long long  lf;
    long long   n;

    if (buf[0] == 1)
        return (buf);
    n = 0;
    lf = number_pow((long long)buf[buf[0]]); //степень первого элемента числа
    len -= lf;
    if (len  > 0)
    {
        n = (len) / (BASELEN);
        if ((len) % BASELEN > 0)
            n++;
    }
    n++;
    buf[buf[0] - n] = n;
    return ( &(buf[buf[0] - n]));
}
