#ifndef CHUNKEDMEMORYPOOL_H
#define CHUNKEDMEMORYPOOL_H

#if 0
class ChunkedMemoryPool : public MemoryChunkPool
{
private:
    struct Block
    {
        char* memory;
        Block* prev;
        Block* next;
    }* blocks;

    struct Watcher {
        Watcher*     next;
        PoolWatcher* watcher;
    }* watcher;

    MemoryChunk* free_list;

    unsigned int block_size;
    unsigned int memory_chunk_size;
    unsigned int number_chunks_used;
    QReadWriteLock lock;

    void allocateBlock ();

public:
    ChunkedMemoryPool();

    virtual ~ChunkedMemoryPool();

    /**
      * Initialise memory pool for chunks of specified size
      */
    void init (unsigned int chunk_size, unsigned int chunks_per_block);

    /**
      * Query the size of the chunks in bytes
      */
    const unsigned int chunkSize ();

    /**
      * Query how many chunks are currently allocated
      */
    const int chunksUsed ();

    /**
      * Query how many bytes are currently allocated
      */
    const unsigned int memoryUsed ();

    /**
      * Request a new memory chunk from the pool
      */
    MemoryChunk* request ();

    /**
      * Release a memory chunk back to the pool
      */
    void release (MemoryChunk* chunk);

    /**
      * Compact unused chunks and free them if they are too old.
      */
    void compact ();

    /**
      * Add a watcher to be notified when memory events occur.
      */
    void addWatcher (PoolWatcher* w);
};
#endif
#endif // CHUNKEDMEMORYPOOL_H
