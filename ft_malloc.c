/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 11:50:30 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 22:14:25 by jwalle           ###   ########.fr       */
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
	g_env.page = NULL;
	g_env.plop = 42;
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
	 static int i = 0;
	if( g_env.plop != 42)
		init_global();
	printf("nb de malloc = %d\n", i++);
	return (get_malloc((int)size));
}
