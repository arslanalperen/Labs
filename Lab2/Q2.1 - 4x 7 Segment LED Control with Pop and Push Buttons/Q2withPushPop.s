 // Q2.s
 // Author: Alperen Arslan

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
.equ GPIOB_ODR,        (GPIOB_BASE + (0x14)) // GPIOB =DR register offset

.equ GPIOA_BASE,       (0x50000000)          // GPIOA base address
.equ GPIOA_MODER,      (GPIOA_BASE + (0x00)) // GPIOA MODER register offset
.equ GPIOA_ODR,        (GPIOA_BASE + (0x14)) // GPIOA ODR register offset

//Delay Interval
.equ delayInterval, 1600000

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
	movs r4, 0x3
	orrs r5, r5, r4
	str r5, [r6]

	// setup PA8, PA9, PA10 and PA15 for 01 in MODER
	ldr r6, =GPIOA_MODER
	ldr r5, [r6]
	// cannot do with movs, so use pc relative
	ldr r4, =[0x7FD50000] //All PA pins used define output
	ands r5, r5, r4
	str r5, [r6]

	// setup PB0, PB1, PB2 ....PB9 for 01 and PB5 for 00 in MODER
	ldr r6, =GPIOB_MODER
	ldr r5, [r6]
	// cannot do with movs, so use pc relative
	ldr r4, =[0x55055] //PB5 pin define input, others used pins define output
	ands r5, r5, r4
	str r5, [r6]

	//D1 Active
	ldr r6, =GPIOA_ODR
	ldr r5, [r6]
	ldr r4, =[0x0700]
	orrs r5, r5, r4
	str r5, [r6]

	movs r2, [0x0]
	movs r3, [0x0]

	loop:
	ldr r6, = GPIOB_IDR
	ldr r5, [r6] //For PB5, Pass Button
	ldr r7, [r6] //For PB4, Countdown button
	movs r4, #0x20 //Status switch connected to PB5
	ands r5, r5, r4 //Getting the value of button pressed or not
	lsrs r5, #5 //Shifting to lsb for compare
	cmp r5, #0x1 //Compare IDR Value with 1 bit
	beq changeNumber //If equal
	/*
	movs r4, #0x10 //Status switch connected to PB4
	ands r7, r7, r4 //Getting the value of button pressed or not
	lsrs r7, #4 //Shifting to lsb for compare
	cmp r7, #0x1 //Compare IDR Value with 1 bit
	beq countdown //If equal
	*/
	b loop

/*------------------------------------*/

	changeNumber:
	push {lr}
	bl Delay
	cmp r2, [0x0]
	beq FirstNumber
	cmp r2, [0x1]
	beq SecondNumber
	cmp r2, [0x2]
	beq ThirdNumber
	b loop

	FirstNumber:
	movs r3, [0x1]
	bl NumberSelect
	movs r2, [0x1]
	b loop

	SecondNumber:
	movs r3, [0x5]
	bl NumberSelect
	movs r2, [0x2]
	b loop

	ThirdNumber:
	movs r3, [0x9]
	bl NumberSelect
	movs r2, [0x0]
	b loop

/*---------------------------------------------------------*/

	Delay: //Delay for program work slowly
	ldr r1, =delayInterval
	delay:
	subs r1, r1, #1
	bne delay
	bx lr

/*----------------------------------------------------------*/

	NumberSelect:
	push {lr}
	bl ResetDigit
	cmp r3, [0x0] //Control r3 for which number sent to NumberSelect
	beq NumberZero
	cmp r3, [0x1]
	beq NumberOne
	cmp r3, [0x2]
	beq NumberTwo
	cmp r3, [0x3]
	beq NumberThree
	cmp r3, [0x4]
	beq NumberFour
	cmp r3, [0x5]
	beq NumberFive
	cmp r3, [0x6]
	beq NumberSix
	cmp r3, [0x7]
	beq NumberSeven
	cmp r3, [0x8]
	beq NumberEight
	cmp r3, [0x9]
	beq NumberNine
	bx lr

	NumberZero: //Display the number sent
	ldr r4, =[0x1C7]
	b toLedsOn

	NumberOne:
	ldr r4, =[0x42]
	b toLedsOn

	NumberTwo:
	ldr r4, =[0x2C5]
	b toLedsOn

	NumberThree:
	ldr r4, =[0x2C3]
	b toLedsOn

	NumberFour:
	ldr r4, =[0x342]
	b toLedsOn

	NumberFive:
	ldr r4, =[0x383]
	b toLedsOn

	NumberSix:
	ldr r4, =[0x387]
	b toLedsOn

	NumberSeven:
	ldr r4, =[0xC2]
	b toLedsOn

	NumberEight:
	ldr r4, =[0x3C7]
	b toLedsOn

	NumberNine:
	ldr r4, =[0x3C3]
	b toLedsOn

	toLedsOn:
	bl LedsOn
	pop {pc}

/*-----------------------------------------*/

	LedsOn:
	push {lr}
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	orrs r5, r5, r4
	str r5, [r6]
	pop {pc}

/*-----------------------------------------*/

	ResetDigit:
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	ldr r4, =[0xFF7]
	bics r5, r5, r4
	str r5, [r6]
	bx lr

/*-----------------------------------------*/

	// this should never get executed
	nop
