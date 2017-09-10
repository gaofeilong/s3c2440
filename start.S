/********************************************************************
 *
 * @ File Name  : start.S
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: first executed code after reset is here
 *
 * *****************************************************************/

.text
.align 4

.global _start
.extern _reset
.extern _undefined
.extern _swi
.extern _prefetch_abort
.extern _data_abort
.extern _reserved
.extern _irq
.extern _fiq            

_start:
        ldr     pc, _vector_reset
        ldr     pc, _vector_undefine
        ldr     pc, _vector_swi
        ldr     pc, _vector_prefetch_abort
        ldr     pc, _vector_data_abort
        ldr     pc, _vector_reserved
        ldr     pc, _vector_irq
        ldr     pc, _vector_fiq

_vector_reset:          .word _reset
_vector_undefine:       .word _undefined
_vector_swi:            .word _swi
_vector_prefetch_abort: .word _prefetch_abort
_vector_data_abort:     .word _data_abort
_vector_reserved:       .word _reserved
_vector_irq:            .word _irq
_vector_fiq:            .word _fiq             
