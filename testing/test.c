/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 14:37:59 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 16:06:55 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	void	**mem;
	void	**first;
	void	**ptr_mem;
	char	*str1;
	char	*str2;
	int		*size_mem;
	int		*free_mem;

	str1 = "abcdefghij";
	str2 = "kmnopqrstu";
	first = malloc(53);
	first[53] = 0;

	mem = first;

	ptr_mem = (void *)mem;
	ptr_mem[0] = (void *)(mem + 16 + 10);
	size_mem = (int *)(mem + 8);
	size_mem[0] = 10;
	free_mem = (int *)(mem + 12);
	free_mem[0] = 0;
	strcpy((char *)(mem + 16), str1);

	printf("first copy\n");
	mem = (void *)(mem + 16 + 10);

	ptr_mem = ptr_mem + 26;
	ptr_mem = (void *)mem;
	ptr_mem[0] = (void *)(mem + 16 + 10);
	size_mem = (int *)(mem + 8);
	size_mem[0] = 10;
	free_mem = (int *)(mem + 12);
	free_mem[0] = 0;
	strcpy((char *)(mem + 16), str2);

	printf("second copy\n");
	mem = (void *)(mem - 16 - 10);

	printf("pointeur = %p, size = %i, free = %d, first str = %s|\n",(void *)(mem)[0],  (int)(mem + 8)[0], (int)(mem + 12)[0], (char *)(mem + 16));
	
	mem = (void *)(mem + 16 + 10);

	printf("pointeur = %p, size = %i, free = %d, first str = %s|\n",(void *)(mem)[0],  (int)(mem + 8)[0], (int)(mem + 12)[0], (char *)(mem + 16));
	
	return (0);
}






	

