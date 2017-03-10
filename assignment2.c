#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

//Defining variables for slot type
#define NAME 30
#define TYPE 3

//function prototypes
void playerInfo(int i, int numPlayers);
void printPlayers(int i, int numPlayers);
void printSlots(int i, int j, int numSlots);
void terrainChanges(int i, int numPlayers);
void attackRight(int i);
void attackLeft(int i);
void moveLeft(int i);
void moveRight(int i);

char slot_type[TYPE][NAME] = {"Ground", "City", "Hill"};

struct players	//array of structs for each player
{
    char name[50];			//variable to store characters name
    char type[50];			//variable to store the character type
    char slotType[50];		//variable to store the characters slot type
    int slotNum;			//variable to store the characters slot number
    int numType; 			//variable to limit user input (e.g. Human = 1)
    int lifePoints, smartness, strength, magicSkills, luck, dexterity ;		//player attributes
} players[6];

struct slots	//array of structs for each slot
{
	char slotType[50];		//variable to store the slot type in characters
	char type[NAME];		//variable to store slot type
	int slotNum;			//variable to store slot number
	int player;				//variable to store player number
	int numSlots;			//variable to store number of each slot
} slots[20];

int main()
{
	srand((unsigned)time(NULL));

	int i = 0, y, x, j = 0, check = 0, numPlayers, numSlots, choice, temp;			//variables for various parts of the program

	//ensures the user inputs a number between 2 and 6
	do{
		printf("\nPlease enter the number of players you wish to play with: ");		//asks for user input
		scanf("%d", &numPlayers);													//records user input

		if (numPlayers == 1)														//if the user wants to play with 1 player
			printf("\nThis game is played with more than 2 players!\n");
		else if (numPlayers <= 1 || numPlayers > 6)									//if the choice is valid prints an error and repeats
			printf("\nMax players is 6, please enter a valid choice!\n");
		}while (numPlayers <= 1 || numPlayers > 6);

    printf("-----------------------------------\n");
    printf("         PLAYER INFORMATION        \n");
    printf("-----------------------------------\n");

    playerInfo(i, numPlayers);				//assigns capabilities to each player

    printf("-----------------------------------\n");
    printf("         PLAYER ATTRIBUTES         \n");
    printf("-----------------------------------\n");

    printPlayers(i, numPlayers);			//prints the data information for each player

    printf("-----------------------------------\n");
    printf("         SLOT INFORMATION          \n");
    printf("-----------------------------------\n");

    do{
    	printf("\nPlease enter the number of slots you wish to use: ");				//asks for user input
    	scanf("%d", &numSlots);														//records user input

    	if(numSlots <= numPlayers)
    		printf("\nPlease enter a value which is greater than the number of players!\n");	//asks user to enter a valid choice
    	else if (numSlots <= 0 || numSlots > 20)
    		printf("\nMax slots is 20, please enter a valid choice!\n");			//tells user that the max slots is 20
      }while (numSlots <= 0 || numSlots > 20);

    for(i = 0; i < numSlots; i++)
    	{
    		y = rand() % 3;								//assigns a random value to y between 1 and 3
    	    strcpy(slots[i].type, slot_type[y]);		//assigns a random type to each slot
    	}

    	for (i=0; i<numPlayers; i++)
    	{
    	    slots[i].player = i;						//assigns the value of i to each player value in the struct
    	}

    	for(i=numPlayers; i<numSlots; i++)
    	{
    		slots[i].player = -1;						//assigns the -1 value to the slots greater than number of players
    	}

    	for(i=0; i<numSlots; i++)
    	{
    		slots[i].numSlots = i + 1;					//assigns the number of the slot to each slot
    	}

    	for (i=numSlots-1; i>0; i--) 					// shuffles the slots
    	{
    		x = rand() % (i+1);
    	    temp = slots[x].player;
    	    slots[x].player = slots[i].player;
    	    slots[i].player = temp;

    	    if(slots[i].player > -1)
    	    {
    	    	players[slots[i].player].slotNum=i; 	// keeps track of the players position
    	    }
    	}

    printSlots(i, j, numSlots);							//prints the slots before player movement

    printf("-----------------------------------\n");
    printf("           PLAYER OPTIONS          \n");
    printf("-----------------------------------\n");


     for(i = 0; i < numSlots; i++)	//loops around each slot
     {
		if(slots[i].player == -1)	//if slot is empty
		{
			printf("");
		}
		else if(slots[i].player == check)	//if the player has played before
		{
			printf("");
		}
		else if((i == 0) && (slots[i+1].player > -1))				//In first slot and player on the right
    	{
			check = slots[i].player;								//checks if the current player has played already

			printf("\n---------- Player %d: %s----------\n", slots[i].player + 1, players[slots[i].player].name);
    		do{
    			printf("1 to attack right\n");							//players option
    			scanf("%d", &choice);									//asks for user input

    			if(choice < 1 || choice > 1)
    				printf("Please enter a valid option\n");
    		}while(choice < 1 || choice > 1);

    		attackRight(i);											//points to the attack right function
    		printf("You attacked right\n");
    	 }
    	 else if((i == numSlots - 1) && (slots[i-1].player > -1))	//In last slot and player on the left
    	 {
    		 check = slots[i].player;								//checks if the current player has played already

    		 printf("\n---------- Player %d: %s ----------\n", slots[i].player + 1, players[slots[i].player].name);
    	     do{
    	    	 printf("1 to attack left\n");							//players option
    	    	 scanf("%d", &choice);									//asks for user input

    	    	 if(choice < 1 || choice > 1)
    	    	     printf("Please enter a valid option\n");
    	     }while(choice < 1 || choice > 1);

    	     attackLeft(i);											//points to the attack left function
    	     printf("You attacked left\n");

    	 }
    	 else if((i == 0) && (slots[i+1].player == -1))				//In first slot and no player on the right
    	 {
    		 check = slots[i].player;								//checks if the current player has played already

    		 printf("\n---------- Player %d: %s ----------\n", slots[i].player + 1, players[slots[i].player].name);
    	     do{
    	    	 printf("1 to move right\n");							//players option
    	    	 scanf("%d", &choice);									//asks for user input

    	    	 if(choice < 1 || choice > 1)
    	    	     printf("Please enter a valid option\n");
    	     }while(choice < 1 || choice > 1);

    	     moveRight(i);
    	     printf("You moved right\n");
    	 }
    	 else if((i == numSlots - 1) && (slots[i-1].player == -1))	//In last slot and no player on the right
    	 {
    		 check = slots[i].player;								//checks if the current player has played already

    		 printf("\n\n---------- Player %d ----------\n", slots[i].player + 1);
    	     do{
    	    	 printf("1 to move left\n");							//players option
    	    	 scanf("%d", &choice);									//asks for user input

    	    	 if(choice < 1 || choice > 1)
    	    		 printf("Please enter a valid option\n");
    	     	}while(choice < 1 || choice > 1);

    	     moveLeft(i);
    	     printf("You moved left\n");
    	 }
    	 else if((slots[i+1].player > -1) && (slots[i-1].player == -1))		//Player on the right and no player on the left
    	 {
    		 check = slots[i].player;								//checks if the current player has played already

    		 printf("\n\n---------- Player %d: %s ----------\n", slots[i].player + 1, players[slots[i].player].name);
    		 do{
    			 printf("1 to attack right || 2 to move left\n");		//players options
    			 scanf("%d", &choice);									//asks for user input

    			 if(choice < 1 || choice > 1)
    				 printf("Please enter a valid option\n");

    		 }while(choice < 1 || choice > 2);

    		 switch(choice)
    		 {
    		 	 case 1:
    		 		 attackRight(i);
    		 		 printf("You attacked right\n");
    		 		 break;
    		     case 2:
    		    	 moveLeft(i);
    		    	 printf("You moved left\n");
    		    	 break;
    		  }
    	 }
    	 else if((slots[i-1].player > -1) && (slots[i+1].player == -1))		//Player on the left and no player on the right
    	 {
    		 check = slots[i].player;									//checks if the current player has played already

    		 printf("\n\n---------- Player %d: %s ----------\n", slots[i].player + 1, players[slots[i].player].name);
    	     do{
    	    	 printf("1 to attack left || 2 to move right\n");		//players options
    	    	 scanf("%d", &choice);									//asks for user input

    	    	 if(choice < 1 || choice > 1)
    	    		 printf("Please enter a valid option\n");
    	     }while(choice < 1 || choice > 2);

    	     switch(choice)
    	     {
    	     	 case 1:
    	     		 attackLeft(i);
    	     		 printf("\nYou attacked left\n");
    	     		 break;
    	     	 case 2:
    	     		 moveRight(i);
    	     		 printf("You moved right");
    	     		 break;
    	     }
    	 }
    	 else if((slots[i-1].player > -1) && (slots[i+1].player > -1))		//Player on the left and player on the right
    	 {
    		 check = slots[i].player;								//checks if the current player has played already

    		 printf("\n\n---------- Player %d: %s ----------\n", slots[i].player + 1, players[slots[i].player].name);
    	     do{
    	    	 printf("1 to attack left || 2 to attack right\n");		//players options
    	    	 scanf("%d", &choice);									//asks for user input

    	    	 if(choice < 1 || choice > 1)
    	    		 printf("Please enter a valid option\n");
    	     }while(choice < 1 || choice > 2);

    	     switch(choice)
    	     {
    	     	 case 1:
    	     		 attackLeft(i);
    	     		 printf("\nYou attacked left\n");
    	     		 break;
    	         case 2:
    	        	 attackRight(i);
    	        	 printf("\nYou attacked right\n");
    	        	 break;
    	     }
    	 }
    	 else if((slots[i-1].player == -1) && (slots[i+1].player == -1))	//No player on right no player on left
    	 {
    		 check = slots[i].player;								//checks if the current player has played already

    		 printf("\n\n---------- Player %d: %s ----------\n", slots[i].player + 1, players[slots[i].player].name);
    		 do{
    			 printf("1 to move left || 2 to move right\n");			//players option
    			 scanf("%d", &choice);									//asks for user input

    			 if(choice < 1 || choice > 1)
    				 printf("Please enter a valid option\n");
    		 }while(choice < 1 || choice > 2);

    		 switch(choice)
    		 {
    		 	 case 1:
    		 		 moveLeft(i);
    		 		 break;
    		 	 case 2:
    		 		 moveRight(i);
    		 		 break;
    		 }
    	 }
	}

    terrainChanges(i, numPlayers);

    printPlayers(i, numPlayers);

    printf("-----------------------------------\n");
    printf("          	 GAME OVER	           \n");
    printf("-----------------------------------\n");

    return 0;
}
void playerInfo(int i, int numPlayers)
{
	for(i = 0; i< numPlayers; ++i)	//loop around each player to input their details
	{
		printf("\n-----Player number %d-----\n", i + 1);	//heading for player number

	    printf("Enter name: ");
	    scanf("%s",players[i].name);						//stores users name in the struct

	    //ensure the user prints a number between 1 and 4 for player type
	    do{
	    	printf("Enter type (1 = Human || 2 = Ogre || 3 = Elf || 4 = Wizard): ");
	        scanf("%d",&players[i].numType);				//records user input for player type

	        if( players[i].numType > 4 || players[i].numType <= 0)
	        	printf("Please enter a valid choice\n");	//prints error if not a valid option
	        }while( players[i].numType > 4 || players[i].numType <= 0);

	    if( players[i].numType == 1)			//if this player is a human
	    {
	    	strcpy(players[i].type, "Human");	//copies the string human to the player type
	    	players[i].lifePoints = 100;			//initializes life points at 100

	    	//loops until the sum of all capabilities are less than 300
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
	    	strcpy(players[i].type, "Ogre");		//copies the string ogre to the player type
	    	players[i].lifePoints = 100;			//initializes life points at 100

	    	players[i].magicSkills = 0;
	    	players[i].dexterity = (rand() % (100 - 80)) + 80;
	    	players[i].strength = (rand() % (100 - 80)) + 80;

	    	//loops until sum of smartness and luck is less than 50
	    	do{
	    		players[i].smartness = rand () % 20;
	    	    players[i].luck = rand () % 100;
	    	  } while ((players[i].smartness + players[i].luck) > 50);
	    }
	    else if(players[i].numType == 3)		//if this player is an elf
	    {
	    	strcpy(players[i].type, "Elf");		//copies the string elf to the player type
	        players[i].lifePoints = 100;			//initializes life points at 100

	        //assigns values to each of the players capabilities
	        players[i].luck = (rand() % (100 - 60)) + 60;
	        players[i].smartness = (rand() % (100 - 70)) + 70;
	        players[i].strength = rand() % 50;
	        players[i].magicSkills = (rand() % (80 - 50)) + 50;
	        players[i].dexterity = rand () % 100;
	    }
	    else if(players[i].numType == 4)		//if this player is a wizard
	    {
	        strcpy(players[i].type, "Wizard");	//copies the string wizard to the player type
	        players[i].lifePoints = 100;			//initializes life points at 100

	        //assigns values to each of the players capabilities
	        players[i].luck = (rand() % (100 - 50)) + 50;
	        players[i].smartness = (rand() % (100 - 90)) + 90;
	        players[i].strength = rand() % 20;
	        players[i].magicSkills = (rand() % (100 - 80)) + 80;
	        players[i].dexterity = rand () % 100;
	    }

	}
}
void printPlayers(int i, int numPlayers)
{
	for(i=0; i < numPlayers; ++i)		//loops around each player to print their capabilities
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
}
void printSlots(int i, int j, int numSlots)
{
	for(i=0; i<numSlots; i++)			//loops around each slot
	{
		if(slots[i].player > -1)		//if theres a player in the slot
	    {
			j = slots[i].player;
	        printf("%d\t%s\t\t%s\n", slots[i].numSlots, slots[i].type, players[j].name);
	    }
	    if(slots[i].player == -1)		//if theres no player in the slot
	    {
	        printf("%d\t%s\t\t--\n", slots[i].numSlots, slots[i].type);
	    }
	}
}
void attackRight(int i)
{
	if(players[slots[i].player+1].strength <= 70)	 //checks if attacked players strength is less than seventy
	{
		players[slots[i].player+1].lifePoints = players[slots[i].player+1].lifePoints - (0.5)*players[slots[i].player+1].strength; //decreases live points accordingly
	}
	else if(players[slots[i].player+1].strength > 70)	//checks if attacked players strength is greater than seventy
	{
		players[slots[i].player+1].lifePoints = players[slots[i].player+1].lifePoints - (0.3)*players[slots[i].player+1].strength;
	}

}
void attackLeft(int i)
{
	if(players[slots[i].player-1].strength <= 70)	//checks if attacked players strength is less than seventy
	{
		players[slots[i].player-1].lifePoints = players[slots[i].player-1].lifePoints - (0.5)*players[slots[i].player-1].strength; //decreases live points accordingly
	}
	else if(players[slots[i].player+1].strength > 70)	//checks if attacked players strength is greater than seventy
	{
		players[slots[i].player-1].lifePoints = players[slots[i].player-1].lifePoints - (0.3)*players[slots[i].player-1].strength; //decreases live points accordingly
	}
}

void moveRight(int i)
{
	int a;
	printf("%s is now in slot #%d - %s.\n", players[slots[i].player].name, slots[i+1].numSlots, slots[i+1].type);
	a = slots[i].player;				//stores player number in a
	slots[i+1].player = a; 				//moves to a new slot
	slots[i].player = -1;				// this slot is now filled
}

void moveLeft(int i)
{
	int a;
	printf("%s is now in slot #%d - %s.\n", players[slots[i].player].name, slots[i-1].numSlots, slots[i-1].type);
	a = slots[i].player;				//stores player number in a
	slots[i-1].player = a; 				//moves to a new slot
	slots[i].player = -1;				// this slot is now filled
}
void terrainChanges(int i, int numPlayers)
{
	for(i=0;i<numPlayers;i++)	//loop around each player to check player capabilities depending on terrain change
	{
		if(strcpy(slots[slots[i].player].type, "Hill") && (players[i].dexterity <50))
	    {
			players[i].strength -= 10;
	    }
	    else if(strcpy(slots[slots[i].player].type,"Hill") && (players[i].dexterity >=60))
	    {
	    	players[i].strength += 10;
	    }
	    else if(strcpy(slots[slots[i].player].type,"City") && (players[i].smartness >50))
	    {
	     	players[i].strength -= 10;
	    }
	    else if(strcpy(slots[slots[i].player].type, "City") && (players[i].smartness <=50))
	    {
	     	players[i].magicSkills -= 10;
	    }
	}
}
