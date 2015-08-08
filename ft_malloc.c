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
	char			*str;
	int				*tab;


	tab = malloc(sizeof(int) * 3);
	tab[0] = 12;
	tab[1] = 1;
	str = strdup("plop\n");
	ft_putstr("my char adress = ");
	ft_atoi_hex((void*)&str);
	ft_putstr("\n");
	printf("printf char adress = %p\n", (void*)&str);
	limit = getrlimit(RLIMIT_FSIZE, &rlp);
	//printf("limit = %d\n", limit);
	//printf("current max is = %d\n", (int)rlp.rlim_cur);
	//printf("current hard is = %d\n", (int)rlp.rlim_max);
	//printf("pagesize = %d\n", getpagesize());
	ft_putstr("my int  adress = ");
	ft_atoi_hex((void*)&tab);
	ft_putstr("\n");
	printf("printf int adress = %p\n", (void*)&tab);	
}

void	init_global(void)
{
	g_env.tiny = NULL;
	g_env.jkaptekedal = "plop\n";
}

void	*get_tiny(size_t size)
{
	void *ret;

	printf("TINY\n");
	ret = mmap(0, size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	get_limit();
	return (ret);	
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

void	*tiny_init(size_t size, void *ptr)
{
	t_tiny	*tiny;

	tiny = NULL;
	if (!ptr)
	{
		tiny = (t_tiny *)malloc(sizeof(tiny));
		tiny->tiny_start = get_tiny(size);
		g_env.tiny = tiny;
		tiny->tiny_size = size;
		tiny->next = NULL;
	}
	return (tiny);
}

void	*ft_malloc(size_t size)
{
	//get_limit();
	init_global();
	tiny_init(TINY_SIZE, g_env.tiny);
	printf("test tiny = %zu\n", g_env.tiny->tiny_size);
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
