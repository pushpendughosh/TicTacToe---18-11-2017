//
//  Code to print all possible board configurations resulted when both player plays optimally
//  Project : tit-tac-toe LCS
//
//  Created by PUSHPENDU GHOSH on 18/11/2017.
//  Duration : 10 days
//  Copyright © 2017 PUSHPENDU. All rights reserved.
//

#include <stdio.h>

//returns exp to remove dependency on math.h library
long long int power(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y%2 == 0)
        return power(x, y/2)*power(x, y/2);
    else
        return x*power(x, y/2)*power(x, y/2);
}

//returns number of digits in a given number
int no(long long n)
{
    int count=0;
    while(n != 0)
    {
        n /= 10;
        ++count;
    }
    return count;
}
int playedTillNow;

//returns number removing all multi-occurencies. Ex: Input:=4517144 Output:=4517   
long long unique(long long input) {
    
    int i,j;
    long long u=0;
    
    for(i=0;i<no(input);i++)
    {
        for(j=0;j<i;j++)
            if((((long long)(input/power(10,i)))%10)==(((long long)(input/power(10,j)))%10))
                break;
        if(i==j)
            u=u*10+(((long long)(input/power(10,i)))%10);
    }
    
    return u;
}

//reverses a given number
long long reverse(long long num)
{
    long long rev_num = 0;
    while(num > 0)
    {
        rev_num = rev_num*10 + num%10;
        num = num/10;
    }
    return rev_num;
}

//outputs the board given the 3x3 array
void output(int A[])
{   
	int i,j;
    printf("\n");
    for(i=0;i<3;i++)
    {   printf("  ");
        for(j=0;j<3;j++)
        { 
            if(A[3*i+j]==1)
                printf(" X ");
            else if(A[3*i+j]==-1)
                printf(" O ");
            else
                printf("   ");
            if(j!=2)
                printf("|");
        }
        if(i!=2)printf("\n  ___ ___ ___\n");
    }printf("\n\n");
}

//checks the win of X or O, given a set of board configurations
int checkwin(int A[],int XorO)
{
    if(A[0]==XorO && A[1]==XorO && A[2]==XorO) return XorO;
    if(A[3]==XorO && A[4]==XorO && A[5]==XorO) return XorO;
    if(A[6]==XorO && A[7]==XorO && A[8]==XorO) return XorO;
    if(A[0]==XorO && A[3]==XorO && A[6]==XorO) return XorO;
    if(A[1]==XorO && A[4]==XorO && A[7]==XorO) return XorO;
    if(A[2]==XorO && A[5]==XorO && A[8]==XorO) return XorO;
    if(A[0]==XorO && A[4]==XorO && A[8]==XorO) return XorO;
    if(A[2]==XorO && A[4]==XorO && A[6]==XorO) return XorO;
    
    return 0;
}

//returns 1 if the position is valid; position belongs to {1,2,3,...,9}
int valid(int position,int A[])
{
    if(position>=0 && position<=8)
    {
        if(A[position]==0)
            return 1;
    }
    return 0;
}

//returns 1 if 'player' wins by placing its mark on 'place' in board config 'A' 
int directWin(int place,int A[],int player)
{
    int testBoard[9]={0}; int i;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    if(checkwin(testBoard,player)==player)
        return 1;
    return 0;
}


//returns 1 if there exist a chance of direct win of 'player' in next move, if it places its mark on 'place' in board config 'A' 
int singleWin(int place,int A[],int player)
{
    int testBoard[9]={0}; int i;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
            if(directWin(i,testBoard,player))
                return 1;
    return 0;
}

//returns the position where if placed the 'player' has a chance of direct win in next move 
int positionOfWin(int place,int A[],int player)
{
    int testBoard[9]={0}; int i;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
            if(directWin(i,testBoard,player))
                return i;
    return 10;
}

// returns 1 if 'player' places its mark on 'place' in the board config 'A' and it becomes a force win (two way win -mate)
int doubleWin(int place,int A[],int player)
{
    int testBoard[9]={0};
    int i,j;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
            if(directWin(i,testBoard,player))
                for(j=i+1;j<=8;j++)
                    if(testBoard[j]==0)
                        if(directWin(j,testBoard,player))
                            return 1;
           
    return 0;
}

// returns 1 if there exist a chance of forced win in next move if ...
int nextMoveDoubleWin(int place,int A[],int player)
{
    int testBoard[9]={0}; int i;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
                if(doubleWin(i,testBoard,player))
                    return 1;
    return 0;
}

// returns 1 if there exist a forced win after 2 steps if now 'player' ...
int forcedWin(int place,int A[],int player)
{
    int testBoard[9]={0}; int i,j,k,success;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
            if(directWin(i,testBoard,player))
            {
                testBoard[i]=player*-1;
                    
                for(j=0;j<=8;j++)
                    if(testBoard[j]==0)
                        if(doubleWin(j,testBoard,player))
                        {
                            testBoard[j]=player;
                            success=1;
                            for(k=0;k<=8;k++)
                                if(testBoard[k]==0)
                                    if(directWin(k,testBoard,player*-1))
                                        success=0;
                            if(success==1)
                                return 1;
                            testBoard[j]=0;
                        }
                testBoard[i]=0;
            }
    
    return 0;
}

// returns 1 if checking for forced win 'player' falls in forced win of oponent
int forcedLoose(int place,int A[],int player)
{
    int testBoard[9]={0}; int i,j,k;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
            if(forcedWin(i,testBoard,player*-1))
                return 1;
    return 0;
}
// just a defination
int blockAllDoubleWin(int place,int A[],int player);

// returns 1 if 'player' looses by fluke, own step causing trap for himself
int LooseByChance(int place,int A[],int player)
{
    int testBoard[9]={0}; int i,j,k,exist,possible;
    
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
            if(directWin(i,testBoard,player))
            {
                testBoard[i]=player*-1;
                if(forcedWin(i,testBoard,player*-1))
                    return 1;
                
                exist=0; possible=0;
                for(j=0;j<=8;j++)
                    if(testBoard[j]==0)
                        if(doubleWin(j,testBoard,player*-1))
                            exist=1;
                
                if(exist)
                    for(j=0;j<=8;j++)
                        if(testBoard[j]==0)
                            if(blockAllDoubleWin(j,testBoard,player))
                                possible=1;
                
                if(exist&&(!possible))
                    return 1;
                testBoard[i]=0;
            }
    return 0;
}

// returns if a particular move : 'place' of 'player' blocks all double wins created by oponent
int blockAllDoubleWin(int place,int A[],int player)
{
    int testBoard[9]={0}; int i,j,k;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    for(i=0;i<=8;i++)
        if(testBoard[i]==0)
            if(doubleWin(i,testBoard,player*-1))
                return 0;
    return 1;
}

/* Main sequence of logic which are checked and used to decide all optimal moves possible, this function returns all possible
optimal moves by storing them in a long long variable. Ex: Optimal moves: 3,5,6,9; then program returns 3569. */
long long getMove(int A[],int player)
{
    int i,j,k,l,should,place,moved; int doNotPlace[9]={0}; long long optim=0;
    
    int turn=0;
    for(i=1;i<=8;i++)
        if(A[i]!=0)
            turn++;
    turn++;
    
    //direct Win of player
    for(i=0;i<=8;i++)
        if(A[i]==0)
            if(directWin(i,A,player)) 
                optim=optim*10+i+1;
    if(optim>0) return optim;
    
    //direct Win of oponent
    for(i=0;i<=8;i++)
        if(A[i]==0)
            if(directWin(i,A,player*-1)) 
                optim=optim*10+i+1;
    if(optim>0) return optim;
    
    //double Win of player
    for(i=0;i<=8;i++)
        if(A[i]==0)
            if(doubleWin(i,A,player))
                optim=optim*10+i+1;
    if(optim>0) return optim;
    
    //search all double Win possibilities of oponent
    int indx=0;
    for(i=0;i<=8;i++)
        if(A[i]==0)
            if(doubleWin(i,A,player*-1))
            {
                doNotPlace[indx]=i;
                indx++;
            }
    
    //If any doubleWin exist : 
    //1. places at singleWin which is not a looseByChance, also a ForcedWin to oponent and the position of newly created directWin of player is not a doubleWin position of oponent  
    if(indx>0)
        for(i=0;i<=8;i++)
            if(A[i]==0)
                if(singleWin(i,A,player))
                    if(!LooseByChance(i,A,player))
                        if(forcedWin(i,A,player))
                        {
                            place=positionOfWin(i,A,player);

                            should=1;
                            for(j=0;j<indx;j++) 
                                if(place==doNotPlace[j])
                                    should=0;
                            if(should==1)
                                optim=optim*10+i+1;
                        }
    // (contd..)-> places at a forcedWin
    for(i=0;i<=8;i++)
        if(A[i]==0)
            if(forcedWin(i,A,player))
                optim=optim*10+i+1;
    if(optim>0) return unique(optim);
    
    //2.places where it is able to block all double wins and is not a Loose by chance
    if(indx>0)
        for(i=0;i<=8;i++)
            if(A[i]==0)
                if(blockAllDoubleWin(i,A,player))
                    if(!LooseByChance(i,A,player))
                        optim=optim*10+i+1;
    
    // (contd..)-> places at singleWin and not a Loose by chance and the position of newly created directWin of player is not a doubleWin position of oponent.
    if(indx>0)
        for(i=0;i<=8;i++)
            if(A[i]==0)
                if(singleWin(i,A,player))
                {
                    if(!LooseByChance(i,A,player))
                    {
                        place=positionOfWin(i,A,player);
                        should=1;
                        for(j=0;j<indx;j++) 
                            if(place==doNotPlace[j])
                                should=0;
                        if(should==1)
                            optim=optim*10+i+1;
                    }
                }
    if(optim>0) return unique(optim);
    
    //places anywhere which does not create a forced Loose of player ahead
    for(i=0;i<=8;i++)
        if(A[i]==0)
            if(!forcedLoose(i,A,player))
                optim=optim*10+i+1;
    if(optim>0) return optim;
    
    return 0;    
}

// prints all moves 1 step at a time
void graphic(int key,long long int state,int win)
{
    long long rev; int board[9]={0}; int move=0;
    rev=reverse(state);
    int turn=1;
    
    printf("\nBest move possibility %d :\n",key);
    while(rev!=0)
    {
        board[(rev%10)-1]=turn;
        turn=turn*-1; move++;
        rev=rev/10;
        
        if(move>=playedTillNow)
            output(board);
    }
    if(win)
        printf("      WIN\n");
    else
        printf("      DRAW\n");
    printf("******************\n");
}

/* creates a board config 'board' out of 'init' (a big number which stores previously played moves), then this function returns
the optimal moves after the config 'board' */
long long optim(long long init)
{
    int board[9]={0}; int i,j;
    
    long long rev; 
    rev = reverse(init);
    
    for(i=1;i<=9;i++)
    {
        if((((int)(rev/(power(10,i))))%10)==0) break;
        
        board[(((int)(rev/(power(10,i))))%10)-1]=1;
        if(i%2==0)
            board[(((int)(rev/(power(10,i))))%10)-1]*=-1;
    }
    
    int player;
    player = (int)power(-1,i+1);
    
    if(rev%10 == 1)
    {
        for(j=0;j<9;j++)
            board[j]*=-1;
        player=player*-1;
    }
    
    return getMove(board,player);
}

// returns 1 if state (board config) is not totally filled, 0 if finished and -1 if there was an intermediate win by either players
int finish(long long state)
{
    int board[9]={0}; int i,j;
    
    long long rev; 
    rev = reverse(state);
    
    for(i=1;i<=9;i++)
    {
        if((((int)(rev/(power(10,i))))%10)==0) break;
        
        board[(((int)(rev/(power(10,i))))%10)-1]=1;
        if(i%2==0)
            board[(((int)(rev/(power(10,i))))%10)-1]*=-1;
    }
    
    int player;
    player = (int)power(-1,i+1);
    
    if(rev%10 == 1)
    {
        for(j=0;j<9;j++)
            board[j]*=-1;
        player=player*-1;
    }
    
    if (checkwin(board,1)||checkwin(board,-1))
        return -1;
    
    if(i==10)
        return 0;
    
    return 1;
}

int draw;
int win;

// This is the recursive depth search function that checks for all possible best moves
void depthSearch(long long initial)
{
    long long choice; int checkEnd; long long int rev;
    
    checkEnd = finish(initial);
    
    if(checkEnd == 1)
    {
        choice = optim(initial);
        while(choice!=0)
        {
            depthSearch(initial*10+choice%10);
            choice=(int)(choice/10);
        }
    }
    else if(checkEnd == 0)
    {
        draw++;
        rev=reverse(initial);
        rev/=10;
        //printf("%d %lld\n",draw,reverse(rev));
        graphic(draw,reverse(rev),0);
    }
    else
    {
        win++;
        printf("Initial state was not optimal. ");
        rev=reverse(initial);
        rev/=10;
        //printf("%lld\n",reverse(rev));
        graphic(win,reverse(rev),1);
        return;
    }
}

int main()
{
    long long initial,rev;
    
    	/* input the initial board condn. Ex : If we want to check the board condition after cross plays at 1 and nought plays
	at 4, we input 14 */
	printf("\nGive the starting board : ");
    	scanf("%lld",&initial);
    
    playedTillNow=no(initial);
    
    rev=reverse(initial);
    rev=rev*10+3;
    initial=reverse(rev);
    
    	// Prints all possible wins or draws. Ex : If initial=14 ; it is forced win for cross thereafter, so it shows all possible wins
	depthSearch(initial);
}
