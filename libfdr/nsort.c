/* Uses red-black trees to sort like sort -n -- i.e. it treats each
   line as an integer, and sorts it that way.  If the lines are not
   integers, or there are duplicate lines, anything goes.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"

int main(int argc, char **argv)
{
  JRB b;
  JRB bn;
  IS is;
  int i;

  if (argc != 2) { fprintf(stderr, "usage: nsort.txt filename\n"); exit(1); }

  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  b = make_jrb();

  printf("Noi dung file nsort.txt: \n");
  while (get_line(is) >= 0) {
    (void) jrb_insert_int(b, atoi(is->text1), new_jval_s(strdup(is->text1)));
    printf("%s", is->text1);
  }

  printf("Ket qua chuong trinh nsort.c sap xep cac so nguyen trong file nsort.txt theo thu tu tang dan su dung cay do den: \n");
  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->val));
  }
  exit(0);

}
