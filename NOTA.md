# ERROR: calling PR_SET_PTRACER, vgdb might block
**SOLUCION:** 
          echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope