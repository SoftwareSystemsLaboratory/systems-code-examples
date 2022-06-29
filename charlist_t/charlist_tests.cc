/* test cases */

#include <gtest/gtest.h>
#include <string.h>

#include "charlist.hh"

TEST(CharListTest, Initialization)
{
    charlist_t char_list;

    charlist_init(&char_list);
    charlist_delete(&char_list);
}

TEST(CharListTest, AddChar)
{
    charlist_t char_list;
    char word[] = "C Programming";
    int word_length = sizeof(word) / sizeof(char);
    charlist_init(&char_list);

    for (int i=0; i < word_length; i++)
    {
        charlist_add_char(&char_list, word[i]);
        ASSERT_EQ(charlist_size_slow(&char_list), i+1);
    }

    charlist_delete(&char_list);
}

TEST(CharListTest, AddSring)
{
    charlist_t char_list;
    char word[] = "C Programming";
    charlist_init(&char_list);
    charlist_add_string(&char_list, word);
    ASSERT_EQ(charlist_size_slow(&char_list), strlen(word));
    charlist_add_string(&char_list, word);
    ASSERT_EQ(charlist_size_slow(&char_list), 2*strlen(word));
    charlist_delete(&char_list);
}

TEST(CharListTest, ToString)
{
    charlist_t char_list;
    char word[] = "C Programming";
    charlist_init(&char_list);
    charlist_add_string(&char_list, word);
    char* text = charlist_tostring(&char_list);
    ASSERT_EQ(strcmp(text, word), 0);
    free(text);
    charlist_delete(&char_list);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
