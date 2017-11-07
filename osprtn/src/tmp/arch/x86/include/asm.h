#ifndef ARCH_X86_ASM_H
#define ARCH_X86_ASM_H
/*
 * Сборка под ASM | C 
 */

// форма операндов в ассемблере
#ifdef __ASSEMBLY__
    #define __ASM_FORM(x)	x
    #define __ASM_FORM_COMMA(x) x,
#else
    #define __ASM_FORM(x)	" " #x " "
    #define __ASM_FORM_COMMA(x) " " #x ","
#endif

// расширение счетчика места.
// название секции, счетчик места 8 байт
#ifdef __ASSEMBLY__
    #define _ASM_EXTABLE(from, to)\
        .pushsection "__ex_table", "a";\
        .balign 8;\
        .long (from) - .;\
        .long (to) - .;\
        .popsection    
#else
    #define _ASM_EXTABLE(from, to)\
        ".pushsection \"__ex_table\", \"a\"\n"\
        ".balign 8\n"\
        ".long (" #from ") - .\n"\
        ".long (" #to ") - .\n"\
        ".popsection\n"
#endif
#endif /* ARCH_X86_ASM_H */