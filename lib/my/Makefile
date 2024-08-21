##
## EPITECH PROJECT, 2023
## B-CPE-110-NAN-1-1-organized-albane.merian
## File description:
## libmy
##

SRC =	how_many.c				\
		my_put_nbr.c			\
		my_putstr.c				\
		my_strlen.c				\
		my_unsigned_nbr.c 		\
		my_putchar.c 			\
		my_positive_nbr.c 		\
		my_getnbr.c				\
		my_isnum.c 				\
		my_strdup.c 			\
		my_strcat.c 			\
		my_revstr.c 			\
		my_printf.c 			\
		printf_i.c 				\
		printf_c.c 				\
		printf_d.c 				\
		printf_s.c 				\
		printf_u.c 				\
		printf_x.c 				\
		printf_xm.c 			\
		printf_o.c 				\
		printf_f.c 				\
		printf_fm.c 			\
		printf_cross.c 			\
		printf_l.c	 			\
		my_isalpha.c 			\
		my_strncpy.c	 		\
		my_strcpy.c 			\
		my_strstr.c 			\
		my_strcmp.c 			\
		my_is_even.c			\
		my_strtok.c				\
		my_str_to_word_array.c	\
		my_charcmp.c			\
		my_array.c				\
		my_realloc.c			\
		my_alpha.c				\
		my_malloc.c				\
		string_to_word_array.c	\
		my_arrndup.c			\
		my_arr_to_str.c			\
		my_strncmp.c			\
		my_tok.c				\
		my_str_isprintable.c	\
		move_str.c				\
		my_strndup.c			\
		print_triple.c			\
		my_itoa.c				\
		move_str_end.c			\
		my_tablen.c				\
		my_arraydup.c			\
		string_to_tok.c			\
		clean_str.c

OBJ = $(SRC:.c=.o)

NAME = libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	cp my.h ../../include
	ar rc $(NAME) $(OBJ)
	mv $(NAME) ../../$(NAME)
	@echo -e "\e[1;33m{ Library is ready }\e[00;37m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f ../../$(NAME)
	@echo -e "\e[1;31m{ Cleaned up binary and library }\e[00;37m"

re: fclean all
