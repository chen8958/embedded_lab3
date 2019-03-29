typedef struct lcd_write_info {
  unsigned char Msg[512];
  unsigned short Count;
  int CursorX, CursorY;
  /* data */
} lcd_write_info_t;
typedef struct lcd_full_image_info {
  unsigned short data[0x800];
  /* data */
} lcd_full_image_info_t;

#define LCD_IOCTL_CLEAR     LCD_IO(0x0)
#define LCD_IOCTL_WRITE     LCD_IO(0x01, lcd_write_info_t)
#define LCD_IOCTL_CUR_ON    LCD_IO(0x02)
#define LCD_IOCTL_CUR_OFF   LCD_IO(0x03)
#define LCD_IOCTL_CUR_GET   LCD_IO(0x04, lcd_write_info_t)
#define LCD_IOCTL_CUR_SET   LCD_IO(0x05, lcd_write_info_t)
#define LCD_IOCTL_DRAW_FULL_IMAGE LCD_IOW(0x06, lcd_full_image_info_t)
