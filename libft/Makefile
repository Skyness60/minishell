# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 12:15:54 by jlebard           #+#    #+#              #
#    Updated: 2024/08/29 13:11:56 by jlebard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

WINDOWS = no
NAME = libft.a
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strncat.c
OBJ = $(SRC:.c=.o)
CC = cc
CCFLAGS = -Wall -Wextra -Werror
AR = ar rcs

ifeq ($(WINDOWS), yes)
	CLEAN = del /Q 
else 
	CLEAN = rm -rf 
endif

ifeq ($(WINDOWS), yes)
	FCLEAN = del /Q 
else 
	FCLEAN = rm -f 
endif

%.o : %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(NAME) : $(OBJ)
	$(AR) $@ $^

all: $(NAME)

clean:
	$(CLEAN) *.o

fclean:	clean
	$(FCLEAN) $(NAME)

re:	fclean all
