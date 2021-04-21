#include "../incs/minishell.h"

static int
	get_back_slash_len(char *str, char c)
{
	int		idx;
	int		len;

	idx = -1;
	len = 0;
	while (str[++idx])
	{
		if (str[idx] == c && str[idx + 1] == '\0')
			return (-1);
		if (str[idx] == c && str[idx + 1] != '\0')
		{
			len += 3;
			idx++;
		}
		else
			len++;
	}
	return (len);
}

static int
	has_filename_as_args(char *str)
{
		if (ft_strncmp("rm", str, 2))
			return (1);
		if (ft_strncmp("cd", str, 2))
			return (1);
		if (ft_strncmp("touch", str, 5))
			return (1);
		if (ft_strncmp("mkdir", str, 5))
			return (1);
		return (0);
}

static void
	remove_back_slash_in_filename(
	char *str,
	char *ret,
	int	*idx,
	int *ret_idx)
{
	while (is_bracket(str[*idx]))
	{
		ret[*ret_idx] = str[*idx];
		++(*idx);
		++(*ret_idx);
	}
	while (str[*idx] && str[*idx] == ' ')
		++(*idx);
	while (str[*idx] && str[*idx] != ' '
			&& !is_bracket(str[*idx]))
	{
		if (str[*idx] == '\\')
			++(*idx);
		ret[(*ret_idx)] = str[(*idx)];
		++(*idx);
		++(*ret_idx);
	}
}

static void
	cvt_back_slash_to_quote(char *str, char *ret, int *idx, int *ret_idx)
{
	char	quote;

	quote = '\'';
	if (str[*(idx + 1)] == quote)
		quote = '\"';
	ret[*(ret_idx)] = quote;
	++(*ret_idx);
	++(*idx);
	ret[*(ret_idx)] = str[*(idx)];
	++(*ret_idx);
	ret[*(ret_idx)] = quote;
}

char
	*handle_back_slash(
	char *str,
	char c)
{
	char	*ret;
	char	quote;
	int		len;
	int		idx;
	int		ret_idx;

	if ((len = get_back_slash_len(str, c)) == -1)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	idx = -1;
	ret_idx = -1;
	while (str[++idx] && ++ret_idx < len)
	{
		if (is_bracket(str[idx]) || has_filename_as_args(&str[idx]))
			remove_back_slash_in_filename(str, ret, &idx, &ret_idx);		
		if (str[idx] == c)
			cvt_back_slash_to_quote(str, ret, &idx, &ret_idx);
		else
			ret[ret_idx] = str[idx];
	}
	return (ret);
}
//
//echo \"ABC -> "ABC -> handle arg
//
//echo \;abc -> ;abc -> gen_line_list
//echo \;;abc -> ; abc command not found
//
//echo \\;abc -> \ abc command not found
//echo \\\;abc -> \;abc
//
//echo \"\" 
//
//echo \"abc\" >> \"test.txt\"
//
//"abc" >> '"'test.txt'"'
//
//"test.txt"


