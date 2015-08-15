/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 22:42:32 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/15 22:51:32 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


int main(int ac, char **av)
{
	char 	*str;

	(void)ac;
	str = malloc(atoi(av[2]));

	ft_strcpy(str, "COUCOU");
	printf("%s\n", str);
	return (0);
}
