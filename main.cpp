#include<iostream>
#include<windows.h>
using namespace std;
#include<conio.h>
#include<math.h>
#include<fstream>

void gotoRowCol(int rpos, int cpos)
{
	int xpos=cpos, ypos = rpos;
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void initBoard(char Board[],int Dim)
{
    for(int i=0;i<Dim*Dim;i++)
    {
        Board[i]='_';
    }
}
void print_board(char Board[], int Dim)
{
    for(int i=0;i<Dim*Dim;i++)
    {
        cout<<"  "<<Board[i];
        if((i+1)%Dim==0)
        {
            cout<<endl;
        }
    }
}
void ask_for_move(int &ri, int &ci,int &turn)
{
    cout<<endl<<"Enter row and colomn: "<<endl;
    cin>>ri>>ci;
    cout<<"Player "<<turn<<" turn.";
}
int twoDto1D(int ri,int ci,int Dim)
{
   return((ri-1)*Dim+(ci-1));
}
void write_on_board(char Board[],int Dim, int ri, int ci, char turn)
{
    int index=twoDto1D(ri,ci,Dim);
    Board[index]=turn;
}
void change_turn(int &turn)
{
    turn = (turn + 1)%2;
}
bool islegal(char board[],int ri, int ci, int Dim)
{
    if(ri>Dim || ci>Dim || ri<=0 || ci<=0)
    {
        return false;
    }
    int index=twoDto1D(ri,ci,Dim);
    if(board[index]!='_')
    {
        return false;
    }
    return true;
}
bool boolIsDraw(char Board[],int Dim)
{
    for(int i=0;i<Dim*Dim;i++)
    {
        if (Board[i]=='_')
        {
            return false;
        }
    }
    return true;
}

bool is_D2(char B[], int Dim, char turn)
{
    int counter=0;
    int ri=1;
    for(int ci=Dim; ci>0; ci-- )
    {
        int index=twoDto1D(ri,ci,Dim);
        if (B[index]==turn)
        {
            counter++;
            ri++;
        }
    }
    if(counter==Dim)
        {
            return true;
        }
    return false;
}
bool is_D1(char B[], int Dim, char turn)
{
    int counter=0;
    for(int ci=1; ci<=Dim; ci++ )
    {
        int ri=ci;
        int index=twoDto1D(ri,ci,Dim);
        if (B[index]==turn)
        {
            counter++;
        }
    }
    if(counter==Dim)
        {
            return true;
        }
    return false;
}

bool VW(char B[], int Dim, char turn)
{
    for(int ci=1; ci<=Dim; ci++)
    {
        int counter=0;
        for(int ri=1; ri<=Dim; ri++)
        {
            int index=twoDto1D(ri, ci,Dim);
            if(B[index]==turn)
            {
                counter++;
            }
        }
            if(counter==Dim)
        {
            return true;
        }
    }
    return false;
}
bool HW(char B[], int Dim, char turn)
{

    for(int ri=1; ri<=Dim; ri++)
    {
        int counter=0;
        for(int ci=1; ci<=Dim; ci++)
        {
            int index=twoDto1D(ri, ci,Dim);
            if(B[index]==turn)
            {
                counter++;
            }
        }
        if(counter==Dim)
        {
            return true;
        }
    }
    return false;
}
bool is_WIN(char B[], int Dim,char turn)
{
    return(VW(B,Dim,turn) || HW(B,Dim,turn) || is_D1(B,Dim,turn) || is_D2(B,Dim,turn)) ;
}
void writer(char B[], int Dim, int turn )
{
    ofstream write("shazia.txt");
    write<<Dim<<" ";
    write<<turn<<" ";
    for(int count = 0; count < Dim*Dim; count ++){
    write<< B[count] << " ";
}
    write.close();
}
void reader(char B[], int &Dim, int &turn )
{
    ifstream read("shazia.txt" );

    read>>Dim;
    read>>turn;
    for(int count = 0; count < Dim*Dim; count ++){
    read >>B[count];
}

}
int main()
{
    char y='p';
    cout<<"retain previous game by pressing 'p': ";
    cin>>y;
    int Dim =1, turn =0;
    int z=0;
    system("CLS");
    char Board[Dim*Dim];
    if(y=='p')
    {
        reader(Board, Dim, turn);
    }
    else
    {
        cout<<"Enter the dimension: ";
        cin>>Dim;
        turn=0;
        Board[Dim*Dim];
        initBoard(Board,Dim);
    }
    turn=0;
    char p_symbol[2];
    p_symbol[0]= 'X';
    p_symbol[1]= 'O';
    int ri,ci;
    writer(Board, Dim, p_symbol[turn]);
    do
    {
        gotoRowCol(2,0);
        print_board(Board,Dim);
        writer(Board, Dim, p_symbol[turn]);
        do
        {
            ask_for_move(ri,ci,turn);
            if(ri==0 || ci== 0)
            {
                writer(Board, Dim, p_symbol[turn]);
                exit(2);
            }


        }
        while(islegal(Board,ri,ci,Dim)==false);
        write_on_board(Board,Dim,ri,ci,p_symbol[turn]);
        if(is_WIN(Board,Dim,p_symbol[turn])==true)
        {
            z=1;
            break;
        }
        change_turn(turn);
        writer(Board, Dim, p_symbol[turn]);
    }
    while(boolIsDraw(Board,Dim)==false);
    gotoRowCol(2,0);
    print_board(Board,Dim);
    if(z==0)
    {
        gotoRowCol(10,20);
        cout<<"Game is draw!!"<<endl;
    }
    else{
    gotoRowCol(20, 20);
    if(turn==0)
    {
        cout<<"Player 1 wins ";
    }
    else
    {
        cout<<"Player 2 wins";
    }
    }
    gotoRowCol(25, 20);
}
