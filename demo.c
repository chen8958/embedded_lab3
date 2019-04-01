#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "asm-arm/arch-pxa/lib/creator_pxa270_lcd.h"
int main(int argc, char const *argv[]) {
  unsigned short  led_data, key;
  int             fd, ret, i=0, i_max=0;
  int             input[10];
  unsigned long   seg = 0;
  _7seg_info_t    seg_data;
  lcd_write_info_t display;

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
        break;
      case 'B':
        input[i_max++]=11;
        break;
      case 'C':
        input[i_max++]=12;
        break;
      case 'D':
        input[i_max++]=13;
        break;
      case '*':
        input[i_max++]=14;
        break;
      default:
        input[i_max++]=(key & 0xff)-'0';

    }


    /* code */
  }
  ioctl(fd,LCD_IOCTL_CLEAR,NULL);
  led_data = LED_ALL_OFF;
  ioctl(fd, LED_IOCTL_SET, &led_data);
  printf("turn off all LED lamp\n" );
  ioctl(fd, _7SEG_IOCTL_ON, NULL);
  seg_data.Mode = _7SEG_MODE_PATTERN;
  seg_data.Which= _7SEG_ALL;
  seg_data.Value= 0x00000000;
  ioctl(fd, _7SEG_IOCTL_SET, &seg_data);
  sleep(5);
  led_data = LED_ALL_ON;
  printf("loop start \n");

  while (1) {
  /*LED part*/
    led_data=led_data << 4;
    led_data = 0xff & (led_data+input[i]);
    ioctl(fd, LED_IOCTL_SET, &led_data);
  /*7seg*/
    printf("output[%d] = %d \n",i,input[i]);

      seg = seg >> 8;
      switch (input[i]) {
        case 0:
        seg = seg+(0x3f << 24);
        break;
        case 1:
        seg = seg+(0x06 << 24);
        break;
        case 2:
        seg = seg+(0x5b << 24);
        break;
        case 3:
        seg = seg+(0x4f << 24);
        break;
        case 4:
        seg = seg+(0x66 << 24);
        break;
        case 5:
        seg = seg+(0x6d << 24);
        break;
        seg = seg+(0x7d << 24);
        case 7:
        seg = seg+(0x07 << 24);
        break;
        case 8:
        seg = seg+(0x7f << 24);
        break;
        case 9:
        seg = seg+(0x6f << 24);
        break;
        case 10:
        seg = seg+(0x77 << 24);
        break;
        case 11:
        seg = seg+(0x7c << 24);
        break;
        case 12:
        seg = seg+(0x39 << 24);
        break;
        case 13:
        seg = seg+(0x5e << 24);
        break;
        case 14:
        seg = seg+(0x80 << 24);
        break;
      }

      seg_data.Value = seg;
      ioctl(fd, _7SEG_IOCTL_SET, &seg_data);
      printf("seg = %X \n", seg);
      /* code */

    /*wait*/
    sleep(1);


    if (i < i_max-1) {
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
