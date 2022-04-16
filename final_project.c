#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//#include "userlib.h"

void number_1();
void number_2();
void number_3();
void help();
void regis();
void identity();
void start();
void play();
void display();
void randomMove();
bool moveValid();
bool win();

struct reg{
char name;
};
struct reg *reg1;

int position[8][8];
int size, count=0;
int blankSpace, spaceX, spaceY;
int move;
char arrow;
struct reg *reg1;

int main()
{

    system("COLOR F1");
    //to make the background become white

   printf("---------------------------------Slide Puzzle----------------------------"

           "\n\nThis is dakhilullah muhazzib darwisy (1706019904) final project\n\n"
           "\tIn here we use malloc, array, user library, and other course from the class\n"
           "This the game that usually  exist in the widget of windows xp or windows 7"
           "\nThis game is not exactly same with the original game, but it still have the element of that game\n"
           "I hope you enjoy this game as much as the original one :)"
           "\n\nPress Enter to continue");

    getch();

    number_1();
    //the main screen

    //the starting point of the game




 //free(reg1);
    return 0;
}

void play(){



    do{
        //seed for random number
        srand(time(NULL));

        //Choose the size of the board
        while(1)
        {
            printf("Please insert your board size (2 - 8): ");
            scanf("%d", &size);

            //it is a message that tell us to
            if(size < 2 || size > 8)
                {
                printf("The size is only from 2 to 8!!!\n\n");
                system("cls");
                }

            else if (size >=2 && size <=8)
                break;
        }
         //memory allocation
        /*
        for (int i=0; i<size; i++){
            position[i] = (int *)malloc(size * sizeof(int));
        }
        */
        //to decide the board size
        blankSpace = size*size;
        spaceY = size-1;
        spaceX = size-1;

        //start the game
        start();
        printf("Please wait . . .\n");
        randomMove(100);
        system("cls");
        display();

        //input move hingga menang atau menyerah
        while(!win())
        {
            //to make the righr input
            while(1)
            {
                printf("Your Move : ") ;
                scanf("%d", &move);

                //0 for help
                if(move == 0)
                {
                    help();
                    display();
                }
                //if its tired of the game
                else if(move < 0)
                {
                    break;
                }
                //if the insert is wrong
                else if(!moveValid(move))
                {
                    printf("Put the number around the blank space!!\n\n");
                }
                //if the input is right
                else
                {
                    count++;
                    break;
                }
            }

            //jif the player gave up
            if(move < 0)
            {
                system("cls");
                printf("\nNo way i am winning this game\n\n");
                break;
            }

            system("cls");
            display();
        }

        if(move > 0)
            {
            printf("\nYou Win!\n\n");

            printf("your best score is %d", count);

            }

        //meminta input sampai tidak meminta bantuan(0)
        while(1)
        {
            printf("\nwant to play some more? (press -1 for quit, and 0 for help)\n");
            scanf("%d", &move);

            if(move == 0)
                help();
            else if(move < 0)
                exit(0);
            else
                break;
        }

        system("cls");

    }while(move > 0);
        return 0;

}

void start()
{
    //to insert the data initially
    int i, j;
    int data = 1;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            position[j][i] = data;
            data++;
        }
    }
}

void display(){

 //to insert the data initially
    int i, j;
    int data = 1;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if (position[j][i] != blankSpace){
                printf("%3d", position[j][i]);
            }
            else{
                printf("  _");
            }

        }
        printf("\n\n");
    }

}
//function for winning state
bool win()
{
    //
    int i, j;
    int data = 1;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if (position[j][i] != data)
                return false;
            data++;
        }
    }
    return true;
}

void randomMove(int x)
{
    int i;

    int long a = x;
    //to make it random by x^(size-1)
    for(i = 0; i < size-1; i++)
    {
        a *= x;
    }

     //making the random move while checking whether it is right or not on scale x^(size-1)
     while(a != 0)
     {
            int randomNumber = rand()%64;
            //make sure that every move is valid

            //up
            if(spaceY != 0 && randomNumber == 0 )
            {
                position[spaceY][spaceX] = position[spaceY-1][spaceX];
                position[spaceY-1][spaceX] = blankSpace;

                spaceY -= 1;

                a--;
            }
            //down
            else if(spaceY < size-1 && randomNumber == 1)
            {
                position[spaceY][spaceX] = position[spaceY+1][spaceX];
                position[spaceY+1][spaceX] = blankSpace;

                spaceY += 1;

                a--;
            }
            //left
            else if(spaceX != 0 && randomNumber == 2)
            {
                position[spaceY][spaceX] = position[spaceY][spaceX-1];
                position[spaceY][spaceX-1] = blankSpace;

                spaceX -= 1;

                a--;
            }
            //right
            else if(spaceX < size-1 && randomNumber == 3)
            {
                position[spaceY][spaceX] = position[spaceY][spaceX+1];
                position[spaceY][spaceX+1] = blankSpace;

                spaceX += 1;

                a--;
            }
    }


    //to put the the blank space in the left bottom side
    while(spaceX != size-1)
    {
        position[spaceY][spaceX] = position[spaceY][spaceX+1];
        position[spaceY][spaceX+1] = blankSpace;

        spaceX += 1;
    }

    while(spaceY != size-1)
    {
        position[spaceY][spaceX] = position[spaceY+1][spaceX];
        position[spaceY+1][spaceX] = blankSpace;

        spaceY += 1;
    }
}
//
bool moveValid(int x)
{
    //to find the position of the blank space
    //and to find out whether the move is correct or not

    //up
    if(spaceY != 0)
    {
        if(x == position[spaceY-1][spaceX])
        {
            position[spaceY-1][spaceX] = blankSpace;
            position[spaceY][spaceX] = x;

            spaceY -= 1;

            return true;
        }
    }

    //bottom
    if(spaceY < size-1)
    {
        if(x == position[spaceY+1][spaceX])
        {
            position[spaceY+1][spaceX] = blankSpace;
            position[spaceY][spaceX] = x;

            spaceY += 1;

            return true;
        }
    }

    //left
    if(spaceX != 0)
    {
        if(x == position[spaceY][spaceX-1])
        {
            position[spaceY][spaceX-1] = blankSpace;
            position[spaceY][spaceX] = x;

            spaceX -= 1;

            return true;
        }
    }

    //right
    if(spaceX < size-1)
    {
        if(x == position[spaceY][spaceX+1])
        {
            position[spaceY][spaceX+1] = blankSpace;
            position[spaceY][spaceX] = x;

            spaceX += 1;

            return true;
        }
    }

    //if the move is invalid
    return false;
}


void help(){


//to make the buffer gone
system("cls");
printf("\tHOW TO PLAY\n"
        "[1] Register your Name and ID, id is automatically generate \n"
        "[2] Insert the size of your board \n"
        "[3] Look at your bottom on the most right space!\n"
        "[4] Insert the number that is around the blank space!\n"
        "[5] If you put the number beside the blank space, it will swap their postion\n"
        "[6] The winning state  of this game is to arrange the number to proper position, take a look of example below example below\n"

        "\ncontoh:\n"
        "  1  2  3\n"
        "  4  5  6\n"
        "  7  _  8      Your Move: 8\n\n"

        "  1  2  3\n"
        "  4  5  6\n"
        "  7  8  _      You win!\n\n"

            "Press Enter if you understand");

getch();

regis();


}

void number_1(){
        system("cls");
        printf("\t-----------------SLIDE PUZZLE-----------------\n\n\n\t It is very fun game to play\n\n >[1]register\n [2]Tell me what this is\n [3]Let me quit");
        printf("\n\n\nPress w or s to navigate");
        arrow=getch();

        if(arrow=='w')
        {
            number_3();
        }
        if(arrow=='s')
        {
            number_2();
        }
        if(arrow=='\r')
        {
            regis();
        }
        else{
            number_1();
        }

}

void number_2(){
    system("cls");
    printf("\t-----------------SLIDE PUZZLE-----------------\n\n\n\t It is very fun game to play\n\n [1]register\n >[2]Tell me what this is\n [3]Let me quit");
    printf("\n\n\nPress w or s to navigate");
    arrow=getch();
        if(arrow=='w')
        {
            number_1();
        }
        if(arrow=='s')
        {
            number_3();
        }
        if(arrow=='\r')
        {
            help();
        }
        else{
            number_2();
        }

        }

void number_3(){
    system("cls");
    printf("\t-----------------SLIDE PUZZLE-----------------\n\n\n\t It is very fun game to play\n\n [1]register\n [2]Tell me what this is\n >[3]Let me quit");
    printf("\n\n\nPress w or s to navigate");
    arrow=getch();


        if(arrow=='w')
        {
            number_2();
        }
        if(arrow=='s')
        {
            number_1();
        }
        if(arrow=='\r')
        {

            exit(0);
        }
        else{
            number_3();
        }

        }

        void regis(){

reg1=(struct reg*)malloc(2*sizeof(struct reg));

system("cls");
printf("What is your name : ");
scanf("%s", &(reg1)->name );
printf("This is your id : %d", &(reg1)->name);
getch();


system("cls");
play();

}

void identity(int a) {
printf("\nname : %s\n id : %d\nand your best score is %d", (reg1)->name, &(reg1)->name, a);

}

