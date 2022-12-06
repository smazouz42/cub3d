NAME = cub3D
INC = cub3d.h
SRC = main.c cub_init.c draw.c events.c map_init.c map.c math.c ray_cast.c \
		rend3R.c update.c upload_rays.c cub_tools.c parcer/map_parcer.c \
		parcer/tools.c parcer/full_check.c parcer/ft_split.c parcer/fix_map.c \
		parcer/parcer.c parcer/get_items.c parcer/free.c sprite.c

OBJ = $(SRC:.c=.o)

CC = cc
# CFLAGS = 
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(SRC) $(INC)
	$(CC) $(MLXFLAGS) $(SRC) -o $(NAME)

clean :
	$(RM) $(OBJ)
	@echo "Cleaned"

fclean :
	$(RM) $(OBJ) $(NAME)
	@echo "Fully cleaned"
	
re : fclean all