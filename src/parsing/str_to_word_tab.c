/*
** str_to_word_tab.c for  in /home/mart_4/rendu/PSU_2015_myftp/src/parsing
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Wed May 11 12:59:14 2016 Thomas Martins
** Last update Sun May 15 11:20:38 2016 Thomas Martins
*/

#include "../struct.h"

int	check_word(char *str, char c)
{
  int	len;
  int	a;

  len = 1;
  a = 0;
  while (str[a++])
    {
      if (str[a] == c)
        len++;
      while (str[a] == c)
        a++;
    }
  return (len);
}

char	**clean_tab(char **tab, int size)
{
  int	i;

  i = 0;
  while (i++ < size)
    {
      if (tab[i])
	free(tab[i]);
    }
  free(tab);
  return (NULL);
}

int	str_clen(char *str, char carac)
{
  int	len;

  (void)carac;
  len = 0;
  while (str[len] != '\0')
    len++;
  return (len);
}

char	**wordtab_algo(char *s, char c, t_val *val, char **tab)
{
  while (s[val->i] != '\0' && s[val->i] != '\n')
    {
      if (s[val->i] == c || s[val->i] == '\n')
	while (s[val->i] == c)
	  val->i++;
      val->b = 0;
      if (s[val->i] == '\0' || s[val->i] == '\n')
	break ;
      if ((tab[val->a] = malloc((str_clen(s, c) + 1) * sizeof(char))) == NULL)
	return (clean_tab(tab, val->a - 1));
      while ((s[val->i] != c) && (s[val->i] != '\n') && (s[val->i] != '\0'))
	tab[val->a][val->b++] = s[val->i++];
      tab[val->a][val->b] = '\0';
      val->a++;
    }
  tab[val->a] = 0;
  return (tab);
}

char	**wordtab(char *s, char c, t_val *val)
{
  char	**tab;

  if ((tab = malloc((check_word(s, c) + 1) * sizeof(char *))) == NULL)
    return (NULL);
  init_value(val);
  if ((wordtab_algo(s, c, val, tab)) == NULL)
    return (NULL);
  return (tab);
}
