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
			$(MLX_DIR)mlx.h \
			$(MLX_DIR)mlx_int.h \
			$(LIBFT_DIR)includes/get_next_line_bonus.h \
			$(LIBFT_DIR)includes/ft_printf_bonus.h \
			$(LIBFT_DIR)includes/libft.h

# Files
SRCS	=	srcs/main.c \
			srcs/error.c \
			srcs/vector_operation.c \
			srcs/colors.c \
			srcs/init.c \
			srcs/raytracer.c \
			srcs/raytracer_utils.c \
			srcs/setters.c \
			srcs/getters.c \
			srcs/utils.c \
			srcs/controls/events.c \
			srcs/controls/transform.c \
			srcs/controls/control_utils.c \
			srcs/objects/light.c \
			srcs/objects/light_utils.c \
			srcs/objects/plane.c \
			srcs/objects/sphere.c \
			srcs/objects/cylinder.c

OBJS	=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

LIBFT_F	=	gnl/get_next_line_bonus.c \
			gnl/get_next_line_utils_bonus.c \
			printf/ft_manager_bonus.c \
			printf/ft_printf_bonus.c \
			printf/ft_types_bonus.c \
			lib/ft_free_string_array.c \
			lib/ft_free_matrix.c \
			lib/ft_putnbr_fd.c \
			lib/ft_strmapi.c \
			lib/ft_putstr_fd.c \
			lib/ft_strncmp.c \
			lib/ft_strrev.c \
			lib/ft_atoi.c \
			lib/ft_split.c \
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

$(NAME): $(MLX) $(LIBFT) $(OBJS) $(INC) Makefile
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
	make --no-print-directory -C $(MLX_DIR) clean
	make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make --no-print-directory -C $(MLX_DIR) fclean
	make --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
