#include "alloc.h"

#pragma exceptions on

void __sys_free(void* ptr);
void* memset(void*, int, int);

static void SubBlock_merge_next(SubBlock*, SubBlock**);

inline static SubBlock* SubBlock_merge_prev(SubBlock* ths, SubBlock** start) {
    unsigned long prevsz;
    SubBlock* p;

    if (!(ths->size & 0x04)) {
        prevsz = *(unsigned long*)((char*)ths - sizeof(unsigned long));
        if (prevsz & 0x2)
            return ths;
        p = (SubBlock*)((char*)ths - prevsz);
        SubBlock_set_size(p, prevsz + SubBlock_size(ths));

        if (*start == ths)
            *start = (*start)->next;
        ths->next->prev = ths->prev;
        ths->next->prev->next = ths->next;
        return p;
    }
    return ths;
}

void Block_link(Block* ths, SubBlock* sb) {
    SubBlock** st;
    SubBlock_set_free(sb);
    st = &Block_start(ths);

    if (*st != 0) {
        sb->prev = (*st)->prev;
        sb->prev->next = sb;
        sb->next = *st;
        (*st)->prev = sb;
        *st = sb;
        *st = SubBlock_merge_prev(*st, st);
        SubBlock_merge_next(*st, st);
    } else {
        *st = sb;
        sb->prev = sb;
        sb->next = sb;
    }
    if (ths->max_size < SubBlock_size(*st))
        ths->max_size = SubBlock_size(*st);
}

static void SubBlock_merge_next(SubBlock* pBlock, SubBlock** pStart) {
    SubBlock* next_sub_block;
    unsigned long this_cur_size;

    next_sub_block = (SubBlock*)((char*)pBlock + (pBlock->size & 0xFFFFFFF8));

    if (!(next_sub_block->size & 2)) {
        this_cur_size =
            (pBlock->size & 0xFFFFFFF8) + (next_sub_block->size & 0xFFFFFFF8);

        pBlock->size &= ~0xFFFFFFF8;
        pBlock->size |= this_cur_size & 0xFFFFFFF8;

        if (!(pBlock->size & 2)) {
            *(unsigned long*)((char*)(pBlock) + (this_cur_size)-4) =
                (this_cur_size);
        }

        if (!(pBlock->size & 2)) {
            *(unsigned long*)((char*)pBlock + this_cur_size) &= ~4;
        } else {
            *(unsigned long*)((char*)pBlock + this_cur_size) |= 4;
        }

        if (*pStart == next_sub_block) {
            *pStart = (*pStart)->next;
        }

        if (*pStart == next_sub_block) {
            *pStart = 0;
        }

        next_sub_block->next->prev = next_sub_block->prev;
        next_sub_block->prev->next = next_sub_block->next;
    }
}

inline static Block* __unlink(__mem_pool_obj* pool_obj, Block* bp) {
    Block* result = bp->next;
    if (result == bp) {
        result = 0;
    }

    if (pool_obj->start_ == bp) {
        pool_obj->start_ = result;
    }

    if (result != 0) {
        result->prev = bp->prev;
        result->prev->next = result;
    }

    bp->next = 0;
    bp->prev = 0;
    return result;
}

inline static void deallocate_from_var_pools(__mem_pool_obj* pool_obj,
                                             void* ptr) {
    SubBlock* sb = SubBlock_from_pointer(ptr);
    SubBlock* _sb;

    Block* bp = SubBlock_block(sb);
    Block_link(bp, sb);

    if (Block_empty(bp)) {
        __unlink(pool_obj, bp);
        __sys_free(bp);
    }
}

void deallocate_from_fixed_pools(__mem_pool_obj* pool_obj, void* ptr,
                                 unsigned long size) {
    unsigned long i = 0;
    FixSubBlock* p;
    FixBlock* b;
    FixStart* fs;

    while (size > fix_pool_sizes[i]) {
        ++i;
    }

    fs = &pool_obj->fix_start[i];
    p = FixSubBlock_from_pointer(ptr);
    b = p->block_;

    if (b->start_ == 0 && fs->head_ != b) {
        if (fs->tail_ == b) {
            fs->head_ = fs->head_->prev_;
            fs->tail_ = fs->tail_->prev_;
        } else {
            b->prev_->next_ = b->next_;
            b->next_->prev_ = b->prev_;
            b->next_ = fs->head_;
            b->prev_ = b->next_->prev_;
            b->prev_->next_ = b;
            b->next_->prev_ = b;
            fs->head_ = b;
        }
    }

    p->next_ = b->start_;
    b->start_ = p;

    if (--b->n_allocated_ == 0) {
        if (fs->head_ == b) {
            fs->head_ = b->next_;
        }

        if (fs->tail_ == b) {
            fs->tail_ = b->prev_;
        }

        b->prev_->next_ = b->next_;
        b->next_->prev_ = b->prev_;

        if (fs->head_ == b) {
            fs->head_ = 0;
        }

        if (fs->tail_ == b) {
            fs->tail_ = 0;
        }

        deallocate_from_var_pools(pool_obj, b);
    }
}

inline void __init_pool_obj(__mem_pool* pool_obj) {
    memset(pool_obj, 0, sizeof(__mem_pool_obj));
}

inline static __mem_pool* get_malloc_pool(void) {
    static __mem_pool protopool;
    static unsigned char init = 0;
    if (!init) {
        __init_pool_obj(&protopool);
        init = 1;
    }

    return &protopool;
}

inline void __pool_free(__mem_pool* pool, void* ptr) {
    __mem_pool_obj* pool_obj;
    unsigned long size;

    if (ptr == 0) {
        return;
    }

    pool_obj = (__mem_pool_obj*)pool;
    size = __msize_inline(ptr);

    if (size <= 68) {
        deallocate_from_fixed_pools(pool_obj, ptr, size);
    } else {
        deallocate_from_var_pools(pool_obj, ptr);
    }
}

void free(void* ptr) {
    __pool_free(get_malloc_pool(), ptr);
}
