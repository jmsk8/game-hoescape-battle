
NAME        = Hoescape

SRCS_MAN    = main.c \
              fonction.c \
              game.c \
              setup_game.c \
              spawn.c \
              threads.c \
			  get_next_line.c \
			  get_next_line_utils.c \

MAN_PATH    = ./src/
SRCS        = $(addprefix $(MAN_PATH), $(SRCS_MAN))

OBJS        = $(SRCS:.c=.o)

HEAD        = include/
HEADERS     = include.h

CFLAGS      = -g3 -Wall -Wextra -Werror -I $(HEAD)
LDFLAGS     = -lncurses

CC          = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
