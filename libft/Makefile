# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdemetra <cdemetra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/21 23:08:55 by cdemetra          #+#    #+#              #
#    Updated: 2019/06/26 18:13:11 by cdemetra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC=ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
 	ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
 	ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
 	ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
 	ft_strcmp.c ft_strncmp.c \
 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
 	ft_toupper.c ft_tolower.c \
 	ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
 	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	ft_strtrim.c ft_strsplit.c \
 	ft_itoa.c ft_atoi.c \
 	ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
 	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
 	ft_lstiter.c ft_lstmap.c \
	ft_lst_size.c ft_lstnpoint.c ft_sort_wordtab.c ft_strlowcase.c ft_str_reverse.c ft_strupcase.c ft_lst_contentsearch.c \
	get_next_line.c \

OBJ=$(SRC:.c=.o)
INCL=./
all: $(NAME)
$(NAME): libft.h
	$(CC) $(CFLAGS) -I$(INCL) -c $(SRC) 
	ar rc $(NAME) $(OBJ) 
	ranlib $(NAME)
	
clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
