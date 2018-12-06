#include <stdlib.h>
#include "iostream"
#include "string"

void printError(char *arg);

std::string errMessage = "Incorrect command line arguments.\n"
    "Proper usage: 4d8, 2d6. '[number of dice]d[die face]'";

int main(int argc, char **argv) 
{
    int numDice, faceDice;
    srand(time(NULL));

    /*
     * Do error checking on command line arguments.
     * Requires 1 argument: "[number of dice]d[die faces]"
     */
    if (argc != 2) 
    {
        printError(argv[1]);
        return 0;
    }

    /*
     * Test the arg array for all integers before a single 'd' and all integers
     * after.
     */
    bool foundRadix = false;
    int i = 0;
    std::string temp = "";
    do 
    {
        // Error if char is not a digit or 'd'
        if (!isdigit(argv[1][i]) && (argv[1][i] != 'd' && argv[1][i] != 'D'))
        {
            printError(argv[1]);
            return 0;
        } 
        // Error if there has already been a 'd'
        else if (foundRadix && (argv[1][i] == 'D' || argv[1][i] == 'd'))
        {
            printError(argv[1]);
            return 0;
        }
        // Add digit to temp string for future conversion to int.
        if (isdigit(argv[1][i])) 
        {
            temp.push_back(argv[1][i]);
        }
        // Found the first (and only!) 'd' that should be there.
        // Also convert the temp string into an integer.
        if (argv[1][i] == 'D' || argv[1][i] == 'd')
        {
            numDice = std::stoi(temp);
            temp = "";
            foundRadix = true;
        }

        i++;
    } while (argv[1][i] != '\0');

    faceDice = std::stoi(temp);

    /*
     * At this point, we know that there are only 2 args and argv[1] is in
     * the correct format. The dice values are stored correctly in numDice
     * and faceDice.
     *
     * Now we calculate the actual die roll.
     */

    int total = 0;

    for (int i = 0; i < numDice; i++) 
    {
        total += rand() % faceDice + 1;
    }

    std::cout << "The total value of " << argv[1] << " dice are: " << total
        << std::endl;

    return 0;
}

/*
 * Prints the string error message and an optional C-style string
 * that I'm currently using for debugging.
 */
void printError(char *arg) 
{
    std::cout << errMessage << std::endl;
    // For debugging
    std::cout << arg << std::endl;
}

