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

int		free_page(t_page *page)
{
	t_page	*find;

	if ((find = g_env.page))
	{
		if (page == g_env.page)
		{
			g_env.page = page->next;
			return (munmap((void *)page, page->size + 40));
		}
		else
		{
			while (find->next)
			{
				if (find->next == page)
				{
					find->next = page->next;
					return (munmap((void *)page, page->size + 40));
				}
				find = find->next;
			}
		}
	}
	return (1);
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

// t_page	*find_ptr_in_page(t_header *header)
// {
// 	t_header	*needle;
// 	t_page		*page;

// 	if ((page = g_env.page))
// 	{
// 		while (page)
// 		{
// 			needle = page->start;
// 			while (needle)
// 			{
// 				if (needle == header)
// 				{
// 					printf("2\n");
// 					return (page);
// 				}
// 				needle = needle->next;
// 			}
// 			page = page->next;
// 		}
// 	}
// 	return (NULL);
// }

t_page	*find_ptr_in_page(void *ptr)
{
	t_page		*page;

	if ((page = g_env.page))
	{
		while (page)
		{
			if (ptr > (void *)page->start && ptr < (void *)page->start + page->size)
			{
				//printf("2\n");
				return (page);
			}
			page = page->next;
		}
	}
	return (NULL);
}

t_header	*find_header(void *ptr)
{
	t_page		*page;
	t_header	*needle;

	if ((page = g_env.page))
	{
		while (page)
		{
			needle = page->start;

			while (needle)
			{
				if ((needle = ptr - sizeof(t_header)) != NULL)
				{
					//printf("header size = %zu\n", needle->size);
					return (needle);
				}
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
		//print_error("This is not a pointer");
		return ;
	//header = (t_header*)ptr - 1;

	if ((header = find_header(ptr)) == NULL)
		//print_error("can't free a pointer that wasn't malloced");
		return ;
	if ((page = find_ptr_in_page(header)) == NULL)
		return ;
	pthread_mutex_lock(&g_lock);
	if (page->type == LARGE)
	{
		if (free_page(page) != 0)
			print_error("free error");
		page = NULL;
	}
	header->free = 1;
	ptr = NULL;
	pthread_mutex_unlock(&g_lock);
}
