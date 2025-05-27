CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb
NAME = minishell 

ARC = ./libft/libft.a

SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	   parse.c   ft_printf/ft_printf.c dynamic_str.c dynamic_str_arr.c dynamic_tokens_arr.c\
	   ft_printf/utils.c ft_printf/handle_print_bonus.c ft_printf/ft_memset_and_ptr.c 

MINISHELL_SRCS = $(SRCS) parse.c 

MINISHELL_OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MINISHELL_OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(MINISHELL_OBJS) $(ARC) -lreadline

clean:
	rm -f $(MINISHELL_OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) 
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
