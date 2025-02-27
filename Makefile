CC = cc -Wall -Wextra -Werror #-g -fsanitize=address
INC = -I $(HEADERDIR)
LIBFT := ./libft
LIBRARY = libminishell.a
HEADERDIR = .
SRC = minishell.c \
executable.c \
ft_split2.c \
ft_strcmp.c \
builtin/cd.c \
builtin/exit.c \
builtin/echo.c \
builtin/env.c \
builtin/export.c \
builtin/export3.c \
builtin/pwd.c \
builtin/unset.c

OBJ = $(SRC:.c=.o)
SRCDIR = .
OBJDIR = $(SRCDIR)
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
NAME = minishell

all: $(NAME)

$(NAME): $(LIBRARY)
	make bonus -C $(LIBFT)
	$(CC) $(INC) $(SRC) -o $(NAME) -L. -lminishell -L$(LIBFT) -lft -lreadline

$(LIBRARY): $(OBJS)
	ar -rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(INC) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -f $(LIBRARY)

re: fclean all

.PHONY: all clean fclean re
