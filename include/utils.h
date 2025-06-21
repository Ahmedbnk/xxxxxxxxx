#ifndef UTILS_H
# define UTILS_H

// String utilities
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s, int flag);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isalnum(int c);

// Character utilities
int		is_space(char c);
int		is_quote(char c);
int		is_all_spaces(const char *str);

// Comparison utilities
int		are_they_equal(const char *str1, const char *str2);
int		is_protected(t_shell_control_block *sh, char *str, int index);

// List utilities
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *list);

// Memory management
void	*ft_malloc(size_t size, int flag);
t_list	**get_garbage_pointer(int flag);
void	free_memory(t_list **lst);
t_list	*garbage_collection_lstnew(void *content, int flag);

// Input/Output utilities
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
int		print_error(const char *str, ...);

// Random utilities
char	*generate_random_name(void);
char	*custom_join(char const *s1, char const *s2);

#endif 