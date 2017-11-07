#ifndef GENERIC_PLATFORM_H
#define GENERIC_PLATFORM_H

//#if defined(__X86__)
    #define _SOS_CPU_HDR_DIR_(h) <x86/include/h>
//#endif

#ifndef _NTO_HDR_
    #define _SOS_HDR_(hdr) <hdr>
#endif

#include _SOS_HDR_(compiler.h)

/*#define _BITFIELD64B(__start_bit, __value)   ((_Uint64t)(__value) << (63-(__start_bit)))
#define _BITFIELD32B(__start_bit, __value)   ((__value) << (31-(__start_bit)))
#define _BITFIELD16B(__start_bit, __value)   ((__value) << (15-(__start_bit)))
#define _BITFIELD8B(__start_bit, __value)    ((__value) << ( 7-(__start_bit)))
*/
#define _BITFIELD64(__start_bit, __value)   ((_Uint64t)(__value) << (__start_bit))
#define _BITFIELD32(__start_bit, __value)   ((__value) << (__start_bit))
#define _BITFIELD16(__start_bit, __value)   ((__value) << (__start_bit))
#define _BITFIELD8(__start_bit, __value)    ((__value) << (__start_bit))

/*#define	_ONEBIT64B(__start_bit) _BITFIELD64B(__start_bit, 1)
#define	_ONEBIT32B(__start_bit)	_BITFIELD32B(__start_bit, 1)
#define	_ONEBIT16B(__start_bit)	_BITFIELD16B(__start_bit, 1)
#define	_ONEBIT8B(__start_bit)	_BITFIELD8B(__start_bit, 1)
*/
#define	_ONEBIT64(__start_bit)	_BITFIELD64(__start_bit, 1)
#define	_ONEBIT32(__start_bit)	_BITFIELD32(__start_bit, 1)
#define	_ONEBIT16(__start_bit)	_BITFIELD16(__start_bit, 1)
#define	_ONEBIT8(__start_bit)	_BITFIELD8(__start_bit ,1)

#include _SOS_HDR_(target-ptn.h)

#endif /* GENERIC_PLATFORM_H */