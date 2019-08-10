/* Uses red-black trees to sort like sort -n only now if two lines
   have the same atoi() value, then they are sorted lexicographically.
   This uses jrb_insert_gen().  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int compare(Jval k1, Jval k2)
{
  int i1, i2;

  i1 = atoi(k1.s);
  i2 = atoi(k2.s);

  if (i1 > i2) return 1;
  if (i1 < i2) return -1;
  return strcmp(k1.s, k2.s);
}

int main(int argc, char **argv)
{

  JRB b;
  JRB bn;
  IS is;
  int i;

  if (argc != 2) { fprintf(stderr, "usage: nsort2.txt filename\n"); exit(1); }

  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  b = make_jrb();

  printf("Noi dung file nsort2.txt: \n");
  while (get_line(is) >= 0) {
    if(jrb_find_gen(b, new_jval_s(strdup(is->text1)), compare) == NULL){
      (void) jrb_insert_gen(b, new_jval_s(strdup(is->text1)),
                               new_jval_v(NULL), compare);
      // (void)jrb_insert_gen(b, strdup(is->text1), new_jval_v(NULL), compare);
    }
    printf("%s", is->text1);
  }

  printf("Ket qua chuong trinh nsort2.c sap xep cac (so + dong ki tu)\n cua file dau vao theo thu tu tang dan (duoc trung lap): \n");
  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
  exit(0);
}
