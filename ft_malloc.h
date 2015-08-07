/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:39:17 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/07 14:34:13 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
#include <stdlib.h>
#include <sys/resource.h>
#include "libft.h"
#include <stdio.h> // PRINTF A RETIRER

# define TINY 1
# define SMALL 10
# define LARGE 100

void *ft_malloc(size_t size);
void ft_atoi_hex(void *ptr);

#endif
