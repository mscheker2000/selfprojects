#include <tictactoe.h>
#include <stdio.h>
#include <stdlib.h>
//code Mark Scheker
//instructions just prints out the instructions of how to start the game
int instructions()
{
  printf("\n\nJust a game of tictactoe\n To Select Mode Enter:\n");
  printf("\n1 for Solo\n2 for two players\n");
  selection();
 
  return 0;
}
//selection takes in the user input and calls the gamemode repsective to the input
void selection()
{
  int mode = 0;
  printf("Enter Mode: ");
  scanf("%d",&mode);
  if (mode == 1)
    solo();
  else if(mode == 2)
    twoplayer();
  else
  {
    if (mode == 0)
      scanf("%c", &mode);
    printf("\ninvalid input\n");
    selection();
  }
  printf("\n");
  return;
}
//solo is the gamemode that only requires 1 player, playing against a chicken
void solo()
{
  char display[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; //this is the array that represents the board
  int check;
  int count;
  int num;
  int start;
  int i;
  start = 0;
  check = 0;
  count = 0;
  printf("\n");
  num = selectnum(); //select to start first or have chicken start first
  visual(display); //print out a starting display for player to see board layout
  if(num == 2) //if chicken starts
  {
    start = startchick(&display, 2); //get strategic starting position
    printf("chicken:\n");
    visual(display);
    player(&display,num,1); //player input
    visual(display);
    count+=2;
  }
  else
  {
    player(&display, num, 1); //player input
    visual(display);
    startchick(&display, 1); //strategic starting position for chicken, 
    printf("chicken:\n");
    visual(display);
    count+=2;

  }
  while ((check == 0)&&(count <9))
  {//iterate through taking turns till board is filled
    if(num == 2) //if chicken starts
    {

      circuischicken(&display,count, start); //strategy for winning

      count++;
      printf("chicken:\n");
      visual(display);
      check = checkresult(display, 1, 1); //check if win
      if((count==9)||(check))
      {
        if(check != 1)
          printf("Cats Game!"); //tie
        return;
      }
    }
    player(&display,num, 1); 
    count++;
    visual(display);
    check = checkresult(display, num, 2);
    if((count==9)||(check))
    {
      if(check != 1)
        printf("Cats Game!");
      return;
    }
    if(num == 1) //player starts
    {
      if(counterai(&display,3)!= 2) //see if chicken can get win
      {
      }
      else
      {
        counterai(&display,4); //counter player
      }
      count++;
      printf("chicken:\n");
      visual(display);
      check = checkresult(display, 2, 1);
    }
  }
  return;
}
int selectnum()
{ //select num is to get the players input of starting first or second
  int xo = 0;
  printf("enter 1 or 2 to start first or second\n");
  printf("\nenter: ");
  scanf("%d",&xo);
  
  if(xo == 1)
    return 1;
  else if(xo == 2)
    return 2;
  else
  { if(xo == 0)
        scanf("%c",&xo);
    printf("\ninvalid input\n");
    selectnum();
  }
}
int startchick(char *display, int num)
{//startchick is the strategic starting position for the chicken
  int start;
  char xo = 'X';
  if(num == 1) // if player starts first
    xo = 'O';
  int i;
  start = 1 + rand() % (4 - 1 + 1);
  
  if ((num == 2) || ((num == 1)&&(display[4] == 'X')))
  {
  if(start == 1)
    display[0] = xo;
  else if(start == 2)
    display[2] = xo;
  else if(start ==3)
    display[6] = xo;
  else
    display[8] = xo;
  }
  else
    display[4]= xo;

  return start;

}

void circuischicken(char *display, int count, int start)
{ //circuischicken is the strategic moves that the chicken makes when starting first
  int i;
  i = 0;
  int a;
  int b;
  int c;
  int d;
  int e;
  char xo;
  char ox;
  int bot;
  bot = 1 + rand() / (RAND_MAX / (2 - 1 + 1) + 1);
  ox = 'O';
  xo = 'X';
  
  if((count == 2)&&(start != 0))
  {//moves to make during chickens 2nd turn 
    if((start == 1)||(start == 4))
    {
      if((display[2] == ox)||(display[5] == ox)||(display[1] == ox))
        display[6] = xo;
      else if((display[3] == ox)||(display[6] == ox)||(display[7] == ox))
        display[2] = xo;
      else if((display[0] == ox) || (display[8] == ox)||(display[4] == ox))
        {
          bot = 1 + rand() / (RAND_MAX / (2 - 1 + 1) + 1);
          if(bot == 1)
            display[6] = xo;
          else
            display[2] = xo;
        }
    }
    else if((start == 2)||(start == 3))
    {
      if((display[1] == ox)||(display[0] == ox)||(display[3] == ox))
        display[8] = xo;
      else if((display[5] == ox)||(display[8] == ox)||(display[7] == ox))
        {
        display[0] = xo;
        }
      else if((display[2] == ox) || (display[6] == ox)||(display[4] == ox))
      {
        bot = 1 + rand() / (RAND_MAX / (2 - 1 + 1) + 1);
        if(bot == 1)
          display[8] = xo;
        else
          display[0] = xo;
      }

    }

  }
  else if((count == 4))
   {//moves to make during chickens 3rd turn
    if((counterai(display,2) == 1))
        return;
    if((display[4] == 'O'))
    {
      if(counterai(display,1) == 0)
        return;
    }
     if(start ==1)
     {
       a = 2;
       b = 3;
       c = 6;
       d = 8;
       e = 7;
     }
     else if(start == 2)
     {
       a = 0;
       b = 5;
       c = 8;
       d = 6;
       e = 7;
     }
     else if (start == 3)
     {
       a = 0;
       b = 5;
       c = 8;
       d = 2;
       e = 1;
     }
     else
     {
       a = 2;
       b = 3;
       c = 6;
       d = 0;
       e = 1;
     }
     if((display[a] == xo)&&(display[b] == ox))
       display[4] = xo;
     else if ((display[a] == xo)&&(display[d] != ox))
       display[d] = xo;
     else if((display[a] == xo))
       display[c] = xo;
     else if ((display[c] == xo)&&(display[e] == ox))
       display[4] = xo;
     else if((display[c] == xo)&&(display[d] == ox))
       display[d] = xo;
     else
       display[a] = xo;
  }
  else
    { //moves to make during remaining turns
      if(counterai(display,2)==1)
      {
        //first check if chicken can make a move to win immediatly
      }
      else if(counterai(display,1)==0)
      { //else have the chicken counter player's move
      }
    }
    
}
int counterai(char *display, int num)
{ //counterai, just have general cases for the chicken to counter player's moves
//and check if a winning move can be made
 int xo;
 int ox;
 int obeyme; //this is just the value that the chicken will input on the board
 int i;
 int cnt = 0;
 int nopar; //a value that this function will return for indication of move made or not
 i = 0;
 if (num == 1)
   {//if chicken is tarting and countering
     xo = 'O';
     ox = 'X';
     obeyme = ox;
     nopar = 0;
   }
 else if(num == 2)
 {//if chicken is starting and checking winning moves
   xo = 'X';
   ox = 'O';
   obeyme = xo;
   nopar = 1;
 }
 else if(num == 3)
 {//if player is starting, chicken is checking winning moves
   xo = 'O';
   ox = 'X';
   obeyme = xo;
   nopar = 0;
 }
 else
 {//if player is starting, chicken is countering
   xo = 'X';
   ox = 'O';
   obeyme = ox;
   nopar = 1;
 }
 //start general cases
      while(i < 9)
      {
        if((i<3)&&(display[i] == xo)&&(display[i+6] == xo)&&(display[i+3]!=ox))
          {
            display[i+3] = obeyme;
            return nopar;
          }
          
        else if(((i == 0)||(i == 3)||(i == 6))&&(display[i] == xo)&&(display[i+2]==xo)&&(display[i+1]!=ox))
          {
            display[i+1] = obeyme;
            return nopar;
          }
        else if((display[0] == xo)&&(display[8]==xo)&&(display[4]!=ox))
          {
            display[4] = obeyme; 
            return nopar;
          }
        else if((display[0] == xo)&&(display[8] !=ox)&&(display[4]==xo))
        {
          display[8] = obeyme;
          return nopar;
        }
        else if((display[0] != ox)&&(display[8] ==xo)&&(display[4]==xo))
        {
          display[0] = obeyme;
          return nopar;
        }
        else if((display[2] == xo)&&(display[6]==xo)&&(display[4]!=ox))
          {
            display[4] = obeyme; 
            return nopar;
          }
        else if((display[2] == xo)&&(display[6]!=ox)&&(display[4]==xo))
        {
          display[6] = obeyme;
          return nopar;
        }
        else if((display[2] != ox)&&(display[6]==xo)&&(display[4]==xo))
        {
          display[2] = obeyme;
          return nopar;
        }
        else if((i<3)&&(display[i] == xo)&&(display[i+3] == xo)&&(display[i+6]!=ox))
        {
          display[i+6] = obeyme;
          return nopar;
        }
        else if(((i == 0)||(i == 3)||(i == 6))&&(display[i] == xo)&&(display[i+1]==xo)&&(display[i+2]!=ox))
        {
          display[i+2] = obeyme;
          return nopar;
        }
        else if((i>2)&&(i <6)&&(display[i] == xo)&&(display[i+3] == xo)&&(display[i-3] != ox))
        {
          display[i-3] = obeyme;
          return nopar;
        }
        else if(((i == 1)||(i == 4)||(i == 7))&&(display[i] == xo)&&(display[i+1]==xo)&&(display[i-1]!=ox))
        {
          display[i-1] = obeyme;
          return nopar;
        }
        else if((display[2] != ox)&&(display[5]==xo)&&(display[8]==xo))
        {
          display[2] = obeyme;
          return nopar;
        }
        else if((display[9] ==xo) &&(display[1] == xo) &&(display[i] != xo) && (display[i] != ox))
        {
          display[4] = obeyme;
          return nopar;
        }
        else if((i == 8)&&(num != 3)&&(num != 2))
        {
        while(cnt < 9)
        {
          if((display[cnt] != xo) && (display[cnt] != ox))
            {
              display[cnt] = obeyme;
              cnt = 9;
              i = 9;
              return nopar;
            }
            cnt++;
        }
        i = 9;
        return nopar;
        }
          i++;
      }
      return 2;
    
}

void twoplayer()
{
 //twoplayer is the gamemode that requires 2 players
  char display[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  char x = 'X';
  char o = 'O';
  int check;
  int count;
  check = 0;
  count = 0;
  printf("\n");
  visual(display);
  while ((check == 0)&&(count <9))
  {//just iterate through and take turns inputing moves
  player(&display,1, 0);
  count +=1;
  visual(display);
  check = checkresult(display, 1, 0);
  if((count==9)||(check))
  {
    if(check != 1)
      printf("Cats Game!");

    return;
  }
  player(&display,2, 0);
  count +=1;
  visual(display);
  check = checkresult(display, 2, 0);
  }
  return;
}
void player(char *display, int num, int ply)
{ //player takes the player input and records it on the display
  char input;
  int i = 0;
  if(ply)
    printf("Player:",num);
  else
    printf("Player %d:",num);
  scanf("%d", &i);
  printf("\n");
  if((i < 1)|| (i > 9)|| (display[i-1] == 'O') || (display[i-1] == 'X'))
  {
    if(i == 0)
    {
      scanf("%c", &input);
    }
    printf("invalid input\n");
    player(display, num,ply);
  }
  else if(num == 1)
  {
    display[i-1] = 'X';
  }
  else
    display[i-1] = 'O';

  
  return;
}

void visual(char *display)
{//visual just prints out the display for player to see layout
  printf("\n| %c | %c | %c |\n", display[0],display[1], display[2]);
  printf("| %c | %c | %c |\n", display[3],display[4], display[5]);
  printf("| %c | %c | %c |\n", display[6],display[7], display[8]);
}

int checkresult(char *display, int num, int ckn)
{//checkresult checks if there is already a winning move made
  int check;
  int i;
  i = 0;
  check = 0;
  char xo;
  if (num == 1)
    xo = 'X';
  else
    xo = 'O';

    if(display[0] == xo)
    {
      if(display[1] == xo)
      {
        if(display[2] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }
      if(display[3] == xo)
      {
        if(display[6] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }
      if(display[4] == xo)
      {
        if(display[8] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }

    }
    if(display[1] == xo)
    {
      if(display[4] == xo)
      {
        if(display[7] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }
    }
    if(display[2] == xo)
    {
      if(display[5] == xo)
      {
        if(display[8] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }
      if(display[4] == xo)
      {
        if(display[6] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }
    }
    if(display[3] == xo)
    {
      if(display[4] == xo)
      {
        if(display[5] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }
    }
    if(display[6] == xo)
    {
      if(display[7] == xo)
      {
        if(display[8] == xo)
        {
          if(ckn == 1)
            printf("\nchicken wins! fatality\n");
          else if (ckn == 2)
            printf("\nplayer wins! fatality\n");
          else
            printf("\nplayer %d wins! fatality\n", num);
          return 1;
        }
      }
    }
 return 0;
}



