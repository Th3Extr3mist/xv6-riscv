#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "defs.h"

uint64
sys_getppid(void) 
{

    return myproc()->parent->pid; // Retorna el PID del proceso padre
    
}

uint64
sys_getancestor(void) {
    int n;
    argint(0, &n); // Lee el argumento n pasado a la syscall

    struct proc *p = myproc(); // Obtiene el proceso actual

    // Itera hacia atrás en la cadena de ancestros
    for (int i = 0; i < n; i++) {
        if (p->parent == 0) // Si no hay ancestro válido, retorna -1
            return -1;
        p = p->parent;
    }

    return p->pid; // Retorna el PID del ancestro encontrado
}
