# 1 "../arch/arm_m_gcc/common/core_support.S"
# 1 "C:\\cygwin64\\home\\hiro2\\TECS\\asp3\\asp3_stm32h747_discovery\\obj_h747//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "../arch/arm_m_gcc/common/core_support.S"
# 52 "../arch/arm_m_gcc/common/core_support.S"
# 1 "../kernel/kernel_impl.h" 1
# 60 "../kernel/kernel_impl.h"
# 1 "../kernel/kernel_rename.h" 1
# 198 "../kernel/kernel_rename.h"
# 1 "../target/stm32h747_discovery_m7/target_rename.h" 1
# 24 "../target/stm32h747_discovery_m7/target_rename.h"
# 1 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_rename.h" 1
# 12 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_rename.h"
# 1 "../arch/arm_m_gcc/common/core_rename.h" 1
# 13 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_rename.h" 2
# 25 "../target/stm32h747_discovery_m7/target_rename.h" 2
# 199 "../kernel/kernel_rename.h" 2
# 61 "../kernel/kernel_impl.h" 2




# 1 "../include/kernel.h" 1
# 64 "../include/kernel.h"
# 1 "../include/t_stddef.h" 1
# 65 "../include/t_stddef.h"
# 1 "../target/stm32h747_discovery_m7/target_stddef.h" 1
# 65 "../target/stm32h747_discovery_m7/target_stddef.h"
# 1 "../arch/gcc/tool_stddef.h" 1
# 66 "../target/stm32h747_discovery_m7/target_stddef.h" 2




# 1 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_stddef.h" 1
# 59 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_stddef.h"
# 1 "../arch/arm_m_gcc/common/core_stddef.h" 1
# 60 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_stddef.h" 2
# 71 "../target/stm32h747_discovery_m7/target_stddef.h" 2
# 66 "../include/t_stddef.h" 2
# 65 "../include/kernel.h" 2




# 1 "../target/stm32h747_discovery_m7/target_kernel.h" 1
# 71 "../target/stm32h747_discovery_m7/target_kernel.h"
# 1 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_kernel.h" 1
# 78 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_kernel.h"
# 1 "../arch/arm_m_gcc/common/core_kernel.h" 1
# 79 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_kernel.h" 2
# 72 "../target/stm32h747_discovery_m7/target_kernel.h" 2
# 70 "../include/kernel.h" 2
# 66 "../kernel/kernel_impl.h" 2




# 1 "../include/t_syslog.h" 1
# 71 "../kernel/kernel_impl.h" 2
# 82 "../kernel/kernel_impl.h"
# 1 "../target/stm32h747_discovery_m7/target_kernel_impl.h" 1
# 50 "../target/stm32h747_discovery_m7/target_kernel_impl.h"
# 1 "../target/stm32h747_discovery_m7/discovery_h747.h" 1
# 51 "../target/stm32h747_discovery_m7/target_kernel_impl.h" 2




# 1 "../include/sil.h" 1
# 68 "../include/sil.h"
# 1 "../target/stm32h747_discovery_m7/target_sil.h" 1
# 54 "../target/stm32h747_discovery_m7/target_sil.h"
# 1 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_sil.h" 1
# 65 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_sil.h"
# 1 "../arch/arm_m_gcc/common/core_sil.h" 1
# 66 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_sil.h" 2
# 55 "../target/stm32h747_discovery_m7/target_sil.h" 2
# 69 "../include/sil.h" 2
# 56 "../target/stm32h747_discovery_m7/target_kernel_impl.h" 2
# 97 "../target/stm32h747_discovery_m7/target_kernel_impl.h"
# 1 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_kernel_impl.h" 1
# 62 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_kernel_impl.h"
# 1 "../arch/arm_m_gcc/common/core_kernel_impl.h" 1
# 63 "../arch/arm_m_gcc/stm32h7xx_stm32cube/chip_kernel_impl.h" 2
# 98 "../target/stm32h747_discovery_m7/target_kernel_impl.h" 2
# 83 "../kernel/kernel_impl.h" 2





# 1 "../kernel/allfunc.h" 1
# 89 "../kernel/kernel_impl.h" 2
# 53 "../arch/arm_m_gcc/common/core_support.S" 2
# 1 "../arch/arm_m_gcc/common/arm_m.h" 1
# 54 "../arch/arm_m_gcc/common/core_support.S" 2
# 1 "./offset.h" 1
# 55 "../arch/arm_m_gcc/common/core_support.S" 2
# 1 "../target/stm32h747_discovery_m7/target_asm.inc" 1
# 1 "../arch/arm_m_gcc/common/core_asm.inc" 1
# 49 "../arch/arm_m_gcc/common/core_asm.inc"
.macro __athumb name
 .syntax unified
 .thumb
 .thumb_func
 .type name, function
.endm
# 1 "../target/stm32h747_discovery_m7/target_asm.inc" 2
# 56 "../arch/arm_m_gcc/common/core_support.S" 2




 .align 2
 .text
 __athumb _kernel_core_exc_entry
 .global _kernel_core_exc_entry
_kernel_core_exc_entry:
# 93 "../arch/arm_m_gcc/common/core_support.S"
 mrs r1, basepri
 mrs r2, primask
 orr r1, r1, r2, lsl #8
 tst lr, #0x4
 beq core_exc_entry_1

 mrs r0, psp
 stmfd r0!, {r1, lr}
 push {r1, lr}
 b core_exc_entry_2
core_exc_entry_1:

 push {r1, lr}
 mov r0, sp
core_exc_entry_2:

 ldr r2, =_kernel_lock_flag
 ldr r3, [r2]
 push {r2, r3}
# 126 "../arch/arm_m_gcc/common/core_support.S"
 mrs r3, ipsr
 ldr r1, =_kernel_exc_tbl
 ldr r2, [r1, r3, lsl #2]

 blx r2
# 139 "../arch/arm_m_gcc/common/core_support.S"
 pop {r0-r3}
 str r1, [r0]
 msr basepri, r2
 bx r3




 __athumb _kernel_pendsv_handler
 .global _kernel_pendsv_handler
_kernel_pendsv_handler:

 mov r0, #(((1 << 4) - (-((-15)))) << (8 - 4))
 msr basepri, r0
 ldr r1, =_kernel_p_runtsk
 ldr r0, [r1]

 cbz r0, pendsv_handler_1

 mrs r2, psp

 tst lr, #0x10
 bne pendsv_handler_0
 vstmdb r2!, {s16-s31}

pendsv_handler_0:

 stmfd r2!, {r4-r11}
 str r2, [r0, #24]
 str lr, [r0, #28]
pendsv_handler_1:
# 180 "../arch/arm_m_gcc/common/core_support.S"
 ldr r0, =_kernel_p_schedtsk
 ldr r0, [r0]
 str r0, [r1]
 cbz r0, return_to_idle
# 194 "../arch/arm_m_gcc/common/core_support.S"
 ldr r1, [r0, #28]
 and r2, r1, #0xff000000
 cmp r2, #0xff000000
 bne return_to_thread


 push {r0-r3}
 mov r0, #10
 bl led_set
 mov r0, #10
 bl print_p_run
 pop {r0-r3}


 ldr r2, [r0, #24]
 ldmfd r2!, {r4-r11}

 tst r1, #0x10
 bne pendsv_handler_2
 vldmia r2!, {s16-s31}
pendsv_handler_2:

 msr psp, r2





 mov r0, #(0)
 cpsid f
 msr basepri, r0
 bx r1
return_to_idle:
 mrs r0, psp
 ldr r1, =idle_loop
 ldr r2, =#0x01000000
 stmfd r0!, {r1, r2}
 sub r0, #(4 * 6)
 msr psp, r0






.align 2

 ldr pc, [pc]
 .word 0xfffffffd



return_to_thread:

################
 push {r0-r3}
 mov r0, #9
 bl led_set
 mov r0, #9
 bl print_p_run
 pop {r0-r3}
 ###############

# 263 "../arch/arm_m_gcc/common/core_support.S"
 ldr r2, [r0, #36]
 cbz r2, return_to_thread_no_fp
 ldr r2, =return_to_thread_fp
 ldr r3, =#0x01000000
 ldr r0, [r0, #24]
 ldmfd r0!, {r4-r11}
 stmfd r0!, {r1-r3}
 sub r0, #(4 * 5)
 b return_to_thread_0
return_to_thread_no_fp:

 ldr r0, [r0, #24]
 ldmfd r0!, {r4-r11}
 ldr r2, =#0x01000000
 stmfd r0!, {r1, r2}
 sub r0, #(4 * 6)

return_to_thread_0:

 msr psp, r0

 ldr r0, =_kernel_lock_flag
 mov r1, #1
 str r1, [r0]
 dsb
.align 2







 ldr lr, =#0xfffffffd
 bx lr






return_to_thread_fp:

 vpop {s16-s31}
 bx lr
# 317 "../arch/arm_m_gcc/common/core_support.S"
 __athumb _kernel_svc_handler
 .global _kernel_svc_handler
_kernel_svc_handler:






 push {r0-r3}
 mov r0, #11
 bl led_set
 mov r0, #11
 bl print_p_run
 pop {r0-r3}



 ldr r0, =_kernel_lock_flag
 mov r1, #0
 str r1, [r0]
 ldr r0, =#(0)
 msr basepri, r0




 ldr r0, [r4, #24]
 mov r1, r5
 ldmfd r0!, {r4-r11}

 tst r1, #0x10
 bne svc_handler_0
 vldmia r0!, {s16-s31}
svc_handler_0:

 msr psp, r0
 bx r1




 __athumb _kernel_start_dispatch
 .global _kernel_start_dispatch
_kernel_start_dispatch:
# 378 "../arch/arm_m_gcc/common/core_support.S"
 ldr r0, =_kernel_istkpt
 ldr r1, [r0]
 msr msp, r1



 mov r0, #0x02
 msr control, r0
 isb
 ldr r1, =_kernel_tinib_table
 ldr sp, [r1, #20]


 ldr r1, =_kernel_p_schedtsk
 ldr r1, [r1]
 ldr r2, =_kernel_p_runtsk

 cpsie f
 b dispatcher_0




 __athumb _kernel_exit_and_dispatch
 .global _kernel_exit_and_dispatch
_kernel_exit_and_dispatch:

 ldr r1, =_kernel_p_schedtsk
 ldr r1, [r1]
 ldr r2, =_kernel_p_runtsk
 b dispatcher_0
# 417 "../arch/arm_m_gcc/common/core_support.S"
 __athumb _kernel_do_dispatch
 .global _kernel_do_dispatch
_kernel_do_dispatch:

 mrs r3, control
 and r3, #0x04
 cbz r3, dispatch_1
 vpush {s16-s31}
 mov r3, #0x02
 msr control, r3
 isb
dispatch_1:

 str r3, [r0, #36]

 push {r4-r11}
 str lr, [r0, #28]
 str sp, [r0, #24]
dispatcher_0:







 push {r0-r3}
 mov r0, #12
 bl led_set
 mov r0, #12
 bl print_p_run
 pop {r0-r3}


 str r1, [r2]
 cbz r1, idle_loop
 ldr r2, [r1, #28]

 and r0, r2, #0xff000000
 cmp r0, #0xff000000
 bne _kernel_dispatcher_1


 push {r0-r3}
 mov r0, #13
 bl led_set
 mov r0, #13
 bl print_p_run
 pop {r0-r3}



 mov r4, r1
 mov r5, r2
 svc #0







_kernel_dispatcher_1:


 push {r0-r3}
 mov r0, #14
 bl led_set
 mov r0, #14
 bl print_p_run
 pop {r0-r3}
# 509 "../arch/arm_m_gcc/common/core_support.S"
 ldr sp, [r1, #24]

 pop {r4-r11}

 ldr r3, [r1, #36]
 cbz r3, dispatcher_2
 vpop {s16-s31}
dispatcher_2:

 bx r2

idle_loop:




 ldr r0, =_kernel_lock_flag
 mov r1, #0
 str r1, [r0]
 dsb
 ldr r0, =#(0)
 msr basepri, r0
_idle_loop_1:







 dsb
 wfi
 b _idle_loop_1
 nop





 __athumb _kernel_start_r
 .global _kernel_start_r
_kernel_start_r:




 ldr r0, =_kernel_lock_flag
 mov r1, #0
 str r1, [r0]
 dsb
 ldr r0, =#(0)
 msr basepri, r0
 ldr r0, =_kernel_p_runtsk
 ldr r1, [r0]
 ldr r2, [r1, #8]
 ldr r0, [r2, #4]
 ldr lr, =ext_tsk
 ldr pc, [r2, #8]







 __athumb _kernel_call_exit_kernel
 .global _kernel_call_exit_kernel
_kernel_call_exit_kernel:
 mov r1, #0x00
 msr control, r1
 isb
 b _kernel_exit_kernel




 .align 2
 .text
 __athumb sil_dly_nse
 .global sil_dly_nse
sil_dly_nse:
 sub r0, r0, #162
 cmp r0, #0
 bgt sil_dly_nse1
 bx lr
sil_dly_nse1:
 sub r0, r0, #100
 cmp r0, #0
 bgt sil_dly_nse1
 bx lr
