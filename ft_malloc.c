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

t_env			g_env;
pthread_mutex_t	g_lock;

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
	if (pthread_mutex_init(&g_lock, NULL) != 0)
		print_error("error mutex init.");
}

void	*malloc(size_t size)
{
	void	*ptr;

	if (g_env.set != 42)
		init_global();
	//printf("COUCOUC JE RENTRE DANS MALLOC\n");
	//show_alloc_mem();
	pthread_mutex_lock(&g_lock);
	ptr = get_malloc(size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
