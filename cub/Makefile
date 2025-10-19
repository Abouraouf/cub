NAME = cub3D

SRC = cub3D.c get_next_line.c get_next_line_utils.c utils_1.c utils_2.c \
	map_parse_1.c colors_check.c utils_split.c main.c mlx_tools.c texturing.c dda.c dda2.c \
	utils_3.c utils_4.c utils_5.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lXext -lX11 -lm

%.o: %.c cub3D.h get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
