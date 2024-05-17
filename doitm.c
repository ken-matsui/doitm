#include "doitm.h"
#include "msr.h"

#define MSR_IA32_UARCH_MISC_CTL 0x1B01
#define DOITM_BIT (1ULL << 0)

void enable_doitm(int cpu) {
    uint64_t msr_value;
    msr_value = read_msr(cpu, MSR_IA32_UARCH_MISC_CTL);
    msr_value |= DOITM_BIT;
    write_msr(cpu, MSR_IA32_UARCH_MISC_CTL, msr_value);
}

void disable_doitm(int cpu) {
    uint64_t msr_value;
    msr_value = read_msr(cpu, MSR_IA32_UARCH_MISC_CTL);
    msr_value &= ~DOITM_BIT;
    write_msr(cpu, MSR_IA32_UARCH_MISC_CTL, msr_value);
}

int is_doitm_enabled(int cpu) {
    uint64_t msr_value;
    msr_value = read_msr(cpu, MSR_IA32_UARCH_MISC_CTL);
    return (msr_value & DOITM_BIT) != 0;
}
