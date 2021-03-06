/*
* chash.h
* By Gus Wiedey
*
* A quick-and-dirty hash function in C that allows string
* input to be parsed with switch statements (as opposed
* to ugly chains of ifs and else-ifs).
*
* Note: Because C doesn't like switches with case
* values that aren't compile-time constants, you
* can use hashdef() to generate a header file which
* will define the hashes you need as constant macros.
*/

#ifndef _CHASH_H_
#define _CHASH_H_

#include <stdio.h>
#include <string.h>

#define CHASH_STRLEN 50

// Hash function
int chash(char* str) {
  int i, tmp;
  int hash = 0;
  int shift = 0;
  for(i = 0; i < strlen(str); i++) {
    tmp = str[i] << shift;
    hash = hash ^ tmp;
    shift = ((shift + 3) % 8);
  }
  return hash;
}

// Header generation function
void hashdef(char *cmd_list) {
  int hash;
  char str[CHASH_STRLEN];
  FILE *fp = fopen(cmd_list, "r");

  printf("#ifndef _CONST_HASH_TMP_HEADER_\n");
  printf("#define _CONST_HASH_TMP_HEADER_\n");

  fscanf(fp, "%s", str);
  while(!feof(fp)) {
    if(str[0] == '#') {
      hash = chash(&str[1]);
      printf("\n#define %s_case %d", &str[1], hash);
    } else {
      hash = chash(str);
      printf(": case %d", hash);
    }
    fscanf(fp, "%s", str);
  }

  printf("\n\n#endif /* _CONST_HASH_TMP_HEADER_ */\n");
}

#endif /* _CHASH_H_ */
