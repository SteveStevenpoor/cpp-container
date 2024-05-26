#ifndef CONTAINER_H
#define CONTAINER_H

#include <new>
#include <utility>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;


template<typename T>
concept CopyConstructibleType = is_copy_constructible_v<T>;

//std forward??
template<size_t SIZE, CopyConstructibleType... Types>
class Container {
    void* memory_;
    vector<size_t> offsets_ = {0};
    
public:
    constexpr Container(Types... args) requires((sizeof(Types) + ... + 0) <= SIZE) {
        memory_ = std::malloc(SIZE);
        allocate<Types...>(memory_, args...);
    }

    template<typename T>
    void destruct_some(T* p) {
        p->~T();
    }

    void cleanup() {
        size_t offset = 0;
        (destruct_some<Types>((Types*)(static_cast<char*>(memory_) + (offset += sizeof(Types)))), ...);
    }

    ~Container() noexcept {
        cleanup();
        if (memory_) std::free(memory_);
    }

    template<CopyConstructibleType T>
    T getElement(size_t idx) {
        return *((T*)(static_cast<char*>(memory_) + offsets_[idx]));
    }


private:
    template<CopyConstructibleType... TTypes>
    void allocate(void* mem, TTypes... args) {
        if (!mem) return;

        if constexpr (sizeof...(TTypes) > 0) {
            allocate_block<TTypes...>(mem, args...);
        }

        return;
    }

    template<CopyConstructibleType T, CopyConstructibleType... TTypes>
    void allocate_block(void* mem, T arg, TTypes... args) {
        T* tptr = new (mem) T(arg);
        offsets_.push_back(offsets_.back() + sizeof(T));
        allocate<TTypes...>(static_cast<char*>(mem) + sizeof(T), args...);
    }

};


#endif // CONTAINER_H
