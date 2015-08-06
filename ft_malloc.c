/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 11:50:30 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/06 18:53:59 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include "libft/libft.h"
#include "ft_malloc.h"

void	get_limit(void)
{
	struct rlimit	rlp;
	int				limit;
	char			*str;


	str = strdup("plop\n");
	ft_putstr("my adress = ");

	ft_atoi_hex((void*)&str, 0);
	ft_putstr("\n");
	printf("printf adress = %p\n", (void*)&str);
	limit = getrlimit(RLIMIT_FSIZE, &rlp);
	printf("limit = %d\n", limit);
	printf("current max is = %d\n", (int)rlp.rlim_cur);
	printf("current hard is = %d\n", (int)rlp.rlim_max);
	printf("pagesize = %d\n", getpagesize());
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

void	*ft_malloc(size_t size)
{
	get_limit();
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
