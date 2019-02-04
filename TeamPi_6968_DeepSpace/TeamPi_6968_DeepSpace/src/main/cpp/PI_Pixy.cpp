/*

#include "include/PI_Pixy.h"


Pixy::Pixy(){

  uint8_t data;

    uint8_t i, lenReceived, recvBuf[32];
    uint8_t versionRequest[] =
    {
      0xae,  // first byte of no_checksum_sync (little endian -> least-significant byte first)
      0xc1,  // second byte of no_checksum_sync
      0x0e,  // this is the version request type
      0x00   // data_length is 0
    };

  uint8_t port = 0;
  
  HAL_SPIPort port =kOnboardCS0 
  int32_t HAL_TransactionSPI(HAL_SPIPort port, const uint8_t* dataToSend,
                           uint8_t* dataReceived, int32_t size);
    int32_t HAL_WriteSPI(HAL_SPIPort port, const uint8_t* dataToSend,
                     int32_t sendSize);
                     int32_t HAL_ReadSPI(HAL_SPIPort port, uint8_t* buffer, int32_t count);
                     void HAL_CloseSPI(HAL_SPIPort port);
                     void HAL_SetSPIChipSelectActiveHigh(HAL_SPIPort port, int32_t* status);


    

    spi.begin();
    spi.Transaction
  
    // You need to write send(), which takes a pointer to the data you want to send and the number of 
    // bytes to send via your serial port (SPI, I2C or UART).  It returns the number of bytes successfully sent.
    spi.Write(uint8_t *data, uint8_t len);
    spi.Write()
    
    // You also need to write recv(), which takes a pointer to a data buffer where the received data
    // will be written/returned and the number of bytes to receive via your serial port (SPI, I2C or UART).  
    // It returns the number of bytes immediately available and written into the buffer (without needing 
    // to busy-wait.)
    extern uint8_t recv(uint8_t *data, uint8_t len);
    
    // clear out any stale data
    while(spi.receive(recvBuf, 1));
    
    spi.send(versionRequest, 4);   
    delayMillisecond(1); // delay a little so we don't receive too fast (may not be necessary.)  
    lenReceived = spi.receive(recvBuf, 6 + 16); // 6 bytes of header and checksum and 16 bytes of version data
    
    // print result
    printf("Received %hhu bytes.\n", lenReceived);
    for (i=0; i<lenReceived; i++)
      printf("%hhu: 0x%hhx\n", i, recvBuf[i]); 
  
    
    
}*/