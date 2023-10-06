/*
    VGA Handler
*/
#define WIDTH 80
#define HEIGHT 25
// Current row
int row = 0;
int debug = 1;
// Framebuffer adress
static char* const fb = (char*)(0xb8000);

void initTerminal(){
    char* tmp = "                                                                              ";
    for(int i = 0; i < 25; i++){
        kprintf(tmp);
    }
    row = 0;
}


/*
    Print to the terminal
*/
void kprintf(char *string){
 // clearScreen();
  for(int i = 0; i < strlen(string); i++){
    charAt(string[i], i, row, 0xF);
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