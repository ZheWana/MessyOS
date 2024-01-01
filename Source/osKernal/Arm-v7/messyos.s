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
    POP {LR} ; 恢复LR寄存器
    TST R0,#0x1 
    BXEQ LR
	
    MRS R0,MSP
    PUSH {LR} ; 压栈保护LR寄存器
    BL MOS_TaskScheduling
    POP {LR} ; 恢复LR寄存器

    ; 检查SaveFlag进而决定是否压栈
    TST R0,#0x1
    BEQ WithOutPush
    STMDB SP!,{R4-R11}

;    MRS R1,CONTROL
;    ORR R1,#0x2
;    MSR CONTROL,R1

WithOutPush
    ; 恢复栈地址到R0
    BIC R0,R0,#0x1
    MSR MSP,R0

    LDMIA SP!,{R4-R11}
	
;	MOV R0,LR
;	TST R0,#0x4
;	ADDEQ LR,R0,#0x4
    BX LR

    ENDP

MOS_SetSP PROC ; 参数为当前任务栈指针
    EXPORT MOS_SetSP

    MOV SP,R0
    MOV PC,LR

    ENDP
    END
		