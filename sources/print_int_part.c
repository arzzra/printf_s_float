/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:28:25 by bcharity          #+#    #+#             */
/*   Updated: 2019/09/20 14:32:58 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/ft_printf.h"


void    solve_int_part(char *s_int) //ДОБАВИТЬ ОБРАБОТКУ ФЛАГОВ!!
 {
     uint64_t buf[2000];
   // char                *p;

    convert_integer(buf, s_int);

   // p = save_int_part(*res_str, buf, fmt_feature);

    //print_buf(buf, 0, 'i', fmt_feature); // добавить индекс для целой и дробной частей

}



uint64_t  *convert_integer(uint64_t *buf, char *s_int)
{
    unsigned            maxpow;
    unsigned            i;
    uint64_t 	  buf_2n[2000];

    buf[0] = 1;
    buf[1] = 0;
    if (*s_int == '\0')
        return (buf);
    i = 0;
    maxpow = ft_strlen(s_int) - 1;
    while(s_int[maxpow - i] == '0' )//пропустить младшие "0"
    {
        if (maxpow - i == 0)
            return (buf);
        i++;
    }
    pow_of_two(buf_2n, i);//сохраняю начальную степень 2
    while(i <= maxpow)  //перевод в десятичный массив
    {
        if (i == 0)
            buf[1] = 0;
        if (s_int[maxpow - i] == '1')
            add(buf, buf_2n);
        mul_s(buf_2n, 2);
        i++;
    }
    return (buf);
}
