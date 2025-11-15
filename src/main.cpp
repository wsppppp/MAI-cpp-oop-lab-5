#include <iostream>
#include "../include/MemoryResource.h"
#include "../include/DynamicArray.h"
#include "../include/MyStruct.h"
#include <memory_resource>

int main() {
    // Создадим свой memory_resource
    ReusingMemoryResource mem_resource;

    // Полиморфные аллокаторы для int и MyStruct
    std::pmr::polymorphic_allocator<int> alloc_int(&mem_resource);
    std::pmr::polymorphic_allocator<MyStruct> alloc_struct(&mem_resource);

    // Контейнер для intов
    DynamicArray<int, std::pmr::polymorphic_allocator<int>> arr_int(alloc_int);
    arr_int.push_back(10);
    arr_int.push_back(20);
    arr_int.push_back(30);

    std::cout << "Int array: ";
    for (auto v : arr_int) std::cout << v << ' ';
    std::cout << std::endl;

    // Контейнер для сложного типа
    DynamicArray<MyStruct, std::pmr::polymorphic_allocator<MyStruct>> arr_struct(alloc_struct);
    arr_struct.push_back(MyStruct(1, "one", 1.1));
    arr_struct.push_back(MyStruct(2, "two", 2.2));
    arr_struct.push_back(MyStruct(3, "three", 3.3));

    std::cout << "Struct array:\n";
    for (auto& s : arr_struct) {
        std::cout << "  MyStruct{x=" << s.x << ", name=" << s.name << ", value=" << s.value << "}\n";
    }

    std::cout << "Blocks in use: " << mem_resource.in_use_count() << std::endl;
    std::cout << "Blocks free: " << mem_resource.free_count() << std::endl;

    arr_struct.pop_back();
    arr_int.pop_back();
    std::cout << "\nAfter pop_back:\n";
    std::cout << "Blocks in use: " << mem_resource.in_use_count() << std::endl;
    std::cout << "Blocks free: " << mem_resource.free_count() << std::endl;
}