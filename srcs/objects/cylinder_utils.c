/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel  cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/07 19:01:03 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	get_caps_center(t_cylinder *cyl, int i, t_vec3 centers[2])
{
	t_vec3	axis;
	float	half_h;

	axis = normalize(cyl->axis[i]);
	half_h = cyl->height[i] / 2.0f;
	centers[0] = add_vector(cyl->center[i], scale_vector(axis, half_h));
	centers[1] = add_vector(cyl->center[i], scale_vector(axis, -half_h));
}

t_cyl_h	*find_closest(t_cyl_h hits[3])
{
	t_cyl_h	*closest;
	int		i;

	closest = NULL;
	i = -1;
	while (++i < 3)
	{
		if (hits[i].t > 0 && (!closest || hits[i].t < closest->t))
			closest = &hits[i];
	}
	return (closest);
}

t_q_eq	init_quadratic(t_vec3 proj_dir, t_vec3 proj_oc, float radius)
{
	t_q_eq	q;

	q.a = dot(proj_dir, proj_dir);
	q.b = 2.0f * dot(proj_dir, proj_oc);
	q.c = dot(proj_oc, proj_oc) - radius * radius;
	q.delta = q.b * q.b - 4 * q.a * q.c;
	return (q);
}

float	solve_quadratic(t_q_eq q)
{
	float	sq_d;
	float	t1;
	float	t2;

	if (q.delta < 0 || fabs(q.a) < 1e-6)
		return (-1.0f);
	sq_d = sqrt(q.delta);
	t1 = (-q.b - sq_d) / (2.0f * q.a);
	t2 = (-q.b + sq_d) / (2.0f * q.a);
	if (t1 > 1e-4)
		return (t1);
	if (t2 > 1e-4)
		return (t2);
	return (-1.0f);
}

int	in_height(t_vec3 center, t_vec3 axis, t_vec3 pt, float height)
{
	t_vec3	to_pt;
	float	proj;

	to_pt = vector_from_to(center, pt);
	proj = dot(to_pt, axis);
	if (fabs(proj) > height / 2.0f)
		return (0);
	return (1);
}
