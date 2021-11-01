Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

    THUMB

    AREA    RESET, DATA, READONLY
    EXPORT  __Vectors

__Vectors
    DCD     __initial_sp                   ; Top of Stack
    DCD     Reset_Handler                  ; Reset Handler
    DCD     NMI_Handler                    ; NMI Handler
    DCD     HardFault_Handler              ; Hard Fault Handler

    AREA    |.text|, CODE, READONLY
; nmi handler
NMI_Handler    PROC
    EXPORT  NMI_Handler
    B .
    ENDP


; hardfault handler
HardFault_Handler    PROC
    EXPORT  HardFault_Handler
    B .
    ENDP

; entry function
Reset_Handler    PROC
    EXPORT  Reset_Handler
    ; Edit below this line

    LDR     R1,=0x50000000      ; pointer to base of GPIOA
    LDR     R3,=0x00000100      ; set LED 1 on (bit 8 aka PA8 is 'one')
    STR     R3,[R1,#0x14]       ; set outputs directly (base+0x14)
	
    ; Edit above this line
    B .
    ENDP

    END
