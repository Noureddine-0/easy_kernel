#ifndef __VERSION_H
#define __VERSION_H

#include <stdint.h>

uint32_t kversion ;

void set_kversion(uint32_t major , uint32_t minor , uint32_t patch){
	kversion &=((1 <<11) - 1);
    kversion |= (((major & 0x7f) << 25) | ((minor & 0x7f) << 18) | ((patch & 0x7f) << 11));
}

void set_patchlevel(unsigned year, unsigned month) {
    kversion &= ~((1 << 11) - 1);
    os_version |= (((year - 2000) & 0x7f) << 4) | ((month & 0xf) << 0);
}