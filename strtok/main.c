#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int split_string(char *str, char *tokens[], const int max_tokens);

void test_split_string();

void assert_equals_str(const char *expected, const char *actual);

void assert_equals_int(const int expected, const int actual);

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--test") == 0) {
        test_split_string();
        printf("tests pass!\n");
    }
    return 0;
}

void test_split_string() {
    const int max_tokens = 20;
    char test_str[] = "hello\tworld testing 123\nhello again";
    char *tokens[max_tokens];

    int token_count = split_string(test_str, tokens, max_tokens);

    assert_equals_int(6, token_count);
    assert_equals_str("hello", tokens[0]);
    assert_equals_str("world", tokens[1]);
    assert_equals_str("testing", tokens[2]);
    assert_equals_str("123", tokens[3]);
    assert_equals_str("hello", tokens[4]);
    assert_equals_str("again", tokens[5]);
}

void assert_equals_str(const char *expected, const char *actual) {
    if (strcmp(expected, actual) != 0) {
        printf("expected <%s> but was <%s>\n", expected, actual);
        exit(1);
    }
}

void assert_equals_int(const int expected, const int actual) {
    if (expected != actual) {
        printf("expected <%d> but was <%d>\n", expected, actual);
        exit(1);
    }
}

int split_string(char *str, char *tokens[], const int max_tokens) {
    int i = 0;
    for (i = 0; i < max_tokens; i++) {
        char *token = strtok(str, " \t\n");
        str = NULL;
        tokens[i] = token;
        if (token == NULL) {
            break;
        }
    }
    return i;
}
