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
	if (page)
	{
		munmap(page->start, get_maxsize(page->type) + 1);
		
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
	}
	return (1);
}

t_page	*find_ptr_in_page(void *ptr)
{
	char	*needle;

	if (g_env.page)
	{
		page = g_env.page;
		while (page)
		{
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
	page = find_ptr_in_page(ptr);
	if (page_is_empty(page))
		free_page(page);
}
