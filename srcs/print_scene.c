#include "../includes/miniRT.h"

#define COL_1 4
#define COL_2 22
#define COL_3 22
#define COL_4 8
#define COL_5 8
#define COL_6 14
#define COL_7 8
#define COL_8 8

void	put_spaces(int spaces, int fd)
{
	while (spaces-- > 0)
		ft_putchar_fd(' ', fd);
}

void	get_sphere_data(t_sphere sphere, t_parse_data *data, int i)
{
	data->center = sphere.center[i];
	data->radius = sphere.radius[i];
	data->color = sphere.color[i];
	data->shininess = sphere.shininess[i];
	data->spec_force = sphere.spec_force[i];
	data->reflectivity = sphere.reflectivity[i];
}

void	get_plane_data(t_plane plane, t_parse_data *data, int i)
{
	data->point = plane.point[i];
	data->normal = plane.normal[i];
	data->color = plane.color[i];
	data->shininess = plane.shininess[i];
	data->spec_force = plane.spec_force[i];
	data->reflectivity = plane.reflectivity[i];
}

void	get_cylinder_data(t_cylinder cylinder, t_parse_data *data, int i)
{
	data->center = cylinder.center[i];
	data->normal = cylinder.axis[i];
	data->radius = cylinder.radius[i];
	data->height = cylinder.height[i];
	data->color = cylinder.color[i];
	data->shininess = cylinder.shininess[i];
	data->spec_force = cylinder.spec_force[i];
	data->reflectivity = cylinder.reflectivity[i];
}

void	get_light_data(t_light light, t_parse_data *data, int i)
{
	data->point = light.pos[i];
	data->shininess = light.intensity[i];
	data->color = light.color[i];
}

int print_float(float value, int fd)
{
	char	str[32];
	int		len;

	len = snprintf(str, sizeof(str), "%.2f", value);
	ft_putstr_fd(str, fd);
	return (len);
}

int	print_coordinates(t_vec3 coord, int fd)
{
	int		len;
	char	str[64];

	len = snprintf(str, sizeof(str), "%.2f", coord.x);
	ft_putstr_fd(str, fd);
	len += write(fd, ",", 1);
	len += snprintf(str, sizeof(str), "%.2f", coord.y);
	ft_putstr_fd(str, fd);
	len += write(fd, ",", 1);
	len += snprintf(str, sizeof(str), "%.2f", coord.z);
	ft_putstr_fd(str, fd);
	return (len);
}

int	print_color(t_color color, int fd)
{
	int		len;
	char	*str;

	str = ft_itoa((int)(color.r * 255.0f));
	len = ft_strlen(str);
	ft_putstr_fd(str, fd);
	len += write(fd, ",", 1);
	str = ft_itoa((int)(color.g * 255.0f));
	len += ft_strlen(str);
	ft_putstr_fd(str, fd);
	str = ft_itoa((int)(color.b * 255.0f));
	len += ft_strlen(str);
	len += write(fd, ",", 1);
	ft_putstr_fd(str, fd);
	return (len);
}

void	put_sphere_data(int fd, t_parse_data data)
{
	int	len;

	len = write(fd, "sp", 2);
	put_spaces(COL_1 - len, fd);
	len = print_coordinates(data.center, fd);
	put_spaces(COL_2 + COL_3 - len, fd);
	len = print_float(data.radius * 2, fd);
	put_spaces(COL_4 + COL_5 - len, fd);
	len = print_color(data.color, fd);	
	put_spaces(COL_6 - len, fd);
	len = print_float(data.shininess, fd);
	put_spaces(COL_7 - len, fd);
	len = print_float(data.spec_force, fd);
	put_spaces(COL_8 - len, fd);
	len = print_float(data.reflectivity, fd);
	len = write(fd, "\n", 1);
	(void)len;
}

void	put_plane_data(int fd, t_parse_data data)
{
	int	len;

	len = write(fd, "pl", 2);
	put_spaces(COL_1 - len, fd);
	len = print_coordinates(data.point, fd);
	put_spaces(COL_2 - len, fd);
	len =print_coordinates(data.normal, fd);
	put_spaces(COL_3 + COL_4 + COL_5 - len, fd);
	len = print_color(data.color, fd);	
	put_spaces(COL_6 - len, fd);
	len = print_float(data.shininess, fd);
	put_spaces(COL_7 - len, fd);
	len = print_float(data.spec_force, fd);
	put_spaces(COL_8 - len, fd);
	len = print_float(data.reflectivity, fd);
	len = write(fd, "\n", 1);
	(void)len;
}

void	put_camera_data(int fd, t_camera camera)
{
	int	len;

	len = write(fd, "C ", 1);
	put_spaces(COL_1 - len, fd);
	len = print_coordinates(camera.pos, fd);
	put_spaces(COL_2 - len, fd);
	len = print_coordinates(camera.forward, fd);
	put_spaces(COL_3 - len, fd);
	len = print_float(camera.fov, fd);
	len = write(fd, "\n", 1);
	(void)len;
}

void	put_ambient_data(int fd, t_scene *scene)
{
	int	len;

	len = write(fd, "A", 1);
	put_spaces(COL_1 - len, fd);
	len = print_float(scene->amb_ratio, fd);
	put_spaces(COL_2 + COL_3 + COL_4 + COL_5 - len, fd);
	len = print_color(scene->amb_color, fd);	
	len = write(fd, "\n\n", 2);
	(void)len;
}

void	put_light_data(int fd, t_parse_data data)
{
	int	len;

	len = write(fd, "L", 1);
	put_spaces(COL_1 - len, fd);
	len = print_coordinates(data.point, fd);
	put_spaces(COL_2 + COL_3 - len, fd);
	len = print_float(data.shininess, fd);
	put_spaces(COL_4 + COL_5 - len, fd);
	len = print_color(data.color, fd);	
	len = write(fd, "\n", 1);
	(void)len;
}

void	put_data_in_file(t_scene *scene)
{
	t_parse_data	data;
	int						i;
	int						fd;

	fd = open("new_scene", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return ;
	put_ambient_data(fd, scene);
	put_camera_data(fd, scene->camera);
	for (i = 0; i < scene->light.count; i++)
	{
		get_light_data(scene->light, &data, i);
		put_light_data(fd, data);
	}
	ft_putchar_fd('\n', fd);
	for (i = 0; i < scene->plane.count; i++)
	{
		get_plane_data(scene->plane, &data, i);
		put_plane_data(fd, data);
	}
	if (i > 0)
		ft_putchar_fd('\n', fd);
	// for (i = 0; i < scene->cylinder.count; i++)
	// {
		// get_sphere_data(scene->cylinder, &data, i);
		// put_sphere_data(fd, data);
	// }
	// if (i > 0)
		// ft_putchar_fd('\n', fd);
	for (i = 0; i < scene->sphere.count; i++)
	{
		get_sphere_data(scene->sphere, &data, i);
		put_sphere_data(fd, data);
	}
	// if (i > 0)
	// 	ft_putchar_fd('\n', fd);
	// for (i = 0; i < scene->triangle.count; i++)
	// {
		// get_sphere_data(scene->triangle, &data, i);
		// put_sphere_data(fd, data);
	// }
	close(fd);
}