.include "asm/exe3.asm"
.definelabel addr_main_hook, 0x08000324
.definelabel addr_rng_hook, 0x0800164C
.definelabel addr_font, 0x0867A180
.definelabel FREE_SPACE, 0x087FF814

.gba
.open ROM_IN, ROM_OUT, 0x08000000

// hook end of main function to call our c function
.org addr_main_hook
    dw main_trampoline|1

// Reset RNG on soft reset
.org addr_rng_hook
	ldr r0,=ResetRngIndex|1
	bx r0
	.pool

// Increase RNG index and delta
.org addr_rng_hook+0xC
	ldr	r0,=UpdateRngIndex|1
	mov	r14,r15
	bx	r0
	b	.+0x8
	.pool

// Increase RNG index and delta
.org addr_rng_hook+0x22
	ldr	r0,=UpdateRngIndex|1
	mov	r14,r15
	bx	r0
	b	.+0x8
	.pool

// Increase RNG index and delta
.org addr_rng_hook+0x3C
	ldr	r0,=UpdateRngIndex|1
	mov	r14,r15
	bx	r0
	b	.+0x8
	.pool

// Increase RNG index and delta
.org addr_rng_hook+0x52
	ldr	r0,=UpdateRngIndex|1
	mov	r14,r15
	bx	r0
	b	.+0x8
	.pool

.org addr_font
.area 0x800
	.import	"res\font.bin"
.endarea
.pool

.org FREE_SPACE
.align 2
ResetRngIndex:
	b hooked_rng_reset

// eventually replace this entirely with a c function
.align 2
UpdateRngIndex:
	push r14

	// pass RNG address (which is in r7 currently) as param to hooked_rng
	mov r0, r7
	bl hooked_rng

    // overwritten normal RNG function
    ldr r0, [r7]
	ldr	r1,=0x873CA9E5
	lsl	r2,r0,0x1
	lsr	r3,r0,0x1F
	add	r0,r2,r3
	add	r0,0x1
	eor	r0,r1

    pop r15

.align 2
main_trampoline:
    push r14

    // call C function
    bl hooked_main

    // overwritten code for the hook
    ldr	r0,=0x03006824|1
    mov	r14,r15
    bx	r0

    pop r15
    
.pool
.importlib LIB_IN
.close