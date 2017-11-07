#ifndef ARCH_X86_APIC_DEFS_H
#define ARCH_X86_APIC_DEFS_H

#include _SOS_CPU_HDR_DIR_(apic-flags.h)

/*
 * расширенный программируемый контроллер прерываний
 */
struct x86_apic_lvt {

/*000*/	struct { _Uint32t __reserved[4]; } __reserved_01;

/*010*/	struct { _Uint32t __reserved[4]; } __reserved_02;

/*020*/	struct { /* APIC ID Register */
            _Uint32t __reserved_1 : 24,
                    phys_apic_id : 4,
                    __reserved_2 : 4;
            _Uint32t __reserved[3];
	} id;

/*030*/	const struct { /* APIC Version Register */
            _Uint32t version : 8,
                    __reserved_1 : 8,
                    max_lvt : 8,
                    __reserved_2 : 8;
            _Uint32t __reserved[3];
	} version;

/*040*/	struct { _Uint32t __reserved[4]; } __reserved_03;

/*050*/	struct { _Uint32t __reserved[4]; } __reserved_04;

/*060*/	struct { _Uint32t __reserved[4]; } __reserved_05;

/*070*/	struct { _Uint32t __reserved[4]; } __reserved_06;

/*080*/	struct { /* Task Priority Register */
            _Uint32t priority : 8,
                    __reserved_1 : 24;
            _Uint32t __reserved_2[3];
	} tpr;

/*090*/	const struct { /* Arbitration Priority Register */
            _Uint32t priority : 8,
                    __reserved_1 : 24;
            _Uint32t __reserved_2[3];
	} apr;

/*0A0*/	const struct { /* Processor Priority Register */
            _Uint32t priority : 8,
                    __reserved_1 : 24;
            _Uint32t __reserved_2[3];
	} ppr;

/*0B0*/	struct { /* End Of Interrupt Register */
		_Uint32t eoi;
		_Uint32t __reserved[3];
	} eoi;

/*0C0*/	struct { _Uint32t __reserved[4]; } __reserved_07;

/*0D0*/	struct { /* Logical Destination Register */
            _Uint32t __reserved_1 : 24,
                    logical_dest : 8;
            _Uint32t __reserved_2[3];
	} ldr;

/*0E0*/	struct { /* Destination Format Register */
            _Uint32t __reserved_1 : 28,
                    model : 4;
            _Uint32t __reserved_2[3];
	} dfr;

/*0F0*/	struct { /* Spurious Interrupt Vector Register */
            _Uint32t spurious_vector : 8,
                    apic_enabled : 1,
                    focus_cpu : 1,
                    __reserved_2 : 22;
            _Uint32t __reserved_3[3];
	} svr;

/*100*/	struct { /* In Service Register */
/*170*/     _Uint32t bitfield;
            _Uint32t __reserved[3];
	} isr [8];

/*180*/	struct { /* Trigger Mode Register */
/*1F0*/     _Uint32t bitfield;
            _Uint32t __reserved[3];
	} tmr [8];

/*200*/	struct { /* Interrupt Request Register */
/*270*/     _Uint32t bitfield;
            _Uint32t __reserved[3];
	} irr [8];

/*280*/	union { /* Error Status Register */
            struct {
                _Uint32t send_cs_error			:  1,
                        receive_cs_error		:  1,
                        send_accept_error		:  1,
                        receive_accept_error		:  1,
                        __reserved_1			:  1,
                        send_illegal_vector		:  1,
                        receive_illegal_vector		:  1,
                        illegal_register_address	:  1,
                        __reserved_2			: 24;
                _Uint32t __reserved_3[3];
            } error_bits;
            struct {
                _Uint32t errors;
                _Uint32t __reserved_3[3];
            } all_errors;
	} esr;

/*290*/	struct { _Uint32t __reserved[4]; } __reserved_08;

/*2A0*/	struct { _Uint32t __reserved[4]; } __reserved_09;

/*2B0*/	struct { _Uint32t __reserved[4]; } __reserved_10;

/*2C0*/	struct { _Uint32t __reserved[4]; } __reserved_11;

/*2D0*/	struct { _Uint32t __reserved[4]; } __reserved_12;

/*2E0*/	struct { _Uint32t __reserved[4]; } __reserved_13;

/*2F0*/	struct { _Uint32t __reserved[4]; } __reserved_14;

/*300*/	struct { /* Interrupt Command Register 1 */
            _Uint32t vector : 8,
                    delivery_mode : 3,
                    destination_mode : 1,
                    delivery_status : 1,
                    __reserved_1 : 1,
                    level : 1,
                    trigger : 1,
                    __reserved_2 : 2,
                    shorthand : 2,
                    __reserved_3 : 12;
            _Uint32t __reserved_4[3];
	} icr1;

/*310*/	struct { /* Interrupt Command Register 2 */
            union {
                _Uint32t __reserved_1 : 24,
                        phys_dest : 4,
                        __reserved_2 : 4;
                _Uint32t __reserved_3 : 24,
                        logical_dest : 8;
            } dest;
            _Uint32t __reserved_4[3];
	} icr2;

/*320*/	struct { /* LVT - Timer */
            _Uint32t vector : 8,
                    __reserved_1 : 4,
                    delivery_status : 1,
                    __reserved_2 : 3,
                    mask : 1,
                    timer_mode : 1,
                    __reserved_3 : 14;
            _Uint32t __reserved_4[3];
	} lvt_timer;

/*330*/	struct { /* LVT - Thermal Sensor */
            _Uint32t vector : 8,
                    delivery_mode : 3,
                    __reserved_1 : 1,
                    delivery_status : 1,
                    __reserved_2 : 3,
                    mask : 1,
                    __reserved_3 : 15;
            _Uint32t __reserved_4[3];
	} lvt_thermal;

/*340*/	struct { /* LVT - Performance Counter */
            _Uint32t vector : 8,
                    delivery_mode : 3,
                    __reserved_1 : 1,
                    delivery_status : 1,
                    __reserved_2 : 3,
                    mask : 1,
                    __reserved_3 : 15;
            _Uint32t __reserved_4[3];
	} lvt_pc;

/*350*/	struct { /* LVT - LINT0 */
            _Uint32t vector : 8,
                    delivery_mode : 3,
                    __reserved_1 : 1,
                    delivery_status : 1,
                    polarity : 1,
                    remote_irr : 1,
                    trigger : 1,
                    mask : 1,
                    __reserved_2 : 15;
            _Uint32t __reserved_3[3];
	} lvt_lint0;

/*360*/	struct { /* LVT - LINT1 */
            _Uint32t vector : 8,
                    delivery_mode : 3,
                    __reserved_1 : 1,
                    delivery_status : 1,
                    polarity : 1,
                    remote_irr : 1,
                    trigger : 1,
                    mask : 1,
                    __reserved_2 : 15;
            _Uint32t __reserved_3[3];
	} lvt_lint1;

/*370*/	struct { /* LVT - Error */
            _Uint32t vector : 8,
                    __reserved_1 : 4,
                    delivery_status : 1,
                    __reserved_2 : 3,
                    mask : 1,
                    __reserved_3 : 15;
            _Uint32t __reserved_4[3];
	} lvt_error;

/*380*/	struct { /* Timer Initial Count Register */
            _Uint32t initial_count;
            _Uint32t __reserved_2[3];
	} timer_icr;

/*390*/	const struct { /* Timer Current Count Register */
            _Uint32t curr_count;
            _Uint32t __reserved_2[3];
	} timer_ccr;

/*3A0*/	struct { _Uint32t __reserved[4]; } __reserved_16;

/*3B0*/	struct { _Uint32t __reserved[4]; } __reserved_17;

/*3C0*/	struct { _Uint32t __reserved[4]; } __reserved_18;

/*3D0*/	struct { _Uint32t __reserved[4]; } __reserved_19;

/*3E0*/	struct { /* Timer Divide Configuration Register */
            _Uint32t divisor : 4,
                    __reserved_1 : 28;
            _Uint32t __reserved_2[3];
	} timer_dcr;

/*3F0*/	struct { _Uint32t __reserved[4]; } __reserved_20;
}__attribute__((packed)); 

enum ioapic_destination_types {
    dm_Fixed        = 0,
    dm_LowestPrio   = 1,
    dm_SMI          = 2,
    dm_reserved_1   = 3,
    dm_NMI          = 4,
    dm_INIT         = 5,
    dm_reserved_2   = 6,
    dm_ExtINT       = 7
};
#endif /* ARCH_X86_APIC_DEFS_H */