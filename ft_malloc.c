/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 11:50:30 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 21:21:59 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_env		g_env;

void	get_limit(void)
{
	struct rlimit	rlp;
	int				limit;

	limit = getrlimit(RLIMIT_AS, &rlp);
	printf("limit = %d\n", limit);
	printf("current max is = %d\n", (int)rlp.rlim_cur);
	printf("curren hard is = %d\n", (int)rlp.rlim_max);
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

void	*ft_malloc(size_t size)
{
	//get_limit();
	if( g_env.plop != 42)
		init_global();
	static int i = 1;

	printf("nb of malloc = %i\n", i++);
	//tiny_init(TINY_SIZE, g_env.tiny);
	//printf("test tiny = %zu\n", g_env.tiny->size);
	//ft_putstr(g_env.jkaptekedal);
	if (size < TINY_SIZE)
		return (get_tiny((int)size));
	if (size >= SMALL_SIZE && size < LARGE_SIZE)
		return (get_small(size));
	if (size >= LARGE)
		return (get_large(size));
	printf("NULL\n");
	return (NULL);
}
