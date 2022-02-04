#include <stdlib.h>

static void	ft_setcounts(const char *s, char c, size_t *nbytes, size_t *nwords)
{
	if (*s == c || *s == '\0')
	{
		*nbytes = 0;
		*nwords = 0;
		if (*s == '\0')
			return ;
	}
	else
	{	
		*nbytes = 1;
		*nwords = 1;
	}
	while (*(++s))
	{
		if (*s != c)
		{
			++(*nbytes);
			if (*(s - 1) == c)
				++(*nwords);
		}
	}
	*nbytes += *nwords;
}

static void	ft_split_helper(char **pdest, char *dest, const char *src, char c)
{
	while (*src && *src == c)
		++src;
	if (*src == '\0')
	{
		*pdest = NULL;
		return ;
	}
	*pdest = dest;
	while (*src && *src != c)
		*(dest++) = *(src++);
	*(dest++) = '\0';
	ft_split_helper(pdest + 1, dest, src, c);
}

char	**ft_strsplit(const char *s, char c, int *ntab)
{
	size_t	nbytes;
	size_t	nwords;
	char	*buff;
	char	**tab;

	ft_setcounts(s, c, &nbytes, &nwords);
	*ntab = nwords + 1;
	tab = malloc(sizeof(char *) * (nwords + 1));
	if (!tab)
		return (NULL);
	if (nwords != 0)
	{
		buff = malloc(sizeof(char) * nbytes);
		if (!buff)
		{
			free(tab);
			return (NULL);
		}
	}
	ft_split_helper(tab, buff, s, c);
	return (tab);
}	
