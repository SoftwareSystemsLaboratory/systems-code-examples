#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int SplitString(char* str, char* tokens[], const int maxTokens);
void testSplitString();
void assertEqualsStr(const char *expected, const char *actual);
void assertEqualsInt(const int expected, const int actual);

int main(int argc, char* argv[]) {
    if(argc == 2 && strcmp(argv[1], "--test") == 0) {
        testSplitString();
        printf("tests pass!\n");
    }
    return 0;
}

void testSplitString() {
    const int maxTokens = 20;
    char testStr[] = "hello\tworld testing 123\nhello again";
    char* tokens[maxTokens];

    int tokenCount = SplitString(testStr, tokens, maxTokens);

    assertEqualsInt(6, tokenCount);
    assertEqualsStr("hello", tokens[0]);
    assertEqualsStr("world", tokens[1]);
    assertEqualsStr("testing", tokens[2]);
    assertEqualsStr("123", tokens[3]);
    assertEqualsStr("hello", tokens[4]);
    assertEqualsStr("again", tokens[5]);
}

void assertEqualsStr(const char* expected, const char* actual) {
    if(strcmp(expected, actual) != 0) {
        printf("expected <%s> but was <%s>\n", expected, actual);
        exit(1);
    }
}

void assertEqualsInt(const int expected, const int actual) {
    if(expected != actual) {
        printf("expected <%d> but was <%d>\n", expected, actual);
        exit(1);
    }
}

int SplitString(char* str, char* tokens[], const int maxTokens) {
    int i = 0;
    for(i = 0; i < maxTokens; i++) {
        char* token = strtok(str, " \t\n");
        str = NULL;
        tokens[i] = token;
        if(token == NULL) {
            break;
        }
    }
    return i;
}
