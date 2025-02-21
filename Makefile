CC = cc -Wall -Wextra -Werror
INC = -I $(HEADERDIR)
LIBFT := ./libft
LIBRARY = libminishell.a
HEADERDIR = .
SRC = minishell.c\
      executable.c\
      ft_split2.c\
      ft_strcmp.c\
      exit.c\
      builtin/echo.c
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
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -f $(LIBRARY)

re: fclean all

.PHONY: all clean fclean re
