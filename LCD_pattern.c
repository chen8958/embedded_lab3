#include<stdio.h>
#include<stdlib.h>
#include<sys/fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include"asm-arm/arch-pxa/lib/creator_pxa270_lcd.h"
int main(int argc, char const *argv[]) {
  int fd ,i , j;
  lcd_full_image_info_t display;
  if((fd = open("/dev/lcd",O_RDWR)) < 0){
    printf("Open /dev/lcd_faild.\n");
    exit(-1);
  }
  ioctl(fd,LCD_IOCTL_CLEAR,NULL);

  for (i=0;i < 0x800 ;i++){
    display.data[i] = (1<<16)-1;
    
  }
    ioctl(fd,LCD_IOCTL_DRAW_FULL_IMAGE,&display);

  close(fd);
  return 0;
}
