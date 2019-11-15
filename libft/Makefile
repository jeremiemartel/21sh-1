NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

C_PATH = ./srcs/

O_PATH = ./objs/

H_PATH = ./includes/

SRCS_F = ft_bzero.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
		 ft_memcpy.c ft_memdel.c ft_memmove.c ft_memreplace.c ft_memrev.c \
		 ft_memset.c \
		 ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
		 ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
		 ft_strcat.c ft_strchr.c ft_strchrnul.c ft_strclr.c ft_strcmp.c \
		 ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
		 ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
		 ft_strjoin_onef.c ft_strjoin_free.c ft_strjoin_one.c \
		 ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
		 ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strreplace.c ft_strrev.c \
		 ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
		 ft_toupper.c ft_tolower.c ft_strtolower.c \
		 ft_atoi.c ft_itoa.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		 ft_isblank.c ft_iscntrl.c ft_isdigit.c ft_islower.c ft_isprint.c \
		 ft_ispunct.c ft_isspace.c ft_isupper.c get_next_line.c

OBJS_F = $(SRCS_F:.c=.o)

SRCS = $(addprefix $(C_PATH),$(SRCS_F))
OBJS = $(addprefix $(O_PATH),$(OBJS_F))
INCS = $(addprefix -I, $(H_PATH))

all : $(NAME)

$(NAME) : $(OBJS)
	@echo ""
	@echo "\033[0;32m LIBFT BUILD DONE \033[0m"
	@echo ""
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(O_PATH)%.o: $(C_PATH)%.c
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [LIBFT] Compiling libft :\033[0m" $<
	@mkdir -p objs
	@$(CC) $(FLAGS) $(INCS) -o $@ -c $<

clean :
	@rm -rf $(OBJS)
	@rm -rf $(O_PATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [LIBFT] Deleted all .o\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [LIBFT] Deleted libft.a\033[0m"

re : fclean all
