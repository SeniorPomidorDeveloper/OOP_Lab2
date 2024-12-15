#include <gtest/gtest.h>

#include "../src/libs/string/string.hpp"

TEST(StringTest, MoveConstructor)
{
    String str = String("Hello");
    String copy = std::move(str);
    ASSERT_STREQ(copy.get_cstring(), "Hello");
}

TEST(StringTest, OperatorPlus)
{
    String str1 = String("Hello");
    String str2 = String(", wrold!");
    ASSERT_STREQ((str1 + str2).get_cstring(), "Hello");
}