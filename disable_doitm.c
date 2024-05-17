#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "doitm.h"

int main() {
    if (getuid() != 0) {
        fprintf(stderr, "This program must be run as root.\n");
        return 1;
    }

    int cpu = 0;
    disable_doitm(cpu);
    if (is_doitm_enabled(cpu)) {
        printf("Err: DOIT mode is enabled on CPU %d.\n", cpu);
    } else {
        printf("Ok: DOIT mode is disabled on CPU %d.\n", cpu);
    }

    return 0;
}
