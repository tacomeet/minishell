#include "expander.h"

size_t	var_len(const char *str)
{
	size_t	len;

	len = 0;
	while (!ft_strchr(EXPANSION_DELIMITER, str[len]))
		len++;
	return (len);
}

char	*search_env_vars(char *data, size_t var_start, t_env_var *vars)
{
	const char		*start = &data[var_start];
	const size_t	len = var_len(start);

	while (vars && ft_strncmp(vars->key, start, len))
		vars = vars->next;
	if (vars)
		return (vars->value);
		// todo: 環境変数が見つからなかった場合の処理
	else
		return (NULL);
}

char	*str_insert(char *data, size_t replace_start, char *env_value, size_t env_value_len)
{
	const size_t	origin_len = ft_strlen(data);
	const size_t	env_var_len = var_len(&data[replace_start + 1]) + 1;
	const size_t	expansion_len = origin_len - env_var_len + env_value_len;
	char			*prev_data;
	char			*expanded_str;

	prev_data = data;
	expanded_str = (char *)malloc(sizeof(char) * (expansion_len + 1));
	if (!expanded_str)
		return (NULL);
	ft_memmove(&expanded_str[0], &data[0], replace_start);
	ft_memmove(&expanded_str[replace_start], env_value, env_value_len);
	ft_memmove(&expanded_str[replace_start + env_value_len],
		&data[replace_start + env_var_len], origin_len - replace_start - env_var_len);
	data = expanded_str;
	free(prev_data);
	expanded_str[expansion_len] = '\0';
	return (data);
}
