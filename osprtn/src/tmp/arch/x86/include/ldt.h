#ifndef ARCH_X86_LDT_H
#define ARCH_X86_LDT_H

// количество записей в таблице LTD
#define LDT_ENTRIES 8192

// размер записи
#define LDT_ENTRY_SIZE	8

// пользовательский дескриптор
struct x86_user_desc {
	unsigned int  entry_number;
	unsigned int  base_addr;
	unsigned int  limit;
	unsigned int  seg_32bit:1;
	unsigned int  contents:2;
	unsigned int  read_exec_only:1;
	unsigned int  limit_in_pages:1;
	unsigned int  seg_not_present:1;
	unsigned int  useable:1;
#ifdef __x86_64__
	unsigned int  lm:1;
#endif
};

#define MODIFY_LDT_CONTENTS_DATA	0
#define MODIFY_LDT_CONTENTS_STACK	1
#define MODIFY_LDT_CONTENTS_CODE	2

#endif /* ARCH_X86_LDT_H */