# ERROR: calling PR_SET_PTRACER, vgdb might block
**SOLUCION:** 
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope


# Valgrind
valgrind ./principal


# Test propio
./principal < test/propio.in > test/salidas/popio.sal
diff test/propio.out test/salidas/popio.sal