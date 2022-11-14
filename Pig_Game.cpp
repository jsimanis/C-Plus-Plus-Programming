/*
	The game of Pig is a simple 2 player dice game in which the first player to reach 100 is the winner. 
	On each turn a player rolls a six sided dice. After each roll,
		if the player rolls a 1:
			player gets a score of 0 and loses their turn
		if the player rolls a 2-6, then they can either
			Roll again to acculmate more points. OR
			Hold. The sum of all rolls is added to the player's total score and ends their turn. 
*/

#include <iostream>
#include <cstdlib>
using namespace std; 

//Completes 1 turn of the human and returns the score for that one round
int humanTurn();
//Completes 1 turn of the computer and returns the score for that one round
int computerTurn();
bool isWinner(int score) {return score>=100;}

int main()
{
	int humanTotalScore =0;
	int computerTotalScore =0;
	int roundNum =1;
	srand(time(NULL));
	while (true){
		printf("\n***Round %d***\n", roundNum);
		int humanTurnScore = humanTurn();
		humanTotalScore += humanTurnScore;
		printf("You earned %d points this round\n", humanTurnScore);
		if (isWinner(humanTotalScore))
			{
				cout<<"\n\nHuman has won.\n";
				break;
			}
		
		int computerTurnScore= computerTurn();
		computerTotalScore += computerTurnScore;
		printf ("Computer earned %d points this turn.\n", computerTurnScore);
		if (isWinner(computerTotalScore))
			{
				cout<<"\n\nComputer has won.\n";
				break;
			}
		printf ("\nHuman total: %d\n", humanTotalScore);
		printf ("Computer total: %d\n", computerTotalScore);
		roundNum++;
	}
	printf ("Match ended with a human score of %d, and a computer score of %d/n", humanTotalScore, computerTotalScore);

} 


int humanTurn(){
	int currentTotal=0;
	while (true){
		int roll = (rand()% 5)+1;
		printf("You rolled a %d. Total turn score is %d.\n", roll, roll+currentTotal);
		if (roll ==1){
			cout<< "You lose a turn!\n";
			return 0;
		}
		else
			currentTotal += roll;
			cout<<"Roll again or hold? r/h: ";
			char input;
			cin>> input;
			if (input =='r')
				continue;
			else //input == h
				return currentTotal;
	}
}
/*
Computer will keep rolling until it has gained 20 or more points.
*/
int computerTurn(){
	int currentTotal=0;
	while (true){
		int roll = (rand()% 5)+1;
		if (roll ==1)
			return 0;
		else{
			currentTotal += roll;
			if (currentTotal >= 20)
				return currentTotal;
			else
				continue;
		}
	}
}

