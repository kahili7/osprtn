enum {
    MEMTYPE_NONE,
    MEMTYPE_RAM,
    MEMTYPE_IMAGEFSYS,
    MEMTYPE_BOOTRAM,
    MEMTYPE_RESERVED,
    MEMTYPE_IOMEM,
    MEMTYPE_FLASHFSYS
};

struct meminfo_entry {
    _Paddr32t   addr;
    _Uint32t    size;
    _Uint32t    type;
    _Uint32t    spare;
};