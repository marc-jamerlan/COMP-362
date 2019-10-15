/**
* Name: Marc Julian Jamerlan
* Lab: Lab 2
* Date: 9/10/18
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processFiles(char *, char *, size_t);
void printHelp();

int main(int argc, char **argv)
{
	char *c;
	char *inputChar = NULL; // characters to replace
	char *outputChar = NULL; // replacement chars
       	size_t cLength;
       	size_t inputCharLength = 0;
       	size_t outputCharLength = 0;

	if(argc==1) // check if arguments have been passed
	{
		printf("No arguments passed, use 'sub -h' for help.\n");
	}
	if(argc>=2)
	{
		// go through all arguments
		for(int i = 1; i < argc; i++)
		{
			c = argv[i];

			switch(c[0])
			{
				case '-':
					switch(c[1])
					{
						// help screen
						case 'h':
							printHelp();
							exit(0);
						// character to be replaced	
						case '-':
						// get substring of c, copy to inputChar, get inputChar length
							cLength = strlen(c+2);
							inputChar = malloc(cLength+1);
							strncpy(inputChar, c+2, cLength);
							inputChar[cLength] = '\0';
               					        inputCharLength = strlen(inputChar);
							break;
						// replacement character
						case '+':
                           			// get substring of c, copy to outputChar, get outputChar length
							cLength = strlen(c+2);
							outputChar = malloc(cLength+1);
							strncpy(outputChar, c+2, cLength);
							outputChar[cLength] = '\0';
							outputCharLength = strlen(outputChar);
							break;	
						// input file 
						case 'i':
							i++;
							freopen(argv[i], "r", stdin);
							break;
						// output file
						case 'o':
							i++;
							freopen(argv[i], "w+", stdout);
							break;
						default:
							break;	
					}
					break;
				// characters used by terminal to specify standard input and output
                		case '>':
                    		i++;
                    		break;
                		case '<':
                    		i++;
                    		break;
				// all other important commands have '-' in front; disregard everything else
				default:
					printf("Invalid command line argument '%s', use 'sub -h' for help.\n", c);
					exit(1);
			}		
	
		}
		// proceed to process files after going through all args
		if(inputChar != NULL && outputChar != NULL)
        	{
			if(inputCharLength < outputCharLength) // use the smaller array as the size for processing
            			{
                			processFiles(inputChar, outputChar, inputCharLength);
            			}
            		else
            			{
                			processFiles(inputChar, outputChar, outputCharLength);
            			}
        	}
        	else
        	{
            		printf("Not enough arguments, use 'sub -h' for help.\n");
        	}
	}
	return 0;
}

void processFiles(char *inputChar, char *outputChar, size_t size)
{
	char c = getchar(); // get character from stdin

	while(c != EOF)
 	{
        	for(int i = 0; i < size; i++)
        	{
            		if(c == inputChar[i])
            		{	
                		c = outputChar[i];
                		break; // checks if stdin matches character to be replaced, replace c and break out of loop
            		}
        	}

        printf("%c", c); // prints the character to stdout
        c = getchar(); // reinitialize while loop
    	}
}

void printHelp()
{
	const char * const helpText = "\nUSAGE:\n\n"

"\tsub [ -h | --fromChars -+toChars [-i inputFile] [-o outputFile] ]\n\n"
"DESCRIPTION:\n\n"
"\tThis utility copies text from an input stream to an output stream replacing every\n" 
"\tinstance of a specific character in fromChars with a corresponding (position-wise)\n" 
"\tcharacter from toChars. Any characters in fromChars and in toChars that do not\n" 
"\thave corresponding counterparts in the other one are ignored. If an input file is\n" 
"\tprovided, the content is read from that file; otherwise, the standard input is used.\n" 
"\tIf an output file is provided, then the modified content is written to that file;\n" 
"\totherwise, the standard output is used.\n\n"
"OPTIONS:\n\n"

"\t-- (followed by a string without separating space)\n"
"\t indicates all characters that will be replaced in the processed text\n\n"

"\t-+ (followed by a string without separating space)\n"
"\t indicates the characters that will be used to replace corresponding\n" 
"\t (position-wise) characters from fromChars in the processed text\n\n"

"\t-i (followed by input file name)\n"
"\t use the provided file as an input stream instead of standard input\n\n" 

"\t-o (followed by output file name)\n"
"\t use the provided file as an output stream instead of standard output\n\n" 

"\t-h prints this help message\n\n";

printf("%s", helpText);

}
