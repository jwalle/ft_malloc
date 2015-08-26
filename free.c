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
			munmap(page->start, get_max_size(page->type, page->size) + 1);
			munmap(page, sizeof(t_page));
			//page->start = NULL;
			//page = NULL;
			return ;	
		}
		else
		{
			while (find->next)
			{
				if (find->next == page)
				{
					find->next = page->next;
					munmap(page->start, get_max_size(page->type, page->size) + 1);
					munmap(page, sizeof(t_page));
					//page->start = NULL;
					//page = NULL;
					return ;
				}
				find = find->next;
			}
		}
	}
	g_env.total_free = 0;
}

int		page_is_empty(t_page *page)
{
	t_header	*header;

	if (page)
	{
		header = page->start;
		while (header)
		{
			if (header->free == 0)
				return (0);
			header = header->next;
		}
		return (1);
	}
	return (0);
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
					return(page);
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

	header = (t_header*)ptr - 1;
	header->free = 1;
	g_env.total_free++;
	//ft_bzero(ptr, header->size);
	page = find_ptr_in_page(ptr);
	if (page_is_empty(page) && g_env.total_free > 10)
		free_page(page);
}
