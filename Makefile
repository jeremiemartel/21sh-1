# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 18:51:58 by mabayle           #+#    #+#              #
#    Updated: 2019/12/06 03:56:26 by mabayle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	21sh

CC			:=	gcc
LINKER		:=	gcc -o

DEBUG		:=	0

LIBFT		:=	libft/libft.a

INCLUDES	:=	./includes

#libft
INCLUDES	:=	$(INCLUDES) -I$(dir $(LIBFT))includes
LDFLAGS		:=	-L$(dir $(LIBFT)) -lft

CFLAGS		:=	-Wall -Wextra -Werror -I$(INCLUDES)

ifeq ($(DEBUG), 1)
	CFLAGS	:=	$(CFLAGS) -fsanitize=address -ggdb -fno-omit-frame-pointer
endif

SRC_PATH	:=	./src/
OBJ_PATH	:=	./obj/

SRC		:=	main.c \
			lexer/lexer.c \
			lexer/list_utils.c \
			lexer/utils.c \
			lexer/type_token.c \
			lexer/print_debug.c \
			edl/edl_assoc.c \
			edl/edl_controller.c \
			edl/edl_key_arrow.c \
			edl/edl_key_cn_arrow.c \
			edl/edl_key_utils.c \
			edl/ft_str_in_array.c \
			edl/sh_cursor_move.c \
			edl/sh_term_switch.c \
			parser/parserV2.c \
			parser/grammar/and_or.c \
			parser/grammar/cmd_name.c \
			parser/grammar/cmd_prefix.c \
			parser/grammar/cmd_suffix.c \
			parser/grammar/cmd_word.c \
			parser/grammar/complete_cmd.c \
			parser/grammar/complete_cmds.c \
			parser/grammar/filename.c \
			parser/grammar/here_end.c \
			parser/grammar/io_file.c \
			parser/grammar/io_here.c \
			parser/grammar/io_redirect.c \
			parser/grammar/linebreak.c \
			parser/grammar/list_grammar.c \
			parser/grammar/newline_list.c \
			parser/grammar/pipe_sequence.c \
			parser/grammar/pipeline.c \
			parser/grammar/program.c \
			parser/grammar/separator_op.c \
			parser/grammar/separator.c \
			parser/grammar/simple_command.c

OBJ		:=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))
SRC		:=	$(addprefix $(SRC_PATH), $(SRC))

$(NAME):  $(LIBFT) $(OBJ)
	@$(LINKER) $(NAME) $(LDFLAGS) $(OBJ)
	@echo ""
	@echo "\033[0;32m 21_SH BUILD DONE \033[0m"
	@echo ""

all: $(NAME)

$(LIBFT):	$(dir $(LIBFT))Makefile
	@make -C $(dir $(LIBFT))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Compiling 21sh :\033[0m" $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Deleted all .o\033[0m"

fclean:
	@make -C libft/ fclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Deleted all .o\033[0m"
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Deleted 21sh\033[0m"

re: fclean all

.PHONY:	all clean fclean re
