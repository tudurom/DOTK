#include "engine.h"
#include <stdlib.h>

CONSOLE_SCREEN_BUFFER_INFO initialConsoleInfo;
WORD initialConsoleAttributes;

inline long long getTime() {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000LL + tv.tv_sec;
}

int getRandInRange( int min, int max ) {
	srand(getTime());

	return min + rand() % (max - min + 1);
}

int getConsoleWidth() {
  CONSOLE_SCREEN_BUFFER_INFO info;
  int width;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
  width = info.srWindow.Right - info.srWindow.Left + 1;

  return width;
}

int getConsoleHeight() {
  CONSOLE_SCREEN_BUFFER_INFO info;
  int height;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
  height = info.srWindow.Bottom - info.srWindow.Top + 1;

  return height;
}

void setWindowSize(int width, int height) {
  char result[100];

  sprintf(result, "mode %d,%d", width, height);
  system(result);
}


void putStrAlign( int y, char *s, enum ALIGN align ) {
  switch(align) {
  case LEFT:
    putStr(0, y, s);
    break;
  case CENTER:
    putStr((getConsoleWidth() - strlen(s)) / 2, y, s);
    break;
  case RIGHT:
    putStr((getConsoleWidth() - strlen(s)), y, s);
    break;
  }
}

int printASCIIArt( int y, char *s, enum ALIGN align ) {
  char *line;
  int i;

  line = strtok(s, "\n"); // Afiseaza linie cu linie
  i = 0;
  while(line != NULL) {
    putStrAlign(y + i, line, align);
    line = strtok(NULL, "\n");
    i++;
  }

  return i;
}

int printASCIIArtFromFile( int y, char *path, enum ALIGN align ) {
  FILE *file = fopen(path, "r");
    char fileContents[1000];
    char c;
    int i;
    // Pune tot continutul fisierului intr-un string, apoi il paseaza functiei
    // printASCIIArt
    memset(&fileContents, 0, sizeof(fileContents));
    if(file != NULL) {
      c = fgetc(file);
      i = 0;
      while(c != EOF) {
        fileContents[i] = c;
        i++;
        c = fgetc(file);
      }
      fclose(file);
    }
    return printASCIIArt(y, fileContents, align);
}

void initConsole() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  GetConsoleScreenBufferInfo(hConsole, &initialConsoleInfo);
  initialConsoleAttributes = initialConsoleInfo.wAttributes;
}

void resetColor() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(hConsole, initialConsoleAttributes);
}

int buildOptionsMenu(int y, int n, char* options[], enum ALIGN align, int color) {
  int i;
  char str[100];
  int pressed, escPressed;

  for(i = 0; i < n; i++) {
    sprintf(str, "%d) %s", i + 1, options[i]);
    setTextColor(color);
    putStrAlign(y + i, str, align);
    resetColor();
  }
  i = 1;
  pressed = 0;
  do {
    Sleep(SLEEPCONST);
    pressed = getKey(VK_0 + i);
    escPressed = getKey(VK_ESCAPE);
    if(!pressed)
      i = (i + 1) % (n + 1);
  } while(!pressed && !escPressed);
  if(escPressed)
    return 0;
  return i;
}
