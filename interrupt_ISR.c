/*
 * interrupt_ISR.c
 *
 *  Created on: Dec 27, 2020
 *      Author: Tinh_deptrai
 */

#include "driverlib.h"




//
// cla1Isr1 - CLA1 ISR 1
//
__interrupt void cla1Isr1 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);


    //
    // Uncomment to halt debugger and stop here
    //
//    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 2
//
__interrupt void cla1Isr2 ()
{
    asm(" ESTOP0");

    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

}

//
// cla1Isr1 - CLA1 ISR 3
//
__interrupt void cla1Isr3 ()
{
    asm(" ESTOP0");
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

}

//
// cla1Isr1 - CLA1 ISR 4
//
__interrupt void cla1Isr4 ()
{
    asm(" ESTOP0");
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

}

//
// cla1Isr1 - CLA1 ISR 5
//
__interrupt void cla1Isr5 ()
{
    asm(" ESTOP0");
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

}

//
// cla1Isr1 - CLA1 ISR 6
//
__interrupt void cla1Isr6 ()
{
    asm(" ESTOP0");
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

}

//
// cla1Isr1 - CLA1 ISR 7
//
__interrupt void cla1Isr7 ()
{
    asm(" ESTOP0");
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

}

//
// cla1Isr1 - CLA1 ISR 8
//
__interrupt void cla1Isr8 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);


    //
    // Uncomment to halt debugger and stop here
    //
//    asm(" ESTOP0");
}

