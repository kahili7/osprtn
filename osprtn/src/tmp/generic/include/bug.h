#ifndef GENERIC_BUG_H
#define GENERIC_BUG_H

// останавливает компилирование, если выражение истина
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))


#endif /* GENERIC_BUG_H */