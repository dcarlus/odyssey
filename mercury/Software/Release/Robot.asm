;/////////////////////////////////////////////////////////////////////////////////
;// Code Generator: BoostC Compiler - http://www.sourceboost.com
;// Version       : 7.21
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
; Heap block 3, size:33 (0x0000004F - 0x0000006F)
__HEAP_BLOCK3_BANK               EQU	0x00000000
__HEAP_BLOCK3_START_OFFSET       EQU	0x0000004F
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
CompTempVarRet650                EQU	0x00000032 ; bytes:2
CompTempVar656                   EQU	0x00000031 ; bytes:1
EEPROMRead_0001B_arg_Address     EQU	0x00000031 ; bytes:1
CompTempVarRet657                EQU	0x00000036 ; bytes:2
EEPROMRead_0001B_1_Return_Value  EQU	0x00000032 ; bytes:2
EEPROMRead_0001B_1_High_Byte     EQU	0x00000034 ; bytes:1
EEPROMRead_0001B_1_Low_Byte      EQU	0x00000035 ; bytes:1
CompTempVarRet662                EQU	0x00000037 ; bytes:1
CompTempVar660                   EQU	0x00000036 ; bytes:1
CompTempVar661                   EQU	0x00000037 ; bytes:1
EEPROMWrit_0001C_arg_Address     EQU	0x00000040 ; bytes:1
EEPROMWrit_0001C_arg_Word        EQU	0x00000041 ; bytes:2
EEPROMRead_0001F_arg_Address     EQU	0x00000036 ; bytes:1
EEPROMWrit_00020_arg_Address     EQU	0x00000043 ; bytes:1
EEPROMWrit_00020_arg_Byte        EQU	0x00000044 ; bytes:1
UARTInit_00000_arg_Baud_Rate     EQU	0x00000031 ; bytes:1
CompTempVarRet663                EQU	0x0000003D ; bytes:1
UARTWriteB_00016_arg_Byte        EQU	0x0000003D ; bytes:1
gbl_19_Battery_Voltage           EQU	0x00000023 ; bytes:2
CompGblVar73                     EQU	0x0000002D ; bit:0
interrupt_1_Is_Magic_Numbe_00021 EQU	0x0000002E ; bytes:1
interrupt_1_Command              EQU	0x00000038 ; bytes:1
interrupt_1_Motor                EQU	0x00000039 ; bytes:1
interrupt_1_State                EQU	0x0000003A ; bytes:1
interrupt_1_Direction            EQU	0x0000003B ; bytes:1
CompTempVar664                   EQU	0x0000003C ; bytes:1
gbl_20_Motor_Left_Duty_Cyc_00000 EQU	0x00000025 ; bytes:2
gbl_20_Motor_Left_Duty_Cyc_00001 EQU	0x00000027 ; bytes:2
gbl_20_Motor_Right_Duty_Cy_00002 EQU	0x00000029 ; bytes:2
gbl_20_Motor_Right_Duty_Cy_00003 EQU	0x0000002B ; bytes:2
gbl_20_Motor_Left_State          EQU	0x0000002F ; bytes:1
gbl_20_Motor_Right_State         EQU	0x00000030 ; bytes:1
MotorSetSt_00018_arg_Motor       EQU	0x00000045 ; bytes:1
MotorSetSt_00018_arg_State       EQU	0x00000046 ; bytes:1
MotorSetSt_00018_1_Pointer_00022 EQU	0x00000047 ; bytes:2
MotorSetSt_00018_1_Pointer_00023 EQU	0x00000049 ; bytes:2
MotorSetSt_00018_1_Duty_Cycle    EQU	0x0000004B ; bytes:2
CompTempVar670                   EQU	0x0000004D ; bytes:1
CompTempVar671                   EQU	0x0000004D ; bytes:1
CompTempVar673                   EQU	0x0000004D ; bytes:1
CompTempVar674                   EQU	0x0000004D ; bytes:1
CompTempVar675                   EQU	0x0000004E ; bytes:1
MotorChang_00019_arg_Motor       EQU	0x0000003D ; bytes:1
MotorChang_00019_arg_Direction   EQU	0x0000003E ; bytes:1
MotorChang_00019_arg_Is_Sp_0001A EQU	0x0000003F ; bytes:1
delay_ms_00000_arg_del           EQU	0x00000032 ; bytes:1
delay_s_00000_arg_del            EQU	0x00000031 ; bytes:1
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
MotorSetSt_00018
; { MotorSetState ; function begin
	MOVF MotorSetSt_00018_arg_Motor, F
	BTFSS STATUS,Z
	GOTO	label4
	MOVLW HIGH(gbl_ccp1con+D'0')
	MOVWF MotorSetSt_00018_1_Pointer_00022+D'1'
	MOVLW LOW(gbl_ccp1con+D'0')
	MOVWF MotorSetSt_00018_1_Pointer_00022
	MOVLW HIGH(gbl_ccpr1l+D'0')
	MOVWF MotorSetSt_00018_1_Pointer_00023+D'1'
	MOVLW LOW(gbl_ccpr1l+D'0')
	MOVWF MotorSetSt_00018_1_Pointer_00023
	MOVF MotorSetSt_00018_arg_State, W
	MOVWF gbl_20_Motor_Left_State
	GOTO	label5
label4
	MOVLW HIGH(gbl_ccp2con+D'0')
	MOVWF CompTempVar670
	MOVLW LOW(gbl_ccp2con+D'0')
	MOVWF MotorSetSt_00018_1_Pointer_00022
	MOVF CompTempVar670, W
	MOVWF MotorSetSt_00018_1_Pointer_00022+D'1'
	MOVLW HIGH(gbl_ccpr2l+D'0')
	MOVWF CompTempVar671
	MOVLW LOW(gbl_ccpr2l+D'0')
	MOVWF MotorSetSt_00018_1_Pointer_00023
	MOVF CompTempVar671, W
	MOVWF MotorSetSt_00018_1_Pointer_00023+D'1'
	MOVF MotorSetSt_00018_arg_State, W
	MOVWF gbl_20_Motor_Right_State
label5
	MOVF MotorSetSt_00018_arg_State, W
	XORLW 0x00
	BTFSC STATUS,Z
	GOTO	label6
	XORLW 0x01
	BTFSC STATUS,Z
	GOTO	label7
	XORLW 0x03
	BTFSC STATUS,Z
	GOTO	label9
	GOTO	label11
label6
	BCF STATUS,IRP
	BTFSC MotorSetSt_00018_1_Pointer_00022+D'1',0
	BSF STATUS,IRP
	MOVF MotorSetSt_00018_1_Pointer_00022, W
	MOVWF FSR
	MOVLW 0x00
	MOVWF INDF
	RETURN
label7
	MOVF MotorSetSt_00018_arg_Motor, F
	BTFSS STATUS,Z
	GOTO	label8
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000, W
	MOVWF MotorSetSt_00018_1_Duty_Cycle
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000+D'1', W
	MOVWF MotorSetSt_00018_1_Duty_Cycle+D'1'
	GOTO	label11
label8
	MOVF gbl_20_Motor_Right_Duty_Cy_00002, W
	MOVWF MotorSetSt_00018_1_Duty_Cycle
	MOVF gbl_20_Motor_Right_Duty_Cy_00002+D'1', W
	MOVWF MotorSetSt_00018_1_Duty_Cycle+D'1'
	GOTO	label11
label9
	MOVF MotorSetSt_00018_arg_Motor, F
	BTFSS STATUS,Z
	GOTO	label10
	MOVF gbl_20_Motor_Left_Duty_Cyc_00001, W
	MOVWF MotorSetSt_00018_1_Duty_Cycle
	MOVF gbl_20_Motor_Left_Duty_Cyc_00001+D'1', W
	MOVWF MotorSetSt_00018_1_Duty_Cycle+D'1'
	GOTO	label11
label10
	MOVF gbl_20_Motor_Right_Duty_Cy_00003, W
	MOVWF MotorSetSt_00018_1_Duty_Cycle
	MOVF gbl_20_Motor_Right_Duty_Cy_00003+D'1', W
	MOVWF MotorSetSt_00018_1_Duty_Cycle+D'1'
label11
	SWAPF MotorSetSt_00018_1_Duty_Cycle, W
	ANDLW 0xF0
	MOVWF CompTempVar673
	MOVLW 0x30
	ANDWF CompTempVar673, F
	BCF STATUS,IRP
	BTFSC MotorSetSt_00018_1_Pointer_00022+D'1',0
	BSF STATUS,IRP
	MOVF MotorSetSt_00018_1_Pointer_00022, W
	MOVWF FSR
	MOVF CompTempVar673, W
	MOVWF INDF
	MOVF MotorSetSt_00018_1_Duty_Cycle, W
	MOVWF CompTempVar674
	RRF MotorSetSt_00018_1_Duty_Cycle+D'1', W
	MOVWF CompTempVar675
	RRF CompTempVar674, F
	RRF CompTempVar675, F
	RRF CompTempVar674, F
	BCF STATUS,IRP
	BTFSC MotorSetSt_00018_1_Pointer_00023+D'1',0
	BSF STATUS,IRP
	MOVF MotorSetSt_00018_1_Pointer_00023, W
	MOVWF FSR
	MOVF CompTempVar674, W
	MOVWF INDF
	BCF STATUS,IRP
	BTFSC MotorSetSt_00018_1_Pointer_00022+D'1',0
	BSF STATUS,IRP
	MOVF MotorSetSt_00018_1_Pointer_00022, W
	MOVWF FSR
	MOVLW 0x0C
	IORWF INDF, F
	RETURN
; } MotorSetState function end

	ORG 0x00000097
EEPROMWrit_00020
; { EEPROMWriteByte ; function begin
	MOVF EEPROMWrit_00020_arg_Address, W
	BSF STATUS, RP1
	MOVWF gbl_eeadr
	BCF STATUS, RP1
	MOVF EEPROMWrit_00020_arg_Byte, W
	BSF STATUS, RP1
	MOVWF gbl_eedata
	BCF gbl_intcon,7
	BSF STATUS, RP0
	BCF gbl_eecon1,7
	BSF gbl_eecon1,2
	MOVLW 0x55
	MOVWF gbl_eecon2
	MOVLW 0xAA
	MOVWF gbl_eecon2
	BSF gbl_eecon1,1
label12
	BTFSC gbl_eecon1,1
	GOTO	label12
	BCF gbl_eecon1,2
	BSF gbl_intcon,7
	RETURN
; } EEPROMWriteByte function end

	ORG 0x000000AC
EEPROMWrit_0001C
; { EEPROMWriteWord ; function begin
	MOVLW 0xFF
	SUBWF EEPROMWrit_0001C_arg_Address, W
	BTFSC STATUS,C
	RETURN
	MOVF EEPROMWrit_0001C_arg_Address, W
	MOVWF EEPROMWrit_00020_arg_Address
	MOVF EEPROMWrit_0001C_arg_Word, W
	MOVWF EEPROMWrit_00020_arg_Byte
	CALL EEPROMWrit_00020
	BCF STATUS, RP0
	BCF STATUS, RP1
	INCF EEPROMWrit_0001C_arg_Address, W
	MOVWF EEPROMWrit_00020_arg_Address
	MOVF EEPROMWrit_0001C_arg_Word+D'1', W
	MOVWF EEPROMWrit_00020_arg_Byte
	CALL EEPROMWrit_00020
	RETURN
; } EEPROMWriteWord function end

	ORG 0x000000BD
UARTWriteB_00016
; { UARTWriteByte ; function begin
label13
	BTFSS gbl_pir1,4
	GOTO	label13
	MOVF UARTWriteB_00016_arg_Byte, W
	MOVWF gbl_txreg
	RETURN
; } UARTWriteByte function end

	ORG 0x000000C2
UARTReadBy_00015
; { UARTReadByte ; function begin
	BCF STATUS, RP0
	BCF STATUS, RP1
	BTFSS gbl_rcsta,1
	GOTO	label14
	BCF gbl_rcsta,1
	BCF gbl_rcsta,4
	BSF gbl_rcsta,4
label14
	BTFSS gbl_pir1,5
	GOTO	label14
	MOVF gbl_rcreg, W
	MOVWF CompTempVarRet663
	RETURN
; } UARTReadByte function end

	ORG 0x000000CE
MotorChang_00019
; { MotorChangeSpeed ; function begin
	MOVF MotorChang_00019_arg_Motor, F
	BTFSS STATUS,Z
	GOTO	label23
	MOVF MotorChang_00019_arg_Direction, F
	BTFSS STATUS,Z
	GOTO	label18
	MOVF MotorChang_00019_arg_Is_Sp_0001A, F
	BTFSC STATUS,Z
	GOTO	label15
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000, W
	SUBLW 0x00
	BTFSC STATUS,C
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000+D'1', W
	BTFSC STATUS,Z
	GOTO	label17
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000, F
	BTFSC STATUS,Z
	DECF gbl_20_Motor_Left_Duty_Cyc_00000+D'1', F
	DECF gbl_20_Motor_Left_Duty_Cyc_00000, F
	GOTO	label17
label15
	MOVLW 0x03
	SUBWF gbl_20_Motor_Left_Duty_Cyc_00000+D'1', W
	BTFSS STATUS,Z
	GOTO	label16
	MOVLW 0xFF
	SUBWF gbl_20_Motor_Left_Duty_Cyc_00000, W
label16
	BTFSC STATUS,C
	GOTO	label17
	INCF gbl_20_Motor_Left_Duty_Cyc_00000, F
	BTFSC STATUS,Z
	INCF gbl_20_Motor_Left_Duty_Cyc_00000+D'1', F
label17
	CLRF EEPROMWrit_0001C_arg_Address
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000, W
	MOVWF EEPROMWrit_0001C_arg_Word
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000+D'1', W
	MOVWF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
	GOTO	label22
label18
	MOVF MotorChang_00019_arg_Is_Sp_0001A, F
	BTFSC STATUS,Z
	GOTO	label20
	MOVLW 0x03
	SUBWF gbl_20_Motor_Left_Duty_Cyc_00001+D'1', W
	BTFSS STATUS,Z
	GOTO	label19
	MOVLW 0xFF
	SUBWF gbl_20_Motor_Left_Duty_Cyc_00001, W
label19
	BTFSC STATUS,C
	GOTO	label21
	INCF gbl_20_Motor_Left_Duty_Cyc_00001, F
	BTFSC STATUS,Z
	INCF gbl_20_Motor_Left_Duty_Cyc_00001+D'1', F
	GOTO	label21
label20
	MOVF gbl_20_Motor_Left_Duty_Cyc_00001, W
	SUBLW 0x00
	BTFSC STATUS,C
	MOVF gbl_20_Motor_Left_Duty_Cyc_00001+D'1', W
	BTFSC STATUS,Z
	GOTO	label21
	MOVF gbl_20_Motor_Left_Duty_Cyc_00001, F
	BTFSC STATUS,Z
	DECF gbl_20_Motor_Left_Duty_Cyc_00001+D'1', F
	DECF gbl_20_Motor_Left_Duty_Cyc_00001, F
label21
	MOVLW 0x02
	MOVWF EEPROMWrit_0001C_arg_Address
	MOVF gbl_20_Motor_Left_Duty_Cyc_00001, W
	MOVWF EEPROMWrit_0001C_arg_Word
	MOVF gbl_20_Motor_Left_Duty_Cyc_00001+D'1', W
	MOVWF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
label22
	BCF STATUS, RP0
	BCF STATUS, RP1
	CLRF MotorSetSt_00018_arg_Motor
	MOVF gbl_20_Motor_Left_State, W
	MOVWF MotorSetSt_00018_arg_State
	CALL MotorSetSt_00018
	RETURN
label23
	MOVF MotorChang_00019_arg_Direction, F
	BTFSS STATUS,Z
	GOTO	label27
	MOVF MotorChang_00019_arg_Is_Sp_0001A, F
	BTFSC STATUS,Z
	GOTO	label25
	MOVLW 0x03
	SUBWF gbl_20_Motor_Right_Duty_Cy_00002+D'1', W
	BTFSS STATUS,Z
	GOTO	label24
	MOVLW 0xFF
	SUBWF gbl_20_Motor_Right_Duty_Cy_00002, W
label24
	BTFSC STATUS,C
	GOTO	label26
	INCF gbl_20_Motor_Right_Duty_Cy_00002, F
	BTFSC STATUS,Z
	INCF gbl_20_Motor_Right_Duty_Cy_00002+D'1', F
	GOTO	label26
label25
	MOVF gbl_20_Motor_Right_Duty_Cy_00002, W
	SUBLW 0x00
	BTFSC STATUS,C
	MOVF gbl_20_Motor_Right_Duty_Cy_00002+D'1', W
	BTFSC STATUS,Z
	GOTO	label26
	MOVF gbl_20_Motor_Right_Duty_Cy_00002, F
	BTFSC STATUS,Z
	DECF gbl_20_Motor_Right_Duty_Cy_00002+D'1', F
	DECF gbl_20_Motor_Right_Duty_Cy_00002, F
label26
	MOVLW 0x04
	MOVWF EEPROMWrit_0001C_arg_Address
	MOVF gbl_20_Motor_Right_Duty_Cy_00002, W
	MOVWF EEPROMWrit_0001C_arg_Word
	MOVF gbl_20_Motor_Right_Duty_Cy_00002+D'1', W
	MOVWF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
	GOTO	label31
label27
	MOVF MotorChang_00019_arg_Is_Sp_0001A, F
	BTFSC STATUS,Z
	GOTO	label28
	MOVF gbl_20_Motor_Right_Duty_Cy_00003, W
	SUBLW 0x00
	BTFSC STATUS,C
	MOVF gbl_20_Motor_Right_Duty_Cy_00003+D'1', W
	BTFSC STATUS,Z
	GOTO	label30
	MOVF gbl_20_Motor_Right_Duty_Cy_00003, F
	BTFSC STATUS,Z
	DECF gbl_20_Motor_Right_Duty_Cy_00003+D'1', F
	DECF gbl_20_Motor_Right_Duty_Cy_00003, F
	GOTO	label30
label28
	MOVLW 0x03
	SUBWF gbl_20_Motor_Right_Duty_Cy_00003+D'1', W
	BTFSS STATUS,Z
	GOTO	label29
	MOVLW 0xFF
	SUBWF gbl_20_Motor_Right_Duty_Cy_00003, W
label29
	BTFSC STATUS,C
	GOTO	label30
	INCF gbl_20_Motor_Right_Duty_Cy_00003, F
	BTFSC STATUS,Z
	INCF gbl_20_Motor_Right_Duty_Cy_00003+D'1', F
label30
	MOVLW 0x06
	MOVWF EEPROMWrit_0001C_arg_Address
	MOVF gbl_20_Motor_Right_Duty_Cy_00003, W
	MOVWF EEPROMWrit_0001C_arg_Word
	MOVF gbl_20_Motor_Right_Duty_Cy_00003+D'1', W
	MOVWF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
label31
	MOVLW 0x01
	BCF STATUS, RP0
	BCF STATUS, RP1
	MOVWF MotorSetSt_00018_arg_Motor
	MOVF gbl_20_Motor_Right_State, W
	MOVWF MotorSetSt_00018_arg_State
	CALL MotorSetSt_00018
	RETURN
; } MotorChangeSpeed function end

	ORG 0x00000167
EEPROMRead_0001F
; { EEPROMReadByte ; function begin
	MOVF EEPROMRead_0001F_arg_Address, W
	BSF STATUS, RP1
	MOVWF gbl_eeadr
	BSF STATUS, RP0
	BCF gbl_eecon1,7
	BSF gbl_eecon1,0
label32
	BTFSC gbl_eecon1,0
	GOTO	label32
	BCF STATUS, RP0
	MOVF gbl_eedata, W
	BCF STATUS, RP1
	MOVWF CompTempVarRet662
	RETURN
; } EEPROMReadByte function end

	ORG 0x00000174
EEPROMRead_0001B
; { EEPROMReadWord ; function begin
	CLRF EEPROMRead_0001B_1_Return_Value
	CLRF EEPROMRead_0001B_1_Return_Value+D'1'
	MOVLW 0xFF
	SUBWF EEPROMRead_0001B_arg_Address, W
	BTFSC STATUS,C
	GOTO	label33
	MOVF EEPROMRead_0001B_arg_Address, W
	MOVWF EEPROMRead_0001F_arg_Address
	CALL EEPROMRead_0001F
	MOVF CompTempVarRet662, W
	MOVWF EEPROMRead_0001B_1_Low_Byte
	INCF EEPROMRead_0001B_arg_Address, W
	MOVWF EEPROMRead_0001F_arg_Address
	CALL EEPROMRead_0001F
	MOVF CompTempVarRet662, W
	MOVWF EEPROMRead_0001B_1_High_Byte
	CLRF CompTempVar660
	MOVF EEPROMRead_0001B_1_High_Byte, W
	MOVWF CompTempVar661
	MOVF EEPROMRead_0001B_1_Low_Byte, W
	IORWF CompTempVar660, F
	MOVF CompTempVar660, W
	MOVWF EEPROMRead_0001B_1_Return_Value
	MOVF CompTempVar661, W
	MOVWF EEPROMRead_0001B_1_Return_Value+D'1'
label33
	MOVF EEPROMRead_0001B_1_Return_Value, W
	MOVWF CompTempVarRet657
	MOVF EEPROMRead_0001B_1_Return_Value+D'1', W
	MOVWF CompTempVarRet657+D'1'
	RETURN
; } EEPROMReadWord function end

	ORG 0x00000192
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

	ORG 0x0000019F
MotorInit_00000
; { MotorInit ; function begin
	BSF STATUS, RP0
	BCF STATUS, RP1
	BCF gbl_trisc,2
	BCF gbl_trisc,1
	BCF STATUS, RP0
	BCF gbl_portc,2
	BCF gbl_portc,1
	CLRF EEPROMRead_0001B_arg_Address
	CALL EEPROMRead_0001B
	MOVF CompTempVarRet657, W
	MOVWF gbl_20_Motor_Left_Duty_Cyc_00000
	MOVF CompTempVarRet657+D'1', W
	MOVWF gbl_20_Motor_Left_Duty_Cyc_00000+D'1'
	MOVF gbl_20_Motor_Left_Duty_Cyc_00000, W
	XORLW 0xFF
	MOVLW 0xFF
	BTFSC STATUS,Z
	XORWF gbl_20_Motor_Left_Duty_Cyc_00000+D'1', W
	BTFSS STATUS,Z
	GOTO	label34
	CLRF EEPROMWrit_0001C_arg_Address
	MOVLW 0xC8
	MOVWF EEPROMWrit_0001C_arg_Word
	CLRF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
	MOVLW 0x02
	BCF STATUS, RP0
	BCF STATUS, RP1
	MOVWF EEPROMWrit_0001C_arg_Address
	MOVLW 0xF4
	MOVWF EEPROMWrit_0001C_arg_Word
	MOVLW 0x01
	MOVWF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
	MOVLW 0x04
	BCF STATUS, RP0
	BCF STATUS, RP1
	MOVWF EEPROMWrit_0001C_arg_Address
	MOVLW 0x20
	MOVWF EEPROMWrit_0001C_arg_Word
	MOVLW 0x03
	MOVWF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
	MOVLW 0x06
	BCF STATUS, RP0
	BCF STATUS, RP1
	MOVWF EEPROMWrit_0001C_arg_Address
	MOVLW 0x2C
	MOVWF EEPROMWrit_0001C_arg_Word
	MOVLW 0x01
	MOVWF EEPROMWrit_0001C_arg_Word+D'1'
	CALL EEPROMWrit_0001C
	MOVLW 0xC8
	BCF STATUS, RP0
	BCF STATUS, RP1
	MOVWF gbl_20_Motor_Left_Duty_Cyc_00000
	CLRF gbl_20_Motor_Left_Duty_Cyc_00000+D'1'
	MOVLW 0xF4
	MOVWF gbl_20_Motor_Left_Duty_Cyc_00001
	MOVLW 0x01
	MOVWF gbl_20_Motor_Left_Duty_Cyc_00001+D'1'
	MOVLW 0x20
	MOVWF gbl_20_Motor_Right_Duty_Cy_00002
	MOVLW 0x03
	MOVWF gbl_20_Motor_Right_Duty_Cy_00002+D'1'
	MOVLW 0x2C
	MOVWF gbl_20_Motor_Right_Duty_Cy_00003
	MOVLW 0x01
	MOVWF gbl_20_Motor_Right_Duty_Cy_00003+D'1'
	GOTO	label35
label34
	MOVLW 0x02
	MOVWF EEPROMRead_0001B_arg_Address
	CALL EEPROMRead_0001B
	MOVF CompTempVarRet657, W
	MOVWF gbl_20_Motor_Left_Duty_Cyc_00001
	MOVF CompTempVarRet657+D'1', W
	MOVWF gbl_20_Motor_Left_Duty_Cyc_00001+D'1'
	MOVLW 0x04
	MOVWF EEPROMRead_0001B_arg_Address
	CALL EEPROMRead_0001B
	MOVF CompTempVarRet657, W
	MOVWF gbl_20_Motor_Right_Duty_Cy_00002
	MOVF CompTempVarRet657+D'1', W
	MOVWF gbl_20_Motor_Right_Duty_Cy_00002+D'1'
	MOVLW 0x06
	MOVWF EEPROMRead_0001B_arg_Address
	CALL EEPROMRead_0001B
	MOVF CompTempVarRet657, W
	MOVWF gbl_20_Motor_Right_Duty_Cy_00003
	MOVF CompTempVarRet657+D'1', W
	MOVWF gbl_20_Motor_Right_Duty_Cy_00003+D'1'
label35
	MOVLW 0xFF
	BSF STATUS, RP0
	MOVWF gbl_pr2
	MOVLW 0x06
	BCF STATUS, RP0
	MOVWF gbl_t2con
	RETURN
; } MotorInit function end

	ORG 0x00000201
ADCReadWor_00017
; { ADCReadWord ; function begin
	BCF STATUS, RP0
	BCF STATUS, RP1
	BSF gbl_adcon0,2
label36
	BTFSC gbl_adcon0,2
	GOTO	label36
	CLRF CompTempVarRet650
	MOVF gbl_adresh, W
	MOVWF CompTempVar656
	MOVLW 0x00
	ANDWF CompTempVarRet650, F
	MOVF CompTempVar656, W
	ANDLW 0xFF
	MOVWF CompTempVarRet650+D'1'
	BSF STATUS, RP0
	MOVF gbl_adresl, W
	BCF STATUS, RP0
	IORWF CompTempVarRet650, F
	RETURN
; } ADCReadWord function end

	ORG 0x00000213
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

	ORG 0x0000021C
main
; { main ; function begin
	BSF STATUS, RP0
	BCF STATUS, RP1
	CLRF gbl_trisb
	BCF STATUS, RP0
	BCF gbl_portb,7
	CALL MotorInit_00000
	CALL ADCInit_00000
	MOVLW 0x01
	MOVWF UARTInit_00000_arg_Baud_Rate
	CALL UARTInit_00000
	CLRF MotorSetSt_00018_arg_Motor
	CLRF MotorSetSt_00018_arg_State
	CALL MotorSetSt_00018
	MOVLW 0x01
	MOVWF MotorSetSt_00018_arg_Motor
	CLRF MotorSetSt_00018_arg_State
	CALL MotorSetSt_00018
	BCF gbl_portb,7
	CALL ADCReadWor_00017
	CALL ADCReadWor_00017
	MOVLW 0xC0
	MOVWF gbl_intcon
label37
	BSF STATUS, RP0
	BCF gbl_pie1,5
	CALL ADCReadWor_00017
	MOVF CompTempVarRet650, W
	MOVWF gbl_19_Battery_Voltage
	MOVF CompTempVarRet650+D'1', W
	MOVWF gbl_19_Battery_Voltage+D'1'
	BSF STATUS, RP0
	BSF gbl_pie1,5
	MOVLW 0x01
	BCF STATUS, RP0
	MOVWF delay_s_00000_arg_del
	CALL delay_s_00000
	GOTO	label37
; } main function end

	ORG 0x00000240
_startup
	BCF STATUS, RP0
	BCF STATUS, RP1
	BCF CompGblVar73,0
	CLRF gbl_19_Battery_Voltage
	CLRF gbl_19_Battery_Voltage+D'1'
	CLRF gbl_20_Motor_Left_Duty_Cyc_00000
	CLRF gbl_20_Motor_Left_Duty_Cyc_00000+D'1'
	CLRF gbl_20_Motor_Left_Duty_Cyc_00001
	CLRF gbl_20_Motor_Left_Duty_Cyc_00001+D'1'
	CLRF gbl_20_Motor_Right_Duty_Cy_00002
	CLRF gbl_20_Motor_Right_Duty_Cy_00002+D'1'
	CLRF gbl_20_Motor_Right_Duty_Cy_00003
	CLRF gbl_20_Motor_Right_Duty_Cy_00003+D'1'
	CLRF gbl_20_Motor_Left_State
	CLRF gbl_20_Motor_Right_State
	BCF PCLATH,3
	BCF PCLATH,4
	GOTO	main
	ORG 0x00000252
interrupt
; { interrupt ; function begin
	BCF STATUS, RP0
	BCF STATUS, RP1
	BTFSC CompGblVar73,0
	GOTO	label39
	CLRF interrupt_1_Is_Magic_Numbe_00021
	BSF CompGblVar73,0
label39
	BTFSS gbl_pir1,5
	GOTO	label57
	CALL UARTReadBy_00015
	MOVF CompTempVarRet663, W
	MOVWF interrupt_1_Command
	MOVF interrupt_1_Is_Magic_Numbe_00021, F
	BTFSS STATUS,Z
	GOTO	label41
	MOVF interrupt_1_Command, W
	XORLW 0xA5
	BTFSS STATUS,Z
	GOTO	label40
	MOVLW 0x01
	MOVWF interrupt_1_Is_Magic_Numbe_00021
label40
	BCF gbl_pir1,5
	GOTO	label57
label41
	CLRF interrupt_1_Is_Magic_Numbe_00021
	MOVLW 0xC0
	ANDWF interrupt_1_Command, W
	MOVWF CompTempVar664
	MOVF CompTempVar664, W
	XORLW 0x00
	BTFSC STATUS,Z
	GOTO	label42
	XORLW 0x40
	BTFSC STATUS,Z
	GOTO	label48
	XORLW 0xC0
	BTFSC STATUS,Z
	GOTO	label50
	XORLW 0x40
	BTFSC STATUS,Z
	GOTO	label51
	GOTO	label56
label42
	BTFSS interrupt_1_Command,5
	GOTO	label43
	MOVLW 0x01
	MOVWF interrupt_1_Motor
	GOTO	label44
label43
	CLRF interrupt_1_Motor
label44
	RRF interrupt_1_Command, F
	RRF interrupt_1_Command, F
	RRF interrupt_1_Command, F
	MOVLW 0x1F
	ANDWF interrupt_1_Command, F
	MOVLW 0x03
	ANDWF interrupt_1_Command, F
	DECF interrupt_1_Command, W
	BTFSS STATUS,Z
	GOTO	label45
	MOVLW 0x01
	MOVWF interrupt_1_State
	GOTO	label47
label45
	MOVF interrupt_1_Command, W
	XORLW 0x02
	BTFSS STATUS,Z
	GOTO	label46
	MOVLW 0x02
	MOVWF interrupt_1_State
	GOTO	label47
label46
	CLRF interrupt_1_State
label47
	MOVF interrupt_1_Motor, W
	MOVWF MotorSetSt_00018_arg_Motor
	MOVF interrupt_1_State, W
	MOVWF MotorSetSt_00018_arg_State
	CALL MotorSetSt_00018
	GOTO	label56
label48
	MOVLW 0x28
	ANDWF interrupt_1_Command, W
	BTFSC STATUS,Z
	GOTO	label49
	BSF gbl_portb,7
	GOTO	label56
label49
	BCF gbl_portb,7
	GOTO	label56
label50
	MOVF gbl_19_Battery_Voltage+D'1', W
	MOVWF UARTWriteB_00016_arg_Byte
	CALL UARTWriteB_00016
	MOVF gbl_19_Battery_Voltage, W
	MOVWF UARTWriteB_00016_arg_Byte
	CALL UARTWriteB_00016
	GOTO	label56
label51
	BTFSS interrupt_1_Command,5
	GOTO	label52
	MOVLW 0x01
	MOVWF interrupt_1_Motor
	GOTO	label53
label52
	CLRF interrupt_1_Motor
label53
	BTFSS interrupt_1_Command,4
	GOTO	label54
	MOVLW 0x01
	MOVWF interrupt_1_Direction
	GOTO	label55
label54
	CLRF interrupt_1_Direction
label55
	MOVLW 0x08
	ANDWF interrupt_1_Command, F
	RRF interrupt_1_Command, F
	RRF interrupt_1_Command, F
	RRF interrupt_1_Command, F
	MOVLW 0x1F
	ANDWF interrupt_1_Command, F
	MOVF interrupt_1_Motor, W
	MOVWF MotorChang_00019_arg_Motor
	MOVF interrupt_1_Direction, W
	MOVWF MotorChang_00019_arg_Direction
	MOVF interrupt_1_Command, W
	MOVWF MotorChang_00019_arg_Is_Sp_0001A
	CALL MotorChang_00019
label56
	BCF gbl_pir1,5
label57
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
