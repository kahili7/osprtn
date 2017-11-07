#ifndef GENERIC_STRINGIFY_H
#define GENERIC_STRINGIFY_H
/*
 * compile with -DFOO=bar, __stringify(FOO)
 */

#define __stringify_1(x...) #x
#define __stringify(x...)   __stringify_1(x)
#endif /* GENERIC_STRINGIFY_H */