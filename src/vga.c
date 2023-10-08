/*
    VGA Handler
*/
#define WIDTH 80
#define HEIGHT 25
// Current row
int row = 0;
int debug = 0;
// Framebuffer adress
static char* const fb = (char*)(0xb8000);

void initTerminal(){
    // Clear the terminal
    char* tmp = "                                                                              ";
    for(int i = 0; i < 25; i++){
        kprintf(tmp);
    }
    row = 0;
    // Disable cursor
    outb(0x3D4, 0x0A);
  	outb(0x3D5, 0x20);
}


/*
    Print to the terminal
*/
void kprintf(char *string){
 // clearScreen();
  for(int i = 0; i < strlen(string); i++){
    charAt(string[i], i, row, 0x7);
  }
  row++;
}

void dkprintf(char* string){
    if(debug == 1)
        kprintf(string);
}

void charAt(char c, int x, int y, unsigned char color){
  int position = 2 * x + 160 * y;
  fb[position] = c;
  fb[position+1] = color;
}



int strlen(char *str){
  int i = 0;
  while(str[i++]){}
  return i;
}