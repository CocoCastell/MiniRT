/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel  cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/07 19:00:54 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Adds a cylinder at index i in a SoA structure.
 *
 * This function inserts the cylinder data (center, color, radius, etc.)
 * into the corresponding arrays of the `t_cylinder` structure at the given idx.
 * 
 * @param data Parsed cylinder data to insert (position, color, radius, etc.).
 * @param cylinder Structure holding SoA arrays of all cylinders.
 * @param i Index at which to insert the cylinder data in the `cylinder` struct.
 */
void	add_cylinder(t_parse_data data, t_cylinder cylinder, int i)
{
	cylinder.radius[i] = data.radius;
	cylinder.height[i] = data.height;
	cylinder.axis[i] = data.normal;
	cylinder.center[i] = data.center;
	cylinder.color[i] = data.color;
	cylinder.shininess[i] = data.shininess;
	cylinder.spec_force[i] = data.spec_force;
	cylinder.reflectivity[i] = data.reflectivity;
}

static float	body_intersect(t_ray ray, t_cylinder *cyl, int i)
{
	t_vec3	axis;
	t_vec3	oc;
	t_vec3	proj_d;
	t_vec3	proj_oc;

	axis = cyl->axis[i];
	oc = vector_from_to(cyl->center[i], ray.origin);
	proj_d = vector_from_to(scale_vector(axis, dot(ray.direction, axis)), \
			ray.direction);
	proj_oc = vector_from_to(scale_vector(axis, dot(oc, axis)), oc);
	return (solve_quadratic(init_quadratic(proj_d, proj_oc, cyl->radius[i])));
}

static void	set_body_hit(t_ray ray, t_cylinder *cyl, int i, t_cyl_h *hit)
{
	float	t;
	t_vec3	pt;

	t = body_intersect(ray, cyl, i);
	hit->t = -1.0f;
	if (t < 0)
		return ;
	pt = add_vector(ray.origin, scale_vector(ray.direction, t));
	if (!in_height(cyl->center[i], cyl->axis[i], pt, cyl->height[i]))
		return ;
	hit->t = t;
	hit->is_cap = 0;
}

float	cap_intersect_dist(t_ray ray, t_vec3 center, t_vec3 normal, float rad)
{
	float	denom;
	float	t;
	float	dist;
	t_vec3	hit_pt;

	denom = dot(normal, ray.direction);
	if (fabs(denom) < 1e-6)
		return (-1.0f);
	t = dot(vector_from_to(ray.origin, center), normal) / denom;
	if (t < 1e-4)
		return (-1.0f);
	hit_pt = ray_at(ray.origin, ray.direction, t);
	dist = vector_length(vector_from_to(center, hit_pt));
	if (dist > rad)
		return (-1.0f);
	return (t);
}

void	cylinder_intersect(t_hit_info *hit, t_ray ray, t_cylinder *cyl, int i)
{
	t_cyl_h	hits[3];
	t_cyl_h	*closest;
	t_vec3	caps[2];

	set_body_hit(ray, cyl, i, &hits[0]);
	get_caps_center(cyl, i, caps);
	hits[1].t = cap_intersect_dist(ray, caps[0], cyl->axis[i], cyl->radius[i]);
	hits[1].is_cap = 1;
	hits[2].t = cap_intersect_dist(ray, caps[1], cyl->axis[i], cyl->radius[i]);
	hits[2].is_cap = 1;
	closest = find_closest(hits);
	if (!closest || (hit->has_hit && closest->t >= hit->distance))
		return ;
	hit->has_hit = true;
	hit->distance = closest->t;
	hit->ent_index = i;
	if (closest->is_cap)
		hit->type = CYLINDER_CAP;
	else
		hit->type = CYLINDER;
}
