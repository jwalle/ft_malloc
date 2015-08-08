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
#include <sys/mman.h>
#include "libft.h"
#include <stdio.h> // PRINTF A RETIRER

# define TINY 1
# define SMALL 10
# define LARGE 100

#define FLAGS_PROT PROT_READ | PROT_WRITE
#define FLAGS_MAP MAP_ANON | MAP_PRIVATE

#define TINY_SIZE	512
#define SMALL_SIZE	10240
#define LARGE_SIZE	200000

typedef struct			s_block
{
	size_t				size;
	void				*start;
	struct s_block		*next;
}						t_block;

typedef struct			s_tiny
{
	size_t				size;
	void				*start;
	struct s_tiny		*next;
}						t_tiny;

typedef struct			s_env
{
	t_tiny				*tiny;
	int					plop;
	char				*jkaptekedal;
	long long unsigned	total;
}						t_env;

extern t_env			g_env;

void	*ft_malloc(size_t size);
void	ft_atoi_hex(void *ptr);
void	show_alloc_mem(void);
void	tiny_init(size_t size, void *ptr);

#endif
