/* Uses red-black trees to sort standard input lexicographically, and
   it removes duplicate lines.  It does this by checking for a line
   before inserting it into the tree. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int main(int argc, char **argv)
{

  JRB b;
  JRB bn;
  IS is;
  int i;

  if (argc != 2) { fprintf(stderr, "usage: strusort.txt filename\n"); exit(1); }

  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  b = make_jrb();

  printf("Noi dung file strusort.txt: \n");

  while (get_line(is) >= 0) {
    if (jrb_find_str(b, is->text1) == NULL) {
      (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
    }
  }

  printf("Ket qua chuong trinh strusort.c sap xep cac dong ki tu cua file dau vao theo thu tu abc (phan biet chu hoa chu thuong), BO cac dong giong nhau, su dung cay do den: \n");
  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
  exit(0);
}
