/* Strsort.c - sort lines of input lexicographically using JRB's. */
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

  if (argc != 2) { fprintf(stderr, "usage: strsort.txt filename\n"); exit(1); }

  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  b = make_jrb();

  printf("Noi dung file strsort.txt: \n");
  while (get_line(is) >= 0) {
    (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
    printf("%s", is->text1);
  }

  printf("Ket qua chuong trinh strsort.c sap xep cac dong ki tu cua file dau vao theo abc (phan biet chu hoa chu thuong), su dung cay do den: \n");
  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
  exit(0);

}

