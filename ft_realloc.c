/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 20:02:44 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/15 20:02:51 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


void	*smaller_realloc(int size, t_header	*header, void *ptr)
{
	ptr = get_malloc(size);
	ft_memcpy(ptr, (void *)header + 1, size);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_header	*header;
	t_page		*page;
	void		*tmp;

	header = (t_header *)ptr - 1;
	printf(" HEADER size = %i\n", header->size);
	page = find_ptr_in_page(ptr);

	if (page->type == LARGE)
	{
		printf("LARGE\n");
		// get_malloc()
	}
	if (header->next == NULL && (page->size + (int)size + 16) >
		get_max_size(page->type, size))
	{
		header->size = (int)size;
		return (ptr);
	}
	else
	{
		tmp = get_malloc(size);
		return (ft_memcpy(tmp, ptr, header->size));
	}

	return (NULL);
}


/*
void	*realloc(void *ptr, size_t size)
{
	t_header	*header;
	void		*tmp;
	int			size_mem;

	if (!size && ptr)
		return (ptr = get_malloc(16));
	if (!ptr)
		return (get_malloc(size));
	header = (t_header *)ptr - 1;
	size_mem = header->size;
	if ((int)size == size_mem)
		return (ptr);
	if ((int)size < size_mem)
		return (ptr = smaller_realloc((int)size, header, ptr));
	else if (header)
	{
		tmp = get_malloc(size);
		ft_memcpy(tmp, ptr, size_mem);
		ft_bzero(ptr, size);
		ptr = ft_memcpy(ptr, tmp, size_mem);
		return (ptr);
	}
	else
		return (ft_memcpy(get_malloc(size), ptr, size));
	return (ptr);
}

*/