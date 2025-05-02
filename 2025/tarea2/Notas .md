# Problemas con los test

- `LDEPerro2-crear-insertar-imprimir-liberar`  
- `LDEPerro3-crear-insertar-imprimir-liberar`  

A veces, si los corro con el `make`, lanza como si tuviera un error pero luego los testeo manualmente y funcionan correctamente.  
Desconozco el porqué.

---

## `LDEPerro2-crear-insertar-imprimir-liberar`

```bash
  seba@Raz:~/prog2/2025/tarea2$ ./principal < test/LDEPerro2-crear-insertar-imprimir-liberar.in > test/salidas/LDEPerro2-crear-insertar-imprimir-liberar.sal
  seba@Raz:~/prog2/2025/tarea2$ diff test/LDEPerro2-crear-insertar-imprimir-liberar.out test/salidas/LDEPerro2-crear-insertar-imprimir-liberar.sal
  seba@Raz:~/prog2/2025/tarea2$ make t-LDEPerro2-crear-insertar-imprimir-liberar 
  ---- Bien ----
  seba@Raz:~/prog2/2025/tarea2$ 
```

## `LDEPerro3-crear-insertar-imprimir-liberar`
```bash
  seba@Raz:~/prog2/2025/tarea2$ ./principal < test/LDEPerro3-crear-insertar-imprimir-liberar.in > test/salidas/LDEPerro3-crear-insertar-imprimir-liberar.sal
  seba@Raz:~/prog2/2025/tarea2$ diff test/LDEPerro3-crear-insertar-imprimir-liberar.out test/salidas/LDEPerro3-crear-insertar-imprimir-liberar.sal
  seba@Raz:~/prog2/2025/tarea2$ make t-LDEPerro3-crear-insertar-imprimir-liberar 
  ---- Bien ----
  seba@Raz:~/prog2/2025/tarea2$ 
```