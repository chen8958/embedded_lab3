typedef struct _7Seg_Info{
  unsigned char Mode;
  unsigned char Which;
  unsigned long Value;
} _7seg_info_t;

#ifndef _7SEG_MODE_PATTERN
#define _7SEG_MODE_PATTERN 0
#endif

#ifndef  _7SEG_MODE_HEX_VALUE
#define _7SEG_MODE_HEX_VALUE 1
#endif

#ifndef  _7SEG_D5_INDEX
#define _7SEG_D5_INDEX 8
#endif

#ifndef  _7SEG_D6_INDEX
#define _7SEG_D6_INDEX 4
#endif

#ifndef  _7SEG_D7_INDEX
#define _7SEG_D7_INDEX 2
#endif

#ifndef  _7SEG_D8_INDEX
#define _7SEG_D8_INDEX 1
#endif

#ifndef  _7SEG_ALL
#define _7SEG_ALL (_7SEG_D5_INDEX|_7SEG_D6_INDEX|_7SEG_D7_INDEX|_7SEG_D8_INDEX)
#endif

_7seg_info_t  data;
int           fd, ret, i;
if ((fd = open('/dev/lcd',O_RDWR)) <0 ) {
  return (-1);
  /* code */
}
ioctl(fd, _7SEG_IOCTL_ON, NULL);
data.Mode = _7SEG_MODE_HEX_VALUE;
data.Which= _7SEG_ALL;
data.Value= 0x2004;
iocal(fd, _7SEG_IOCTL_SET, &data);
sleep (3);
data.Mode=_7SEG_MODE_PATTERN;
data.Which=_7SEG_D5_INDEX|_7SEG_D8_INDEX;
data.Value=0x6d7f;
ioctl(fd,_7SEG_IOCTL_SET,&data);
ioctl(fd,_7SEG_IOCTL_OFF,NULL);
close(fd);
