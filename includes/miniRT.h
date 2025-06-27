#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/ft_printf_bonus.h"

# define WIN_WIDTH 1400
# define WIN_HEIGHT 800
# define ESC 65307


typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		frame_count;
} t_data_img;

typedef struct s_color
{
	int t;
	int r;
	int g;
	int b;
} t_color;

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

typedef struct s_scene
{
} t_scene;

typedef struct s_miniRt
{
	void		*mlx;
	void		*win;
	t_data_img	img;
	t_scene		*scene;
} t_miniRt;

// Events
void	event_manager(t_miniRt *minirt);
int	key_pressed(int keycode, t_miniRt *minirt);
int     my_close(t_miniRt *minirt);


// Error
void	exit_error(char *msg, int error);
void	free_mlx(t_miniRt *minirt);
void	free_error(t_miniRt *minirt, char *msg, int error);

#endif
