/*
* author 2011136033 김형근
* 컴파일러 및 실습
* this program is implementation of context-free grammar.
* this program do not need sets of nontermianl, terminal.
* just use set of production and start symbol
*/
#include <stdio.h>
#include <string.h>

#define MAX_LEFT_HAND 16
#define MAX_RIGHT_HAND 32
#define MAX_STR 128

// production is a set of rules.
// P: left-hand side -> right-hand side
typedef struct _tagprod{
	char lhs[MAX_LEFT_HAND];			// left-hand side
	char rhs[MAX_RIGHT_HAND];			// right-hand side
} Production;

/*
* when use this function, you have to use NULL as prevInput
* @param 	prevInput 			Previous Input string
* @param 	input				input string
* @param 	production			a set of productions
* @param 	numOfProduction		number of productions
*/
void context_free_grammar(char* prevInput, char* input, Production* production, int numOfProduction, char* startSymbol){
	int prev, cur = 0;										// string pointer
	char temp[MAX_STR];										// we save converted input at this string
	int i;
	
	if(!strcmp(input, startSymbol))							// when input is same startSymbol, function end
		return;

	
	if(prevInput != NULL && !strcmp(prevInput, input)){		// prevInput is eventually same with input if you enter wrong input
		printf("Input Error: check your input\n");
		printf("Error String: %s\n", input);
		return;
	}
	
	memset(temp, 0, sizeof(char)*MAX_STR);
	
	while(cur < strlen(input)){
		prev = cur;
		
		for(i=0; i<numOfProduction; i++){	// check a set of production
			if(!strncmp(input + cur, production[i].rhs, strlen(production[i].rhs))){ // when has right-hand side of production
				strcat(temp, production[i].lhs);
				cur += strlen(production[i].rhs);
				break;
			}
		}
		
		if(prev == cur){	// when different with right-hand side of production
			strncat(temp, input+cur, 1);
			cur++;
		}
	}
	
	printf("%s\n", temp);
	context_free_grammar(input, temp, production, numOfProduction, startSymbol);	// recursive
}

int main(){
	Production prods[10];
	char str[MAX_STR];
	/*
	E -> int
	E -> E Op E
	E -> (E)
	Op -> +
	Op -> -
	Op -> *
	Op -> /
	The production below is used for the compatibility of E Op E
	E -> EOp E
	E -> E OpE
	E -> EOpE
	*/
	// initialize productions
	strcpy(prods[0].lhs, "E");
	strcpy(prods[0].rhs, "int");

	strcpy(prods[1].lhs, "E");
	strcpy(prods[1].rhs, "E Op E");
	
	strcpy(prods[2].lhs, "E");
	strcpy(prods[2].rhs, "(E)");
	
	strcpy(prods[3].lhs, "Op");
	strcpy(prods[3].rhs, "+");
	
	strcpy(prods[4].lhs, "Op");
	strcpy(prods[4].rhs, "-");
	
	strcpy(prods[5].lhs, "Op");
	strcpy(prods[5].rhs, "*");	
	
	strcpy(prods[6].lhs, "Op");
	strcpy(prods[6].rhs, "/");
	
	strcpy(prods[7].lhs, "E");
	strcpy(prods[7].rhs, "EOp E");
	
	strcpy(prods[8].lhs, "E");
	strcpy(prods[8].rhs, "E OpE");
	
	strcpy(prods[9].lhs, "E");
	strcpy(prods[9].rhs, "EOpE");
	
	gets(str);
	context_free_grammar(NULL, str, prods, sizeof(prods)/sizeof(Production), "E");
	return 0;
}
