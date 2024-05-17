#ifndef MSR_H
#define MSR_H

#include <stdint.h>

uint64_t read_msr(int cpu, uint32_t msr);
void write_msr(int cpu, uint32_t msr, uint64_t value);

#endif // MSR_H
