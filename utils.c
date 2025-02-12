#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	if (src_len + 1 < size)
		len = src_len;
	else
		len = size - 1;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = 0;
	return (src_len);
}

char	*ft_strdup(const char *str)
{
	char	*duplicate;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	duplicate = (char *)malloc(sizeof(char) * (len + 1));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, str, len + 1);
	return (duplicate);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if ((s_len - start) < len)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	while (i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff != 0 || !s1[i] || !s2[i])
			return (diff);
		i++;
	}
	if (i == n)
		return (0);
	return (diff);
}
