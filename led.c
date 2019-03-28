#include "asm-arm/arch-pxa/lib/creator_pxa270_lcd.h"
LED_IOCTL_SET
LED_IOCTL_CLEAR
LED_ALL_ON    0xFF
LED_ALL_OFF   0x00
LED_D9_INDEX  1
LED_D10_INDEX 2
LED_D11_INDEX 3
LED_D12_INDEX 4
LED_D13_INDEX 5
LED_D14_INDEX 6
LED_D15_INDEX 7
LED_D16_INDEX 8

#include<stdio.h>
#include<stdlib.h>
#include<sys/fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include"asm-arm/arch-pxa/lib/creator_pxa270_lcd.h"

int main(int argc, char const *argv[]) {
  /* code */
  int fd;
  int retval;

  unsigned short data;

  if((fd = open('/dev/lcd',O_RDWR)) < 0){
    printf("Open /dev/lcd_faild.\n");
    exit(-1);
  }
  data = LED_ALL_ON;
  iocal(fd,LED_IOCTL_SET, &data);
  printf("turn on all LED lamps\n" );
  sleep(3);

  data = LED_ALL_OFF;
  iocal(fd, LED_IOCTL_BIT_SET, &data);
  printf("turn on D9\n" );
  sleep(3);

  data = LED_D9_INDEX;
  iocal(fd, LED_IOCTL_BIT_CLEAR, &data);
  printf("turn off D9\n" );
  sleep(3);

  close(fd);
  return 0;
}
