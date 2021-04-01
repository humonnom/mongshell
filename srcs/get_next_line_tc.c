#include "../incs/minishell.h"

static char	*get_str_by_inst_arr(long inst_arr[], int inst_arr_size)
{
	int		inst_arr_idx;
	char	*ret;
	char	*tmp_ret;
	int		tmp_ret_idx;

	tmp_ret = (char *)malloc(sizeof(char) * (inst_arr_size + 1));
	tmp_ret[inst_arr_size] = '\0';

	tmp_ret_idx = 0;
	inst_arr_idx = -1;
	while (++inst_arr_idx < inst_arr_size)
	{
		if (inst_arr[inst_arr_idx] == KEY_BACKSPACE)
		{
			tmp_ret_idx = calc_max(tmp_ret_idx - 1, 0);
			tmp_ret[tmp_ret_idx] = '\0';
		}
		else if (inst_arr[inst_arr_idx] == KEY_LEFT_ARROW)
			continue ;
		else if (inst_arr[inst_arr_idx] == KEY_RIGHT_ARROW)
			continue ;
		else
			tmp_ret[tmp_ret_idx++] = (char)inst_arr[inst_arr_idx];
	}
	ret = ft_substr(tmp_ret, 0, tmp_ret_idx);
	free(tmp_ret);
	printf("\n\nret: %s\n", ret);
	return (ret);
}

static int	handle_up_arrow(t_tc tc, long inst_arr[], int inst_arr_size)
{
	int		idx;
	char	*str_out;

	ft_cursor_clr_line_all(tc.tc_str, tc.cursor.row);
	ft_cursor_mv_head(tc.tc_str, tc.cursor.row);

	str_out = "NEW LINE";
	
	char	*prompt = ">> ";
	write(1, prompt, ft_strlen(prompt));
	ft_putstr_fd(str_out, 1);
	idx = -1;
	while (++idx < ft_strlen(str_out))
	{
		inst_arr[idx] = (long)str_out[idx];
	}
	return (idx);
}

char	get_inst_arr_in_loop()
{
	long	c;
	long	inst_arr[BUFFER_SIZE];
	int		inst_arr_idx;

	inst_arr_idx = -1;
	while ((read(STDIN_FILENO, &c, sizeof(c)) > 0) && (c != '\n'))
	{
		if (c <= KEY_LEFT_ARROW)
			inst_arr[++inst_arr_idx] = c;
		get_cursor_pos(&tc.cursor.col, &tc.cursor.row);
		if (ft_isprint(c))
		{
			ft_putchar_fd(c, 1);
			++buf_len;
		}
		else if (c == KEY_LEFT_ARROW)
			ft_cursor_mv_left(tc.cursor.col, prompt.size);
		else if (c == KEY_RIGHT_ARROW)
			ft_cursor_mv_right(tc.cursor.col, prompt.size + buf_len);
		else if (c == KEY_UP_ARROW)
			inst_arr_idx = handle_up_arrow(tc, inst_arr, inst_arr_idx) - 1;
		else if (c == KEY_BACKSPACE)
		{
			ft_cursor_clr_line_end(tc.tc_str, tc.cursor.col, prompt.size);
			--buf_len;
		}
		c = 0;
	}

}


char	*get_next_line_tc(t_info *info, t_prompt prompt)
{
	t_tc	tc;
	char	*ret;
	int		buf_len;

	tc = info->tc;
	c = 0;
	get_cursor_pos(&tc.cursor.col, &tc.cursor.row);
	ft_cursor_mv_head(tc.tc_str, tc.cursor.row);
	write(1, prompt.data, prompt.size);
	buf_len = 0;
	ft_memset(inst_arr, 0, BUFFER_SIZE);

	// new function
	ret = get_str_by_inst_arr(inst_arr, inst_arr_idx + 1);
	return (ret);	
}
