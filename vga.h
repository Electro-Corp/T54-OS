/*
    Header for VGA
*/


// Terminal
void initTerminal();
void kprintf(char *string);
void dkprintf(char* string);

// UTILS
void charAt(char c, int x, int y, unsigned char color);
int strlen(char *str);