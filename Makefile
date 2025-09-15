NAME = cub3D
SRC = cub3D.c utils.c 
SRC_O = $(SRC:.c=.o)

%.o:%.c cub3D.h get_next_line.h
	cc -Wall -Wextra -Werror -c $< -o $@

all : $(NAME)

$(NAME) : $(SRC_O)
	cc -Wall -Wextra -Werror $(SRC_O) -o $(NAME)

clean :
	rm -rf $(SRC_O)

fclean : clean
	rm -rf $(NAME)

re : clean all