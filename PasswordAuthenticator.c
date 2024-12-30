#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
int textfile(char * username, char* password)
{
    FILE *ptr = fopen("data.txt", "r");
    if(ptr == NULL)
    {
        printf("File not found");
        return 0;
    }
    char line[200];
    int i = 0;
    while(fgets(line, sizeof(line), ptr) != NULL)
    {
        line[strcspn(line, "\n")] = 0;
        if(i % 2 == 0)
        {
            if(strcmp(line, username) == 0)
            {
                if(fgets(line, sizeof(line), ptr) != NULL)
                {
                    line[strcspn(line, "\n")] = 0;
                    if(strcmp(line, password) == 0)
                    {
                		fclose(ptr);
						return 1;
					}
				}
			}
		}
		i++;
	}
	fclose(ptr);
	return 0;
}
void alarm()
{
	for (int i = 0; i < 3; i++) {
        MessageBeep(MB_ICONERROR);
        Sleep(100);
    }

}

int main()
{
    char *un = (char *) malloc(100 * sizeof(char));
    char *pas = (char *) malloc(100 * sizeof(char));
    int attempts = 0;
    time_t start_time, current_time;
	
    while (1) {
        if (attempts > 2) {
        	alarm();
            start_time = time(NULL);
            printf("Please wait 10 seconds before trying again...\n");
            do {
                current_time = time(NULL);
                printf("\rTime remaining: %2ld seconds", 10 - (current_time - start_time));
                fflush(stdout);
            } while (current_time - start_time < 10);
            printf("\n\n");
            attempts = 2;
        }
		while (_kbhit()) {
        _getch();
    	}
        puts("Enter your username and then your password\n");
        
        fgets(un, 100, stdin);
        un[strcspn(un, "\n")] = 0;
        fgets(pas, 100, stdin);
        pas[strcspn(pas, "\n")] = 0;
        printf("\n");

        int result = textfile(un, pas);
        if(result)
        {
            printf("Success\n");
            break;
        }
        else
        {
            printf("Not Successful\n");
            attempts++;
        }
    }

    free(un);
    free(pas);
}