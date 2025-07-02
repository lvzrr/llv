#include <llv/alloc.h>
#include <llv/macros.h>
#include <llv/cstr.h>
#include <llv/ctype.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define L1_TEST 10
#define L2_TEST 500
#define L3_TEST 5000
#define L4_TEST 50000
#define L5_TEST 500000

// Helper functions for lv_strmapi and lv_striteri
char strmapi_toupper_cb(unsigned int i, char c) {
    (void)i;
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

char strmapi_add_index_cb(unsigned int i, char c) {
    return c + (char)(i % 10);
}

void striteri_toupper_cb(unsigned int i, char *c) {
    (void)i;
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 32;
}

void striteri_set_to_index_cb(unsigned int i, char *c) {
    *c = (char)('0' + (i % 10));
}

void tolower_toupper_tests() {
    size_t i = 0;
    {
        assert(lv_tolower('A') == 'a');
        assert(lv_tolower('Z') == 'z');
        assert(lv_tolower('a') == 'a');
        assert(lv_tolower('0') == '0');
        assert(lv_tolower('$') == '$');
        printf("lv_tolower passed tests: %lu\r", i++);
    }
    {
        assert(lv_toupper('a') == 'A');
        assert(lv_toupper('z') == 'Z');
        assert(lv_toupper('A') == 'A');
        assert(lv_toupper('9') == '9');
        assert(lv_toupper('&') == '&');
        printf("lv_toupper passed tests: %lu\r", i++);
    }
    {
        assert(lv_tolower(EOF) == EOF);
        assert(lv_toupper(EOF) == EOF);
        printf("lv_tolower/toupper passed tests: %lu\r\n", i++);
    }
}

void strlen_tests() {
    size_t i = 0;
    {
        assert(lv_strlen("hello") == 5);
        printf("lv_strlen passed tests: %lu\r", i++);
    }
    {
        assert(lv_strlen("") == 0);
        printf("lv_strlen passed tests: %lu\r", i++);
    }
    {
        assert(lv_strlen("hello\0world") == 5);
		printf("lv_strlen passed tests: %lu\r", i++);
    }
    {
        assert(lv_strlen(NULL) == 0);
        printf("lv_strlen passed tests: %lu\r\n", i++);
    }
}

void strdup_tests() {
    size_t i = 0;
    {
        const char *src = "hello world";
        LV_DEFER char *dup = lv_strdup(src);
        assert(dup != NULL);
        assert(strcmp(dup, src) == 0);
        assert(dup != src);
        printf("lv_strdup passed tests: %lu\r", i++);
    }
    {
        const char *src = "";
        LV_DEFER char *dup = lv_strdup(src);
        assert(dup != NULL);
        assert(strcmp(dup, src) == 0);
        assert(dup != src);
        printf("lv_strdup passed tests: %lu\r", i++);
    }
    {
        char *dup = lv_strdup(NULL);
        assert(dup == NULL);
        printf("lv_strdup passed tests: %lu\r\n", i++);
    }
}

void strchr_strrchr_tests() {
    size_t i = 0;
    const char *str = "banana";
    {
        assert(lv_strchr(str, 'b') == str);
        printf("lv_strchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strchr(str, 'a') == str + 1);
        printf("lv_strchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strchr(str, 'z') == NULL);
        printf("lv_strchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strchr(str, '\0') == str + strlen(str));
        printf("lv_strchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strchr("", 'a') == NULL);
        printf("lv_strchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strchr(NULL, 'a') == NULL);
        printf("lv_strchr passed tests: %lu\r\n", i++);
    }
    {
		assert(lv_strrchr(str, 'a') == str + 5);
        printf("lv_strrchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strrchr(str, 'b') == str);
        printf("lv_strrchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strrchr(str, 'z') == NULL);
        printf("lv_strrchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strrchr(str, '\0') == str + strlen(str));
        printf("lv_strrchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strrchr("", 'a') == NULL);
        printf("lv_strrchr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strrchr(NULL, 'a') == NULL);
        printf("lv_strrchr passed tests: %lu\r\n", i++);
    }
}

void strlcpy_tests() {
    size_t i = 0;
    {
        LV_DEFER char *dest = lv_alloc(L1_TEST);
        const char *src = "abc";
        size_t res = lv_strlcpy(dest, src, L1_TEST);
        assert(strcmp(dest, "abc") == 0);
        assert(res == strlen(src));
        printf("lv_strlcpy passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *dest = lv_alloc(5);
        const char *src = "longstring";
        size_t res = lv_strlcpy(dest, src, 5);
        assert(strcmp(dest, "long") == 0);
        assert(res == strlen(src));
        printf("lv_strlcpy passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *dest = lv_alloc(1);
        const char *src = "abc";
        size_t res = lv_strlcpy(dest, src, 1);
        assert(dest[0] == '\0');
        assert(res == strlen(src));
        printf("lv_strlcpy passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *dest = lv_alloc(L1_TEST);
        const char *src = "";
        size_t res = lv_strlcpy(dest, src, L1_TEST);
        assert(strcmp(dest, "") == 0);
        assert(res == 0);
        printf("lv_strlcpy passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *dest = lv_alloc(L1_TEST);
        assert(lv_strlcpy(dest, NULL, 1) == 0);
        assert(lv_strlcpy(NULL, "a", 1) == 0);
        assert(lv_strlcpy(NULL, NULL, 0) == 0);
        printf("lv_strlcpy passed tests: %lu\r\n", i++);
    }
}

void strlcat_tests() {
    size_t i = 0;
    {
        LV_DEFER char *dest = lv_alloc(L1_TEST);
        strcpy(dest, "hello ");
        const char *src = "world";
        size_t res = lv_strlcat(dest, src, L1_TEST);
        assert(res == 11);
		printf("lv_strlcat passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *dest = lv_alloc(5);
        strcpy(dest, "abc");
        const char *src = "defg";
        size_t res = lv_strlcat(dest, src, 5);
        assert(strcmp(dest, "abcd") == 0);
        assert(res == strlen("abc") + strlen("defg"));
        printf("lv_strlcat passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *dest = lv_alloc(L1_TEST);
        dest[0] = '\0';
        const char *src = "source";
        size_t res = lv_strlcat(dest, src, L1_TEST);
        assert(strcmp(dest, "source") == 0);
        assert(res == strlen(src));
        printf("lv_strlcat passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *dest = lv_alloc(L1_TEST);
        strcpy(dest, "full");
        const char *src = "";
        size_t res = lv_strlcat(dest, src, L1_TEST);
        assert(strcmp(dest, "full") == 0);
        assert(res == strlen("full"));
        printf("lv_strlcat passed tests: %lu\r", i++);
    }
}

void strncmp_tests() {
    size_t i = 0;
    {
        assert(lv_strncmp("abc", "abc", 3) == 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp("abc", "abd", 2) == 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp("abc", "abd", 3) < 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp("abd", "abc", 3) > 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp("abc", "ab", 3) > 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp("ab", "abc", 3) < 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp("", "", 0) == 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp("test", "test", 0) == 0);
        printf("lv_strncmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strncmp(NULL, "a", 1) != 0);
        assert(lv_strncmp("a", NULL, 1) != 0);
        printf("lv_strncmp passed tests: %lu\r\n", i++);
    }
}

void strnstr_tests() {
    size_t i = 0;
    const char *haystack = "foo bar baz";
    {
        assert(lv_strnstr(haystack, "bar", strlen(haystack)) == haystack + 4);
        printf("lv_strnstr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strnstr(haystack, "foo", strlen(haystack)) == haystack);
        printf("lv_strnstr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strnstr(haystack, "baz", strlen(haystack)) == haystack + 8);
        printf("lv_strnstr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strnstr(haystack, "qux", strlen(haystack)) == NULL);
        printf("lv_strnstr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strnstr(haystack, "bar", 3) == NULL);
        printf("lv_strnstr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strnstr(haystack, "", strlen(haystack)) == haystack);
        printf("lv_strnstr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strnstr("", "a", 0) == NULL);
        printf("lv_strnstr passed tests: %lu\r", i++);
    }
    {
        assert(lv_strnstr(NULL, "a", 1) == NULL);
        assert(lv_strnstr("a", NULL, 1) == "a");
        printf("lv_strnstr passed tests: %lu\r\n", i++);
    }
}

void strtrim_tests() {
    size_t i = 0;
    {
        LV_DEFER char *trimmed = lv_strtrim("  hello world  ", " ");
        assert(strcmp(trimmed, "hello world") == 0);
        printf("lv_strtrim passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *trimmed = lv_strtrim("---abcde+++", "-+");
        assert(strcmp(trimmed, "abcde") == 0);
        printf("lv_strtrim passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *trimmed = lv_strtrim("xxxxx", "x");
        assert(strcmp(trimmed, "") == 0);
        printf("lv_strtrim passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *trimmed = lv_strtrim("  ", " ");
        assert(strcmp(trimmed, "") == 0);
        printf("lv_strtrim passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *trimmed = lv_strtrim("abc", "xyz");
        assert(strcmp(trimmed, "abc") == 0);
        printf("lv_strtrim passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *trimmed = lv_strtrim("", "abc");
        assert(strcmp(trimmed, "") == 0);
        printf("lv_strtrim passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *trimmed = lv_strtrim("hello", "");
        assert(strcmp(trimmed, "hello") == 0);
        printf("lv_strtrim passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *trimmed = lv_strtrim(NULL, " ");
        assert(trimmed == NULL);
        trimmed = lv_strtrim("abc", NULL);
        assert(!strcmp(trimmed, "abc"));
        printf("lv_strtrim passed tests: %lu\r\n", i++);
    }
}

void strjoin_tests() {
    size_t i = 0;
    {
        LV_DEFER char *joined = lv_strjoin("hello", "world");
        assert(strcmp(joined, "helloworld") == 0);
        printf("lv_strjoin passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *joined = lv_strjoin("hello", "");
        assert(strcmp(joined, "hello") == 0);
        printf("lv_strjoin passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *joined = lv_strjoin("", "world");
        assert(strcmp(joined, "world") == 0);
        printf("lv_strjoin passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *joined = lv_strjoin("", "");
        assert(strcmp(joined, "") == 0);
        printf("lv_strjoin passed tests: %lu\r", i++);
    }
    {
        char *joined = lv_strjoin(NULL, "a");
        assert(joined == NULL);
        joined = lv_strjoin("a", NULL);
        assert(joined == NULL);
        joined = lv_strjoin(NULL, NULL);
        assert(joined == NULL);
        printf("lv_strjoin passed tests: %lu\r\n", i++);
    }
}

void substr_tests() {
    size_t i = 0;
    const char *str = "0123456789";
    {
        LV_DEFER char *sub = lv_substr(str, 2, 5);
        assert(strcmp(sub, "23456") == 0);
        printf("lv_substr passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *sub = lv_substr(str, 0, 3);
        assert(strcmp(sub, "012") == 0);
        printf("lv_substr passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *sub = lv_substr(str, 7, L1_TEST);
        assert(strcmp(sub, "789") == 0);
        printf("lv_substr passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *sub = lv_substr(str, 10, 5);
        assert(strcmp(sub, "") == 0);
        printf("lv_substr passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *sub = lv_substr(str, 12, 5);
        assert(strcmp(sub, "") == 0);
        printf("lv_substr passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *sub = lv_substr("", 0, 5);
        assert(strcmp(sub, "") == 0);
        printf("lv_substr passed tests: %lu\r", i++);
    }
    {
        LV_DEFER char *sub = lv_substr(NULL, 0, 5);
        assert(sub == NULL);
        printf("lv_substr passed tests: %lu\r\n", i++);
    }
}

void split_tests() {
    size_t i = 0;
    {
        LV_DEFER_ARR void **arr = (void **) lv_split("hello,world,foo", ',');
        assert(arr != NULL);
        assert(strcmp(arr[0], "hello") == 0);
        assert(strcmp(arr[1], "world") == 0);
        assert(strcmp(arr[2], "foo") == 0);
        assert(arr[3] == NULL);
        printf("lv_split passed tests: %lu\r", i++);
    }
    {
        LV_DEFER_ARR void **arr = (void **) lv_split(",hello,,world,", ',');
        assert(arr != NULL);
        assert(strcmp(arr[0], "hello") == 0);
        assert(strcmp(arr[1], "world") == 0);
        assert(arr[2] == NULL);
        printf("lv_split passed tests: %lu\r", i++);
    }
    {
        LV_DEFER_ARR void **arr = (void **) lv_split("singleword", ',');
        assert(arr != NULL);
        assert(strcmp(arr[0], "singleword") == 0);
        assert(arr[1] == NULL);
        printf("lv_split passed tests: %lu\r", i++);
    }
    {
        LV_DEFER_ARR void **arr = (void **) lv_split("", ',');
        assert(arr != NULL);
        assert(arr[0] == NULL);
        printf("lv_split passed tests: %lu\r", i++);
    }
    {
        LV_DEFER_ARR void **arr = (void **) lv_split(NULL, ' ');
        assert(arr == NULL);
        printf("lv_split passed tests: %lu\r\n", i++);
    }
}

void strcmp_tests() {
    size_t i = 0;
    {
        assert(lv_strcmp("abc", "abc") == 0);
        printf("lv_strcmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strcmp("abc", "abd") < 0);
        printf("lv_strcmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strcmp("abd", "abc") > 0);
        printf("lv_strcmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strcmp("abc", "ab") > 0);
        printf("lv_strcmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strcmp("ab", "abc") < 0);
        printf("lv_strcmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strcmp("", "") == 0);
        printf("lv_strcmp passed tests: %lu\r", i++);
    }
    {
        assert(lv_strcmp(NULL, "a") != 0);
        assert(lv_strcmp("a", NULL) != 0);
        assert(lv_strcmp(NULL, NULL) == 0);
        printf("lv_strcmp passed tests: %lu\r\n", i++);
    }
}

void isnumeric_tests() {
    size_t i = 0;
    {
        assert(lv_isnumeric("12345") == 1);
        printf("lv_isnumeric passed tests: %lu\r", i++);
    }
    {
        assert(lv_isnumeric("0") == 1);
        printf("lv_isnumeric passed tests: %lu\r", i++);
    }
    {
        assert(lv_isnumeric("") == 0);
        printf("lv_isnumeric passed tests: %lu\r", i++);
    }
    {
        assert(lv_isnumeric("123a45") == 0);
        printf("lv_isnumeric passed tests: %lu\r", i++);
    }
    {
        assert(lv_isnumeric("-123") ==  1);
        printf("lv_isnumeric passed tests: %lu\r", i++);
    }
    {
        assert(lv_isnumeric("+123") == 1);
        printf("lv_isnumeric passed tests: %lu\r", i++);
    }
    {
        assert(lv_isnumeric(NULL) == 0);
        printf("lv_isnumeric passed tests: %lu\r\n", i++);
    }
}

int main() {
    tolower_toupper_tests();
	strlen_tests();
	strdup_tests();
    strchr_strrchr_tests();
    strlcpy_tests();
    strlcat_tests();
    strncmp_tests();
    strnstr_tests();
    strtrim_tests();
    strjoin_tests();
    substr_tests();
    split_tests();
    strcmp_tests();
    isnumeric_tests();
    printf("[TESTER] All cstr tests passed\n");
    return 0;
}
