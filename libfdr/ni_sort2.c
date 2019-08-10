/* ni_sort2.c

   James S. Plank
   CS360 lecture notes on red-black trees.
   January, 2015

   This program works like ni_sort1.c, except it doesn't calculate the key string.
   Instead, it uses the person struct as a key, and writes a comparison function
   for persons.  It uses jrb_insert_gen() to insert into the tree.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"

typedef struct {
  char *name;
  int score;
} Person;

int compare(Jval j1, Jval j2)
{
  Person *p1, *p2;

  p1 = (Person *) j1.v;
  p2 = (Person *) j2.v;

  if (p1->score > p2->score) return 1;
  if (p1->score < p2->score) return -1;
  return strcmp(p1->name, p2->name);
}

int main(int argc, char **argv)
{
  JRB t, tmp;
  IS is;
  Person *p;
  int nsize, i;


  if (argc != 2) { fprintf(stderr, "usage: input-nn.txt filename\n"); exit(1); }

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  t = make_jrb();

  // while (get_line(is) >= 0) {
  //   if (is->NF > 1) {

  //     /* Creating the person is just like ni_sort1.c -- please see the comments
  //        there for how this is done. */

  //     p = malloc(sizeof(Person));
  //     p->score = atoi(is->fields[is->NF-1]);

  //     nsize = strlen(is->fields[0]);
  //     for (i = 1; i < is->NF-1; i++) nsize += (strlen(is->fields[i])+1);

  //     p->name = (char *) malloc(sizeof(char)*(nsize+1));
  //     strcpy(p->name, is->fields[0]);

  //     nsize = strlen(is->fields[0]);
  //     for (i = 1; i < is->NF-1; i++) {
  //       p->name[nsize] = ' ';
  //       strcpy(p->name+nsize+1, is->fields[i]);
  //       nsize += strlen(p->name+nsize);
  //       // strcat(p->name, " ");
  //       // strcat(p->name, is->fields[i]);
  //     }

  //     /* We now insert using jrb_insert_gen, with the person struct as a key. */
  //     jrb_insert_gen(t, new_jval_v((void *) p), new_jval_v(NULL), compare);
  //   }
  // }

  while(get_line(is) >= 0){
    if(is->NF > 1){
      p = malloc(sizeof(Person));
      p->score = atoi(is->fields[is->NF-1]);
      nsize = strlen(is->fields[0]);
      for(int i = 1; i < is->NF-1; i++){
        nsize += strlen(is->fields[i]) + 1;
      }
      p->name = (char *)malloc(sizeof(char) * (nsize+1));
      strcpy(p->name, is->fields[0]);
      for(int i = 1; i < is->NF-1; i++){
        strcat(p->name, " ");
        strcat(p->name, is->fields[i]);
      }
    }
    jrb_insert_gen(t, new_jval_v((void*)p), new_jval_v(NULL), compare);
  }

  printf("In ra man hinh theo format yeu cau: \n");
  /* To print the people:*/
  jrb_traverse(tmp, t) { //t: RBTree
    p = (Person *) tmp->key.v;
    printf("%-40s %2d\n", p->name, p->score);
  }
  exit(0);
}
