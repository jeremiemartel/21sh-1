#include "../../includes/jobcontrol.h"

void	redirect_to_file(char *file, mode_t mode, int stfd)
{
	int	fd;

	if (stfd)
	{
		if (access(file, F_OK) == -1)
		{
			if ((fd = open(file, O_CREAT, 0644)) < 0)
				return (ft_putendl_fd("Failure : error while creating the file", 2));
		}
		fd = open(file, O_WRONLY | mode);
		dup2(fd, 1);
	}
	else
	{
		if (access(file, F_OK) == -1)
			return (ft_putendl_fd("No such file or directory", 2));
		fd = open(file, O_RDONLY);
		dup2(fd, 0);
	}
}
