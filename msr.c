#include "msr.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>

// https://github.com/intel/msr-tools/blob/master/rdmsr.c

uint64_t read_msr(int cpu, uint32_t msr) {
    char msr_file_name[64];
    int fd;
    uint64_t data;

    sprintf(msr_file_name, "/dev/cpu/%d/msr", cpu);
    fd = open(msr_file_name, O_RDONLY);
    if (fd < 0) {
        if (errno == ENXIO) {
            fprintf(stderr, "rdmsr: No CPU %d\n", cpu);
            exit(2);
        } else if (errno == EIO) {
            fprintf(stderr, "rdmsr: CPU %d doesn't support MSRs\n", cpu);
            exit(3);
        } else {
            perror("rdmsr: open");
            exit(127);
        }
    }

    if (pread(fd, &data, sizeof data, msr) != sizeof data) {
        if (errno == EIO) {
            fprintf(stderr, "rdmsr: CPU %d cannot read MSR 0x%08" PRIx32 "\n", cpu, msr);
            exit(4);
        } else {
            perror("rdmsr: pread");
            exit(127);
        }
    }

    close(fd);
    return data;
}

void write_msr(int cpu, uint32_t msr, uint64_t value) {
    char msr_file_name[64];
    int fd;

    sprintf(msr_file_name, "/dev/cpu/%d/msr", cpu);
    fd = open(msr_file_name, O_WRONLY);
    if (fd < 0) {
        if (errno == ENXIO) {
            fprintf(stderr, "wrmsr: No CPU %d\n", cpu);
            exit(2);
        } else if (errno == EIO) {
            fprintf(stderr, "wrmsr: CPU %d doesn't support MSRs\n", cpu);
            exit(3);
        } else {
            perror("wrmsr: open");
            exit(127);
        }
    }

    if (pwrite(fd, &value, sizeof value, msr) != sizeof value) {
        if (errno == EIO) {
            fprintf(stderr, "wrmsr: CPU %d cannot write MSR 0x%08" PRIx32 "\n", cpu, msr);
            exit(4);
        } else {
            perror("wrmsr: pwrite");
            exit(127);
        }
    }

    close(fd);
}
