/* Uses red-black trees to sort standard input lexicographically in reverse order.
   It does this by traversing the tree in reverse order.  */

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

 if (argc != 2) { fprintf(stderr, "usage: strrsort1.txt filename\n"); exit(1); }

  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  b = make_jrb();

  printf("Noi dung file strrsort1.txt: \n");
  while (get_line(is) >= 0) {
    (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
  }

  printf("Ket qua chuong trinh strrsort1.c sap xep cac so + dong ki tu cua file dau vao theo thu tu NGUOC abc (phan biet chu hoa chu thuong), su dung cay do den: \n");
  jrb_rtraverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
  exit(1);
}
