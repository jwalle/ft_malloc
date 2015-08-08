/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 11:50:30 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/08 10:57:51 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include "libft/libft.h"
#include "ft_malloc.h"

t_env		g_env;

void	get_limit(void)
{
	struct rlimit	rlp;
	int				limit;
	//char			*str;


	//str = strdup("plop\n");
	//ft_putstr("my char adress = ");
	// ft_atoi_hex((void*)&str);
	// ft_putstr("\n");
	// printf("printf char adress = %p\n", (void*)&str);
	limit = getrlimit(RLIMIT_AS, &rlp);
	printf("limit = %d\n", limit);
	printf("current max is = %d\n", (int)rlp.rlim_cur);
	printf("current hard is = %d\n", (int)rlp.rlim_max);
	printf("pagesize = %d\n", getpagesize());
}

void	init_global(void)
{
	g_env.tiny = NULL;
	g_env.jkaptekedal = "plop\n";
}

void	*get_tiny(size_t size)
{
	//void *ret;

	(void)size;
	printf("TATATATATATTATATATATTAn\n");
	if (!g_env.tiny->start)
		tiny_init(TINY_SIZE, g_env.tiny);
	//ret = mmap(0, size + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
	get_limit();
	return (g_env.tiny->start);	
}

void	*get_small(size_t size)
{
	void *ret;

	printf("SMALL\n");
	ret = mmap(0, (SMALL * size) + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	get_limit();
	return (ret);	
}

void	*get_large(size_t size)
{
	void *ret;

	printf("LARGE\n");
	ret = mmap(0, (LARGE * size + 1), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	get_limit();
	return (ret);	
}

void	tiny_init(size_t size, void *ptr)
{
	t_tiny	*tiny;

	tiny = NULL;
	if (!ptr)
	{
		printf("PLPLPLPOPLPLPLPOPLPLPLPOPLPLPLPOPLPLPLPOPLPLPLPOPL\n");
		tiny = (t_tiny *)malloc(sizeof(tiny));
		tiny = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		tiny->start = mmap(0, TINY_SIZE + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		g_env.tiny = tiny;
		tiny->size = size;
		tiny->next = NULL;
	}
}

void	*ft_malloc(size_t size)
{
	//get_limit();
	init_global();
	//tiny_init(TINY_SIZE, g_env.tiny);
	//printf("test tiny = %zu\n", g_env.tiny->size);
	ft_putstr(g_env.jkaptekedal);
	if (size < TINY)
		return (NULL);
	if (size >= TINY && size <= SMALL)
		return (get_tiny(size));
	if (size >= SMALL && size <= LARGE)
		return (get_small(size));
	if (size >= LARGE)
		return (get_large(size));
	return (NULL);
}
