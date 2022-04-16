#include <SDL.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <dirent.h>


//#define Music path
char musicBox[50][100], musicExtension[50][50], name[50][100], decoyA[10] = "./Music/";

// Our music file
Mix_Music *music = NULL;

int search(int n);
int change(int n);
void first();
void second();
void third();
void fourth();
void setting();
void help();
void musicFinished();

int x;

int main(int argc, char* argv[]){
    system("color F0");
    begin:
	first();
    int a=0, k, b=0, c=0, i=0, j=0, index=0, p=0, d=0, e=0, f=0, n=0, gans=0;
    char text, line[1024];
    struct dirent *de;  // Pointer for directory entry


    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir("./Music");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
    /*Get music name with its extension type */
     while ((de = readdir(dr)) != NULL)
     {
         if(f>=2)
               {
                   strcpy(musicBox[i],decoyA); /*This code means that musicBox will always point to the music folder*/
                   strcpy(musicExtension[i],de->d_name); /*copy the name with the type fie*/
               i++;
               }
               f++;
      }
      f=0;

      n=i; /*n is the number of how many music file in the music folder*/

    closedir(dr);

    i=0;
    /*Get Music Name*/

    for(i=0;i<n;i++)
    {
        for(j=0;j<strlen(musicExtension[i])-4;j++)
        {
		name[i][j]=musicExtension[i][j]; /*By decreasing the last 4 character, we can get the music name without the ".mp3" sticking in the back */
        }
    }

    /*Get Music Path*/

    for(i=0;i<n;i++)
    {
        strcat(musicBox[i],musicExtension[i]); /*We add the music name to the folder path making a file path*/
    }


	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return -1;

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		return -1;

    /*Start*/
    back:
        printf("MUSIC PLAYER\n\n");
        for(i=0;i<n;i++)
        {
            printf("%d.%s\n", i+1, name[i]); /*Display all the music in the music folder*/
        }
        printf("\n\nSelect a music to play\n");
        scanf("%d", &c);
        printf("Press any button to continue.....\n\n");
        getchar();/*This is just to get all the data type stdin beside integer so it won't break the program*/
    if(c == NULL || c<1 || c>n)
    {
        printf("INVALID INPUT!\n");
        system("pause");
        system("cls");
        goto back;
    }

	// Load our music
	music = Mix_LoadMUS(musicBox[c-1]);

	if (music == NULL)
		return -1;
    /*Play music*/
    Mix_PlayMusic( music, 1);

	while ( a != 1)
    {
    Mix_HookMusicFinished(musicFinished); /*Checking if the music has been finished or not*/
    printf("Input 1 to stop playing music and exit\n");
    printf("Input 2 to pause music\n");
    printf("Input 3 to resume music\n");
    printf("Input 4 to change music\n");
    printf("Input 5 to rewind music\n");
    printf("Input 6 to set position music (seconds)\n");
    printf("Input 7 to search music\n");
    if(e==1)
        printf("The Music has been paused\n");
    scanf("%d", &a);
    printf("Press any button to continue\n");
    getchar();
    switch(a)
    {
        case 1:
        break;

        case 2:
        Mix_HookMusicFinished(musicFinished);
        Mix_PauseMusic(); /*Pause The Music*/
        e=1;
        break;

        case 3:
        Mix_HookMusicFinished(musicFinished);
        Mix_ResumeMusic(); /*Resume the paused Music*/
        e=0;
        break;

        case 4:
        Mix_HookMusicFinished(musicFinished);
        gans = change(n); /*The gans variable will get the number of which array the file's path has been stored*/
        music = Mix_LoadMUS(musicBox[gans]);

        if (music == NULL)
		return -1;

        if ( Mix_PlayMusic( music, 1) == -1 )
            {
                return -1;
            }
        break;

        case 5:
        Mix_RewindMusic(); /*Rewind Music from the beginning*/
        break;

        case 6:
        Mix_HookMusicFinished(musicFinished);
        printf("Skip Music to (second)\n");
        scanf("%d", &d);
        Mix_RewindMusic();
        /*Forward the music into whatever seconds ahead*/
        if(Mix_SetMusicPosition(d)==-1) {
        printf("Mix_SetMusicPosition: %s\n", Mix_GetError());
        }
        break;

        case 7:
        Mix_HookMusicFinished(musicFinished);
        search(n); /*A function to search music in the array*/

        break;

        default:
            printf("INVALID INPUT!!\n");
            printf("Press any button to continue\n");
            getch();
        break;
    }
    system("cls");

    }

	// clean up our resources
	Mix_FreeMusic(music);

	// quit SDL_mixer
	Mix_CloseAudio();
	system("pause");

	goto begin;
}

int change(int n)
{
        int c=0, i=0;
        restart:

        system("cls");
        for(i=0;i<n;i++)
        {
            printf("%d.%s\n", i+1, name[i]);
        }
        scanf("%d", &c);
        printf("Press any button to continue\n");
        getchar();
        if(c>0 && c<n+1)
        {
            return c-1;
        }
        else
        {
            goto restart;
        }
}

int search(int n)
{
    int i, j, k=0, m, y, p, t;
    char *result , searchSong[100], list[50][100], point, listSong[100];
    search:
    printf("Search your song\n\n");
    scanf("%s", searchSong);

    /*Searching substring from string*/
    for(i=0;i<n;i++)
    {
       result = strstr(name[i],searchSong);
        if(result)
        {
            strcpy(list[k], name[i]);
            k++;
        }
        else
        {
            m++;
        }
    }
    lookout:
    if(k>0){ /*When search has found something then it will sort it*/
    for(i=0; i<k; i++)
    {
        printf("%d.%s\n", i+1 ,list[i]);
    }}
    else
    { /*If no music found*/
        printf("No music found\n");
        printf("\nSearch again?\n");
        printf("1.Yes\n2.No\n");
        scanf("%d", &t);
        if(t==1)
        {
            goto search;
        }
        if(t==2)
        {
            return 0;
        }
        else{
            system("cls");
            goto lookout;
        }
    }

    printf("Input your music number\n");
    scanf("%d", &y);
    printf("Press any button to continue\n");
    getchar();
    if(y<0 || y>k)
    {
        printf("INVALID INPUT!\n");
        system("pause");
        system("cls");
        goto lookout;
    }
    strcpy(listSong,list[y-1]);
    printf("%s", listSong);
    for(i=0;i<n;i++)
    {
        if(strcmp(name[i],listSong) == 0)
        {
            printf("%s",listSong);
            p = i;
            break;
        }
    }
        music = Mix_LoadMUS(musicBox[p]);

        if (music == NULL)
		return -1;

        if ( Mix_PlayMusic( music, 1) == -1 )
            {
                return -1;
            }
}

void musicFinished()
{
    printf("Music stopped.\n");
}

void first()
{
	x==NULL;
	system("cls");
	printf("\t\t\t\t\t\tMUSIC PLAYER\n\n\n");
	printf("\t\t\t\t\t\t  >[1] Start\n");
	printf("\t\t\t\t\t\t  [2] Setting\n");
	printf("\t\t\t\t\t\t  [3] Help\n");
	printf("\t\t\t\t\t\t  [4] Exit\n");
	printf("\n\n\n\n\n\nNOTE: To navigate through this section, use arrow keys to go up and down\n      and press enter to get inside the chosen function\n");
	x=getch();
	if(x==72)
	{
		fourth();
	}
	if(x==80)
	{
		second();
	}
	if(x=='\r')
		{
			x='+';
			return;
		}
	if(x=='+')
		{
			return;
		}
	else
	{
		first();
	}
}

void second()
{
	x==NULL;
	system("cls");
	printf("\t\t\t\t\t\tMUSIC PLAYER\n\n\n");
	printf("\t\t\t\t\t\t  [1] Start\n");
	printf("\t\t\t\t\t\t  >[2] Setting\n");
	printf("\t\t\t\t\t\t  [3] Help\n");
	printf("\t\t\t\t\t\t  [4] Exit\n");
	printf("\n\n\n\n\n\nNOTE: To navigate through this section, use arrow keys to go up and down\n      and press enter to get inside the chosen function\n");
	x=getch();
		if(x==72)
		{
			first();
		}
		if(x==80)
		{
			third();
		}
		if(x=='\r')
		{
			setting();
		}
		if(x=='+')
		{
			return;
		}
		else
	{
		second();
	}
}

void third()
{
	x==NULL;
	system("cls");
	printf("\t\t\t\t\t\tMUSIC PLAYER\n\n\n");
	printf("\t\t\t\t\t\t  [1] Start\n");
	printf("\t\t\t\t\t\t  [2] Setting\n");
	printf("\t\t\t\t\t\t  >[3] Help\n");
	printf("\t\t\t\t\t\t  [4] Exit\n");
	printf("\n\n\n\n\n\nNOTE: To navigate through this section, use arrow keys to go up and down\n      and press enter to get inside the chosen function\n");
	x=getch();
		if(x==72)
		{
			second();
		}
		if(x==80)
		{
			fourth();
		}
		if(x=='\r')
		{
			help();
		}
		if(x=='+')
		{
			return;
		}
		else
	{
		third();
	}
}

void fourth()
{
	x==NULL;
	system("cls");
	printf("\t\t\t\t\t\tMUSIC PLAYER\n\n\n");
	printf("\t\t\t\t\t\t  [1] Start\n");
	printf("\t\t\t\t\t\t  [2] Setting\n");
	printf("\t\t\t\t\t\t  [3] Help\n");
	printf("\t\t\t\t\t\t  >[4] Exit\n");
	printf("\n\n\n\n\n\nNOTE: To navigate through this section, use arrow keys to go up and down\n      and press enter to get inside the chosen function\n");
	x=getch();
		if(x==72)
		{
			third();
		}
		if(x==80)
		{
			first();
		}
		if(x=='\r')
		{
			exit(0);
		}
		if(x=='+')
		{
			return;
		}
		else
	{
		fourth();
	}
}

void setting()
{
	int b,t,e;
	e=NULL;
	set:
	printf("\t1.Change color\n\t2.Back to main menu\n\nChoose one of them!\n");
	scanf(" %d", &e);
	switch(e)
	{
		case 1:
			set2:
			printf("1. Black Background White Text\n2. Black Background Green Text\n3. White Background Black Text\n4. White Background Red Text\n");
			scanf(" %d", &b);
				switch(b)
				{
					case 1:
						system("color 0");
						break;

					case 2:
						system("color 0A");
						break;

					case 3:
						system("color 70");
						break;

					case 4:
						system("color F4");
						break;

					default:
						printf("Invalid Input!");
						goto set2;
						break;
				}
			break;
		case 2:
			break;

		default:
			goto set;
			break;
	}
	second();
}

void help()
{
	system("cls");
	printf("This is a music player that can play a music\n");
	system("pause");
	third();
}
