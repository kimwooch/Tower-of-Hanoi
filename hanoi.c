#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "list.h"


//******************************************************************||
//                      TOWER OF HANOI                              ||
//******************************************************************||

//**********************************
//helper functions
//**********************************

//structs for hanoi
//===================================
struct mstack
{
  list_t* list;
};

typedef struct mstack tower_t;

typedef struct hanoi
{
  tower_t * tower0;
  tower_t * tower1;
  tower_t * tower2;
  int move;
} hanoi_t;

//makes hanoi_t
//===================================

hanoi_t * make_hanoi(int disk)
{
  hanoi_t *hn = (hanoi_t *) malloc(sizeof(hanoi_t));
  hn->tower0 = make_mstack();
  hn->tower1 = make_mstack();
  hn->tower2 = make_mstack();
  for(int i = disk; i >=1 ; i--)
    {
      push(hn->tower0, i);
    }
  hn->move = 0;
  return hn;
}

//frees hanoi
//===================================

void free_hanoi(hanoi_t *game)
{
  free_stack(game->tower0);
  free_stack(game->tower1);
  free_stack(game->tower2);
  free(game);
}

//checks if it is valid move
//===================================

bool has_valid_move(tower_t *src, tower_t *dest)
{
  if(size_stack(src) == 0)
    {
      return false;
    }
  if (peek_stack(dest) == 0)
  {
    return true;
  }
  if(peek_stack(src) >= peek_stack(dest))
    {
      return false;
    }
  else
    {
      return true;
    }
}

//moves disk
//pre: it is a valid move
//===================================

void move_disk(tower_t *src, tower_t *dest)
{
  push(dest, peek_stack(src));
  pop(src);
}

//checks if tower is complete
//===================================

bool is_complete_tower(tower_t *src, int disk)
{
  if (size_stack(src) == disk)
    {
      return true;
    }
  else
    {
      return false;
    }
}

//prints a single disk
//===================================

void print_disk(int disk, int width)
{
  for (int i = 0; i < width - disk; i++)
  {
    printf(" ");
  }
  for (int i = 0; i < disk; i++)
  {
    printf("-");
  }
  printf("|");
  for (int i = 0; i < disk; i++)
  {
    printf("-");
  }
  printf("\n");
}


//prints a single tower
//===================================

void print_tower(tower_t *t, int id, int height)
{
  printf("Tower %d:\n", id);
  for (int k = 0; k < height-size_stack(t); k++)
  {
    print_disk(0, height);
  }

  int index = 0;
  while(index < size_stack(t))
    {
      print_disk(get_element_at(t->list, index), height);
      index++;
    }

  for(int j = 0; j < height*2 + 1; j++)
    {
      printf("=");
    }
  printf("\n");
}



//prints the game: towers and moves
//===================================

void print_hanoi(hanoi_t *game, int disk)
{
  printf("Moves: %d\n", game->move);
  print_tower(game->tower0, 0, disk);
  print_tower(game->tower1, 1, disk);
  print_tower(game->tower2, 2, disk);
}

//checks if tower range is valid
//return True iff value is either 0, 1, or 2
//===================================

bool check_tower_range(int val)
{
  return (val == 0 || val == 1 || val == 2);
}

//matches a tower to user input
//===================================

tower_t * match_tower(hanoi_t * game, int val)
{
  if (val == 0)
    {
      return game->tower0;
    }
   if (val == 1)
    {
      return game->tower1;
    }
   else
    {
      return game->tower2;
    }
}


//==========================================
//===================================
//============================
//=====================
//  play tower of hanoi
//=====================
//============================
//==========================================

int play_hanoi(hanoi_t * game, int disk)
{

  while(!(is_complete_tower(game->tower1, disk)) && !(is_complete_tower(game->tower2, disk)))
    {
      //Print the current state of the game
      print_hanoi(game, disk);
      int src, dest;

      printf("\nEnter a source tower: ");

      //check input for source tower to make sure it's an integer. If not, reprompt the user until getting an integer  
      char source[50];
      fgets(source, 50, stdin);
      while(!(sscanf(source, "%d", &src)) || !(strcmp(source, "\n")))
        {
          printf("\nPlease enter a valid source tower number: ");
          fgets(source, 50, stdin);
        }

      printf("Enter a destination tower: ");

      //check input for destination tower to make sure it's an integer. If not, reprompt the user until getting an integer
      char destination[50];
      fgets(destination, 50, stdin);
      while(!(sscanf(destination, "%d", &dest)) || !(strcmp(destination, "\n")))
        {
          printf("\nPlease enter a valid destination tower number: ");
          fgets(destination, 50, stdin);
        }      
      
      //checks if src or dest is a value other than 0, 1,2
      if (!(check_tower_range(src)) ||!( check_tower_range(dest)))
        {
          printf("\nPlease enter value 0, 1 or 2 for the source or destination tower number!\n");
        }
      
      //Check for an invalid case where source and destination tower is the same:
      else if(src == dest)
        {
          printf("\nThis move is invalid!. Pleaser re-enter source and destination tower numbers!\n\n\n");
        }
      
      //Since we checked if the inputs are valid, proceed to check if the move is valid
      else
        {
          //Match the input with the corresponding tower in the game
          tower_t * t1 = match_tower(game,src);
          tower_t * t2 = match_tower(game,dest);
      
          //checks if it is valid move
          if (has_valid_move (t1, t2))
            {
              move_disk(t1, t2);
              game->move++;
              printf("\n\n");
            }
          else //if disk is not smaller in src than dest
            {
              printf("\nThis move is invalid!\nThe disk in Tower %d is bigger than the current top disk in Tower %d.\nPlease enter a valid move.\n\n\n", src, dest);
            }
        }
    }
  
  printf("You won in %d moves!\n", game->move);
  print_hanoi(game, disk);
  return 0;
}
//**********************************
//main function
//**********************************

int main(void)
{
  int disk;
  printf("Enter a number of disks you want for each tower: "); //extra credit

  //Check user input to make sure it's an integer
  char d[10];
  fgets(d, 10, stdin);
  while(!(sscanf(d, "%d", &disk)) || !(strcmp(d, "\n")))
    {
      printf("\nPlease enter a valid disk number: ");
      fgets(d, 10, stdin);
    }

  //Start the game with valid number of disks per tower
  hanoi_t *game = make_hanoi(disk);
  play_hanoi(game, disk);
  free_hanoi(game);
  return 0;
}
