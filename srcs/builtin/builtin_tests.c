#include "minishell.h"

//	CD
// int	main(int argc, char **argv, char **envp)
// {
// 	int	res;

// 	if (argc == 1)
// 		return (1);
// 	res = ft_cd(argv + 1);
// 	ft_putnbr_fd(res, 1);
// 	ft_putendl_fd("", 1);
// 	execute_command("pwd", envp);
// 	return (0);
// }

// PWD
// int	main(int argc, char **argv)
// {
// 	int	res;

// 	(void)argc;
// 	if (ft_strncmp(argv[1], "pwd", 4) != 0)
// 		return (1);
// 	res = ft_pwd(argv + 1);
// 	ft_cd(ft_split("cd srcs", ' '));
// 	res = ft_pwd(argv + 1);
// 	printf("%d\n", res);
// }

// ECHO
// int	main(int argc, char *argv[])
// {
// 	int	res;

// 	(void)argc;
// 	if (ft_strncmp(argv[1], "echo", 4) != 0)
// 		return (1);
// 	res = ft_echo(argv + 1);
// 	printf("%d\n", res);
// 	return (0);
// }

// ENV
// int	main(int argc, char *argv[], char **envp)
// {
// 	t_list	*env;

// 	(void)argc;
// 	env = init_env(envp);
// 	if (ft_strncmp(argv[1], "env", 4) != 0)
// 		return (1);
// 	ft_env(argv + 1, env);
// 	ft_lstclear(&env, free);
// 	return (0);
// }

// EXPORT VE UNSERT
// void	f(char *content)
// {
// 	printf("%s\n", content);
// }

// int	main(int argc, char const *argv[], char **envp)
// {
// 	t_list	*env;

// 	(void)argc;
// 	(void)argv;
// 	env = init_env(envp);
// 	ft_lstiter(env, (void *)f);
// 	ft_export(&env, "mail=ertu.pakdamar@gmail.com");
// 	ft_lstclear(&env, free);
// 	return (0);
// }
