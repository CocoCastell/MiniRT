/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:36:23 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/13 17:37:53 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

// Variables
# define WIN_WIDTH				1080
# define WIN_HEIGHT				720
# define V_PORT_WIDTH			2.0f
# define V_PORT_DIST			1 
# define PIXEL_RATIO			(V_PORT_WIDTH / WIN_WIDTH)
# define M_PIF					3.1415927f
# define STEP					0.2
# define ZOOM_IN      1.1
# define ZOOM_OUT			0.9
# define SAMPLE_PER_PIX			12
# define DEPTH					2
# define NB_MANDATORY_DATA  	6
# define STRIPE_NB				30

// Control keys
# define ESC					65307
# define LEFT_CLICK				1
# define WHEEL					2
# define RIGHT_CLICK			3
# define SCROLL_UP				4
# define SCROLL_DOWN			5
# define KEY_1					49
# define KEY_2					50
# define KEY_3					51
# define KEY_4					52
# define SPACE					32
# define SHIFT					65505	
# define CTRL					65307
# define PLUS_KEY				43	
# define MINUS_KEY				45
# define K_1					49
# define K_2					50
# define K_3					51
# define K_4					52
# define K_5					53
# define K_6					54
# define W_KEY					119
# define S_KEY					115
# define A_KEY					97
# define D_KEY					100
# define E_KEY					101
# define I_KEY					105
# define L_KEY					108
# define Q_KEY					113
# define R_KEY					114
# define LEFT_K					65361
# define RIGHT_K				65363
# define UP_K					65362
# define DOWN_K					65364

// Color
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"
# define BLACK "\033[1;30m"
# define BL "\033[94m"
# define DEF "\033[0m"

#endif
