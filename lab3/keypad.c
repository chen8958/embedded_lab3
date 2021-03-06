/*
#define VK_S2   1
#define VK_S3   2
#define VK_S4   3
#define VK_S5   10
#define VK_S6   4
#define VK_S7   5
#define VK_S8   6
#define VK_S9   11
#define VK_S10  7
#define VK_S11  8
#define VK_S12  9
#define VK_S13  12
#define VK_S14  14
#define VK_S15  0
#define VK_S16  15
#define VK_S17  13
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include"asm-arm/arch-pxa/lib/creator_pxa270_lcd.h"


int main(int argc, char const *argv[]) {
  unsigned short  key;
  int             fd, ret;
  if ((fd = open("/dev/lcd", O_RDWR)) < 0) {
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
    printf("%c\n",(key & 0xff));
    if ((key & 0xff) == '#') {
      break;
      /* code */
    }
    /* code */
  }
  close(fd);

  return 0;
}
