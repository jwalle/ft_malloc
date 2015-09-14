/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:17:05 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/25 16:11:02 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_malloc.h"
# include <time.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# define Mo (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int test5(void)
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}

int		test4(void)
{
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
	return (0);
}

int		test3bis(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char *)malloc(16 * Mo);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char *)malloc(16 * Mo);
	addr3 = (char *)realloc(addr1, 128 * Mo);
	addr3[127 * Mo] = 42;
	print(addr3);
	return (0);
}

int		test3(void)
{
	char *addr1;
	char *addr3;

	addr1 = (char *)malloc(16 * Mo);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128 * Mo);
	addr3[127 * Mo] = 42;
	print(addr3);
	return (0);
}

int test2(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		//addr = mmap(0, 1024, FLAGS);
		addr = (char*)malloc(1024);
		addr[0] = 42;
		//munmap(addr, 1024);
		free(addr);
		i++;
	}
	/*i = 0;
	while (i < 1024)
	{
		printf("PLPOPo\n");
		//addr = mmap(0, 1024, FLAGS);
		//munmap(addr, 1024);
		free(addr[i]);
		i++;
	}
	free(addr);*/
	return (0);
}

int test1(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}

int test0(void)
{
	int		i;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!strcmp(av[1], "test0"))
			test0();
		if (!strcmp(av[1], "test1"))
			test1();
		if (!strcmp(av[1], "test2"))
			test2();
		if (!strcmp(av[1], "test3"))
			test3();
		if (!strcmp(av[1], "test3bis"))
			test3bis();
		if (!strcmp(av[1], "test4"))
			test4();
		if (!strcmp(av[1], "test5"))
			test5();
	}
	else
	{
		char str[2048];
		int fd;

		system("./print_win.sh");
		printf("Press a key to start the test.\n");
		getchar();
		printf("test 0 : \n");
		system("/usr/bin/time -l ./test test0 2> ./test0.txt");
		fd = open("./test0.txt", O_RDONLY);
		while (read(fd, str, 2048))
			puts(str);
		//	if (strstr(str, "reclaims"))

		//dprintf(fd, "%s", str);
		//scanf("%s", str);
		
		getchar();
		printf("test 1 : \n");
		system("/usr/bin/time -l ./test test1");
		getchar();
		printf("test 2 : \n");
		system("/usr/bin/time -l ./test test2");
		getchar();
		printf("test 3 : \n");	
		system("./test test3");
		getchar();
		printf("test 3bis : \n");
		system("./test test3bis");
		getchar();
		printf("test 4 : \n");
		system("./test test4");
		getchar();
		printf("test 5 : \n");
		system("./test test5");
	}
	return (0);
}
