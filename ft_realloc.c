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

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = get_malloc(count * size);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	*smaller_realloc(size_t size, void *ptr)
{
	void	*tmp;

	tmp = get_malloc(size);
	ptr = ft_memcpy(tmp, ptr, size);
	return (ptr);
}

void	*bigger_realloc(size_t size, t_header *header, t_page *page, void *ptr)
{
	void	*tmp;

	if (page->type != LARGE)
	{
		if (header->next == NULL)
		{
			if ((page->size + size) > get_max_size(page->type, size))
			{
				header->size = size;
				return (ptr);
			}
		}
	}
	tmp = get_malloc(size);
	ptr = ft_memcpy(tmp, ptr, header->size);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_header	*header;
	t_page		*page;

	if (!ptr)
		return (get_malloc(size));
	if (!size && ptr)
	{
		free(ptr);
		return (get_malloc(TINY_SIZE));
	}
	header = (t_header *)ptr - 1;
	if (!header->size)
		print_error("can't realloc this either");
	page = find_ptr_in_page(header);
	if (size > header->size)
		return (bigger_realloc(size, header, page, ptr));
	else if (size < header->size)
		return (smaller_realloc(size, ptr));
	else
		return (ptr);
	print_error("realloc error");
	return (NULL);
}
