/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdemetra <cdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:22:54 by cdemetra          #+#    #+#             */
/*   Updated: 2019/09/27 16:09:58 by cdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include "ft_printf.h"
# include "../libft/libft.h"

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <float.h>
# include <string.h>

# include <stdio.h>
# define TYPES "cspdiouxXegfC%SbF"
# define ALLFLG "#0-+ "
# define SPACE " "
# define ADDRESS "0x"
# define ADDRESS2 "0X"
# define ZERO "0"
# define PLUS "+"
# define MINUS "-"
# define NULLPRINT "(null)"
# define BASE 1000000000
# define BASELEN 9

typedef struct				s_qualfrs
{
	int						countchr;
	int						signum;
	int						typs;
	int						width;
	int						prcs;
	char					*num;
	char					*sformat;
	int						countnum;
	struct s_float			*ld;
	struct s_flag			*flg;
	struct s_length			*len;
	va_list					ap;
}							t_qualfrs;

typedef struct				s_float
{
	short					newmem;
	long long				intlen;
	long long				sf_index;
	int						iflg;//если intpart = 0 (первая цифра из fracpart)
	int						fflg;//fmt->ld->fflg = 0;
	char					tmp;//
	unsigned				ovrld;
	int 					delta;
	short					carry;
	long long				totallen;
	long long				realprec;
	long long				count_0;
	long double				d;
	long long				e;
	long long				exp;
	short					sign_exp;
}							t_float;

typedef struct				s_flag
{
	int						sharp;
	int						zero;
	int						minus;
	int						plus;
	int						space;
}							t_flag;


typedef struct				s_length
{
	int						l;
	int						h;
	int						L;
}							t_length;

typedef union
{
	long double d;
	struct
	{
		uint64_t mantissa : 64;
		uint64_t exponent : 15;
		uint64_t sign     : 1;
	}	bits;
}		u_ld;

typedef struct				s_div_coef
{
	long					n;
	uint64_t				m;
	uint64_t				scale;	// коэффициент нормализации
	uint64_t				qGuess;	// догадка для частного и соответствующий остаток
	uint64_t				temp1;
	uint64_t				r;

	long long				temp;
	long long				temp2;
	long long				carry; // переносы

	long					uJ;
	long					vJ;
	long					i;
	short					borrow;  // переносы
}							t_div_coef;


/*
 * * save_int_part_e.c
 */
char						*save_int_part_e(char *res_str, t_qualfrs *fmt);
long						fill_left_part(char *res_str, t_qualfrs *fmt);

/*
 * *solve_e.c
 */
char						*solve_e(uint64_t *p_int, uint64_t *p_frac, char **res_str, t_qualfrs *fmt);
uint64_t					*cut_buf(uint64_t *buf, long long len);
char						*save_frac_part_e(char *sf, uint64_t *p_int, uint64_t *p_frac, t_qualfrs *fmt);
int							fill_right_part(char *res_str, t_qualfrs *fmt);
void						fill_e_end(char *s_full, t_qualfrs *fmt);

long long 					number_pow(long long num);

/*
 * *solve_f.c
 */
char						*solve_f(uint64_t *p_int, uint64_t *p_frac, char **res_str, t_qualfrs *fmt);
char						*save_int_part(char *res_str, uint64_t *buf, t_qualfrs *fmt);
long long					get_totallen_f(uint64_t *p_int, t_qualfrs *fmt);
void						zero_prec(char *s_full, uint64_t *buf, t_qualfrs *fmt);
void						put_first_simbol(char **p, t_qualfrs *fmt);


/*
 * *save_frac_part.c
 */
char						*save_frac_part(char *res_str, uint64_t *p_frac,uint64_t *p_int, t_qualfrs *fmt);
long long					get_buflen(uint64_t *buf);
void						fill_prec(char *s_full, uint64_t *buf, t_qualfrs *fmt);
void						round_line(char *s_full, t_qualfrs *fmt);
int							check_last_dig(char *s);
void						replace_dig(char *s_base_i, short *f);

/*
 * *fill_res.c
 */
char 						*fill_res_f(char* res_str, char *s_full, t_qualfrs *fmt);
char 						*fill_res_e(char* res_str,  t_qualfrs *fmt);
//char 		*fill_res_i(char** res_str, char *s_full, t_qualfrs *fmt);

/*
 * long_operations.c
 */
//int     mod (unsigned long long *buf, unsigned dig,  unsigned long long *res);
uint64_t					*mul_s(uint64_t *buf, unsigned dig);
uint64_t					*add(uint64_t *buf1, uint64_t *buf2);
uint64_t					*add_s(uint64_t *buf,  uint64_t dig);
uint64_t 					*div_s(uint64_t *buf, unsigned dig, uint64_t *res);

void						div_mod_s(uint64_t *buf_a, uint64_t b, uint64_t *res, uint64_t *rem);

unsigned long				*mul_l( unsigned long  *buf1,  unsigned long *buf2,  unsigned  long *res);
void						print_bits(size_t size, void *ptr, char space);

/*
 * div_mod_l.c
 */
void						div_mod_l(uint64_t *buf_a, uint64_t *buf_b, uint64_t *res);
int							simple_case_div_mod(uint64_t *buf_a, uint64_t *buf_b, uint64_t *res);
void						buf_normalize(uint64_t *scale, uint64_t *buf_a, uint64_t *buf_b);
void						guess_stabilization(uint64_t *r, uint64_t *qGuess, uint64_t nextpart, uint64_t *buf_b);
short						get_borrow(long long temp2, long vJ, unsigned i, uint64_t *buf_a);
long long					buf_b_cicle(t_div_coef *divcoef, uint64_t *buf_a, uint64_t *buf_b);
void						check_borrow(t_div_coef *divcoef, uint64_t *buf_a, uint64_t *buf_b, uint64_t *res);
void						get_zero_buf(uint64_t *buf, uint64_t m);
void						cicle_de_grandiozo(t_div_coef *divcoef, uint64_t *buf_a, uint64_t *buf_b, uint64_t *res);





/*
 * convert_mantiss.c
 */
void						replace_bit_max(void *src, char *int_part, char *frac_part, size_t size, t_qualfrs *fmt);
void						replace_bit_min(void *src, char *frac_part, size_t size, long long exp);
char						*lead_zeros(long long exp, char *_part, char flag);
void						frac_to_str(void *src, char *frac_part, int i,int k, t_qualfrs *fmt);

/*
 * print_int_part.c
 */
void						solve_int_part(char *s_int);
uint64_t					*convert_integer(uint64_t *buf, char *s_int);
//void            get_buflen(long long   *len,unsigned long  *buf);
void						check_len_fmt(long long   *count, t_qualfrs *fmt);



unsigned long				max_len_pow_5(unsigned long long *buf_5n, unsigned long  base,  unsigned baselen);
unsigned					start_index(char *s_part);
void						keep_fraction(char *s_part, unsigned start_i, unsigned long  *buf_5n, unsigned  long base, unsigned baselen);
unsigned					maxpow_five(char *s_frac);

/*
 * print_frac_partv2.c
 */
void						pow_of_num(uint64_t *buf_n, uint64_t  exp, unsigned num);
void						print_last_zero(int prec);
void						copy_buf_ull(const uint64_t *src, uint64_t *dst);
uint64_t					*convert_fraction(char *s_frac, uint64_t *buf,  t_qualfrs *fmt_feature);
void						keep_mod(unsigned long *buf, unsigned long base, unsigned baselen, long long exp);
void						div_mod(unsigned long *buf, unsigned long *res, unsigned  long base, unsigned baselen, long long exp);
void						convert_string(uint64_t *buf, char *s_part);


/*
** buffer.c
*/
unsigned long				*init_buf(unsigned long long_num, unsigned  long base, unsigned buflen);
unsigned					ret_buflen(unsigned long long_num, unsigned  long base);
void						print_buf(unsigned long *buf, unsigned count_0, char c, t_qualfrs *fmt_feature);
void						buf_to_str(uint64_t *buf, char *s_full);

/*
** start.c
*/

void						divide_and_conquer(u_ld *un, t_qualfrs *fmt);
char						*ft_itoa_base_ll(uint64_t dig, int radix);
void						pow_of_two(uint64_t *buf_2n, unsigned long exp);
uint64_t					count_zero_after_point(long double d, t_qualfrs *fmt);
void						conver_parts(char *s_int, char *s_frac, t_qualfrs *fmt);

//************************************************************************************************************************

void						ft_print_floats(t_qualfrs *ql);

int							ft_printf(const char *format, ...);

int							ft_flags(char *format, t_qualfrs *ql);
int							ft_width(char *frm, t_qualfrs *ql);
int							ft_precision(char *frm, t_qualfrs *ql);
int							ft_length(char *frm, t_qualfrs *ql);
char						*ft_types(char *frm, t_qualfrs *ql);

void						ft_print_di(t_qualfrs *ql);
void						ft_print_di_2(t_qualfrs *ql);
void						ft_print_di_neg(t_qualfrs *ql);
void						ft_print_di_neg2(t_qualfrs *ql);
void						ft_print_di_neg3(t_qualfrs *ql);
void						ft_print_di_neg4(t_qualfrs *ql);
void						ft_print_di_pos(t_qualfrs *ql);
void						ft_print_di_pos2(t_qualfrs *ql);
void						ft_print_di_pos3(t_qualfrs *ql);
void						ft_print_di_pos4(t_qualfrs *ql);
void						ft_print_number(t_qualfrs *ql);
int							ft_zd(char *frm, t_qualfrs *ql);

char						*ft_sign_lenchoose(t_qualfrs *ql);
char						*ft_sign_lenchoose2(t_qualfrs *ql);

char						*ft_unsign_lenchoose(t_qualfrs *ql);
char						*ft_unsign_lenchoose2(t_qualfrs *ql);

void						ft_print_ox(t_qualfrs *ql);
char						*ft_len_ox2(unsigned long long numb, t_qualfrs *ql);
char						*ft_len_ox(unsigned long long numb, t_qualfrs *ql);
void						ft_print_sharp(t_qualfrs *ql);
void						ft_print_ox2(t_qualfrs *ql);
void						ft_print_xo(t_qualfrs *ql);
void						ft_print_xo2(t_qualfrs *ql);
void						ft_print_xo3(t_qualfrs *ql);
void						ft_print_xo4(t_qualfrs *ql);

void						ft_print_u(t_qualfrs *ql);
void						ft_print_u2(t_qualfrs *ql);
void						ft_print_u_1(t_qualfrs *ql);
void						ft_print_u_2(t_qualfrs *ql);
void						ft_print_u_3(t_qualfrs *ql);

char						*ft_itoa2(unsigned long long int n, int *x);
void						ft_print_space(int	a, t_qualfrs *ql);
void						ft_print_zero(int	a, t_qualfrs *ql);
char						*ft_10_to_8(unsigned long long x, t_qualfrs *ql);
char						*ft_10_to_16(unsigned long long x, t_qualfrs *ql);
void						ft_search_syntax(char *format, t_qualfrs *qual);
void						ft_print_pointer(t_qualfrs *ql);
void						ft_print_pointer2(t_qualfrs *ql);
void						ft_print_pointer2_1(t_qualfrs *ql);
void						ft_print_str(t_qualfrs *ql);
void						ft_print_str2(t_qualfrs *ql);
void						ft_printwchar(wchar_t c, t_qualfrs *ql);
size_t						ft_wstrlen(const char *str);
int							ft_putwchar(int c);
void						ft_print_char(t_qualfrs *ql);
char						*ft_print_format(char *as, t_qualfrs *qual);

void						ft_how_to_print2(t_qualfrs *ql);
void						ft_how_to_print(t_qualfrs *ql);

void						ft_color(t_qualfrs *ql);
void						ft_zero_struct(t_qualfrs *ql);
void						ft_zero_struct2(t_qualfrs *ql);
void						ft_without_typs(t_qualfrs *ql);
void						ft_print_percent(t_qualfrs *ql);
void						ft_print_str_uni(t_qualfrs *ql);

int							ft_inf_nan(t_qualfrs *ql);
void						print_bits2(void *ptr, char *frac, int i);
void						ft_print_b(t_qualfrs *ql);
#endif
