#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*rtn;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_calloc(1, sizeof(char)));
	if (len_s < (start + len))
		len = len_s - start;
	rtn = (char *)ft_calloc(len + 1, sizeof(char));
	if (!rtn)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		rtn[i] = s[start + i];
		i++;
	}
	return (rtn);
}
