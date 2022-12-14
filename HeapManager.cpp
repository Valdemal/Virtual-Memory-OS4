#include <iostream>
#include <atomic>
#include <sys/mman.h>

#include "HeapManager.h"

HeapManager::chunk_t *HeapManager::chunk_list_head = nullptr;

void *HeapManager::allocate(size_t size) {
    const auto ALIGNED_SIZE = align_up(size, 16);
    const auto ALLOC_SIZE = get_alloc_size(ALIGNED_SIZE);

#if DEBUG
    std::cout << "Aligned size " << ALIGNED_SIZE << std::endl;
#endif

    if (ALLOC_SIZE >= MAX_ALLOC_SIZE) {
#if DEBUG
        std::cout << "Big size. Trying to allocate with map!" << std::endl;
#endif
        return map_allocate(ALIGNED_SIZE, ALLOC_SIZE)->get_memory_ptr();
    }

    auto new_chunk = get_available_free_chunk(size);

    if (new_chunk != nullptr) {
#if DEBUG
        std::cout << "Chunk reused!" << std::endl;
#endif
        new_chunk->is_free = false;
    } else {
        new_chunk = (chunk_t *) (sbrk(intptr_t(ALLOC_SIZE)));
        if (new_chunk != nullptr) {
            *new_chunk = chunk_t(ALIGNED_SIZE);
            insert_chunk_in_list(new_chunk);
        } else {
#if DEBUG
            std::cout << "Failed to alloc with sbrk! Trying mmapp alloc" << std::endl;
#endif
            return map_allocate(size, ALLOC_SIZE)->get_memory_ptr();
        }
    }

    return new_chunk->get_memory_ptr();
}


void HeapManager::free(void *ptr) {
    auto chunk_ptr = chunk_t::get_from_memory(ptr);

    if (chunk_ptr->is_free) {
#if DEBUG
        std::cout << "Chunk is already free!" << std::endl;
#endif

        return;
    }

    if (chunk_ptr->is_mapped) {
        int status = munmap(chunk_ptr, get_alloc_size(chunk_ptr->size));

#if DEBUG
        if (status == 0) {
            std::cout << "Unmap done!" << std::endl;
        } else {
            std::cout << "Unmap failed with code" << status << '!' << std::endl;
        }
#endif
    } else {

#if DEBUG
        std::cout << "Chunk marked as free!" << std::endl;
#endif
        chunk_ptr->is_free = true;
    }
}

size_t HeapManager::align_up(size_t num, size_t align) {
    return (num + align - 1) & ~(align - 1);
}

size_t HeapManager::get_alloc_size(size_t size) {
    return size + sizeof(chunk_t);
}

HeapManager::chunk_t *HeapManager::map_allocate(size_t size, size_t alloc_size) {
    auto new_chunk = (chunk_t *) mmap(
            nullptr, alloc_size, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0
    );

    if (new_chunk == MAP_FAILED) {
#if DEBUG
        std::cout << "Chunk mapping failed!" << std::endl;
#endif
        return nullptr;
    }

    *new_chunk = chunk_t(size, true);

#if DEBUG
    std::cout << "Chunk mapping ok!" << std::endl;
#endif

    return new_chunk;
}

HeapManager::chunk_t *HeapManager::get_available_free_chunk(size_t size) {
    auto current = chunk_list_head;

    while (current != nullptr) {
        if (current->is_free and current->size >= size)
            return current;

        current = current->next;
    }

    return nullptr;
}

void HeapManager::insert_chunk_in_list(HeapManager::chunk_t *new_chunk) {

    chunk_t *previous = nullptr;
    auto current = chunk_list_head;

    while (current != nullptr and new_chunk->size > current->size) {
        previous = current;
        current = current->next;
    }

    if (previous == nullptr) {
        chunk_list_head = new_chunk;
    } else {
        previous->next = new_chunk;
        new_chunk->prev = previous;
    }

    if (current != nullptr) {
        new_chunk->next = current;
        current->prev = new_chunk;
    }

#if DEBUG
    std::cout << "Chunk inserted in list!" << std::endl;
#endif
}

HeapManager::chunk_t::chunk_t(size_t size, bool mapped)
        : size(size), next(nullptr), prev(nullptr), is_free(false), is_mapped(mapped) {}

void *HeapManager::chunk_t::get_memory_ptr() const {
    return (void *) ((char *) this + sizeof(chunk_t));
}

HeapManager::chunk_t *HeapManager::chunk_t::get_from_memory(void *ptr) {
    return (chunk_t *) ((char *) ptr - sizeof(chunk_t));
}

#if DEBUG

void HeapManager::print_chunks_sizes() {
    auto current = chunk_list_head;

    while (current != nullptr) {
        std::cout << current->size << ' ';
        current = current->next;
    }

    std::cout << std::endl;
}

#endif