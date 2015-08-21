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

	if (g_env.page)
	{
		find = g_env.page;
		while (find->next)
		{
			if (find == page)
			{
				g_env.page = page->next;
				munmap(page->start, get_max_size(page->type, page->size) + 1);
				munmap(page, sizeof(t_page));
				page->start = NULL;
				page = NULL;
				return ;
			}
			else if (find->next == page)
			{
				find->next = page->next;
				munmap(page->start, get_max_size(page->type, page->size) + 1);
				munmap(page, sizeof(t_page));
				page->start = NULL;
				page = NULL;
				return ;
			}
			find = find->next;
		}
	}
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
	char	*needle;
	t_page	*page;

	if (g_env.page)
	{
		page = g_env.page;
		while (page)
		{
			needle = page->start;
			if (needle + 16 == ptr)
				return(page);
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
	page = find_ptr_in_page(header);
	if (page_is_empty(page))
		free_page(page);
}
