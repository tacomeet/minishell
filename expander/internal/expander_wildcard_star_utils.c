#include "expander_internal.h"

char	*remove_multi_stars(char *data)
{
	size_t	i;
	size_t	j;
	int		status;

	i = 0;
	status = OUTSIDE;
	while (data[i])
	{
		status = quotation_status(data[i], status);
		if (status == OUTSIDE && data[i] == '*')
		{
			j = i;
			while (data[j] == '*')
				j++;
			ft_memmove(&data[i + 1], &data[j], ft_strlen(&data[j]) + 1);
		}
		i++;
	}
	return (data);
}

bool	contain_expandable_star(char *data, size_t *pre_len)
{
	size_t	i;
	int		status;

	i = 0;
	status = OUTSIDE;
	while (data[i])
	{
		status = quotation_status(data[i], status);
		if (data[i] == '*' && status == OUTSIDE)
		{
			*pre_len = i;
			return (true);
		}
		i++;
	}
	return (false);
}
