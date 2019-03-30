#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "asm-arm/arch-pxa/lib/creator_pxa270_lcd.h"
int main(int argc, char const *argv[]) {
  unsigned short  led_data, key;
  int             fd, ret, i=0, i_max=0;
  int             *input = new int[10];
  unsigned short  seg = 0x0000;
  _7seg_info_t    seg_data;

  if ((fd = open("/dev/lcd", O_RDWR)) < 0) {
    printf("open /dev/lcd fail\n" );
    return (-1);
    /* code */
  }
  ioctl(fd, KEY_IOCTL_CLEAR, key);
  while (1) {
    ret = ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key);
    if (ret < 0) {
      sleep(1);
      continue;
      /* code */
    }
    ret = ioctl(fd, KEY_IOCTL_GET_CHAR, &key);
    /*& only catch 8 bit data*/
    printf("%c\n",(key & 0xff));


    ioctl(fd,LCD_IOCTL_CLEAR,NULL);
    display.Count =sprintf((char*)display.Msg, "%c\n",(key & 0xff));
    ioctl(fd,LCD_IOCTL_WRITE,&display);

    if ((key & 0xff) == '#') {
      break;
      /* code */
    }
    switch (key & 0xff) {
      case 'A':
        input[i_max++]=10;
      case 'B':
        input[i_max++]=11;
      case 'C':
        input[i_max++]=12;
      case 'D':
        input[i_max++]=13;
      case '*':
        input[i_max++]=14;
      default:
        input[i_max++]=(key & 0xff)-'0';

    }


    /* code */
  }
  ioctl(fd,LCD_IOCTL_CLEAR,NULL);
  led_data = LED_ALL_OFF;
  ioctl(fd, LED_IOCTL_SET, &data);
  printf("turn off all LED lamp\n" );
  sleep(5);
  led_data = LED_ALL_ON;
  while (1) {
  /*LED part*/
    led_data << 4;
    led_data = led_data+input[i];
    ioctl(fd, LED_IOCTL_SET, &data);
  /*7seg*/
    if (input[i] < 10) {
      seg >> 4;
      seg = seg+input[i]*65536;
      seg_data.Mode = _7SEG_MODE_HEX_VALUE;
      seg_data.Which= _7SEG_ALL;
      seg_data.Value= seg;
      /* code */
    }


    if (i < imax-1) {
      i++;
      /* code */
    } else {
      i=0;
      /* code */
    }
    /* code */
  }

  close(fd);
  return 0;
}
