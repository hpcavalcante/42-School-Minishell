// int		write_error_ampersand(char *cmd)
// {
// 		cmd++;
// 		write_error_red_2_signs(cmd);
// 		return (0);
// }

// int		check_syntax(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (cmd[i + 1] != '\0')
// 	{
// 		if ((cmd[i] == '&' && cmd[i + 4] == '>') || (cmd[i] == '*' && cmd[i + 4] == '>') || (cmd[i] == '(' && cmd[i + 4] == '>'))
// 		{
// 			cmd++;
// 			write_error_red_2_signs(cmd);
// 			return (0);
// 		}
// 		else if ((cmd[i] == '&' && cmd[i + 3] == '>') || (cmd[i] == '*' && cmd[i + 4] == '>'))
// 		{
// 			cmd++;
// 			write_error_red_1_sign(cmd);
// 			return (0);
// 		}
// 		else if (cmd[i] == '&' && cmd[i + 1] == '>')
// 		{
// 			write_error_red_NL(cmd);
// 			return (0);
// 		}
// 	}
//     if ((cmd[i] == '&' || cmd[i] == ';' || cmd[i] == '\\'\
// 	||cmd[i] == '(' || cmd[i] == ')' || cmd[i] == '*'))
// 	{
// 		syntax_error(cmd[i]);
// 		return (0);
// 	}
// 	return (0);
// }