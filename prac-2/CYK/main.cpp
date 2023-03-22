#include "CYK.h"

int main() {
  CYK cyk("input.txt");
  cyk.recognize("toRecognize.txt", "output.txt");

  return 0;
}
