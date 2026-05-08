CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make
FTPRINTF_DIR = ftprintf
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a
INCLUDE = -Iinclude -I$(FTPRINTF_DIR)

NAME = fdf
SRC = src/fdf.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(FTPRINTF) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(FTPRINTF)

$(FTPRINTF):
	$(MAKE) -C $(FTPRINTF_DIR)

%.o: %.c
	$(CC) $(CLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(FTPRINTF_DIR) $@

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FTPRINTF_DIR) $@

re:	fclean all

.PHONY: all clean fclean re
