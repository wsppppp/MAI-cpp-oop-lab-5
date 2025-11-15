#include <gtest/gtest.h>
#include "MemoryResource.h"
#include "DynamicArray.h"
#include "MyStruct.h"

TEST(ReusingMemoryResource, BlockAccounting) {
    ReusingMemoryResource res;
    std::pmr::polymorphic_allocator<int> alloc(&res);

    DynamicArray<int, std::pmr::polymorphic_allocator<int>> arr(alloc);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    EXPECT_EQ(res.in_use_count(), 1); // Обычно 1 блок на массив, если resize() не вызывался
    arr.pop_back();
    arr.pop_back();
    arr.pop_back();
    EXPECT_EQ(arr.getSize(), 0);
    // после clear блока in_use может быть 0
}

TEST(DynamicArray, PushPop) {
    DynamicArray<int> arr;
    arr.push_back(5);
    arr.push_back(7);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 7);
    arr.pop_back();
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr[0], 5);
}

TEST(DynamicArray, StructStorage) {
    DynamicArray<MyStruct> arr;
    arr.push_back(MyStruct(1, "one", 1.1));
    arr.push_back(MyStruct(2, "two", 2.2));
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0].x, 1);
    EXPECT_EQ(arr[1].name, "two");
    EXPECT_DOUBLE_EQ(arr[0].value, 1.1);
}

TEST(DynamicArray, IteratorWorks) {
    DynamicArray<int> arr;
    for(int i = 0; i < 5; ++i) arr.push_back(i);

    int cnt = 0;
    for(auto it = arr.begin(); it != arr.end(); ++it) {
        EXPECT_EQ(*it, cnt++);
    }
}

TEST(DynamicArray, EmptyArray) {
    DynamicArray<int> arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.getSize(), 0);
}