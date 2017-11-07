#ifndef ARCH_X86_ALTERNATIVE_H
#define ARCH_X86_ALTERNATIVE_H

#include <stringify.h>

/*
 * альтернативные инструкции
 */
#ifdef CONFIG_SMP
    #define LOCK_PREFIX_HERE\
        ".pushsection .smp_locks,\"a\"\n"\
        ".balign 4\n"\
        ".long 671f - .\n"\
        ".popsection\n"\
        "671:"

    #define LOCK_PREFIX LOCK_PREFIX_HERE "\n\tlock; "
#else
    #define LOCK_PREFIX_HERE ""
    #define LOCK_PREFIX ""
#endif

#define OLDINSTR(oldinstr)      "661:\n\t" oldinstr "\n662:\n"
#define b_replacement(number)   "663"#number
#define e_replacement(number)	"664"#number

#define alt_slen                "662b-661b"
#define alt_rlen(number)        e_replacement(number)"f-"b_replacement(number)"f"

#define ALTINSTR_ENTRY(feature, number)\
    " .long 661b - .\n"				/* label           */\
    " .long " b_replacement(number)"f - .\n"	/* new instruction */\
    " .word " __stringify(feature) "\n"		/* feature bit     */\
    " .byte " alt_slen "\n"			/* source len      */\
    " .byte " alt_rlen(number) "\n"		/* replacement len */

// rlen <= slen
#define DISCARD_ENTRY(number)   " .byte 0xff + (" alt_rlen(number) ") - (" alt_slen ")\n"

// replacement
#define ALTINSTR_REPLACEMENT(newinstr, feature, number) b_replacement(number) ":\n\t" newinstr "\n" e_replacement(number) ":\n\t"

// альтернативные сборки примитивов
#define ALTERNATIVE(oldinstr, newinstr, feature)\
    OLDINSTR(oldinstr)\
    ".pushsection .altinstructions,\"a\"\n"\
    ALTINSTR_ENTRY(feature, 1)\
    ".popsection\n"\
    ".pushsection .discard,\"aw\",@progbits\n"\
    DISCARD_ENTRY(1)\
    ".popsection\n"\
    ".pushsection .altinstr_replacement, \"ax\"\n"\
    ALTINSTR_REPLACEMENT(newinstr, feature, 1)\
    ".popsection"

// вторые альтернативные сборки примитивов
#define ALTERNATIVE_2(oldinstr, newinstr1, feature1, newinstr2, feature2)\
    OLDINSTR(oldinstr)\
    ".pushsection .altinstructions,\"a\"\n"\
    ALTINSTR_ENTRY(feature1, 1)\
    ALTINSTR_ENTRY(feature2, 2)\
    ".popsection\n"\
    ".pushsection .discard,\"aw\",@progbits\n"\
    DISCARD_ENTRY(1)\
    DISCARD_ENTRY(2)\
    ".popsection\n"\
    ".pushsection .altinstr_replacement, \"ax\"\n"\
    ALTINSTR_REPLACEMENT(newinstr1, feature1, 1)\
    ALTINSTR_REPLACEMENT(newinstr2, feature2, 2)\
    ".popsection"

// альтернативные инструкции для различных типов процессоров
#define alternative(oldinstr, newinstr, feature)    asm volatile(ALTERNATIVE(oldinstr, newinstr, feature) : : : "memory")
#endif /* ARCH_X86_ALTERNATIVE_H */