//
// Created by zengjun on 2020/1/5.
//

#ifndef SERAILIMU_COM_H
#define SERAILIMU_COM_H




signed char	SendUARTMessageLength(const unsigned long ulChannelNo, const unsigned char chrMessage[],const unsigned short usLen);
unsigned short CollectUARTData(const unsigned long ulChannelNo, unsigned char chrUARTBufferOutput[]);
signed char OpenCOMDevice(const unsigned long ulPortNo);
signed char SetBaundrate(const unsigned long ulPortNo,const unsigned long ulBaundrate);
signed char OpenCOMDevice(const unsigned long ulPortNo,const unsigned long ulBaundrate);
void CloseCOMDevice(void);

#endif

