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
/*
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
*/

void	init_global(void)
{
	g_env.page = NULL;
	g_env.set = 42;
	g_env.mutex = 0;
}

void	*malloc(size_t size)
{
	void	*ptr;

	if (g_env.set != 42)
		init_global();
	//printf("COUCOUC JE RENTRE DANS MALLOC\n");
	//show_alloc_mem();
	while (1)
	{
		if (g_env.mutex == 0)
			break ;
	}
	g_env.mutex = 1;
	ptr = get_malloc(size);
	g_env.mutex = 0;
	return (ptr);
}
