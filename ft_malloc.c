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

	limit = getrlimit(RLIMIT_AS, &rlp);
	printf("limit = %d\n", limit);
	printf("current max is = %llu\n", rlp.rlim_cur);
	printf("curren hard is = %llu\n", rlp.rlim_max);
	printf("pagesize = %d\n", PAGE_SIZE);
}

void	init_global(void)
{
	g_env.tiny = NULL;
	g_env.plop = 42;
	//g_env.tiny->start = NULL;
	//g_env.tiny->next = NULL;
	g_env.jkaptekedal = "plop\n";
}

void	*get_tiny(size_t size)
{
	printf("TINY\n");
	if (!g_env.tiny)
		tiny_init();
	get_limit();
	printf("size = %zu, genv size = %zu\n", size, g_env.tiny->size);

	while (g_env.tiny->next != NULL)
		g_env.tiny = g_env.tiny->next;

	while(g_env.tiny->block != NULL)
		g_env.tiny->block = g_env.tiny->block->next;

	if (!g_env.tiny->start)
		g_env.tiny->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);

	if ((g_env.tiny->size + size < TINY_SIZE * 100))
	{
		g_env.tiny->next =
	}
	g_env.tiny->block = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
	g_env.tiny->block->size = size;
	g_env.tiny->block->start = g_env.tiny->start + g_env.tiny->size;
	g_env.tiny->size += size;
	g_env.tiny->block->next = NULL;
	printf("page start = %p ; block start = %p\n", g_env.tiny->start, g_env.tiny->block->start);
	return(g_env.tiny->block->start);

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

void	tiny_page_init(void)
{

}

void	tiny_init(void)
{
	t_tiny	*tiny;

	tiny = NULL;
	tiny = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
	//tiny->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);
	tiny->size = 0;
	tiny->next = NULL;
	g_env.tiny = tiny;
}

void	*ft_malloc(size_t size)
{
	//get_limit();
	if( g_env.plop != 42)
		init_global();
	//tiny_init(TINY_SIZE, g_env.tiny);
	//printf("test tiny = %zu\n", g_env.tiny->size);
	ft_putstr(g_env.jkaptekedal);
	if (size < TINY_SIZE)
		return (get_tiny(size));
	if (size >= SMALL_SIZE && size < LARGE_SIZE)
		return (get_small(size));
	if (size >= LARGE)
		return (get_large(size));
	printf("NULL\n");
	return (NULL);
}
