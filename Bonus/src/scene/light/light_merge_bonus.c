/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_merge_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:46:02 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/03 23:06:23 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt_bonus.h"

static double	shadow_ray(t_world *w, t_hit *hit_origin, t_vec light_dir,
		double light_n)
{
	t_ray	sray;
	t_hit	hit;
	double	shadow;

	sray.dir = light_dir;
	sray.origin = vec_add(hit_origin->point,
			vec_mult_scalar(hit_origin->normal, 0.01));
	shadow = 0.0;
	while (shadow < 1.0)
	{
		hit = find_closest_hit(w, sray, 1);
		if (!hit.hit || hit.t <= 0 || hit.t >= light_n || hit.t >= SHADOW_DIST)
			break ;
		if (hit.object->texture.type != TEX_IMG)
			return (1.0);
		hit.pixel_color = get_texture(&hit);
		shadow += (1.0 - shadow) * (hit.pixel_color.a / 255.0);
		sray.origin = vec_add(hit.point, vec_mult_scalar(light_dir, 0.001));
	}
	return (shadow);
}

static double	calc_specular(t_hit *hit, double coef_diffuse,
		t_vec light_dir, t_vec cam)
{
	t_vec	reflect;
	t_vec	view_dir;

	reflect = vec_sub(vec_mult_scalar(hit->normal, 2.0 * coef_diffuse),
			light_dir);
	vec_normalize(&reflect);
	view_dir = vec_sub(cam, hit->point);
	vec_normalize(&view_dir);
	return (vec_dot(reflect, view_dir));
}

static void	apply_light(t_light_ctx *ctx)
{
	double	shadow;
	double	factor;
	double	coef_s;

	shadow = shadow_ray(ctx->w, ctx->hit,
			ctx->light_dir, ctx->light_norm);
	factor = ctx->coef_d * ctx->light->intensity * (1.0 - shadow);
	ctx->l->diffuse[R] += (ctx->light->color.r / 255.0) * factor;
	ctx->l->diffuse[G] += (ctx->light->color.g / 255.0) * factor;
	ctx->l->diffuse[B] += (ctx->light->color.b / 255.0) * factor;
	coef_s = calc_specular(ctx->hit, ctx->coef_d,
			ctx->light_dir, ctx->w->camera.origin);
	if (coef_s > EPS)
	{
		coef_s = pow(coef_s, SHINY) * KS
			* ctx->light->intensity * (1.0 - shadow);
		ctx->l->specular[R] += (ctx->light->color.r / 255.0) * coef_s;
		ctx->l->specular[G] += (ctx->light->color.g / 255.0) * coef_s;
		ctx->l->specular[B] += (ctx->light->color.b / 255.0) * coef_s;
	}
}

void	calc_one_light(t_world *w, t_hit *hit, t_light *light,
		t_light_managment *l)
{
	t_light_ctx	ctx;

	ctx.w = w;
	ctx.hit = hit;
	ctx.light = light;
	ctx.l = l;
	ctx.light_dir = vec_sub(light->position, hit->point);
	ctx.light_norm = vec_norm(ctx.light_dir);
	vec_normalize(&ctx.light_dir);
	ctx.coef_d = vec_dot(hit->normal, ctx.light_dir);
	if (hit->object->type == OBJ_RING)
		ctx.coef_d = fabs(ctx.coef_d);
	if (ctx.coef_d > 0.001)
		apply_light(&ctx);
}
