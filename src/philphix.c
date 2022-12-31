/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  //fprintf(stderr, "You need to implement readDictionary\n");
  const int length = 60;
  FILE *fp;
  if((fp = fopen(dictName, "r")) != NULL){
  	while (1) {
		char *key = malloc(sizeof(char *) * length);
		char *value = malloc(sizeof(char *) * length);
		if(fscanf(fp, "%s%s", key, value) == EOF) {
			break;
		}

		if(strlen(key) && strlen(value)) {
			insertData(dictionary, key, value);
		}
  	}
  	fclose(fp);
  }else {
	fprintf(stderr, "no file!\n");
	exit(61);
  }

}

/* Task 4 */
void processInput() {
  // -- TODO --
  //fprintf(stderr, "You need to implement processInput\n");
  const int length = 60;
  char *word = malloc(sizeof(char *)*length);
  char ch;  
  int index = 0;
  
  while ((ch = getchar()) != EOF || strlen(word) != 0) {
    
    if(isalpha(ch) || isdigit(ch)) {
      strcpy(word + index++, &ch);
	    continue;
    }

    strcpy(word + index, "\0");
    index = 0;
    char *str = malloc(sizeof(char *)*length);
    strcpy(str, word);
    
    //exact word
    char *result; 
    result= (char *)findData(dictionary, word);
    if(result != NULL) {
	    output(result, ch, word, str);
	  continue;
    }
    
    //all but first character lowercase
    int i; 
    for(i = 1 ;i < strlen(word); i++){
       *(word + i) = tolower(*(word + i));
    }
    result = (char*)findData(dictionary, word);
    if(result != NULL) {
      output(result, ch, word, str);
      continue;      
    } 

    //all lowercase
    *word = tolower(*word);
    result = (char*)findData(dictionary, word);
    if(result != NULL) {
      output(result, ch, word, str);
      continue;      
    }

    
    //can't find
    output(str, ch, word, str);
    
  }
  free(word); 
}

void output(char* res, char ch, char* word, char* str){
    printf("%s", res);
    if(ch != EOF) printf("%c", ch);
    memset(word, 0 ,sizeof(*word));
    free(str);
}
