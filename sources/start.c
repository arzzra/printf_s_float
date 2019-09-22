
#include "../includes/ft_printf.h"


/*int main ()
{
    long double d =3.85;
    printf("original:\n*%-05.0f*\n", 7.3);//prec0_1,0,1569134519
    ft_printf("ft_:\n*%-05.0f*\n", 7.3);
   ft_printf("ft_:\n*%.8Lf*\n", 3.85);
    ft_printf("ft_:\n*%.8Lf*\n", d);
    return (0);
}*/

void     init_float(t_qualfrs *fmt, u_ld *un)
{
    long double             d;

    fmt->ld->sign_exp = 1;
    if (fmt->len->L)
        d = (long double)va_arg(fmt->ap, long double);
    else
        d = (long double)va_arg(fmt->ap, double);
    un->d = d;
    fmt->ld->d = d;
    fmt->ld->exp  = un->bits.exponent - 16383;
    if (fmt->ld->exp < 0 )
    {
        fmt->ld->sign_exp = -1;
        fmt->ld->exp *= -1;
    }
    if(un->bits.sign == 1)
        fmt->flg->plus = -1;
    else if(fmt->flg->plus && un->bits.sign == 0)
        fmt->flg->plus = 1;
    else
        fmt->flg->plus = 0;
    if (fmt->prcs == -1)
        fmt->prcs = 6;
    fmt->ld->newmem = 0;
}

void	ft_print_floats(t_qualfrs *fmt)
{
    u_ld                 un;
    t_float              ldbl;

    fmt->ld = &ldbl;
    init_float(fmt, &un);
    if (ft_inf_nan(fmt))
        return ;
    divide_and_conquer(&un, fmt);

}

void    divide_and_conquer(u_ld *un,  t_qualfrs *fmt)
{
    char                s_int[64 + fmt->ld->exp + 1];
    char                s_frac[64 + fmt->ld->exp + 1];
    uint64_t            tmp;

    s_frac[0] = '\0';
    s_int[0] = '\0';
    tmp = un->bits.mantissa;
    fmt->ld->d = un->d;
    if (fmt->ld->sign_exp > 0)
        replace_bit_max(&tmp, s_int, &(s_frac[0]), 8, fmt);
    else
        replace_bit_min(&tmp, s_frac, 8, fmt->ld->exp);
    conver_parts(s_int, s_frac, fmt);
    return ;
}

void conver_parts(char *s_int, char *s_frac, t_qualfrs *fmt)
{
    static char         *res_str;
    uint64_t       buf_i[2000];
    uint64_t       buf_f[2000];
    uint64_t       *p_int;
    uint64_t       *p_frac;

    fmt->ld->fflg = 0;
	//printf("len__\n");	printf("\n");
    //printf("frac_part_%s", s_frac);
    p_int = convert_integer(buf_i, s_int);
    if (buf_i[0] == 1 && buf_i[1] == 0 )
        fmt->ld->iflg = 0;
    else
        fmt->ld->iflg = 1;


    if (fmt->ld->d < 0)
        fmt->ld->d *= -1;


    if (fmt->ld->sign_exp == -1)
    {
        fmt->ld->exp *= -1;
    }
    fmt->ld->realprec = fmt->prcs;
    if (fmt->prcs  < 6)
    {
        fmt->prcs = 6;
    }
	fmt->ld->ovrld = 0;
	if (fmt->prcs  > 16383)
	{
		fmt->ld->ovrld = fmt->prcs - 16383;
		fmt->prcs = 16383;
		fmt->ld->realprec = fmt->prcs;

	}
    if (fmt->ld->fflg  == 1 || s_frac[0] == '\0')
    {
        fmt->ld->count_0 = 0;
    }
    else
        fmt->ld->count_0 = count_zero_after_point(fmt->ld->d, fmt);

	p_frac = convert_fraction(s_frac, buf_f, fmt);


	if (buf_f[0] == 1 && buf_f[1] == 0 )
        fmt->ld->fflg = 0;
    else
        fmt->ld->fflg = 1;

   if ((fmt->typs) == 'f')
        solve_f(p_int, p_frac, &res_str, fmt);
   if ((fmt->typs) == 'e')
	    solve_e(p_int, p_frac, &res_str, fmt);
    if ((fmt->typs) == 'g')
        solve_e(p_int, p_frac, &res_str, fmt);

   free(res_str);


   return ;
}

uint64_t count_zero_after_point(long double d, t_qualfrs *fmt)
{
    size_t              part_int;   //???
    uint64_t            count_0;

    part_int = (size_t)d;
    count_0 = 0;

    if ((d -= part_int) == 0)
    	return(count_0);
    while(d < 1)// количество нулей после зпт
    {
        d *=10;
        count_0++;
    }
    if ((size_t)d == 9)
        fmt->ld->carry = 1;
    count_0 -= 1;
    return (count_0);
}

void pow_of_two(uint64_t *buf_2n, unsigned long  exp)
{
    buf_2n[0] = 1;
    buf_2n[1] = 1;

    while (exp > 0)
    {
        mul_s(buf_2n, 2);
        exp--;
    }
}

char    *ft_itoa_base_ll(uint64_t dig, int radix)
{
    char *s;
    static char res[8 * 8  + 1];
    int i;

    s = "0123456789abcdef";
    i = 0;
    res[8 * 8] = '\0';
    if (dig == 0)
    {
        res[8 * 8 - 1] = '0';
        return(&(res[8 * 8 - 1]));
    }
    while(dig != 0)
    {
        res[8 * 8 - 1 - i] = s[dig % radix];

        dig /= radix;
        i++;
    }
    return(&(res[8 * 8 - i]));
}
