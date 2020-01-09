#include "tss_switch.h"
#include "x86_desc.h"
#include "types.h"
uint32_t esp_holder;
uint32_t esp_array[6];
void switch_esp(int process_flag){
		if(process_flag > 0)
			esp_array[process_flag-1] = esp_holder;
		tss.esp0 = 0x800000-0x4-(0x2000*process_flag);
		tss.ss0 = 0x18;
}

void switch_esp_halt(int process_flag){
		tss.esp0 = esp_array[process_flag];
		tss.ss0 = 0x18;
}
