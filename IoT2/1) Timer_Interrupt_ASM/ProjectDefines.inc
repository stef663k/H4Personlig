#ifndef PROJECT_DEFINES_INC
#define PROJECT_DEFINES_INC

/********************************************************************************************************
 Defines f�lger herefter.
*********************************************************************************************************/
#if defined (__ATmega168__) || defined (__ATmega328P__)
    .equ    RedLEDBitPosition = 1
    .equ    YellowLEDBitPosition = 2
    .equ    GreenLEDBitPosition = 3

    .equ    KeyPosition = 2

    .equ    EEpromStartAddress = 0x0000
#endif

#if defined (__ATmega2560__)
    .equ    RedLEDBitPosition = 2
    .equ    YellowLEDBitPosition = 1
    .equ    GreenLEDBitPosition = 0
#endif

#if defined (__ATmega328PB__)
    .equ    RedLEDBitPosition = 3
    .equ    YellowLEDBitPosition = 2
    .equ    GreenLEDBitPosition = 1
    .equ    OVF0addr = TIMER0_OVFaddr
    .equ    RWW_START_ADDR = FIRSTBOOTEND
#endif

    .equ    RedLedBitValue = (1 << RedLEDBitPosition)
    .equ    YellowLedBitValue = (1 << YellowLEDBitPosition)
    .equ    GreenLEDValue = (1 << GreenLEDBitPosition)
/********************************************************************************************************
 Slut p� Defines.
*********************************************************************************************************/

/********************************************************************************************************
  Register (om)definitioner f�lger herefter.
*********************************************************************************************************/
    ;.def    LED=r16
    .def    Temp=r16
    .def    Count=r17
    .def    Count1=r18
    .def    UsartSendCharacter=r22
    .def    BackupRegister=r24
/********************************************************************************************************
 Slut p� Register (om)definitioner. 
*********************************************************************************************************/

/********************************************************************************************************
 Symbol erkl�ringer f�lger herefter.
 *********************************************************************************************************/
    .equ    EEPromStopReadCharacter = 0xFF
    .equ    FlashpromStopReadCharacter = 0xFF
    .equ    CounterValue = 0x01
/********************************************************************************************************
 Slut p� Symbol erkl�ringer.
*********************************************************************************************************/

#endif  ; End of include guard
