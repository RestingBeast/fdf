CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make
FTPRINTF_DIR = ftprintf
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a
INCLUDE = -Iinclude -I$(FTPRINTF_DIR) -I$(MINILIBX_DIR)

NAME = fdf
SRC = src/fdf.c \
	  src/image.c \
	  src/window.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(FTPRINTF) $(OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(FTPRINTF) $(MINILIBX) -lXext -lX11

$(FTPRINTF):
	$(MAKE) -C $(FTPRINTF_DIR)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

%.o: %.c
	$(CC) $(CLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(FTPRINTF_DIR) $@
	$(MAKE) -C $(MINILIBX_DIR) $@

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FTPRINTF_DIR) $@
	$(MAKE) -C $(MINILIBX_DIR) $@

re:	fclean all

.PHONY: all clean fclean re
