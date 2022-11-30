#ifndef HEAP_MANAGER_H
#define HEAP_MANAGER_H


#include <cstddef>
#include <cstdint>

#define DEBUG true

static const size_t MAX_ALLOC_SIZE = 33554432;

class HeapManager {
public:
    static void *allocate(size_t size);

    static void free(void *ptr);

#if DEBUG

    static void print_chunks_sizes();

#endif


private:
    struct chunk_t {
        size_t size;

        bool is_mapped;
        bool is_free;

        chunk_t *next;
        chunk_t *prev;

        explicit chunk_t(size_t size, bool mapped = false);

        // Возвращает указатель на данные по chunk
        inline void* get_memory_ptr() const;

        // Возвращает указатель на chunk по данным ptr
        static inline chunk_t* get_from_memory(void *ptr);
    };

    static chunk_t* chunk_list_head;

    static chunk_t *get_available_free_chunk(size_t size);

    static void insert_chunk_in_list(chunk_t* new_chunk);

    static inline size_t align_up(size_t num, size_t align);

    static inline size_t get_alloc_size(size_t size);

    static HeapManager::chunk_t *map_allocate(size_t size, size_t alloc_size);
};


#endif //HEAP_MANAGER_H
