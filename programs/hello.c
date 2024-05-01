/*
  Basic "Hello World" program
*/

int main(){
  unsigned int c = 3;
  for(int i = 0; i < 500; i++){
    c+= i;
  } 
int src = 1;
int dst;

/*asm ("mov %1, %0\n\t"
    "add $1, %0"
    : "=r" (dst)
    : "r" (src));*/
asm("mov 0x4c, %dl\n"
"mov $'H', %al\n"
"movb %al, 0xB8000\n"
"movb %dl, 0xB8001");
return 0;
}