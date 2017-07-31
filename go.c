/*
* CGG (C Go Game)
* By Gus Wiedey
* Version 0.1.0
*/

/**********************
*  PREPROCESSOR CRAP  *
**********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"

#define VER_NUM "v0.1.0"
#define CMD_LEN 50
#define ARG_MAX 5
#define ARG_LEN 10

/**********************
*      FUNCTIONS      *
**********************/
int cmdParse(char*, char**);
int move(char*, char*, char*, Board*);
void saveGame(char*, Board*);
int loadGame(char*, Board*);
void display(int, Board*);
void help();


int main(int argc, char *argv[]) {
  // Welcome message
  printf("WELCOME TO CGG (C Go Game) %s\nBy Gus Wiedey\nType \'help\' for a list of commands.\n\n", VER_NUM);

  // Variable definitions
  int a, i, j, valid, argCount, exitVal;
  int continueLoop = 1;
  char c, colChar, colMax;
  char cmd[CMD_LEN], exitString[60];
  char **args = (char**)malloc(sizeof(char*) * ARG_MAX);
  Board *board;

  // malloc each element of **args
  for(i = 0; i < ARG_MAX; i++) {
    args[i] = (char*)malloc(sizeof(char) * ARG_LEN);
  }

  // Read & process user commands
  while(continueLoop) {
    printf("> ");
    fgets(cmd, CMD_LEN, stdin);
    argCount = cmdParse(cmd, args);

    if(!strcmp(args[0], "init")) {
      // Allocate memory for a new board of the correct size
      if(!strcmp(args[1], "beginner")) {
        board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 9));
        board->dim = beginner;
      }
      else if(!strcmp(args[1], "small")) {
        board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 13));
        board->dim = small;
      }
      else if(!strcmp(args[1], "standard")) {
        board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 19));
        board->dim = standard;
      }
      else {
        printf("ERROR: Invalid size argument \'%s\' - expected either \'beginner\', \'small\', or \'standard\'\n", args[1]);
        continue;
      }

      // Allocate memory for grid rows and fill grid with empty spaces
      for(i = 0; i < board->dim; i++) {
        board->grid[i] = (Space*)malloc(sizeof(Space) * board->dim);
        for(j = 0; j < board->dim; j++) {
          board->grid[i][j] = empty;
        }
      }

      printf("New game created (board size %dx%d)\n", board->dim, board->dim);
    }
    else if(!strcmp(args[0], "show")) {
      if(!strcmp(args[1], "noindex")) {
        display(0, board);
      }
      else {
        display(1, board);
      }
    }
    else if(!strcmp(args[0], "move")) {
      switch(argCount) {
        case 3:
        exitVal = move("!", args[1], args[2], board);
        break;
        case 4:
        exitVal = move(args[1], args[2], args[3], board);
      }
      exitVal = move(args[1], args[2], args[3], board);
      switch(exitVal) {
        case 0:
        printf("a winner is you!");
        break;
        case -1:
        printf("nice job breaking it dipshit, this is why we can\'t have nice things");
        break;
        case 1:
        printf("nice job breaking it dipshit, this is why we can\'t have nice things");
        break;
        case 2:
        printf("nice job breaking it dipshit, this is why we can\'t have nice things");
        break;
        case 3:
        printf("nice job breaking it dipshit, this is why we can\'t have nice things");
        break;
        case 4:
        printf("nice job breaking it dipshit, this is why we can\'t have nice things");
        break;
        case 5:
        printf("nice job breaking it dipshit, this is why we can\'t have nice things");
        break;
      }
    }
    else if(!strcmp(args[0], "save")) {
      saveGame(args[1], board);
    }
    else if(!strcmp(args[0], "load")) {
      exitVal = loadGame(args[1], board);
      switch(exitVal) {
        case 0:
        printf("Saved game successfully loaded from file \'%s\'.\n", args[1]);
        break;
        case 1:
        printf("ERROR: Could not open file \'%s\'\n", args[1]);
        break;
        case 2:
        printf("ERROR: Invalid board size parameter in file \'%s\'\n", args[1]);
        break;
        case 3:
        printf("ERROR: Invalid board state data in file \'%s\'\n", args[1]);
        break;
      }
    }
    else if(!strcmp(args[0], "help")) {
      help();
    }
    else if(!strcmp(args[0], "quit")) {
      // set continueLoop to false so that loop ends
      continueLoop = 0;
    }
    else if(!strcmp(args[0], "")) {
      // extra condition to prevent program from printing error message if user simply hits enter with no input
      continue;
    }
    else {
      // error message for invalid input
      printf("ERROR: Unknown command \'%s\'. (Type \'help\' for a list of commands)\n", args[0]);
    }
  }

  // Ask user if they want to save before quitting (and then quit)
  strcpy(exitString, "Do you want to save your game before quitting? (y/n): ");
  do {
    printf("%s", exitString);
    c = getc(stdin);
    switch(tolower(c)) {
      case 'y':
      printf("\nWhere do you want to save your game?\nFilename: ");
      fgets(cmd, CMD_LEN, stdin);
      cmdParse(cmd, args);
      saveGame(args[0], board);
      printf("Game saved to file %s\n", args[0]);
      continueLoop = 0;
      break;
      case 'n':
      printf("\n");
      continueLoop = 0;
      break;
      default:
      strcpy(exitString, "Please enter either y or n: ");
      continueLoop = 1;
      break;
    }
  } while(continueLoop);
  printf("Goodbye!\n\n");
}


int cmdParse(char *cmd, char *args[]) {
  // Variable definitions
  int i = 0; // current index in string cmd
  int a = 0; // current index in array args
  int b = 0; // current index in string args[a]

  // While loop to iterate over the raw string and split it into arguments
  while((cmd[i] != '\0') && (cmd[i] != '\n') && (i < CMD_LEN)) {
    if(cmd[i] == ' ') {
      args[a][b] = '\0';
      a++;
      b = 0;
    }
    else {
      args[a][b] = cmd[i];
      b++;
    }
    i++;
  }

  // Add final terminating null char and return number of arguments
  args[a][b] = '\0';
  return (a + 1);
}
