##
## EPITECH PROJECT, 2023
## my_lib
## File description:
## my_lib
##

CC	=	gcc

NAME	=	42sh

UNIT_TEST	=	unit_test

CFLAGS	=	-Wshadow -Wall -Werror -I./include

FLCRIT	= 	-I./include

CRITFLAG	=	--coverage -lcriterion

LIBS	=	-L./ -lmy -lncurses

SRC	=   main.c					\
		src/ncurses.c			\
		src/ncurses_moves.c

SRC	+=	src/alias/alias_handler.c		\
		src/alias/find_alias.c			\
		src/alias/alias_command_line.c

SRC	+=	src/backticks/execute_backticks.c	\
		src/backticks/replace_backticks.c 	\
		src/backticks/handle_backticks.c

SRC	+=	src/base/cd_comand.c		\
		src/base/echo_command.c		\
		src/base/env.c				\
		src/base/error_handling.c	\
		src/base/exit.c				\
		src/base/fork_usage.c		\
		src/base/helper.c			\
		src/base/init_and_find.c	\
		src/base/list_to_array.c	\
		src/base/option_handler.c	\
		src/base/path_handling.c	\
		src/base/set_env_solo.c		\
		src/base/shell.c			\
		src/base/unset_env.c		\
		src/base/glob.c				\
		src/base/cd_permitions.c	\
		src/base/check_env_error.c	\
		src/base/init_ncurse.c		\
		src/base/free_func.c

SRC	+=	src/file_descriptor/find_error.c	\
		src/file_descriptor/handle_pipes.c	\
		src/file_descriptor/init_fd.c		\
		src/file_descriptor/parse_line.c	\
		src/file_descriptor/test_pipes.c	\
		src/file_descriptor/file_error_handling.c

SRC	+=	src/histroy/history_handler.c	\
		src/histroy/handle_exlamations.c

SRC	+=	src/linked_lists/list.c			\
		src/linked_lists/manage_list.c	\
		src/linked_lists/my_list_len.c	\
		src/linked_lists/node.c

SRC	+=	src/parenthesis/find_parnethese.c	\
		src/parenthesis/init_parenthese.c

SRC	+=	src/priorities/delim_tok.c		\
		src/priorities/find_prorities.c	\
		src/priorities/init_commands.c	\
		src/priorities/tok_delims.c

SRC	+=	src/redirections/double_left.c	\
		src/redirections/left.c			\
		src/redirections/right.c

SRC	+=	src/shell_scripting/execute.c

SRC	+=	src/variables/display_set.c			\
		src/variables/set_variable.c		\
		src/variables/set.c					\
		src/variables/sort_set.c			\
		src/variables/unset.c				\
		src/variables/set_parsing.c 		\
		src/variables/specials/cwd.c		\
		src/variables/specials/cwdcmd.c		\
		src/variables/specials/home.c		\
		src/variables/specials/ignoreof.c	\
		src/variables/specials/last_cmd.c	\
		src/variables/specials/prompt.c		\
		src/variables/specials/term.c		\
		src/variables/specials/precmd.c		\
		src/variables/specials/postcmd.c	\
		src/variables/specials/value.c

SRCTEST	=	$(filter-out main.c, $(SRC))

OBJ		=	$(SRC:.c=.o)

CRITFLAG+=	tests/test_lib.c				\
			tests/test_alias.c				\
			tests/test_base.c				\
			tests/test_file_descriptor.c	\
			tests/test_histroy.c			\
			tests/test_linked_lists.c		\
			tests/test_parenthesis.c		\
			tests/test_priorities.c			\
			tests/test_redirections.c		\
			tests/test_shell_scripting.c	\
			tests/test_variables.c			\
			tests/test_backticks.c			\
			tests/test_ero_file.c			\
			tests/test_cd.c					\
			tests/test_env.c				\
			tests/test_gork.c				\
			tests/test_helper.c				\
			tests/test_shell.c

all:	libmy $(NAME)

libmy:
	@$(MAKE) -C lib/my > /dev/null 2>&1

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)
	@echo -e "\e[1;32m{ Makefile is ready }\e[00;37m"
	@echo -e "\e[1;36m{ Binary is ready }\e[00;37m"
	@cp -f $(NAME) tests/
	@echo -e "\e[1;35m{ ./42sh copied in tests/ }\e[00;37m"

$(UNIT_TEST): libmy
	@$(CC) -o $(UNIT_TEST) $(SRCTEST) $(FLCRIT) $(CRITFLAG) $(LIBS)

tests_run:	$(UNIT_TEST)
	@./$(UNIT_TEST)
	@-gcovr --exclude tests/
bash:
	@$(MAKE) > /dev/null 2>&1
	@cd tests/ && ./tester.sh; cd ..
clean:
	@$(MAKE) -C lib/my clean > /dev/null
	@rm -f $(OBJ)
	@rm -f *.gc*
	@rm -f coding-style-reports.log
	@rm -f *~
	@rm -f *.gc*

fclean:	clean
	@$(MAKE) -C lib/my fclean
	@rm -f $(NAME)
	@rm -f $(UNIT_TEST)
	@echo -e "\e[1;33m{ REPOSITORY has been cleaned }\e[00;37m"

norm: fclean
	@coding-style . .
	@cat coding-style-reports.log

re:	fclean all

.PHONY: libmy clean fclean re all norm tests_run bash
