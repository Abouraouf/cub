NAME = cub3D
SRC = cub3D.c get_next_line.c get_next_line_utils.c utils_1.c utils_2.c \
map_parse_1.c colors_check.c utils_split.c

SRC_O = $(SRC:.c=.o)

%.o:%.c cub3D.h get_next_line.h
	cc -Wall -Wextra -Werror   -c $< -o $@  -fsanitize=address -g 

all : $(NAME)

$(NAME) : $(SRC_O)
	cc -Wall -Wextra -Werror $(SRC_O) -o $(NAME) -fsanitize=address -g 
clean :
	rm -rf $(SRC_O)

fclean : clean
	rm -rf $(NAME)

re : clean all
#  -fsanitize=address -g 