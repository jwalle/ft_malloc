/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 14:53:29 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/20 14:53:30 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


void	free_page(t_page *page)
{
	t_page	*find;

	find = g_env.page;
	if (g_env.page)
	{
		if (page == g_env.page)
		{
			g_env.page = page->next;
			// printf("size free = %zu\n", get_max_size(page->type, page->size) + 40);
			munmap((void *)page, get_max_size(page->type, page->size) + 40);
			page = NULL;
			return ;
		}
		else
		{
			while (find->next)
			{
				if (find->next == page)
				{
					find->next = page->next;
					munmap(page, get_max_size(page->type, page->size) + 40);
					return ;
				}
				find = find->next;
			}
		}
	}

}

int		page_is_empty(t_page *page)
{
	t_header	*header;
	int			i;

	i = 0;
	if (page)
	{
		header = page->start;
		while (header)
		{
			if (header->free == 0)
				i++;
			header = header->next;
		}
	}
	return (i);
}

t_page	*find_ptr_in_page(void *ptr)
{
	t_header	*needle;
	t_page		*page;

	if (g_env.page)
	{
		page = g_env.page;
		while (page)
		{
			needle = page->start;
			while (needle)
			{
				if (needle + 1 == ptr)
					return (page);
				needle = needle->next;
			}
			page = page->next;
		}
	}
	return (NULL);
}

void	free(void *ptr)
{
	t_header	*header;
	t_page		*page;

	if (!ptr)
		print_error("can't free this");
	header = (t_header*)ptr - 1;
	if (!header->size)
		print_error("can't free this either");
	header->free = 1;
	ft_bzero(ptr, header->size);
	page = find_ptr_in_page(ptr);
	page->size -= header->size;
	if (!page_is_empty(page))
		free_page(page);
}
