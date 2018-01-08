#include <stdio.h>
#include <math.h>

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

long long unique(long long input) {
    
    int i,j;
    long long u=0;
    
    for(i=0;i<no(input);i++)
    {
        for(j=0;j<i;j++)
            if((((long long)(input/pow(10,i)))%10)==(((long long)(input/pow(10,j)))%10))
                break;
        if(i==j)
            u=u*10+(((long long)(input/pow(10,i)))%10);
    }
    
    return u;
}

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

void output(int A[])
{   
	int i,j;
    printf("\n\n");
    for(i=0;i<3;i++)
    {   printf("  ");
        for(j=0;j<3;j++)
        { 
            if(A[3*i+j]==1)
                printf(" X ");
            else if(A[3*i+j]==-1)
                printf(" O ");
            else
                printf(" %d ",3*i+j+1);
            if(j!=2)
                printf("|");
        }
        if(i!=2)printf("\n  ___ ___ ___\n");
    }printf("\n");
}

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

int valid(int position,int A[])
{
    if(position>=0 && position<=8)
    {
        if(A[position]==0)
            return 1;
    }
    return 0;
}

int directWin(int place,int A[],int player)
{
    int testBoard[9]={0}; int i;
    for(i=0;i<=8;i++) testBoard[i]=A[i];
    testBoard[place]=player;
    
    if(checkwin(testBoard,player)==player)
        return 1;
    return 0;
}

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

int doubleWin(int place,int A[],int player)
{
    int testBoard[9]={0};
    int i,j;
    for(int i=0;i<=8;i++) testBoard[i]=A[i];
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
int blockAllDoubleWin(int place,int A[],int player);

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


int get_random(int till) {
    srand(time(NULL));
    return rand() % till;
}

int getRandomMove(int A[],int player)
{
    long long int opt; int num,pos;
    
    opt=getMove(A,player);
    
    num=no(opt);
    pos=get_random(num);
    
    return (int)((long long int)(opt/((long long int)pow(10,pos))))%10;
}

int main()
{
    int board[9]={0};
    int position;
    int turn=1;
    int compPlaysX=1; int X=1; int O=-1; 
    
    while(1){
        printf("For computer to play first, input 1; if you want to play first, input -1 : ");
        scanf("%d",&compPlaysX);
        if( compPlaysX==X || compPlaysX==O ) break; 
        else printf("Invalid Input.\n");
    }
    
    do{
        output(board);
        if(turn%2==1)
        {
            printf("X-Input : ");
            if(compPlaysX==1) {position=getRandomMove(board,X); printf("%d",position);}
            else scanf("%d",&position);
            position--;
        }
        if(turn%2==0)
        {
            printf("O-Input : ");
            if(compPlaysX==-1) {position=getRandomMove(board,O); printf("%d",position);}
            else scanf("%d",&position);
            position--;
        }
        
        if(valid(position,board))
        {
            board[position]=(int)(pow(-1,turn+1));
            if( checkwin(board,pow(-1,turn+1)) == pow(-1,turn+1) )
            {
                output(board);
                if(pow(-1,turn+1)==1) printf("\nX wins\n");
                else printf("\nO wins\n");
                return 0;
            }
            turn++;
        }
    
    }while(turn<=9);
    
    output(board);
    printf("\nIts a draw.\n");
}