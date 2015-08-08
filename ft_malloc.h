/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:39:17 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/08 10:55:02 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
#include <stdlib.h>
#include <sys/resource.h>
#include "libft.h"
#include <stdio.h> // PRINTF A RETIRER

# define TINY 1
# define SMALL 10
# define LARGE 100

#define TINY_SIZE	512


typedef struct			s_tiny
{
	size_t				tiny_size;
	void				*tiny_start;
	struct s_tiny		*next;
}						t_tiny;

typedef struct			s_env
{
	t_tiny				*tiny;
	int					plop;
	char				*jkaptekedal;
}						t_env;

extern t_env			g_env;

void	*ft_malloc(size_t size);
void	ft_atoi_hex(void *ptr);
void	show_alloc_mem(void);

#endif
