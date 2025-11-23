typedef struct Block {
    struct Block* prev;
    struct Block* next;
    unsigned long max_size;
    unsigned long size;
} Block;

typedef struct SubBlock {
    unsigned long size;
    Block* block;
    struct SubBlock* prev;
    struct SubBlock* next;
} SubBlock;

struct FixSubBlock;

typedef struct FixBlock {
    struct FixBlock* prev_;
    struct FixBlock* next_;
    unsigned long client_size_;
    struct FixSubBlock* start_;
    unsigned long n_allocated_;
} FixBlock;

typedef struct FixSubBlock {
    FixBlock* block_;
    struct FixSubBlock* next_;
} FixSubBlock;

typedef struct FixStart {
    FixBlock* tail_;
    FixBlock* head_;
} FixStart;

typedef struct __mem_pool_obj {
    Block* start_;
    FixStart fix_start[6];
} __mem_pool_obj;

typedef struct __mem_pool {
    void* reserved[14];
} __mem_pool;

typedef signed long tag_word;

typedef struct block_header {
    tag_word tag;
    struct block_header* prev;
    struct block_header* next;
} block_header;

typedef struct list_header {
    block_header* rover;
    block_header header;
} list_header;

typedef struct heap_header {
    struct heap_header* prev;
    struct heap_header* next;
} heap_header;

struct mem_pool_obj;
typedef void* (*sys_alloc_ptr)(unsigned long, struct mem_pool_obj*);
typedef void (*sys_free_ptr)(void*, struct mem_pool_obj*);

typedef struct pool_options {
    sys_alloc_ptr sys_alloc_func;
    sys_free_ptr sys_free_func;
    unsigned long min_heap_size;
    int always_search_first;
} pool_options;

typedef struct mem_pool_obj {
    list_header free_list;
    pool_options options;
    heap_header* heap_list;
    void* userData;

} mem_pool_obj;

static const unsigned long fix_pool_sizes[] = {4, 12, 20, 36, 52, 68};

#define SubBlock_size(ths) ((ths)->size & 0xFFFFFFF8)
#define SubBlock_block(ths) ((Block*)((unsigned long)((ths)->block) & ~0x1))
#define Block_size(ths) ((ths)->size & 0xFFFFFFF8)
#define Block_start(ths)                                                       \
    (*(SubBlock**)((char*)(ths) + Block_size((ths)) - sizeof(unsigned long)))

#define SubBlock_set_free(ths)                                                 \
    unsigned long this_size = SubBlock_size((ths));                            \
    (ths)->size &= ~0x2;                                                       \
    *(unsigned long*)((char*)(ths) + this_size) &= ~0x4;                       \
    *(unsigned long*)((char*)(ths) + this_size - sizeof(unsigned long)) =      \
        this_size

#define SubBlock_is_free(ths) !((ths)->size & 2)
#define SubBlock_set_size(ths, sz)                                             \
    (ths)->size &= ~0xFFFFFFF8;                                                \
    (ths)->size |= (sz)&0xFFFFFFF8;                                            \
    if (SubBlock_is_free((ths)))                                               \
    *(unsigned long*)((char*)(ths) + (sz) - sizeof(unsigned long)) = (sz)

#define SubBlock_from_pointer(ptr) ((SubBlock*)((char*)(ptr)-8))
#define FixSubBlock_from_pointer(ptr) ((FixSubBlock*)((char*)(ptr)-4))

#define FixBlock_client_size(ths) ((ths)->client_size_)
#define FixSubBlock_size(ths) (FixBlock_client_size((ths)->block_))

#define classify(ptr)                                                          \
    (*(unsigned long*)((char*)(ptr) - sizeof(unsigned long)) & 1)
#define __msize_inline(ptr)                                                    \
    (!classify(ptr) ? FixSubBlock_size(FixSubBlock_from_pointer(ptr))          \
                    : SubBlock_size(SubBlock_from_pointer(ptr)) - 8)

#define Block_empty(ths)                                                       \
    (_sb = (SubBlock*)((char*)(ths) + 16)),                                    \
        SubBlock_is_free(_sb) && SubBlock_size(_sb) == Block_size((ths)) - 24
