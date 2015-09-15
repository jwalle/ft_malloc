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
//# include <stdio.h> // PRINTF A RETIRER
# include <errno.h>
# include <time.h>
# include <pthread.h>

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define TINY 84
# define SMALL 83
# define LARGE 76
# define M (size_t)1000
# define PAGE_SIZE getpagesize()

# define FLAGS_PROT PROT_READ | PROT_WRITE
# define FLAGS_MAP MAP_ANON | MAP_PRIVATE
# define FLAGS FLAGS_PROT ,FLAGS_MAP, -1, 0

# define TINY_SIZE	(size_t)(PAGE_SIZE)
# define SMALL_SIZE	(size_t)(PAGE_SIZE * 20)

# define TINY_SIZE_MAX TINY_SIZE * 101
# define SMALL_SIZE_MAX SMALL_SIZE * 101

typedef struct			s_page
{
	size_t				size;
	int					full;
	void				*start;
	char				type;
	void				*next;
}						t_page;

typedef struct			s_header
{
	size_t				size;
	int					free;
	time_t				time;
	void				*next;
}						t_header;

typedef struct			s_env
{
	t_page				*page;
	int					set;
}						t_env;

extern t_env			g_env;

void					set_header(size_t size, t_header *header, void *next);
void					print_stuff_two(void *ptr, size_t size, time_t time);
void					print_time(time_t time);
void					print_mem(void *ptr, size_t size);
void					get_limit();
t_page					*page_push(t_page *first, size_t size);
void					*ft_malloc(size_t size);
void					ft_atoi_hex(void *ptr);
void					show_alloc_mem(void);
void					*get_malloc(size_t size);
t_page					*tiny_init(void);
void					free(void *ptr);
void					*get_next(void *ptr);
void					*get_ptr(void *ptr);
void					*find_last(void *ptr, size_t size);
void					free_tiny(void *ptr);
void					*realloc(void *ptr, size_t size);
size_t					get_max_size(char type, size_t size);
void					print_error(char *str);
char					ft_get_type(size_t size);
t_page					*find_ptr_in_page(t_header *header);

#endif
