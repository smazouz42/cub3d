#include"cub3d.h"
char	*ft_strchr(const char *s, int c)
{
	while (*s || c == '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
size_t  ft_strlen(const char *str)
{
    int len;

    len = 0;
    while(str[len])
        len++;
    return(len);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	count;

	res = 0;
	i = 0;
	count = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			count = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (count == -1)
		return (-res);
	else
		return (res);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	s;
	unsigned int	i;
	char			*dst;

	i = 0;
	s = 0;
	while (s1[s] != '\0')
		s++;
	dst = (char *)malloc((s + 1) * sizeof(*dst));
	if (dst == 0)
		return (NULL);
	while (i < s)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dst;
	unsigned int	len;
	unsigned int	j;
	unsigned int	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = -1;
	len = (ft_strlen(s1)) + (ft_strlen(s2));
	dst = (char *)malloc((len + 1) * sizeof(*dst));
	if (dst == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[++j])
	{
		dst[i] = s2[j];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
char *map_read(int fd)
{
    if(fd < 0)
        return(NULL);
    char line[1000000] = "";
    char buf[2] = "";
    int i = 0;
    int n = 0;
    while((n = read(fd,buf,1)) > 0)
    {
        buf[n] = '\0';
        line[i] = buf[0];
        if(buf[0] == '\n')
        {
            line[i + 1] = '\0';
            return(ft_strdup(line));
        }
        i++;
    }
    if(n < 0)
        return(NULL);
    line[i] = '\0';
    if(line[0] == '\0')
        return(NULL);
    return(ft_strdup(line));
}
int is_color(char *str)
{
    int i = 0;
    while(str[i])
    {
        if((str[i] == 'F' || str[i] == 'C') && (i == 0 || str[i - 1] == ' '))
            return(1);
        i++;
    }
    return(0);
}
int is_wall(char *str)
{
    int i = 0;
    while(i < ft_strlen(str) - 1)
    {
        if((str[i] == 'N' && str[i + 1] == 'O' || str[i] == 'S' && str[i + 1] == 'O' || str[i] == 'W' && str[i + 1] == 'E' || str[i] == 'E' && str[i + 1] == 'A') && (i == 0 || str[i - 1] == ' '))
            return(1);
        i++;
    }
    return(0);
}
int is_line(char *str)
{
    int i = 0;
    int zero = 0;
    int one = 0;
    while(i < ft_strlen(str) - 1)
    {
        if(str[i] != ' ' && str[i] != '1' && str[i] != '0')
            return(0);
        if(str[i] == '1')
            one++;
        else if(str[i] == '0')
            zero++;
        i++;
    }
    if(zero > 0 || one > 0)
        return(1);
    else 
        return(0);
}
int     is_empty(char *str)
{
    int i = 0;
    while(i < ft_strlen(str)  - 1)
    {
        if(str[i] != ' ')
            return(0);
        i++;
    }
    return(1);
}
int array_size(char **str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}
void    take_color(t_item *map_items, char *colors)
{
    char **c_table;
    char **c_first;
    char **c_second;
    int i;

    i = 0;
    c_table = ft_split(colors,'\n');
    c_first = ft_split(c_table[0],' ');
    c_second = ft_split(c_table[1],' ');
    if(c_first[0][0] == c_second[0][0])
    {
        printf("Error:\n Duplicated color row.\n");
        exit(0);
    }
    if(c_first[0][0] == 'C')
    {
        c_first = ft_split(c_first[1],',');
        c_second = ft_split(c_second[1],',');
        if(array_size(c_first) != 3 || array_size(c_second) != 3)
        {
            printf("Error:\n Flawed floor or ceiling color\n");
            exit(1);
        }
        map_items->ceiling_colors[0] =  ft_atoi(c_first[0]);
        map_items->ceiling_colors[1] =  ft_atoi(c_first[1]);
        map_items->ceiling_colors[2] =  ft_atoi(c_first[2]);
        map_items->floor_colors[0] =  ft_atoi(c_second[0]);
        map_items->floor_colors[1] =  ft_atoi(c_second[1]);
        map_items->floor_colors[2] =  ft_atoi(c_second[2]);
    }
    else
    {
        c_first = ft_split(c_first[1],',');
        c_second = ft_split(c_second[1],',');
         if(array_size(c_first) != 3 || array_size(c_second) != 3)
            printf("Error:\n Flawed floor or ceiling color\n");
        map_items->ceiling_colors[0] =  ft_atoi(c_second[0]);
        map_items->ceiling_colors[1] =  ft_atoi(c_second[1]);
        map_items->ceiling_colors[2] =  ft_atoi(c_second[2]);
        map_items->floor_colors[0] =  ft_atoi(c_first[0]);
        map_items->floor_colors[1] =  ft_atoi(c_first[1]);
        map_items->floor_colors[2] =  ft_atoi(c_first[2]);
    }
        map_items->floor_colors[3] =  '\0';
        map_items->ceiling_colors[3] =  '\0';

}
void    take_walls(t_item *map_items,char *walls)
{
    int     i = 0;
    char    **wall_array;
    char    **tmp;

    wall_array = ft_split(walls,'\n');
    while(wall_array[i])
    {
        tmp = ft_split(wall_array[i],' ');
        if(tmp[0][0] == 'N')
            map_items->NO = tmp[1];
        else if(tmp[0][0] == 'S')
            map_items->SO = tmp[1];
        else if(tmp[0][0] == 'E')
            map_items->EA = tmp[1];
        else if(tmp[0][0] == 'W')
            map_items->WE = tmp[1];
        i++;
    }
    if(!map_items->EA || !map_items->SO || !map_items->NO || !map_items->WE)
    {
        printf("ZOB\n");
        exit(1);
    }

}
void    ft_make_matrix(int fd,t_item *map_items)
{
	char	*str;
	char	*temp;
    int     M = 0;
    int     W = 0;
    int     C = 0;
    char    *map = NULL;
    char    *walls = NULL;
    char    *colors = NULL;

	str = map_read(fd);
	while (str)
	{
        if(is_color(str) == 1 && M == 0)
        {
            if(C < 2)
            {
		        if (!colors)
			    	colors = ft_strdup(str);
		        else
		        {
			    	temp = colors;
			    	colors = ft_strjoin(colors, str);
			    	free(temp);
		    	}
        	}
			else
			{
				printf("Error:\n Duplicated color row.\n");
				exit(1);
			}
			C++;
		}
        else if(is_wall(str) == 1 && M == 0)
        {
			if(W < 4)
			{
		    	if (!walls)
				    walls = ft_strdup(str);
		    	else
		    	{
				    temp = walls;
				    walls = ft_strjoin(walls, str);
				    free(temp);
		    	}
        	}
			else
			{
				printf("Error:\n Duplicated walls.\n");
				exit(1);
			}
			W++;
		}
        else if(M == 1 || is_line(str) == 1)
        {
            M = 1;
            if(str[0] == '\n' || is_empty(str) == 1)
            {
                printf("Error:\n Empty line\n");
                exit(0);
            }
             if (!map)
			    map = ft_strdup(str);
		    else
		    {
			    temp = map;
			    map = ft_strjoin(map, str);
			    free(temp);
		    }
        }
		free(str);
		str = map_read(fd);
	}
    map_items->map = ft_split(map,'\n');
    take_color(map_items,colors);
    take_walls(map_items,walls);
}
int array_size_(char **map, int *max)
{
    int i = 0;
    *max  = 0;
    while(map[i])
    {
         if((int)ft_strlen(map[i]) > *max)
            *max = (int)ft_strlen(map[i]);
        i++;
    }
    return(i);
}
char    *new_line(char *str, int max)
{
    char *ret;
    ret = (char *)malloc(max + 1);

    int  i = 0;
    while(str[i])
    {
        if(str[i] != ' ')
            ret[i] = str[i];
        else
            ret[i] = '#';
        i++;
    }
    while(i < max)
    {
        ret[i] = '#';
        i++;
    }
    ret[i] = '\0';
    return(ret);
}
char **map_clone(char **map)
{
    int size;
    int max_line;
    int i = 0;
    size = array_size_(map,&max_line);
    char **new_map = malloc((size + 1) * sizeof(char *));
    while(map[i])
    {
        new_map[i] = new_line(map[i], max_line);
        i++;
    }
    new_map[i] = NULL;
    return(new_map);
}
void    map_characters(t_item *item)
{
    int i;
    int j;
    int S = 0;
    int N = 0;
    int W = 0;
    int E = 0;
    int cout  = 0;
    i = 0;
    while(item->map[i])
    {
        j = 0;
        while(item->map[i][j])
        {
            if(item->map[i][j] != ' ' && item->map[i][j] != '1' && item->map[i][j] != '0')
            {
                if(item->map[i][j]== 'E' || item->map[i][j]== 'W' || item->map[i][j]== 'S' || item->map[i][j]== 'N')
                {
                    if(cout == 0)
                    {
                        item->player_x = i;
                        item->player_y = j;
                        cout++;
                    }
                    else
                    {
                        printf("Error:\n Too many players.\n");
                        exit(0);
                    }
                }
                else
                {
                    printf("Error:\n Undefined character.\n");
                    exit(0);
                }
            }
            j++;
        }
        i++;
    }
}
void fisrt_last_line(char *line)
{
    int i = 0;
    while(line[i])
    {
        if(line[i] !=' ' && line[i] != '1' && line[i] != '#')
        {
            printf("Error:\n Corrupted first and last wall\n");
            exit(0);
        }
        i++;
    }
}
void map_parser(t_item *item)
{
    int i = 0;
    int j = 0;
    map_characters(item);
    char **new =  map_clone(item->map);
    while(new[i])
    {
        if(i == 0 || new[i + 1] == NULL)
            fisrt_last_line(new[i]);
        else
        {
            j = 0;
            while(new[i][j])
            {
                if(new[i][j]== '0')
                {
                    if(j == 0 ||  j == ft_strlen(new[i]) - 1)
                    {
                        printf("Error:\n Unclosed walls.\n");
                        exit(0);
                    }
                    if(!ft_strchr("1NSEW0",new[i][j - 1])|| !ft_strchr("1NSEW0",new[i][j + 1]) || !ft_strchr("1NSEW0",new[i - 1][j]) || !ft_strchr("1NSEW0",new[i + 1][j]))
                    {
                        printf("Error:\n Unclosed walls.\n");
                        exit(0);
                    }
                }
                j++;
            }
        }
        i++;
    }
    
}
void    parser(void)
{
    t_item item;
    int fd = open("map",O_RDONLY);
    ft_make_matrix(fd,&item);
    map_parser(&item);
    // for(int i = 0;item.map[i];i++)
    //     printf("%s\n",item.map[i++]);
}
int main(void)
{
   parser();
}