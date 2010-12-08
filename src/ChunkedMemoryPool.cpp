
#include "ChunkedMemoryPool.h"
#include "PoolWatcher.h"

#define CALL_WATCHERS(func)         \
        if (watcher)                \
        {                           \
            Watcher* w = watcher;   \
            do {                    \
                w->watcher->func;   \
                w = w->next;        \
            } while (w);            \
        }

ChunkedMemoryPool::ChunkedMemoryPool () :
        number_chunks_used(0),
        memory_chunk_size(0),
        free_list(0),
        watcher(0)
{
}

ChunkedMemoryPool::~ChunkedMemoryPool ()
{
    // TODO: free memory used by pool
}

// O(n), linear time relative to block size
void ChunkedMemoryPool::allocateBlock ()
{
    Block* block = new Block;
    // Single allocation for all chunks in block.
    block->memory = new char[block_size * memory_chunk_size];
    block->next = 0;

    // Build a sequence of unused memory chunks.
    MemoryChunk* chunk;
    MemoryChunk* chunks = new MemoryChunk[block_size];
    MemoryChunk* prev = free_list;
    char* memory = block->memory;
    for (unsigned int i = block_size; i; --i)
    {
        //chunk = new MemoryChunk;
        chunk = &(chunks[i-1]);
        // Give the chunk a back reference to this pool
        chunk->pool = this;
        // Assign memory chunk
        chunk->pointer = reinterpret_cast<void*>(memory);
        // Link into free list.
        chunk->link = prev;
        prev = chunk;

        // Advance to next chunk
        memory += memory_chunk_size;
    }

    // If the free list is empty, then link in the newly created list.
    if (free_list == 0)
    {
        free_list = prev;
    }

    if (blocks == 0)
    {
        // First block, simply make it the head of the list.
        block->prev = 0;
        blocks = block;
    } else
    {
        // Iterate throguh to the end of the list and insert there.
        Block* link = blocks;
        while (link->next)
        {
            link = link->next;
        }
        // Link the node into the end of the list.
        link->next = block;
        block->prev = link;
    }

    CALL_WATCHERS(onAlloc(sizeof(block_size * memory_chunk_size)));
}

// O(1), constant time initialization
void ChunkedMemoryPool::init (unsigned int chunk_size, unsigned int chunks_per_block)
{
    Atomic atomic(lock);
    memory_chunk_size = chunk_size;
    block_size = chunks_per_block;

    free_list = 0;

    allocateBlock();
}

// O(1), constant time lookup
const unsigned int ChunkedMemoryPool::chunkSize ()
{
    Atomic atomic(lock);
    return memory_chunk_size;
}

// O(1), constant time lookup
const unsigned int ChunkedMemoryPool::chunksUsed ()
{
    Atomic atomic(lock);
    return number_chunks_used;
}

// O(1), constant time size calculation
const unsigned int ChunkedMemoryPool::memoryUsed ()
{
    Atomic atomic(lock);
    return memory_chunk_size * number_chunks_used;
}

// O(1), constant time allocation
virtual MemoryChunk* ChunkedMemoryPool::request ()
{
    Atomic atomic(lock);
    number_chunks_used++;

    // If there are no unused chunks in the pool..
    if (free_list == 0)
    {
        // ...allocate a new block of chunks
        allocateBlock();
    }

    // Unlink the next unused object
    MemoryChunk* chunk = free_list;
    free_list = free_list->link;

    // Notify watchers
    CALL_WATCHERS(onRequest(chunk->pointer));

    // Return new chunk
    return chunk;
}

// O(1), constant time deallocation
virtual void ChunkedMemoryPool::release (MemoryChunk* chunk)
{
    Atomic atomic(lock);
    number_chunks_used--;

    // Notify watchers
    CALL_WATCHERS(onRelease(chunk->pointer));
    // Link the chunk into the list of unused chunks
    chunk->link = free_list;
    free_list = chunk;
}

// O(n), linear time memory compaction
void ChunkedMemoryPool::compact ()
{

}

void ChunkedMemoryPool::addWatcher (PoolWatcher* w)
{
    Atomic atomic(lock);
    Watcher* watch = new Watcher;
    watch->watcher = w;
    watch->next = watcher;
    watcher = watch;
}
