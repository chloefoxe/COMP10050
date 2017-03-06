/*
 * main.c
 *
 *  Created on: 24 Feb 2017
 *      Author: gavin
 */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void moveLeft(int i);
void moveRight(int i);
void attackLeft(int i);
void attackRight(int i);

#define DESCRIPTION 30
#define TYPE 3

char slot_type[TYPE][DESCRIPTION] = {"Ground", "City", "Hill"};

/*array of structs for each player */
struct players
{
    char name[50];
    char type[50];
    char slotType[50];
    int slotNum;
    int numType; 			// To limit what the user has to type (e.g. Human = 1)
    int typeNum;
    int num;
    int lifePoints;
    int smartness;
    int strength;
    int magicSkills;
    int luck;
    int dexterity;
} players[6];

struct slots
{
	char slotType[50];
	int slotNum;
	int typeNum;
	char type[DESCRIPTION];
	int player;
} slots[20];

int main()
{
	srand(time(NULL));

	int i, y, x, j, numPlayers, numSlots, count = 0, choice;

	/* ensures the user inputs a number between 1 and 6 */
    do {
    	printf("\nPlease enter the number of players you wish to play with: ");
    	scanf("%d", &numPlayers);

    	if (numPlayers <= 0 || numPlayers > 6)
    		printf("\nMax players is 6, please enter a valid choice!\n\n");
    	}while (numPlayers <= 0 || numPlayers > 6);

    printf("-----------------------------------\n");
    printf("         PLAYER INFORMATION        \n");
    printf("-----------------------------------\n");

    for(i = 0; i< numPlayers; ++i)
    {
        players[i].num = i+1;		//to be able to visully print the player number when inputting values

        printf("\nPlayer number %d\n",players[i].num);	//heading for player number

        printf("Enter name: ");				//players name
        scanf("%s",players[i].name);

        //ensure the user prints a number between 1 and 4
        do {
        	printf("Enter type (1 = Human || 2 = Ogre || 3 = Elf || 4 = Wizard): ");
        	scanf("%d",&players[i].numType);

        	if( players[i].numType > 4 || players[i].numType <= 0)
        		printf("Please enter a valid choice\n");
        }while( players[i].numType > 4 || players[i].numType <= 0);

       if( players[i].numType == 1)		//if this player is a human
       {
    	   strcpy(players[i].type, "Human");
    	   players[i].lifePoints = 100;

    	   do{
    		   players[i].smartness = rand () % 100;
    		   players[i].strength = rand () % 100;
    		   players[i].magicSkills = rand () % 100;
    		   players[i].luck = rand () % 100;
    		   players[i].dexterity = rand () % 100;

    	    } while ((players[i].smartness + players[i].strength + players[i].magicSkills +
    	    		 players[i].luck + players[i].dexterity) >= 300);
       }
       else if(players[i].numType == 2)		//if this player is an ogre
       {
    	   strcpy(players[i].type, "Ogre");
    	   players[i].lifePoints = 100;
    	   players[i].magicSkills = 0;
    	   players[i].dexterity = (rand() % (100 - 80)) + 80;
    	   players[i].strength = (rand() % (100 - 80)) + 80;

    	   do{
    	       players[i].smartness = rand () % 20;
    	       players[i].luck = rand () % 100;

    	   } while ((players[i].smartness + players[i].luck) > 50);
       }
       else if(players[i].numType == 3)		//if this player is an elf
       {
    	   strcpy(players[i].type, "Elf");
           players[i].lifePoints = 100;
           players[i].luck = (rand() % (100 - 60)) + 60;
           players[i].smartness = (rand() % (100 - 70)) + 70;
           players[i].strength = rand() % 50;
           players[i].magicSkills = (rand() % (80 - 50)) + 50;
           players[i].dexterity = rand () % 100;
       }
       else if(players[i].numType == 4)		//if this player is a wizard
       {
           strcpy(players[i].type, "Wizard");
           players[i].lifePoints = 100;
           players[i].luck = (rand() % (100 - 50)) + 50;
           players[i].smartness = (rand() % (100 - 90)) + 90;
           players[i].strength = rand() % 20;
           players[i].magicSkills = (rand() % (100 - 80)) + 80;
           players[i].dexterity = rand () % 100;
       }

    }

    printf("-----------------------------------\n");
    printf("         PLAYER ATTRIBUTES         \n");
    printf("-----------------------------------\n");

    /*Don't think this has to be printed in the actual program but just have it here to make sure the right things are printing */

    for(i=0; i < numPlayers; ++i)
    {
        printf("\n------------Player Number %d-----------\n",i+1);
        printf("Name:\t\t\t%s\n", players[i].name);
        printf("Type:\t\t\t%s\n", players[i].type);
        printf("Life Points:\t\t%d\n", players[i].lifePoints);
        printf("Smartness:\t\t%d\n", players[i].smartness);
        printf("Strength:\t\t%d\n", players[i].strength);
        printf("Magic Skills:\t\t%d\n", players[i].magicSkills);
        printf("Luck:\t\t\t%d\n", players[i].luck);
        printf("Dexterity:\t\t%d\n", players[i].dexterity);
    }

    printf("-----------------------------------\n");
    printf("         SLOT INFORMATION          \n");
    printf("-----------------------------------\n");

    srand((unsigned)time(NULL));

    do{
    	printf("\nPlease enter the number of slots you wish to use: ");
        scanf("%d", &numSlots);

        if (numSlots <= 0 || numSlots > 20)
        	printf("\nMax slots is 20, please enter a valid choice!\n\n");
        }while (numSlots <= 0 || numSlots > 20);

    for(i = 0; i < numSlots; i++)
    {
    	y = rand() % 3;
    	strcpy(slots[i].type, slot_type[y]);
    }

    for (i=0;i<numPlayers;i++)
    {
            slots[i].player = i;
    }

    for(i=numPlayers; i<numSlots; i++)
    {
    	slots[i].player = -1;
    }

    int temp;
        for (i=numSlots-1;i>0;i--) // shuffling the struct slot array to put players into random slots
        {
            x = rand()%(i+1);
            temp = slots[x].player;
            slots[x].player = slots[i].player;
            slots[i].player = temp;

            if(slots[i].player>-1)
            {
                players[slots[i].player].slotNum=i; // keeps track of each players position in the slot
            }
        }

     for(i=0;i<numSlots;i++)
     {
    	 if(slots[i].player > -1)
         {
    		 j = slots[i].player;
    		 printf("%d\t%s\t\t%s\n", i + 1, slots[i].type, players[j].name);
         }
         if(slots[i].player == -1)
         {
        	 printf("%d\t%s\t\t--\n", i + 1, slots[i].type);
         }
      }

	  // printf("-----------------------------------\n");
     // printf("           PLAYER OPTIONS          \n");
     // printf("-----------------------------------\n");


     for(i = 0; i < numSlots; i++)
     {
					 if(slots[i].player == -1)
					 {
						 printf("This slot is empty\n");
					 }
					 
					 //first slot -> player in second slot
					 else if((i == 0) && (slots[i+1].player > -1))								//1
					 {
						 printf("---------- Player %d ----------\n", slots[i].player + 1);
						 printf("1 to attack right\n");
						 scanf("%d", &choice);
						 if(choice == 1){
							 attackRight(i);
						 }
						 count++;
					 }
					 
					 else if((i == numSlots - 1) && (slots[i-1].player > -1))					//2
					 {
						 printf("---------- Player %d ----------\n", slots[i].player + 1);
						 printf("1 to attack left\n");
						 scanf("%d", &choice);
						 if(choice == 1){
							 attackLeft(i);
						 }
						 count++;
					 }
					 
					 else if((i == 0) && (slots[i+1].player == -1)){							//3
						 printf("---------- Player %d ----------\n", slots[i].player + 1);
						 printf("1 to attack right || 2 to move right\n");
						 scanf("%d", &choice);
						 if(choice == 1){
							 attackRight(i);
						 }
						 else if(choice ==2){
							 moveRight(i);
						 }
						 count++;
					 }
					 else if((i == numSlots - 1) && (slots[i-1].player == -1))					//4
					 {
						 printf("---------- Player %d ----------\n", slots[i].player + 1);
						 printf("1 to attack left || 2 to move left\n");
						 scanf("%d", &choice);
						  printf("1 to attack left\n");
						 scanf("%d", &choice);
						 
						 if(choice == 1){
							 attackLeft(i);
						 }
						 else if(choice == 2){
							 moveLeft(i);
							
						 }
						 count++;
					 }
					 else if((slots[i+1].player > -1) && (slots[i-1].player == -1))				//5
					 {
						 printf("---------- Player %d ----------\n", slots[i].player + 1);

						 if(count == 0)
							printf("1 to attack right || 2 to move left\n");
							scanf("%d", &choice);
							if(choice == 1){
							 attackRight(i);
						 }
							else if(choice == 2){
								moveLeft(i);
							}
							else{
							 printf("1 to attack left || 2 to attack right || 3 to move left\n");
							scanf("%d", &choice);
							if(choice == 1){
							 attackLeft(i);
							}
							else if(choice == 2){
								 attackRight(i);
							}
							else if(choice == 3){
								moveLeft(i);
							}
							}

						 count++;
					 }
					 else if((slots[i-1].player > -1) && (slots[i+1].player == -1))				//6
					 {
						 printf("---------- Player %d ----------\n", slots[i].player + 1);

						 if(count == numPlayers - 1)
							 printf("1 to attack left || 2 to move right\n");
						 scanf("%d", &choice);
						 if(choice == 1){
							 attackLeft(i);
							}
						else if(choice == 2){
								moveRight(i);
							}
						 else{
							 printf("1 to attack left || 2 to attack right || 3 to move right\n");
							scanf("%d", &choice);
							if(choice == 1){
							 attackLeft(i);
							}
							else if(choice == 2){
								 attackRight(i);
							}
							else if(choice == 3){
								moveRight(i);
							}
						 }
						 count++;
					 }
					 else if((slots[i-1].player > -1) && (slots[i+1].player > -1))				//7
					 {
						 printf("---------- Player %d ----------\n", slots[i].player + 1);
						 printf("1 to attack left || 2 to attack right\n");
						 if(choice == 1){
							 attackLeft(i);
							}
							else if(choice == 2){
								 attackRight(i);
							}
						 count++;
					 }
					 else if((slots[i-1].player == -1) && (slots[i+1].player == -1))			//8
					 {
						 printf("---------- Player %d ----------\n", slots[i].player + 1);

						 if(count == numPlayers - 1){
							 printf("1 to attack left || 2 to move right || 3 to move left\n");
							 scanf("%d", &choice);
							 if(choice == 1){
							 attackLeft(i);
							}
								if(choice == 2){
									moveRight(i);
								}
								else if(choice == 3){
									moveLeft(i);
								}
						 }
						 else if(count == 0){
							printf("1 to attack right || 2 to move right || 2 to move left\n");
							scanf("%d", &choice);
							if(choice == 1){
								 attackRight(i);
							}
									else if(choice == 2){
										moveRight(i);
									}
									else if(choice == 3){
										moveLeft(i);
									}
						 }
						 else
							 printf("1 to attack right || 2 to attack left || 3 to move right || 4 to move left\n");
						 scanf("%d", &choice);
						 if(choice == 1){
							 attackLeft(i);
							}
							else if(choice == 2){
								 attackRight(i);
							}
									else if(choice == 3){
										moveRight(i);
									}
									else if(choice == 4){
										moveLeft(i);
									}
						 count++;
						 
						 
					 }
	//change of terrain
	 // if((strcpy(slots[i].type,"Hill")) && (players[i].dexterity <50)){
		// players[i].strength -= 10;
	// }
	// else if((strcpy(slots[i].type,"Hill")) && (players[i].dexterity >=60)){
		// players[i].strength += 10;
	// }
	// else if((strcpy(slots[i].type,"City")) && (players[i].smartness >50)){
		// players[i].strength -= 10;
	// }
	// else if((strcpy(slots[i].type,"City")) && (players[i].smartness <=50)){
		// players[i].magicSkills -= 10;
	// }
     }
	 
	 printf("\n");
	 printf("\n");
//to see if players moved	 
	for(i=0;i<numSlots;i++)
     {
    	 if(slots[i].player > -1)
         {
    		 j = slots[i].player;
    		 printf("%d\t%s\t\t%s\n", i + 1, slots[i].type, players[j].name);
         }
         if(slots[i].player == -1)
         {
        	 printf("%d\t%s\t\t--\n", i + 1, slots[i].type);
         }
      }
//to see if attacks worked
for(i=0; i < numPlayers; ++i)
    {
        printf("\n------------Player Number %d-----------\n",i+1);
        printf("Name:\t\t\t%s\n", players[i].name);
        printf("Type:\t\t\t%s\n", players[i].type);
        printf("Life Points:\t\t%d\n", players[i].lifePoints);
        printf("Smartness:\t\t%d\n", players[i].smartness);
        printf("Strength:\t\t%d\n", players[i].strength);
        printf("Magic Skills:\t\t%d\n", players[i].magicSkills);
        printf("Luck:\t\t\t%d\n", players[i].luck);
        printf("Dexterity:\t\t%d\n", players[i].dexterity);
    }
    return 0;
}

void attackRight(int i){
	if(players[slots[i+1].player].strength <= 70){
		players[slots[i+1].player].lifePoints = players[slots[i+1].player].lifePoints - (0.5)*players[slots[i+1].player].strength;
	}
	else if(players[slots[i+1].player].strength > 70){
		players[slots[i+1].player].lifePoints = players[slots[i+1].player].lifePoints - (0.3)*players[slots[i+1].player].strength;
	}
	
	}

void attackLeft(int i){
	if(players[slots[i-1].player].strength <= 70){
		players[slots[i-1].player].lifePoints = players[slots[i-1].player].lifePoints - (0.5)*players[slots[i-1].player].strength;
	}
	else if(players[slots[i-1].player].strength > 70){
		players[slots[i-1].player].lifePoints = players[slots[i-1].player].lifePoints - (0.3)*players[slots[i-1].player].strength;
	}
}

void moveRight(int i){
	slots[i].player = slots[i-1].player; 	//moves to a new slot
	slots[i].player = i;	// this slot is now filled
	slots[i+1].player = -1;// other slot is now empty
	
}

void moveLeft(int i){
	slots[i].player = slots[i+1].player; //moves to a new slot
	slots[i].player = i;	// this slot is now filled
	slots[i-1].player = -1;	// other slot is now empty
	
}





    
