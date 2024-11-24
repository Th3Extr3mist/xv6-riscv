#include "kernel/types.h"
#include "user/user.h"

int main() {
    char *addr = sbrk(2 * PGSIZE);
    if (mprotect(addr, 1) < 0) {
        printf("mprotect failed\n");
        exit(1);
    }

    addr[0] = 'A'; // Esto debería fallar.
    printf("Should not reach here\n");

    if (munprotect(addr, 1) < 0) {
        printf("munprotect failed\n");
        exit(1);
    }

    addr[0] = 'B'; // Esto debería funcionar.
    printf("Memory write succeeded\n");
    exit(0);
}
