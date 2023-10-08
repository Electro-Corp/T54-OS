/*
  Basic string operations
*/
#ifndef STRING_H
#define STRING_H

static int strlen(char *str){
  int i = 0;
  while(str[i++]){}
  return i;
}

static char* strcat(char *dst, const char *src){
  int n = strlen(src);
	if (n != 0) {
		char *d = dst;
		const char *s = src;
		while (*d != 0)
			d++;
		do {
			if ((*d = *s++) == 0)
				break;
			d++;
		} while (--n != 0);
		*d = 0;
	}
	return (dst);
}

static char* strcpy(char *dst, const char *src){
  int n = strlen(src);
	if (n != 0) {
		char *d = dst;
		const char *s = src;
		do {
			if((*d++ = *s++) == 0) {
				/* NUL pad the remaining n-1 bytes */
				while(--n != 0)
					*d++ = 0;
				break;
			}
		}while (--n != 0);
	}
	return (dst);
}
#endif