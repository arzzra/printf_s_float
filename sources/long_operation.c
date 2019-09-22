/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:28:06 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/19 16:28:06 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_printf.h"

void    zero_ceil(uint64_t *buf, unsigned maxlen)
{
    unsigned i;

    i = (buf[0] + 1);
    while(i <= maxlen)
    {
        buf[i] = 0;
        i++;
    }
}

static void    get_maxlen(unsigned *maxlen, uint64_t *buf1, uint64_t *buf2)
{
    if (buf1[0] > buf2[0])
    {
        *maxlen = buf1[0];
        zero_ceil(buf2, *maxlen);
    }
    else if(buf1[0] < buf2[0] )
    {
        *maxlen = buf2[0];
        zero_ceil(buf1, *maxlen);
        buf1[0] = buf2[0]; //!!только после зануления(или во время)
    }
    else
        *maxlen = buf1[0];
}

uint64_t    *add(uint64_t *buf1, uint64_t *buf2)
{
    unsigned long long c;
    unsigned i;
    unsigned maxlen;

    get_maxlen(&maxlen, buf1, buf2);
    c = 0;
    i = 1;
    while(i <= maxlen)
    {
        c = buf1[i] + buf2[i] + c;
        buf1[i] = c % BASE;
        c = c / BASE;
        if (i ==  maxlen && c != 0)
        {
            buf1[0]++;
            buf1[buf1[0]] = c;
            break;
        }
        i++;
    }
    return(buf1);
}
uint64_t  *add_s(uint64_t *buf,  uint64_t dig)
{
    unsigned long long c;
    unsigned i;
    unsigned maxlen;

    //get_maxlen(&maxlen, buf1, buf2);

    i = 1;
    maxlen = buf[0];

    c = buf[i] + dig;
    while(i <= maxlen)
    {
        buf[i] = c % BASE;
        c = c / BASE;
        if (i ==  maxlen && c != 0)
        {
            buf[0]++;
            buf[buf[0]] = c;
            break;
        }
        i++;
    }
    return(buf);
}


uint64_t * mul_s(uint64_t *buf, unsigned dig)
{
    uint64_t    c;
    unsigned    i;

    c = 0;
    i = 1;
    while (i <= buf[0])
    {
        c = buf[i] * dig + c;
        buf[i] = c % BASE;
        //   printf("buf[%u] = %llu\n", i, buf[i]);
        c = c / BASE;
        if (i ==  buf[0] && c != 0)
        {
            buf[0]++;
            buf[buf[0]] = c;
            break ;
        }
        i++;
    }
    return(buf);
}

void    div_mod_s(uint64_t *buf_a, uint64_t b, uint64_t *res, uint64_t *rem)
{
    uint64_t        r;
    uint64_t        tmp;
    long long       i;


    res[0] = buf_a[0];
    r = 0;
    i = buf_a[0];
    while (i > 0)
    {
        tmp = r*BASE + buf_a[i];
        res[i] = tmp / b;
        r = tmp - res[i]*b;
        i--;
    }
    *rem = r;
    i = buf_a[0];
    while ((i > 0) && (res[i] == 0))
        i--;
    res[0] = i;
}

uint64_t * div_s(uint64_t *buf, unsigned dig, uint64_t *res)
{
    unsigned long long c;
    unsigned long i;

    c = 0;
    i = buf[0];
    res[0] = buf[0];
    while (i >= 1)
    {
        c = c * BASE + buf[i];  //число которое будем делить
        res[i] = c / dig;
        c = c % dig;
        i--;
    }
    i = 1;
    while (i <= buf[0])
    {
        buf[i] = res[i];
        i++;
    }
    return(res);
}

unsigned long  *mul_l( unsigned long  *buf1,  unsigned long  *buf2,  unsigned  long *res)
{
    unsigned long long c;
    unsigned i;
    unsigned j;
    unsigned maxlen;

    res[0] = buf1[0] + buf2[0];
    maxlen = res[0];
    i = 1;
    while (i < maxlen)
    {
        c = 0;
        j = 1;
        while (j < maxlen)
        {
            c = c + buf1[j] * buf2[i] + res[j];
            res[j] = c % BASE;
            c = c / BASE;
            j++;
        }
        i++;
    }
    return (res);
}

void    print_bits(size_t size, void *ptr, char space)
{
    unsigned char    *b;
    unsigned char    byte;
    int                i;
    int                j;

    b = (unsigned char*)ptr;
    i = size - 1;
    j = 7;
    while (i >= 0)
    {
        while (j >= 0)
        {
            byte = (b[i] >> j) & 1;
            ft_putchar(byte + '0');
            j--;
        }
        if (space == 1)
            ft_putchar(' ');
        j = 7;
        i--;
    }
    ft_putchar('\n');
}



