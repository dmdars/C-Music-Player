#include <SDL.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

//#define Music path
char *musicBox[6][50], name[6][40];
char *args[]={"./final_project",NULL};
// Our music file
Mix_Music *music = NULL;

int search();
int change();
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
    int a=0, k, b=0, c=0, i=0, index=0, p=0, d=0, e=0;
    char text, line[1024];
    FILE *file;
    /*Get music path*/
    file = fopen("Music Collection.txt", "r");
        while(fscanf(file,"%s", musicBox[i]) != EOF)
            {
                i++;
            }
    fclose(file);

    i=0;
    /*Get Music Name*/
    FILE *fp = fopen ( "Music Name.txt", "r");
    text = getc ( fp );
        while ( text != EOF )
        {
            if ( text != '\n'){
                line[index++] = text;
            }
            else {
                line[index] = '\0';
                index = 0;
                strcpy(name[i], line);
                i++;
                /*printf ( "%s\n", line );*/
            }
            text = getc ( fp );
        }
    fclose ( fp );

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return -1;

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		return -1;

    /*Start*/
    back:
        printf("MUSIC PLAYER\n\n");
        for(i=0;i<6;i++)
        {
            printf("%d.%s\n", i+1, name[i]);
        }
        printf("\n\nSelect a music to play\n");
        scanf("%d", &c);
        printf("Press any button to continue.....\n\n");
        getchar();
    if(c == NULL || c<1 || c>6)
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
    Mix_HookMusicFinished(musicFinished);
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
        Mix_PauseMusic();
        e=1;
        break;

        case 3:
        Mix_HookMusicFinished(musicFinished);
        Mix_ResumeMusic();
        e=0;
        break;

        case 4:
        Mix_HookMusicFinished(musicFinished);
        change();
        break;

        case 5:
        Mix_RewindMusic();
        break;

        case 6:
        Mix_HookMusicFinished(musicFinished);
        printf("Skip Music to (second)\n");
        scanf("%d", &d);
        Mix_RewindMusic();
        if(Mix_SetMusicPosition(d)==-1) {
        printf("Mix_SetMusicPosition: %s\n", Mix_GetError());
        }
        break;

        case 7:
        Mix_HookMusicFinished(musicFinished);
        search();

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

int change()
{
        int c=0;
        restart:

        system("cls");
        printf("\t1.Impossible\n\t2.Victory\n\t3.Enchantress\n\t4.Star Sky\n\t5.Weight of The World\n\t6.Binary Star\n");
        scanf("%d", &c);
        printf("Press any button to continue\n");
        getchar();
        if(c>0 && c<7)
        {
            music = Mix_LoadMUS(musicBox[c-1]);
            if ( Mix_PlayMusic( music, 1) == -1 )
            {
                return -1;
            }
        }
        else
        {
            goto restart;
        }

    SDL_Quit();
}

int search()
{
    int i, j, k=0, m, n, p, t;
    char *result , searchSong[100], list[6][100], point, listSong[100];
    search:
    printf("Search your song\n\n");
    scanf("%s", searchSong);

    /*Searching substring from string*/
    for(i=0;i<6;i++)
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
    {
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
    scanf("%d", &n);
    printf("Press any button to continue\n");
    getchar();
    if(n<0 || n>k)
    {
        printf("INVALID INPUT!\n");
        system("pause");
        system("cls");
        goto lookout;
    }
    strcpy(listSong,list[n-1]);
    printf("%s", listSong);
    for(i=0;i<6;i++)
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
    int choice;
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
		    printf("press 1 play music and 2 to play game");
		    scanf("%d", &choice);
			x='+';
			//return;
		}
	if(x=='+')
		{
		    if(choice==1)
            {
                return;
            }
            else if(choice==2)
            {
                execvp(args[0],args);
            }

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
