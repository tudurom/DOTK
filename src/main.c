#include "game.h"

void buildMenu();

int main(int argc, char **argv) {
  initConsole();
  setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  buildMenu();
  return 0;
}

void buildMenu() {
  int i;
  int line;

  for (i = TITLE_ART_START_Y; i <= TITLE_ART_END_Y; i++) {
    clearScreen();
    setTextColor(TITLE_ART_COLOR);
    line = printASCIIArtFromFile(i, TITLE_ART, CENTER) + TITLE_ART_END_Y;
    resetColor();
    Sleep(100);
  }
  resetColor();
  char* options[] = {"Play", "Quit"};
  printf("%d", buildOptionsMenu(line + 1, 2, options, CENTER, CYAN));
}
