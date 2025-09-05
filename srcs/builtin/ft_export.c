//#include "../../includes/ft_executor.h"

//char *ft_get_env(t_vars *vars, char *key)
//{
//	int i = 0;
//	while (vars->envp[i])
//	{
//		if (ft_strncmp(vars->envp[i], key, ft_strlen(key)) == 0
//			&& vars->envp[i][ft_strlen(key)] == '=')
//			return vars->envp[i] + ft_strlen(key) + 1;
//		i++;
//	}
//	return NULL;
//}

//void ft_set_env(t_vars *vars, char *key, char *value)
//{
//	// Eğer varsa güncelle
//	int i = 0;
//	size_t len = ft_strlen(key);
//	while (vars->envp[i])
//	{
//		if (ft_strncmp(vars->envp[i], key, len) == 0 && vars->envp[i][len] == '=')
//		{
//			free(vars->envp[i]);
//			vars->envp[i] = ft_strjoin(key, "="); // + value
//			vars->envp[i] = ft_strjoin(vars->envp[i], value);
//			return;
//		}
//		i++;
//	}
//	// Yoksa ekle (dinamik realloc veya fixed size)
//	vars->envp = ft_realloc_add(vars->envp, ft_strjoin3(key, "=", value));
//}

//int ft_export(t_vars *vars, char **args)
//{
//	int i = 1;
//	while (args[i])
//	{
//		char *eq = strchr(args[i], '=');

//		if (eq) // VAR=value formatı
//		{
//			*eq = '\0';
//			ft_set_env(vars, args[i], eq + 1); // kendi fonksiyonunla ekle/güncelle
//		}
//		else // sadece VAR
//		{
//			char *val = ft_get_env(vars, args[i]); // kendi env dizinle bul
//			if (val)
//				printf("declare -x %s=\"%s\"\n", args[i], val);
//			else
//				printf("declare -x %s\n", args[i]);
//		}
//		i++;
//	}
//	return 0;
//}
