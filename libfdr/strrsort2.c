/* Uses red-black trees to sort standard input lexicographically in
   reverse order.  It does this by creating a new comparison function
   revcomp, which simply returns -strcmp().  Now the tree sorts in
   reverse order, so it is traversed in the forward direction. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int revcomp(Jval k1, Jval k2)
{
  return -strcmp(k1.s, k2.s);
}

int main(int argc, char **argv)
{

  JRB b;
  JRB bn;
  IS is;
  int i;

  if (argc != 2) { fprintf(stderr, "usage: strrsort2.txt filename\n"); exit(1); }

  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  b = make_jrb();

  printf("Noi dung file strrsort2.txt: \n");
  while (get_line(is) >= 0) {
        (void) jrb_insert_gen(b, new_jval_s(strdup(is->text1)), new_jval_v(NULL), revcomp);
        // (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
  }

  printf("Ket qua chuong trinh strrsort2.c sap xep cac so + dong ki tu cua file dau vao theo thu tu NGUOC abc (phan biet chu hoa chu thuong), su dung cay do den: \n");
  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
  exit(0);

}
