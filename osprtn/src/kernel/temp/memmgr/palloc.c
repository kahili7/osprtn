#define FREE_LIST_END(bh, list)     ((struct palloc_quantum *)&bh->free[list])
#define FREE_LIST_EMPTY(bh, list)   (bh->free[list].next == (struct palloc_quantum *)&bh->free[list])

typedef struct palloc_restrict sysram_entry_t;

struct sysram_list {
    unsigned        count;
    sysram_entry_t  list[1]; // variable size
};

static struct block_head    **blk_head;

#define TOP_PADDR   (~(word_t)0)

// удалить из очереди
static struct palloc_quantum *dequeue_run(struct block_head *bh, struct palloc_quantum *r)
{
    r->u.free.prev->u.free.next = r->u.free.next;
    r->u.free.next->u.free.prev = r->u.free.prev;
    return r;
}

// вставить в очереди
static void enqueue_run(struct block_head *bh, struct palloc_quantum *r)
{
    unsigned run = r->run;
	
    if (run < PALLOC_FREE_QUEUES)
    {
        // add to head of individual free queue; they're all the same size
        // добавить в голову отдельной очереди
        r->u.free.next = bh->free[run].next;
        r->u.free.prev = FREE_LIST_END(bh, run);
        bh->free[run].next->u.free.prev = r;
        bh->free[run].next = r;
    }
    else
    {
        // If the new entry size is >= than what we think is the largest,
        // add it in front, otherwise add to the end.
        // We are more likely to be able to satisfy large requests
        // with the largest pieces of free memory
        // We use the cached max_free_run to decide this, so no cunning is required.

        if(run >= bh->max_free_run)
        {
            // add to head of default queue
            r->u.free.next = bh->free[PALLOC_DEFAULT_QUEUE].next;
            r->u.free.prev = FREE_LIST_END(bh, PALLOC_DEFAULT_QUEUE);
            bh->free[PALLOC_DEFAULT_QUEUE].next->u.free.prev = r;
            bh->free[PALLOC_DEFAULT_QUEUE].next = r;

            bh->max_free_run = run;
        }
        else
        {
            // add to tail of default queue
            r->u.free.next = FREE_LIST_END(bh, PALLOC_DEFAULT_QUEUE);
            r->u.free.prev = bh->free[PALLOC_DEFAULT_QUEUE].prev;
            bh->free[PALLOC_DEFAULT_QUEUE].prev->u.free.next = r;
            bh->free[PALLOC_DEFAULT_QUEUE].prev = r;
        }
    }
    
    return;
}

static unsigned init_block(struct block_head **bhp, unsigned blk_idx, sysram_entry_t *se, struct palloc_quantum *quanta)
{
    struct block_head *bh = bhp[blk_idx];
    word_t block_size;
    
    bh->start.paddr = se->start;
    bh->end.paddr   = se->end;
    block_size = (bh->end.paddr - bh->start.paddr) + 1;
}

