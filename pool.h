typedef struct Block Block;
typedef struct Pool Pool;

struct Pool
{
    size_t bsize;
    size_t size;
    Block **mem;
};

struct Block
{
    void *mem;
    int free;
};

static Pool *poolcreate(size_t count, size_t blocksize);
void *poolgrab(Pool *pool);
void poolfree(Pool *pool, void *mem);
void pooldestroy(Pool *pool);
