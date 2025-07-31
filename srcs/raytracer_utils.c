/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_ray(t_hit_info *hit, t_vec3 max_distance)
{
	hit->has_hit = false;
	hit->point = max_distance; //depth limit a mettre dans structure car const 
	hit->type = CAMERA;
	hit->distance = 100;
	hit->ent_index = 0;
}

t_ray	make_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

void	fill_hit_data(t_hit_info *hit, t_ray *ray, t_color color, int i)
{
  hit->point = add_vector(ray->origin, scale_vec(ray->direction, hit->distance));
	hit->ray = ray;
	hit->color = color;
	hit->ent_index = i;
}