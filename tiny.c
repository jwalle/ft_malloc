/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:21:41 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 21:51:02 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


int		get_max_size(char type)
{
	if (type == TINY)
		return (TINY_SIZE_MAX);
	if (type == SMALL)
		return (SMALL_SIZE_MAX);
	if (type == LARGE)
		return (LARGE_SIZE_MAX);
	return (0);
}

void	print_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

t_page	*page_push(t_page *first, char type)
{
	t_page	*tmp;
	
	//printf("NEW PAGE\n");
	if (!first)
	{
		first = mmap(0, sizeof(t_page) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->start = (void *)mmap(0, get_max_size(type) * 16 , FLAGS_PROT, FLAGS_MAP , -1, 0);
		if (first->start == MAP_FAILED)
			print_error("MAPPING FAILED");
		ft_bzero(first->start, TINY_SIZE_MAX * 16);
		first->size = 0;
		first->type = type;
		first->next = NULL;
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, sizeof(t_page) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		tmp->next->start = (void *)mmap(0, get_max_size(type) * 16 , FLAGS_PROT, FLAGS_MAP , -1, 0);
		if (tmp->next->start == MAP_FAILED)
			print_error("MAPPING FAILED");
		ft_bzero(tmp->next->start, TINY_SIZE_MAX * 16);
		tmp->next->size = 0;
		tmp->next->type = type;
		tmp->next->next = NULL;
	}
	return (first);
}
/*
void	**find_next_not_free(void **ptr_head)
{
	while (get_mem_size(ptr_head) && (int)(ptr_head + 12)[0] == 1)
		ptr_head = *ptr_head;
	return (ptr_head);
}

void	**find_previous(void **ptr_head)
{
	void	**previous;
}

void	**find_last_not_free(void **ptr_head)
{

}*/

void	*ft_realloc(void *ptr, size_t size)
{
	void	**ptr_head;
	void	*tmp;
	int		size_mem;

	if (!size && ptr)
		return (get_malloc(16));
	if (!ptr)
		return(get_malloc(size));
	ptr_head = (ptr - 16 * 8);
	size_mem = get_mem_size(ptr_head);

	if (get_mem_size(*ptr_head))
	{
		tmp = mmap(0, size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_memcpy(tmp, ptr, size_mem);
		ft_bzero(ptr, size);
		ptr = get_malloc(size);
		ft_memcpy(ptr, tmp, size_mem);
		munmap(tmp, size + 1);
		
		return (ptr);
	}
	else
	{
		tmp = get_malloc(size);
		ft_memcpy(tmp, ptr, size);
		free_tiny(ptr);
		return (tmp);
	}
	return (NULL);
}

void	free_tiny(void *ptr)
{
	void	**ptr_head;
	int		size;
	int		*free_mem;

	ptr_head = (ptr - 16 * 8);
	size = get_mem_size((ptr_head));
	free_mem = (int *)(ptr_head + 12);
	free_mem[0] = 1;
	ft_bzero(ptr, size);
	munmap(ptr, size);
	ptr = NULL;
}

int		get_mem_size(void **ptr)
{
	int		*size_mem;

	size_mem = (int *)(ptr + 8);
	if (size_mem)
		return (size_mem[0]);
	return (0);
}

void	*block_init(void **ptr, int size)
{
	int		*size_mem;
	int		*free_mem;
	void	**ptr_mem;

	while (get_mem_size(ptr))
		ptr = *ptr;
	ptr_mem = (void *)ptr;
	ptr_mem[0] = (void *)(ptr + size + 16);
	size_mem = (int *)(ptr + 8);
	size_mem[0] = size;
	free_mem = (int *)(ptr + 12);
	free_mem[0] = 0;
	return ((void *)(ptr + 16));
}

char	ft_get_type(int size)
{
	if (size < TINY_SIZE)
		return ('T');
	if (size >= TINY_SIZE && size < SMALL_SIZE)
		return ('S');
	if (size >= SMALL_SIZE)
		return ('L');
	return ('W');
}

void	*get_malloc(int size)
{
	t_page	*page;
	void	*ptr;
	char	type;
	static int		i = 0;

	type = ft_get_type(size);
	if (!g_env.page)
		g_env.page = page_push(g_env.page, type);
	page = g_env.page;
	while (page->next != NULL && page->type != type)
		page = page->next;
	if ((page->size + size + 16 > (TINY_SIZE_MAX)))
	{
		g_env.page = page_push(g_env.page, type);
		page = page->next;
	}
	ptr = block_init(page->start, size);
	page->size += size + 16;
	i += size + 16;
	printf("total size = %i\n", i);
	return (ptr);
}
