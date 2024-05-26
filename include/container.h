#ifndef CONTAINER_H
#define CONTAINER_H

#include <new>
#include <utility>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

static vector<size_t> offsets= {0};

template<typename T>
concept CopyConstructibleType = is_copy_constructible_v<T>;

template<size_t SIZE, CopyConstructibleType T, CopyConstructibleType... Types>
void allocate_block(void* memory, T arg, Types... args);

template<size_t SIZE, CopyConstructibleType... Types>
void allocate(void* memory, Types... args) {
    if (!memory) return;
    static_assert((sizeof(Types) + ... + 0) <= SIZE, "Out of memory for allocation");

    if constexpr (sizeof...(Types) > 0) {
        allocate_block<SIZE, Types...>(memory, args...);
    }

    return;
}

template<size_t SIZE, CopyConstructibleType T, CopyConstructibleType... Types>
void allocate_block(void* memory, T arg, Types... args) {
    new (memory) T(arg);
    offsets.push_back(offsets.back() + sizeof(T));
    allocate<SIZE, Types...>(static_cast<char*>(memory) + sizeof(T), args...);
}

template<typename... Types>
class Container {
    void* memory_;
public:
    constexpr Container(Types... args) {
        constexpr size_t size = 1024*8;
        memory_ = std::malloc(size);
        allocate<size, Types...>(memory_, args...);
        
        // for (int i = 1; i < offsets.size(); i++) {
        //     offsets[i] += offsets[i - 1];
        // }
    }
    
    ~Container() noexcept {
        if (memory_) std::free(memory_);
    }

    template<typename T>
    T getElement(size_t idx) {
        return *((T*)(static_cast<char*>(memory_) + offsets[idx]));
    }

};


#endif // CONTAINER_H
