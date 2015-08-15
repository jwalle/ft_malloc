#include "ft_malloc.h"





void	*ft_realloc(void *ptr, size_t size)
{
	void	**ptr_head;
	void	*tmp;
	int		size_mem;

	if (!size && ptr)
		return (get_malloc(16));
	if (!ptr)
		return(get_malloc(size));
	ptr_head = (ptr - 16 * 8);
	size_mem = get_mem_size(ptr_head);
	if (get_mem_size(*ptr_head))
	{
		tmp = mmap(0, size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_memcpy(tmp, ptr, size_mem);
		ft_bzero(ptr, size);
		ptr = get_malloc(size);
		ft_memcpy(ptr, tmp, size_mem);
		munmap(tmp, size + 1);
		return (ptr);
	}
	else
	{
		tmp = get_malloc(size);
		ft_memcpy(tmp, ptr, size);
		free_tiny(ptr);
		return (tmp);
	}
	return (NULL);
}
