;/////////////////////////////////////////////////////////////////////////////////
;// Code Generator: BoostC Compiler - http://www.sourceboost.com
;// Version       : 7.20
;// License Type  : Pro License
;// Limitations   : PIC12,PIC16 max code size:Unlimited, max RAM banks:Unlimited
;/////////////////////////////////////////////////////////////////////////////////

	include "P16F876.inc"
; Heap block 0, size:111 (0x00000110 - 0x0000017E)
__HEAP_BLOCK0_BANK               EQU	0x00000002
__HEAP_BLOCK0_START_OFFSET       EQU	0x00000010
__HEAP_BLOCK0_END_OFFSET         EQU	0x0000007E
; Heap block 1, size:96 (0x00000190 - 0x000001EF)
__HEAP_BLOCK1_BANK               EQU	0x00000003
__HEAP_BLOCK1_START_OFFSET       EQU	0x00000010
__HEAP_BLOCK1_END_OFFSET         EQU	0x0000006F
; Heap block 2, size:80 (0x000000A0 - 0x000000EF)
__HEAP_BLOCK2_BANK               EQU	0x00000001
__HEAP_BLOCK2_START_OFFSET       EQU	0x00000020
__HEAP_BLOCK2_END_OFFSET         EQU	0x0000006F
; Heap block 3, size:69 (0x0000002B - 0x0000006F)
__HEAP_BLOCK3_BANK               EQU	0x00000000
__HEAP_BLOCK3_START_OFFSET       EQU	0x0000002B
__HEAP_BLOCK3_END_OFFSET         EQU	0x0000006F
gbl_status                       EQU	0x00000003 ; bytes:1
gbl_indf                         EQU	0x00000000 ; bytes:1
gbl_tmr0                         EQU	0x00000001 ; bytes:1
gbl_pcl                          EQU	0x00000002 ; bytes:1
gbl_fsr                          EQU	0x00000004 ; bytes:1
gbl_porta                        EQU	0x00000005 ; bytes:1
gbl_portb                        EQU	0x00000006 ; bytes:1
gbl_portc                        EQU	0x00000007 ; bytes:1
gbl_pclath                       EQU	0x0000000A ; bytes:1
gbl_intcon                       EQU	0x0000000B ; bytes:1
gbl_pir1                         EQU	0x0000000C ; bytes:1
gbl_pir2                         EQU	0x0000000D ; bytes:1
gbl_tmr1l                        EQU	0x0000000E ; bytes:1
gbl_tmr1h                        EQU	0x0000000F ; bytes:1
gbl_t1con                        EQU	0x00000010 ; bytes:1
gbl_tmr2                         EQU	0x00000011 ; bytes:1
gbl_t2con                        EQU	0x00000012 ; bytes:1
gbl_sspbuf                       EQU	0x00000013 ; bytes:1
gbl_sspcon                       EQU	0x00000014 ; bytes:1
gbl_ccpr1l                       EQU	0x00000015 ; bytes:1
gbl_ccpr1h                       EQU	0x00000016 ; bytes:1
gbl_ccp1con                      EQU	0x00000017 ; bytes:1
gbl_rcsta                        EQU	0x00000018 ; bytes:1
gbl_txreg                        EQU	0x00000019 ; bytes:1
gbl_rcreg                        EQU	0x0000001A ; bytes:1
gbl_ccpr2l                       EQU	0x0000001B ; bytes:1
gbl_ccpr2h                       EQU	0x0000001C ; bytes:1
gbl_ccp2con                      EQU	0x0000001D ; bytes:1
gbl_adresh                       EQU	0x0000001E ; bytes:1
gbl_adcon0                       EQU	0x0000001F ; bytes:1
gbl_option_reg                   EQU	0x00000081 ; bytes:1
gbl_trisa                        EQU	0x00000085 ; bytes:1
gbl_trisb                        EQU	0x00000086 ; bytes:1
gbl_trisc                        EQU	0x00000087 ; bytes:1
gbl_pie1                         EQU	0x0000008C ; bytes:1
gbl_pie2                         EQU	0x0000008D ; bytes:1
gbl_pcon                         EQU	0x0000008E ; bytes:1
gbl_sspcon2                      EQU	0x00000091 ; bytes:1
gbl_pr2                          EQU	0x00000092 ; bytes:1
gbl_sspadd                       EQU	0x00000093 ; bytes:1
gbl_sspstat                      EQU	0x00000094 ; bytes:1
gbl_txsta                        EQU	0x00000098 ; bytes:1
gbl_spbrg                        EQU	0x00000099 ; bytes:1
gbl_adresl                       EQU	0x0000009E ; bytes:1
gbl_adcon1                       EQU	0x0000009F ; bytes:1
gbl_eedata                       EQU	0x0000010C ; bytes:1
gbl_eeadr                        EQU	0x0000010D ; bytes:1
gbl_eedath                       EQU	0x0000010E ; bytes:1
gbl_eeadrh                       EQU	0x0000010F ; bytes:1
gbl_eecon1                       EQU	0x0000018C ; bytes:1
gbl_eecon2                       EQU	0x0000018D ; bytes:1
CompTempVarRet597                EQU	0x00000026 ; bytes:2
CompTempVar603                   EQU	0x00000025 ; bytes:1
UARTInit_00000_arg_Baud_Rate     EQU	0x00000025 ; bytes:1
CompTempVarRet604                EQU	0x0000002A ; bytes:1
UARTWriteB_00012_arg_Byte        EQU	0x00000025 ; bytes:1
gbl_Battery_Voltage              EQU	0x00000023 ; bytes:2
interrupt_1_Command              EQU	0x00000028 ; bytes:1
CompTempVar605                   EQU	0x00000029 ; bytes:1
delay_ms_00000_arg_del           EQU	0x00000026 ; bytes:1
delay_s_00000_arg_del            EQU	0x00000025 ; bytes:1
Int1Context                      EQU	0x0000007F ; bytes:1
Int1BContext                     EQU	0x00000020 ; bytes:3
	ORG 0x00000000
	GOTO	_startup
	ORG 0x00000004
	MOVWF Int1Context
	SWAPF STATUS, W
	BCF STATUS, RP0
	BCF STATUS, RP1
	MOVWF Int1BContext
	SWAPF PCLATH, W
	MOVWF Int1BContext+D'1'
	SWAPF FSR, W
	MOVWF Int1BContext+D'2'
	BCF PCLATH,3
	BCF PCLATH,4
	GOTO	interrupt
	ORG 0x00000010
delay_ms_00000
; { delay_ms ; function begin
	MOVF delay_ms_00000_arg_del, F
	BTFSS STATUS,Z
	GOTO	label1
	RETURN
label1
	MOVLW 0x99
label2
	NOP
	NOP
	ADDLW 0xFF
	BTFSS STATUS,Z
	GOTO	label2
	NOP
	DECFSZ delay_ms_00000_arg_del, F
	GOTO	label1
	RETURN
; } delay_ms function end

	ORG 0x0000001E
delay_s_00000
; { delay_s ; function begin
label3
	MOVLW 0xFA
	MOVWF delay_ms_00000_arg_del
	CALL delay_ms_00000
	MOVLW 0xFA
	MOVWF delay_ms_00000_arg_del
	CALL delay_ms_00000
	MOVLW 0xFA
	MOVWF delay_ms_00000_arg_del
	CALL delay_ms_00000
	MOVLW 0xFA
	MOVWF delay_ms_00000_arg_del
	CALL delay_ms_00000
	DECFSZ delay_s_00000_arg_del, F
	GOTO	label3
	RETURN
; } delay_s function end

	ORG 0x0000002D
UARTReadBy_00011
; { UARTReadByte ; function begin
label4
	BCF STATUS, RP0
	BCF STATUS, RP1
	BTFSS gbl_pir1,5
	GOTO	label4
	MOVF gbl_rcreg, W
	MOVWF CompTempVarRet604
	RETURN
; } UARTReadByte function end

	ORG 0x00000034
UARTWriteB_00012
; { UARTWriteByte ; function begin
label5
	BTFSS gbl_pir1,4
	GOTO	label5
	MOVF UARTWriteB_00012_arg_Byte, W
	MOVWF gbl_txreg
	RETURN
; } UARTWriteByte function end

	ORG 0x00000039
UARTInit_00000
; { UARTInit ; function begin
	BSF STATUS, RP0
	BSF gbl_trisc,7
	BSF gbl_trisc,6
	BCF STATUS, RP0
	MOVF UARTInit_00000_arg_Baud_Rate, W
	BSF STATUS, RP0
	MOVWF gbl_spbrg
	MOVLW 0x26
	MOVWF gbl_txsta
	MOVLW 0x90
	BCF STATUS, RP0
	MOVWF gbl_rcsta
	RETURN
; } UARTInit function end

	ORG 0x00000046
ADCReadWor_00013
; { ADCReadWord ; function begin
	BCF STATUS, RP0
	BCF STATUS, RP1
	BSF gbl_adcon0,2
label6
	BTFSC gbl_adcon0,2
	GOTO	label6
	CLRF CompTempVarRet597
	MOVF gbl_adresh, W
	MOVWF CompTempVar603
	MOVLW 0x00
	ANDWF CompTempVarRet597, F
	MOVF CompTempVar603, W
	ANDLW 0xFF
	MOVWF CompTempVarRet597+D'1'
	BSF STATUS, RP0
	MOVF gbl_adresl, W
	BCF STATUS, RP0
	IORWF CompTempVarRet597, F
	RETURN
; } ADCReadWord function end

	ORG 0x00000058
ADCInit_00000
; { ADCInit ; function begin
	BSF STATUS, RP0
	BCF STATUS, RP1
	BSF gbl_trisa,0
	MOVLW 0x8E
	MOVWF gbl_adcon1
	MOVLW 0x41
	BCF STATUS, RP0
	MOVWF gbl_adcon0
	RETURN
; } ADCInit function end

	ORG 0x00000061
main
; { main ; function begin
	BSF STATUS, RP0
	BCF STATUS, RP1
	CLRF gbl_trisb
	MOVLW 0x01
	BCF STATUS, RP0
	MOVWF UARTInit_00000_arg_Baud_Rate
	CALL UARTInit_00000
	CALL ADCInit_00000
	BCF gbl_portb,7
	CALL ADCReadWor_00013
	CALL ADCReadWor_00013
label7
	CALL UARTReadBy_00011
	MOVF CompTempVarRet604, W
	XORLW 0xCA
	BTFSS STATUS,Z
	GOTO	label7
	MOVLW 0xC0
	MOVWF gbl_intcon
label8
	BSF STATUS, RP0
	BCF gbl_pie1,5
	CALL ADCReadWor_00013
	MOVF CompTempVarRet597, W
	MOVWF gbl_Battery_Voltage
	MOVF CompTempVarRet597+D'1', W
	MOVWF gbl_Battery_Voltage+D'1'
	BSF STATUS, RP0
	BSF gbl_pie1,5
	MOVLW 0x01
	BCF STATUS, RP0
	MOVWF delay_s_00000_arg_del
	CALL delay_s_00000
	MOVF gbl_Battery_Voltage+D'1', W
	MOVWF UARTWriteB_00012_arg_Byte
	CALL UARTWriteB_00012
	MOVF gbl_Battery_Voltage, W
	MOVWF UARTWriteB_00012_arg_Byte
	CALL UARTWriteB_00012
	GOTO	label8
; } main function end

	ORG 0x00000087
_startup
	BCF PCLATH,3
	BCF PCLATH,4
	GOTO	main
	ORG 0x0000008A
interrupt
; { interrupt ; function begin
	BCF STATUS, RP0
	BCF STATUS, RP1
	BTFSS gbl_pir1,5
	GOTO	label12
	CALL UARTReadBy_00011
	MOVF CompTempVarRet604, W
	MOVWF interrupt_1_Command
	MOVLW 0xC0
	ANDWF interrupt_1_Command, W
	MOVWF CompTempVar605
	MOVF CompTempVar605, W
	XORLW 0x40
	BTFSS STATUS,Z
	GOTO	label11
	MOVLW 0x28
	ANDWF interrupt_1_Command, W
	BTFSC STATUS,Z
	GOTO	label10
	BSF gbl_portb,7
	GOTO	label11
label10
	BCF gbl_portb,7
label11
	BCF gbl_pir1,5
label12
	SWAPF Int1BContext+D'2', W
	MOVWF FSR
	SWAPF Int1BContext+D'1', W
	MOVWF PCLATH
	SWAPF Int1BContext, W
	MOVWF STATUS
	SWAPF Int1Context, F
	SWAPF Int1Context, W
	RETFIE
; } interrupt function end

	ORG 0x00002007
	DW 0x3F71
	END
