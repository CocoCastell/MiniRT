#.SILENT:
.PHONY: all clean fclean re 

NAME	=	miniRT
CC		=	cc
FLAGS	=	-Wall -Werror -Wextra -MMD -MP -O3

# Repositories
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/
MLX_DIR		=	mlx_linux/
LIBFT_DIR	=	libft/

# Librairies
MLX		=	$(MLX_DIR)libmlx.a
LIBFT	=	$(LIBFT_DIR)libft.a
LIBS	=	$(LIBFT) -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Includes
INC		=	includes/miniRT.h \
			includes/structures.h \
			includes/defines.h \
			includes/prototypes.h \
			$(MLX_DIR)mlx.h \
			$(MLX_DIR)mlx_int.h \
			$(LIBFT_DIR)includes/get_next_line_bonus.h \
			$(LIBFT_DIR)includes/ft_printf_bonus.h \
			$(LIBFT_DIR)includes/libft.h

# Files
SRCS	=	srcs/main.c \
			srcs/error.c \
			srcs/raytracer.c \
			srcs/raytracer_utils.c \
			srcs/utils.c \
			srcs/colors/colors.c \
			srcs/colors/colors2.c \
			srcs/math/vector_operations.c \
			srcs/math/create_vectors.c \
			srcs/math/angle.c \
			srcs/math/simple_operations.c \
			srcs/init/init_minirt.c \
			srcs/init/init_utils.c \
			srcs/init/parse.c \
			srcs/init/parse_objects.c \
			srcs/init/parse_utils.c \
			srcs/init/count.c \
			srcs/init/init_obj_struct.c \
			srcs/controls/events.c \
			srcs/controls/events2.c \
			srcs/controls/translations.c \
			srcs/controls/rotations.c \
			srcs/controls/control_utils.c \
			srcs/light/light.c \
			srcs/light/setters.c \
			srcs/light/getters.c \
			srcs/light/light_utils.c \
			srcs/objects/sphere.c \
			srcs/objects/plane.c \
			srcs/objects/triangle.c \
			srcs/objects/cylinder.c  \
			srcs/objects/cylinder_utils.c  \
			srcs/print_scene.c

OBJS	=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

LIBFT_F	=	gnl/get_next_line_bonus.c \
			gnl/get_next_line_utils_bonus.c \
			printf/ft_manager_bonus.c \
			printf/ft_printf_bonus.c \
			printf/ft_types_bonus.c \
			lib/ft_float_to_str.c \
			lib/ft_free_string_array.c \
			lib/ft_free_matrix.c \
			lib/ft_str_array_len.c \
			lib/ft_is_only_digit.c \
			lib/ft_putnbr_fd.c \
			lib/ft_strmapi.c \
			lib/ft_putstr_fd.c \
			lib/ft_strncmp.c \
			lib/ft_strrev.c \
			lib/ft_atoi.c \
			lib/ft_atof.c \
			lib/ft_split.c \
			lib/ft_split_whitespace.c \
			lib/ft_itoa.c \
			lib/ft_strnstr.c \
			lib/ft_bzero.c \
			lib/ft_memchr.c \
			lib/ft_strchr.c \
			lib/ft_strrchr.c \
			lib/ft_calloc.c \
			lib/ft_memcmp.c \
			lib/ft_strdup.c \
			lib/ft_strtrim.c \
			lib/ft_isalnum.c \
			lib/ft_memcpy.c \
			lib/ft_striteri.c \
			lib/ft_substr.c \
			lib/ft_isalpha.c \
			lib/ft_memmove.c \
			lib/ft_strjoin.c \
			lib/ft_tolower.c \
			lib/ft_isascii.c \
			lib/ft_memset.c \
			lib/ft_strlcat.c \
			lib/ft_toupper.c \
			lib/ft_isdigit.c \
			lib/ft_putchar_fd.c \
			lib/ft_strlcpy.c \
			lib/ft_isprint.c \
			lib/ft_putendl_fd.c \
			lib/ft_strlen.c \
			lib/ft_lstadd_back_bonus.c \
			lib/ft_lstadd_front_bonus.c \
			lib/ft_lstclear_bonus.c \
			lib/ft_lstdelone_bonus.c \
			lib/ft_lstiter_bonus.c \
			lib/ft_lstlast_bonus.c \
			lib/ft_lstmap_bonus.c \
			lib/ft_lstnew_bonus.c \
			lib/ft_lstsize_bonus.c

LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(LIBFT_F))

# Compilation
all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(LIBFT_SRCS) $(OBJS) $(INC) Makefile
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS_DIR)srcs/%.o: $(SRCS_DIR)%.c $(INC) | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(MLX):
	make --no-print-directory -C $(MLX_DIR)

$(LIBFT):
	make --no-print-directory -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make clean --no-print-directory -C $(MLX_DIR) 
	make clean --no-print-directory -C $(LIBFT_DIR) 

fclean: clean
	rm -rf $(NAME)
	make fclean --no-print-directory -C $(MLX_DIR)
	make fclean --no-print-directory -C $(LIBFT_DIR)

re: clean all
