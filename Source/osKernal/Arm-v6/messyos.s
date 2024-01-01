 ; @file messyos.s
 ; @author ZheWana (zhewana@qq.com)
 ; @brief
 ; @version 0.1
 ; @date 2022-07-15
 ;
 ; @copyright Copyright (c) 2022

    AREA MESSYOS,CODE,READONLY
	THUMB

PendSV_Handler PROC 
    IMPORT MOS_TaskScheduling
	IMPORT IsOSReady
    EXPORT PendSV_Handler
	
	
    PUSH {LR} ; 压栈保护LR寄存器
	BL IsOSReady
	; Armv6M指令集不支持直接POP到LR寄存器中，
	; 通过R1进行中转，压栈防止数据丢失
	POP {R1}
	MOV LR, R1 
	
	; 若OS没有完成初始化，则直接返回
	MOVS R1, #0x01 
    TST R0, R1
	BEQ OS_Ready
	BX LR
OS_Ready
	
    MRS R0,MSP
    PUSH {LR} ; 压栈保护LR寄存器
    BL MOS_TaskScheduling
	POP {R1}
	MOV LR, R1 

    ; 检查SaveFlag进而决定是否压栈
	MOVS R1, #0x1 
    TST R0, R1
    BEQ WithOutPush
    PUSH {R4-R11}
	
;    MRS R1,CONTROL
;    ORR R1,#0x2
;    MSR CONTROL,R1

WithOutPush
    ; 恢复栈地址到R0
    BIC R0,#0x1
    MSR MSP,R0

    POP {R4-R11}
	
    BX LR

    ENDP

MOS_SetSP PROC ; 参数为当前任务栈指针
    EXPORT MOS_SetSP

    MOV SP,R0
    MOV PC,LR

    ENDP
    END
		