/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** my_lib
*/
#include <stdarg.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#ifndef MY_LIB
    #define MY_LIB
void my_putchar(char c);
void my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
void my_unsigned_nbr(unsigned int n);
void my_positive_nbr(int nb);
int my_isalpha(int a);
int my_isnum(char *nb);
char *my_strdup(char const *src);
char *my_strcat(char *dest, char *src);
void print(const char *format, ...);
int *my_revstr(int argc, char **argv);
int printf_d(const char *format, va_list param_infos, int i, int compt);
int printf_i(const char *format, va_list param_infos, int i, int compt);
int printf_s(const char *format, va_list param_infos, int i, int compt);
int printf_c(const char *format, va_list param_infos, int i, int compt);
int printf_o(const char *format, va_list param_infos, int i, int compt);
int printf_u(const char *format, va_list param_infos, int i, int compt);
int printf_x(const char *format, va_list param_infos, int i, int compt);
int printf_xm(const char *format, va_list param_infos, int i, int compt);
int printf_f(const char *format, va_list param_infos, int i, int compt);
int printf_fm(const char *format, va_list param_infos, int i, int compt);
int printf_cross(const char *format, va_list param_infos, int i, int compt);
int printf_l(const char *format, va_list param_infos, int i, int compt);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strcpy(const char *src, char *dest);
char *my_strstr(const char *str, int c);
int my_strcmp(char const *s1, char const *s2);
int strcmp_my(char const *s1, char const *s2);
bool my_str_cmp(char *s1, char *s2);
int my_is_even(int nb);
int my_cmp(char const *s1, char const *s2);
bool my_str_cmp(char *s1, char *s2);
int my_getnbr(char const *str);
int cmp_my(char const *s1, char const *s2);
int nb_length(int n);
char **my_strtok(const char *str, char separator);
char **my_str_to_word_array(const char *str);
int str_my(char const *s1, char const *s2);
int my_char(char s1, char s2);
char *my_cat(char *destination, char *source);
char *my_realoc(char *base, char *new_size);
int my_al(int a);
void *my_malloc(void *ptr, size_t size);
void my_memset(void *ptr, void *value, size_t num);
char **string_to_word_array(char const *str);
char **my_arrndup(char **arr, int start, int end);
char *my_array_to_str(char **strings);
int my_strncmp(char const *s1, char const *s2, int n);
char **my_tok(char **array, char *line, char *delim);
int my_str_isprintable(char const *str);
void move_str(char *str);
char *my_strndup(char *src, int n);
void print_triple(char ***triple);
char *my_itoa(unsigned int nb);
int my_unsignedlen(unsigned int nb);
void move_str_end(char *str);
int my_tablen(char **array);
char **my_array_dup(char **array);
int how_many(char *str, char c);
int posinstr(char *str, char c);
char **my_array(const char *str);
char **tok_word_array(char const *str, char *delim);
char *clean_str(char *str);
int my_tripletablen(char ***array);
#endif /* !my_lib */
