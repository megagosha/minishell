# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edebi <edebi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 21:47:39 by edebi             #+#    #+#              #
#    Updated: 2021/04/13 12:37:44 by edebi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# LDFLAGS=-L.

# LDLIBS=-lft

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
       ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	   ft_issprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	   ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
	   ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	   ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	   ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	   ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_strarrcpy.c ft_listgetnum.c ft_str_replace.c \
		ft_arrlen.c ft_malloc.c ft_free_char_arr.c

OBJS = ${SRCS:.c=.o}

$(NAME): ${OBJS} libft.h
		 ar -crs ${NAME} ${OBJS}

.c.o:
	${CC} ${CFLAGS} ${OPTIONS} $< -o $@ -c

all: ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean fclean all re
