//
// Created by George Thiruvathukal on 2/17/24.
//

#include <gtest/gtest.h>

#include "int_stack.hh"

TEST(IntStackTests, Initialization)
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    ASSERT_EQ(int_stack_capacity(&stack1), 10);
}

// This test fills the stack to capacity.
// Then it attempts to fill the stack beyond capacity.
// Does not check whether pushed values are valid.

TEST(IntStackTets, PushToCapacityAndOverflow)
{
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }
    ASSERT_EQ(int_stack_size(&stack1), capacity);
    int result = int_stack_push(&stack1, capacity+1);
    ASSERT_FALSE(result);
}

// This files the stack to capacity.
// Then it pops items one at a time and checks that they are the expected values.
// Then it attempts to pop from empty stack.

TEST(IntStackTets, PushToCapcacityPopUntilUnderflow
)
{
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }
    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
