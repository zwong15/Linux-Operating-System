#ifndef _TSS_SWITCH_H
#define _TSS_SWITCH_H

#include "x86_desc.h"
#include "types.h"
extern tss_t tss;

void switch_esp(int process_flag);
void switch_esp_halt(int process_flag);

#endif
