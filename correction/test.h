/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchenut <lchenut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 14:30:13 by lchenut           #+#    #+#             */
/*   Updated: 2015/05/06 14:31:59 by lchenut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# define M (1024 * 1024)

void	show_alloc_mem(void);
void	show_alloc_mem_verbose(void);

#endif
