#ifndef IDT_H
#define IDT_H
#include "multiboot.h"
#include "x86_desc.h"
#include "lib.h"
#include "i8259.h"
#include "debug.h"
#include "tests.h"

#define SYS_CALL     0x80
#define PIT          0x20
#define KEYBOARD     0x21
#define IRQ3         0x23
#define IRQ4         0x24
#define IRQ5         0x25
#define IRQ6         0x26
#define IRQ7         0x27
#define RTC          0x28
#define LOW_PRIV     3
#define HIGH_PRIV    0
#define DE_IDT       0
#define DB_IDT       1
#define NMI_IDT      2
#define BP_IDT       3
#define OF_IDT       4
#define BR_IDT       5
#define UD_IDT       6
#define NM_IDT       7
#define DF_IDT       8
#define CSO_IDT      9
#define TS_IDT       10
#define NP_IDT       11
#define SS_IDT       12
#define GP_IDT       13
#define PF_IDT       14
#define MF_IDT       16
#define AC_IDT       17
#define MC_IDT       18
#define XF_IDT       19
#define HALT_NUM     127

//function to initialize the IDT by setting up the IDT entires
void idt_init();

#endif
