// структура вектора
struct _vector_entry {
    uint16_t    nentries;   // кол. записей
    uint16_t    nfree;      // кол. свободных
    void	*free;
    void	**vector;
};