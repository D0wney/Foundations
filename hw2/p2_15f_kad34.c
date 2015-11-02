// Kevin Downey
// CS431 
// Program 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// === Global Variables ===

int stack_symbol =0; // checking stack symbol (see pda function)
int paras = 0; // checking equal number of paras (see pda function)
int paras_bool = 1; // checking to make sure last para is not an open para (see pda function)


// === PDA Function ===

// 6 states, 1 - 4 non accepting, 5 accepting, 6 trap/crash
// each case represents the corrsponding state

int pda(char input_char, int current_state)
{
	switch(current_state)
	{
		case 0:
			printf("READ: %c\n", input_char);
			if(input_char != '$')
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: trap state!\n");
				return 6;
			}
			else
			{
				printf("POP: nothing\n");
				printf("PUSH: $\n");
				printf("NEW STATE: q1\n");
				stack_symbol++;
				return 1;
			}
		case 1:
			printf("READ: %c\n", input_char);
			if(isalpha(input_char))
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q2\n");
				return 2;
			}
			else if(input_char == '(')
			{
				printf("POP: nothing\n");
				printf("PUSH: (\n");
				printf("NEW STATE: q3\n");
				paras++;
				paras_bool = 0;
				return 3;
			}
			else
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: trap state!\n");
				return 6;
			}
		case 2:
			printf("READ: %c\n", input_char);
			if(isalpha(input_char) || isdigit(input_char) || input_char == '_')
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q2\n");
				return 2;
			}
			else if(input_char == '+' || input_char == '-' || input_char == '*' || input_char == '/' )
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q1\n");
				return 1;
			}
			else if(input_char == ')')
			{
				printf("POP: (\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q4\n");
				paras--;
				paras_bool = 1;
				return 4;
			}
			else if(input_char == '$')
			{
				printf("POP: $\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q5\n");
				stack_symbol--;
				return 5;
			}
			else
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: trap state!\n");
				return 6;
			}
		case 3:
			printf("READ: %c\n", input_char);
			if(input_char == '(')
			{
				printf("POP: nothing\n");
				printf("PUSH: (\n");
				printf("NEW STATE: q3\n");
				paras++;
				paras_bool = 0;
				return 3;
			}
			else if(isalpha(input_char))
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q2\n");
				return 2;
			}
			else
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: trap state!\n");
				return 6;
			}
		case 4:
			printf("READ: %c\n", input_char);
			if(input_char == ')')
			{
				printf("POP: (\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q4\n");
				paras--;
				paras_bool = 1;
				return 4;
			}
			else if(input_char == '+' || input_char == '-' || input_char == '*' || input_char == '/' )
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q3\n");
				return 3;
			}
			else if(input_char == '$')
			{
				printf("POP: $\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: q5\n");
				stack_symbol--;
				return 5;
			}
			else
			{
				printf("POP: nothing\n");
				printf("PUSH: nothing\n");
				printf("NEW STATE: trap state!\n");
				return 6;
			}
		case 5:
			printf("READ: %c\n", input_char);
			printf("POP: nothing\n");
			printf("PUSH: nothing\n");
			printf("NEW STATE: trap state!\n");
			return 6;
		case 6:
			printf("READ: %c\n", input_char);
			printf("POP: nothing\n");
			printf("PUSH: nothing\n");
			printf("NEW STATE: trap state!\n");
			return 6;
	}
}

int main()
{
	char play;
	printf("Do you want to enter a string? (y/n): ");
    scanf("%c", &play);

    while(play == 'y')
    {
    	char* input_string;
        input_string = (char *) malloc(1000);

    	printf("Enter Sting: ");
    	scanf("%s", input_string);
        printf("%s\n", input_string);

    	int current_state = 0; 
    	int length = strlen(input_string); // get length for loop

    	paras = 0;
    	paras_bool = 1; // 1 is true, 0 false 
    	stack_symbol = 0;

    	int i = 0;
    	printf("Starting State: q0\n");
    	while(i<length) // loops until end of string
    	{
    		current_state = pda(input_string[i], current_state);
    		i++;
    		if(current_state == 6) // if trap state/crash breaks
    			break;
    	}

    	//printf("%d | %d | %d", current_state, paras, stack_symbol);

    	if(current_state==5 && paras==0 && stack_symbol==0 && paras_bool == 1)
    		printf("ACCEPTED\n");
    	else
    		printf("REJECTED\n");

    	printf("\n");
    	printf("Do you want to enter a string? (y/n): ");
    	scanf(" %c", &play);
    }
    return 0;
}
