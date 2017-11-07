#define CACHE_FLAG_INSTR	0x0001	/* cache holds instructions */
#define CACHE_FLAG_DATA		0x0002	/* cache holds data */
#define CACHE_FLAG_UNIFIED	0x0003	/* cache holds both ins & data */
#define CACHE_FLAG_SHARED	0x0004	/* cache is shared between multiple  */
									/* processors in an SMP system */
#define CACHE_FLAG_SNOOPED	0x0008	/* cache implements a bus snooping */
									/* protocol */
#define CACHE_FLAG_VIRT_TAG	0x0010	/* cache is virtually tagged */
#define CACHE_FLAG_VIRTUAL	0x0010	/* backwards compatability flag for above */
#define CACHE_FLAG_WRITEBACK 0x0020	/* cache does writeback, not writethru */
#define CACHE_FLAG_CTRL_PHYS 0x0040	/* control function takes 32-bit paddrs */
#define CACHE_FLAG_SUBSET	0x0080	/* this cache obeys the 'subset' property */
#define CACHE_FLAG_NONCOHERENT 0x0100 /* cache is non-coherent on SMP */
#define CACHE_FLAG_NONISA	0x0200 /* cache doesn't obey ISA cache instr */
#define CACHE_FLAG_NOBROADCAST 0x0400 /* cache ops aren't broadcast on bus for SMP */
#define CACHE_FLAG_VIRT_IDX	0x0800	/* cache is virtually indexed */
#define CACHE_FLAG_CTRL_PHYS64 0x1000 /* control function takes 64-bit paddrs */

struct cacheattr_entry {
    _Uint32t	next;       // индекс для следующего, более низкого уровня записи
    _Uint32t	line_size;  // размер строки кэша в байтах
    _Uint32t	num_lines;  // количество строк кэш-памяти
    _Uint32t	flags;      // флаги
    _SPFPTR(unsigned, control, (_Paddr32t, unsigned, int, struct cacheattr_entry *, volatile struct syspage_entry *));  // условное обозначение поставляемого код запуска
    _Uint16t	ways;
    _Uint16t	spare0[1];
    _Uint32t	spare1[2];
};
