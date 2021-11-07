 // Q1.s
 // Author     : Furkan Cayci
 // Arrangement: Alperen Arslan

.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb

// make linker see this
.global Reset_Handler

// get these from linker script
.word _sdata
.word _edata
.word _sbss
.word _ebss

// define clock base and enable addresses
.equ RCC_BASE,         (0x40021000)          // RCC base address
.equ RCC_IOPENR,       (RCC_BASE   + (0x34)) // RCC IOPENR register offset

// define GPIO Base, Moder and ODR pin addresses
.equ GPIOB_BASE,       (0x50000400)          // GPIOB base address
.equ GPIOB_MODER,      (GPIOB_BASE + (0x00)) // GPIOB MODER register offset
.equ GPIOB_IDR,        (GPIOB_BASE + (0x10)) // GPIOB IDR register offset
.equ GPIOB_ODR,        (GPIOB_BASE + (0x14)) // GPIOB IDR register offset

//Delay Interval
.equ delayInterval, 0x30C008

// vector table, +1 thumb mode
.section .vectors
vector_table:
	.word _estack             //     Stack pointer
	.word Reset_Handler +1    //     Reset handler
	.word Default_Handler +1  //       NMI handler
	.word Default_Handler +1  // HardFault handler
	// add rest of them here if needed

// reset handler
.section .text
Reset_Handler:
	// set stack pointer
	ldr r0, =_estack
	mov sp, r0

	// initialize data and bss
	// not necessary for rom only code

	bl init_data
	// call main
	bl main
	// trap if returned
	b .

// initialize data and bss sections
.section .text
init_data:

	// copy rom to ram
	ldr r0, =_sdata
	ldr r1, =_edata
	ldr r2, =_sidata
	movs r3, #0
	b LoopCopyDataInit

	CopyDataInit:
		ldr r4, [r2, r3]
		str r4, [r0, r3]
		adds r3, r3, #4

	LoopCopyDataInit:
		adds r4, r0, r3
		cmp r4, r1
		bcc CopyDataInit

	// zero bss
	ldr r2, =_sbss
	ldr r4, =_ebss
	movs r3, #0
	b LoopFillZerobss

	FillZerobss:
		str  r3, [r2]
		adds r2, r2, #4

	LoopFillZerobss:
		cmp r2, r4
		bcc FillZerobss

	bx lr

// default handler
.section .text
Default_Handler:
	b Default_Handler

// main function
.section .text
main:
	// enable GPIOB clock, bit1 on IOPENR
	ldr r6, =RCC_IOPENR
	ldr r5, [r6]
	// movs expects imm8, so this should be fine
	movs r4, 0x2
	orrs r5, r5, r4
	str r5, [r6]

	// setup PB4 and PB5 for button and led 01 and 00 in MODER
	ldr r6, =GPIOB_MODER
	ldr r5, [r6]
	// cannot do with movs, so use pc relative
	ldr r5, =[0xFFFFF]
	str r5, [r6]
	ldr r4, =[0x5C555]
	ands r5, r5, r4
	str r5, [r6]

	bl statusLed

play:
	// 1. Katman
	ldr r4, =[0x100]
	bl ledsOn
	bl statusLed

	// 3. Katman
	ldr r4, =[0x304]
	bl ledsOn
	bl statusLed

	// 5. Katman
	ldr r4, =[0x325]
	bl ledsOn
	bl statusLed

	// 7. Katman
	ldr r4, =[0x337]
	bl ledsOn
	bl statusLed

	// Reset Katmanı
	ldr r4, =[0x000]
	bl ledsOn
	bl statusLed

	b play

pause:
	ldr r6, = GPIOB_ODR
	ldr r5, [r6] //ODR Value
	movs r4, 0x8
	orrs r5, r5, r4 //Setting led on
	str r5, [r6]

	b statusLed

	ledsOn:
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	cmp r4,0x0
	beq Reset
	bne On
	Reset:
	ands r5, r5, r4
	On:
	orrs r5, r5, r4
	str r5, [r6]
	// Assign value to register r1 to sub 1 per clock
	ldr r1, =delayInterval
	delay:
	subs r1, r1, #1
	bne delay
	bx lr

	statusLed:
	ldr r6, = GPIOB_IDR
	ldr r5, [r6] //IDR Value
	movs r4, #0x40
	ands r5, r5, r4 //Getting the value of button pressed or not
	lsrs r5, #6

	cmp r5, #0x1 //Compare IDR Value with 1 bit
	bne BNE //If not equal
	beq BEQ //If equal

	//If is equal
	BEQ:
	b pause

	//If is not equal
	BNE:
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	ldr r5, =[0x0]
	str r5, [r6]
	bx lr

	// this should never get executed
	//nop
