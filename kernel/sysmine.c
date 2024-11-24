#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "defs.h"

uint64
sys_mprotect(void)
{
  uint64 addr;
  int len;

  // Extraer los argumentos
  argaddr(0, &addr);
  argint(1, &len);

  // Validar los argumentos
  if (addr % PGSIZE != 0 || len <= 0 || addr + len * PGSIZE > myproc()->sz)
    return -1;

  // Implementar protección de memoria
  for (uint64 a = addr; a < addr + len * PGSIZE; a += PGSIZE) {
    pte_t *pte = walk(myproc()->pagetable, a, 0);
    if (pte == 0 || (*pte & PTE_V) == 0)
      return -1;

    *pte &= ~PTE_W; // Deshabilitar escritura
  }

  sfence_vma(); // Sincronizar cambios
  return 0;
}

uint64
sys_munprotect(void)
{
  uint64 addr;
  int len;

  // Extraer los argumentos
  argaddr(0, &addr);
  argint(1, &len);

  // Validar los argumentos
  if (addr % PGSIZE != 0 || len <= 0 || addr + len * PGSIZE > myproc()->sz)
    return -1;

  // Revertir la protección de memoria
  for (uint64 a = addr; a < addr + len * PGSIZE; a += PGSIZE) {
    pte_t *pte = walk(myproc()->pagetable, a, 0);
    if (pte == 0 || (*pte & PTE_V) == 0)
      return -1;

    *pte |= PTE_W; // Habilitar escritura
  }

  sfence_vma(); // Sincronizar cambios
  return 0;
}