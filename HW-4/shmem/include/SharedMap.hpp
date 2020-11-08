#ifndef SHAREDMAP_HPP
#define SHAREDMAP_HPP

#include "SharedAllocator.hpp"
#include "SharedMemory.hpp"
#include "SemLock.hpp"
#include "Semaphore.hpp"

#include <map>
#include <iostream>

namespace shmem {

    template <class Key, class T, class Compare = std::less<Key>>
    class SharedMap {
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;

        using allocator_type = ShAlloc<value_type>;
        using shared_map = std::map<key_type, mapped_type, Compare, allocator_type>;

    private:
        ShUTPtr<char> mmap_;
        shared_map* map_;
        Semaphore* semaphore_;

    public:
        explicit SharedMap(size_t block_size, size_t blocks_count) {
            size_t mmap_size = block_size * blocks_count;
            mmap_ = shmem::create_shmem<char>(mmap_size);

            shmem::ShMemState* state = new(mmap_.get()) shmem::ShMemState{};
            size_t header_size = sizeof(shmem::ShMemState);

            semaphore_ = new(mmap_.get() + header_size) Semaphore(1, 1);
            header_size += sizeof(Semaphore);

            allocator_type map_alloc{state};
            map_ = new(mmap_.get() + header_size) shared_map{map_alloc};
            header_size += sizeof(shared_map);

            header_size += blocks_count;

            size_t header_size_in_blocks = std::ceil(header_size / static_cast<float>(block_size));
            
            state->block_size = block_size;
            state->blocks_count = blocks_count - header_size_in_blocks;
            state->used_blocks_table = mmap_.get() + header_size - state->blocks_count;
            state->first_block = mmap_.get() + header_size;
            ::memset(state->used_blocks_table, shmem::FREE_BLOCK, state->blocks_count);
        }

        ~SharedMap() {
            destroy();
        }

        void destroy() {
            semaphore_->destroy();
            map_->~map();
        }

        allocator_type get_allocator() const {
            SemLock wait(*semaphore_);
            return map_->get_allocator();
        }

        auto begin() {
            SemLock wait(*semaphore_);
            return map_->begin();
        }

        auto end() {
            SemLock wait(*semaphore_);
            return map_->end();
        }

        mapped_type update(const value_type& value) {
            SemLock wait(*semaphore_);
            map_->at(value.first) = value.second;
            return map_->at(value.first);
        }

        auto insert(const value_type& value) {
            SemLock wait(*semaphore_);
            return map_->insert(value);
        }

        mapped_type get(const key_type& key) {
            SemLock wait(*semaphore_);
            return map_->at(key);
        }

        auto remove(const key_type& key) {
            SemLock wait(*semaphore_);
            return map_->erase(key);
        }

    };

}

#endif
