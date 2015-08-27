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
# include <stdlib.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include "libft.h"
# include <stdio.h> // PRINTF A RETIRER
# include <errno.h>

# define TINY 84
# define SMALL 83
# define LARGE 76
# define PAGE_SIZE getpagesize()

# define FLAGS_PROT PROT_READ | PROT_WRITE
# define FLAGS_MAP MAP_ANON | MAP_PRIVATE
# define FLAGS FLAGS_PROT ,FLAGS_MAP, -1, 0

# define TINY_SIZE	4096
# define SMALL_SIZE	20480

# define TINY_SIZE_MAX 409600
# define SMALL_SIZE_MAX 4096000

typedef struct			s_page
{
	int					size;
	int					full;
	void				*start;
	char				type;
	void				*next;
}						t_page;

typedef struct			s_header
{
	int					size;
	int					free;
	void				*next;
}						t_header;

typedef struct			s_env
{
	t_page				*page;
	int					set;
}						t_env;

extern t_env			g_env;

void					get_limit();
t_page					*page_push(t_page *first, int size);
void					*ft_malloc(size_t size);
void					ft_atoi_hex(void *ptr);
void					show_alloc_mem(void);
void					*get_malloc(int size);
t_page					*tiny_init(void);
void					free(void *ptr);
void					*get_next(void *ptr);
void					*get_ptr(void *ptr);
void					*find_last(void *ptr, int size);
void					free_tiny(void *ptr);
void					*realloc(void *ptr, size_t size);
int						get_max_size(char type, int size);
void					print_error(char *str);
char					ft_get_type(int size);
t_page					*find_ptr_in_page(void *ptr);


#endif
