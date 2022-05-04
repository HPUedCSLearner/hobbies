/*  
 *一口Linux
 *2021.6.21
 *version: 1.0.0
*/

#ifndef _PWM_H
#define _PWM_H


#define DEV_FIFO_TYPE 'k'

#define DEV_FIFO_CLEAN _IO(DEV_FIFO_TYPE,0)
#define DEV_FIFO_GETVALUE _IOR(DEV_FIFO_TYPE,1,int)
#define DEV_FIFO_SETVALUE _IOW(DEV_FIFO_TYPE,2,int)


#endif
