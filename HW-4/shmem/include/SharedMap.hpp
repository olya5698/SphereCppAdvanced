#ifndef SHAREDMAP_HPP
#define SHAREDMAP_HPP

#include "SharedAllocator.hpp"
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
            mmap_ = create_shmem<char>(mmap_size);

            shmem::ShMemState* state = new(mmap_.get()) shmem::ShMemState{};
            float header_size = (sizeof(shmem::ShMemState) + blocks_count) / static_cast<float>(block_size);
            
            state->block_size = block_size;
            state->blocks_count = blocks_count - std::floor(header_size);
            state->used_blocks_table = mmap_.get() + sizeof(shmem::ShMemState);
            state->first_block = state->used_blocks_table + state->blocks_count;
            ::memset(state->used_blocks_table, shmem::FREE_BLOCK, state->blocks_count);

            semaphore_ = new(state->first_block) Semaphore(1, 1);
            state->first_block = static_cast<char*>(state->first_block) + sizeof(Semaphore);

            allocator_type map_alloc(state);
            map_ = new(state->first_block) shared_map{map_alloc};
            state->first_block = static_cast<char*>(state->first_block) + sizeof(shared_map);

        }

        void destroy() {
            semaphore_->destroy();
            map_->~map();
        }

        auto get_allocator() const {
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

        void update(const value_type& value) {
            SemLock wait(*semaphore_);
            map_->at(std::get<0>(value)) = std::get<1>(value);
        }

        auto insert(const value_type& value) {
            SemLock wait(*semaphore_);
            return map_->insert(value);
        }

        auto& get(const key_type& key) {
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
