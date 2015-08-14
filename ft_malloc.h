/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:39:17 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 22:14:27 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include "libft.h"
#include <stdio.h> // PRINTF A RETIRER

# define TINY 84
# define SMALL 83
# define LARGE 76
# define PAGE_SIZE getpagesize()

#define FLAGS_PROT PROT_READ | PROT_WRITE
#define FLAGS_MAP MAP_ANON | MAP_PRIVATE

#define TINY_SIZE	512
#define SMALL_SIZE	10240
#define LARGE_SIZE	200000

#define TINY_SIZE_MAX TINY_SIZE * 16 * PAGE_SIZE
#define SMALL_SIZE_MAX SMALL_SIZE * 16 * PAGE_SIZE
#define LARGE_SIZE_MAX LARGE_SIZE * 16 * PAGE_SIZE

typedef struct			s_page
{
	int					size;
	void				**start;
	char				type;
	struct s_page		*next;
}						t_page;

typedef struct			s_env
{
	t_page				*page;
	int					plop;
	char				*jkaptekedal;
	long long unsigned	total;
}						t_env;

extern t_env			g_env;

void					get_limit();
void					*ft_malloc(size_t size);
void					ft_atoi_hex(void *ptr);
void					show_alloc_mem(void);
void					*get_malloc(int size);
t_page					*tiny_init(void);
void					free_tiny(void *ptr);
void					*get_next(void *ptr);
int						get_mem_size(void **ptr);
void					*get_ptr(void *ptr);
void					*find_last(void *ptr, int size);
void					free_tiny(void *ptr);
void					*ft_realloc(void *ptr, size_t size);
#endif
