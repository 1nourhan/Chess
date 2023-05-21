#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int board[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,
                -6,-6,-6,-6,-6,-6,-6,-6,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                6, 6, 6, 6, 6, 6 ,6, 6,
                1 ,2, 3, 4, 5, 3 ,2, 1};
int tempboard[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,
                -6,-6,-6,-6,-6,-6,-6,-6,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                6, 6, 6, 6, 6, 6 ,6, 6,
                1 ,2, 3, 4, 5, 3 ,2, 1};
int board2[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,
                -6,-6,-6,-6,-6,-6,-6,-6,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                6, 6, 6, 6, 6, 6 ,6, 6,
                1 ,2, 3, 4, 5, 3 ,2, 1};

FILE* saveload;
int white = 1;
int inactiveMoves;
int numofmoves = 0;
int countundo = 0;
typedef struct{
int boardcpy[8][8];
int moves;
} movements;
movements arr[5000];
int checkmate = 0;
int stalemate = 0;
int resigned = 0;
int pawnsNom = 0;
int tempPawnsNom = 0;
int black_rook1_moved;
int black_rook2_moved;
int white_rook1_moved;
int white_rook2_moved;
int whiteKingMoved;
int blackKingMoved;
int validMove(int [][8],int ,int ,int ,int);
int makeMove(int [][8],int ,int ,int ,int);
int whitePawns(int [][8],int ,int ,int ,int);
int blackPawns(int [][8],int ,int ,int ,int);
int knight(int [][8],int ,int ,int ,int);
int rooks(int [][8],int ,int ,int ,int );
int bishop(int [][8],int ,int ,int ,int );
int king(int [][8],int ,int ,int ,int );
int castling(int [][8],int ,int ,int ,int );
int kingSafe(int [][8]);
int playerHasValidMove(void);
void castle(int ,int ,int ,int );
void pawn_promotion(int ,int );
void printBoard(void);
void printInvalidMove(void);
void LOAD();
void SAVE();
void undo();
void redo();
void gamesystem();

int main()
{
    black_rook1_moved = 0;
    black_rook2_moved = 0;
    white_rook1_moved = 0;
    white_rook2_moved = 0;
    whiteKingMoved = 0;
    blackKingMoved = 0;
    white = 1;
    tempPawnsNom = 32;
    printf("Hi\n\t\t\t\tWelcome to our game\n\n");
    printf("\t\t\t\tFinal project\t\t\n");
    printf("\t\t\t\tchess\t\t\t\n");
    printf("INSTRUCTIONS :\n");
    printf(">For the board squares . for black squares and - for white squares.\n");
    printf(">The game always start with the white player.\n");
    printf(">White pieces are represented by {p, r, n, b, q, k} for pawns, rooks, knights, bishops, queen and king respectively.\n Black pieces are represented by the same letters but capitalized.\n");
    printf(">Above the board the pieces that are currently taken out from both players.\n");
    printf(">The characters from 'A' to 'H' to denote the columns above and below the board,\n along with the numbers from 1 to 8 to denote the rows to the right and left of the board.\n");
    printf(">player can enter the move by typing:-/n NOTE: The column alphabet and the row number of the pawn they want to move followed by the column alphabet\n and the row number of the position they want their pawn to move to.\n");
    printf(" >>For example A2A4 will move the pawn at column 'A', row 2 to position column 'A', row 4.\n");
    printf(">Spaces in between or small letters are not accepted.\n");
    printf(">For promotion : you ‘ll find a message that ask you about the piese that you want to promote to it.\n");
    printf(">The player can enter 'r' or 'R' to resign at any stage of the game.\n");
    printf(">The player can enter 'save' or 'SAVE' to Save game.\n");
    printf(">The player can enter 'load' or 'LOAD' to load the previous game.\n");
    printf(">The player can enter 'undo' or 'UNDO' to undo game.\n");
    printf(">The player can enter 'redo' or 'REDO' to redo game.\n");
    printf("\n\n\t\t\t\tLet's start new game\t\t\n\n\n");

    gamesystem();
    printBoard();

    if (checkmate)
    {
        printf("\nCongratulations \nCheckmate\n\n");
       if (white)
       {printf("\nWhite wins\n\n");}
       else
       {printf("\nBlack wins\n\n");}
    }
    else if (stalemate)
    {
        printf("\nStalemate\n\n");
        printf("\nMatch drawn\n\n");
        }
    else if (inactiveMoves>50)
    {
        printf("\nfifty inactive moves\n\n");
        printf("\nMatch drawn\n\n");
    }
    else if (resigned)
    {
        if (!white)
        {
          printf("\nWhite wins\n\n");
        }
        else
        {
          printf("\nBlack wins\n\n");
        }
    }
    printf("\nThanks for playing\n\n");


}

//functions
void gamesystem(){
    char move[4],C,c;
        while (playerHasValidMove())
    {
        numofmoves++;
        if (tempPawnsNom == pawnsNom)
            {inactiveMoves++;}
        else
            {inactiveMoves = 1;}

        tempPawnsNom = pawnsNom;

        if (inactiveMoves>50)
            break;

        if(!((move[0] == 'u' || move[0] == 'U' )&&(move[1] == 'n' || move[1] == 'N')&& (move[2] == 'd' || move[2] == 'D') && (move[3] == 'o' || move[3] == 'O')))
     {
         arr[numofmoves-1].moves = numofmoves-1;
         memcpy(arr[numofmoves-1].boardcpy,board,sizeof(board));

     }
     else{
            arr[numofmoves].moves = numofmoves;
         memcpy(arr[numofmoves].boardcpy,board,sizeof(board));

         }
    printBoard();

    if (!kingSafe(board)){
        if (white)
        {printf("\nWhite king in check\n\n");}
        else
        {printf("\nBlack king in check\n\n");}}

    if (white) printf("White");
    else printf("Black");
    printf("'s turn\nEnter your move : ");
    scanf("%s",move);
    if((move[0] == 'S' || move[0] == 's' )&&(move[1] == 'A' || move[1] == 'a')&& (move[2] == 'V' || move[2] == 'v') && (move[3] == 'E' || move[3] == 'e'))
     {SAVE();
     break;
     }
      else if((move[0] == 'l' || move[0] == 'L' )&&(move[1] == 'o' || move[1] == 'O')&& (move[2] == 'A' || move[2] == 'a') && (move[3] == 'd' || move[3] == 'D'))
     {LOAD();
      if (checkmate)
    {
        printf("\nCongratulations \nCheckmate\n\n");
       if (white)
       {printf("\nWhite wins\n\n");}
       else
       {printf("\nBlack wins\n\n");}
    }
    else if (stalemate)
    {
        printf("\nStalemate\n\n");
        printf("\nMatch drawn\n\n");
        }
    else if (inactiveMoves>50)
    {
        printf("\nfifty inactive moves\n\n");
        printf("\nMatch drawn\n\n");
    }
    else if (resigned)
    {
        if (!white)
        {
          printf("\nWhite wins\n\n");
        }
        else
        {
          printf("\nBlack wins\n\n");
        }
    }
    printf("\nThanks for playing\n\n");
    printf("saved");
     continue;
     }
    else if((move[0] == 'u' || move[0] == 'U' )&&(move[1] == 'n' || move[1] == 'N')&& (move[2] == 'd' || move[2] == 'D') && (move[3] == 'o' || move[3] == 'O'))
     {undo();
      white = !white;
     continue;
     }
    else if((move[0] == 'r' || move[0] == 'R' )&&(move[1] == 'e' || move[1] == 'E')&& (move[2] == 'd' || move[2] == 'D') && (move[3] == 'o' || move[3] == 'O') && countundo)
     {redo();
     white = !white;
     continue;
     }

        printf("\n");

        int len,start[2],end[2];
        len = (int)strlen(move);
        if (len == 1 && (move[0] == 'r' || move[0] == 'R'))
        {
            resigned = 1;
            break;
        }

        if ((len == 4) && isalpha(move[0]) && isalpha(move[2]) && isdigit(move[1]) && isdigit(move[3]) )
        {
            switch(move [0])
            {
                case 'A':
                    start[1]=0;
                    break;
                case 'B':
                    start[1]=1;
                    break;
                case 'C':
                    start[1]=2;
                    break;
                case 'D':
                    start[1]=3;
                    break;
                case 'E':
                    start[1]=4;
                    break;
                case 'F':
                    start[1]=5;
                    break;
                case 'G':
                    start[1]=6;
                    break;
                case 'H':
                    start[1]=7;
                    break;
                default:
                    printInvalidMove();
                    continue;
            }
            start[0] = ('9' - move[1]) - 1;
            end[0]= ('9' - move[3]) - 1;
            if (start[0]>8 || end[0]>8)
            {
                printInvalidMove();
                continue;
            }
            switch(move [2])
            {
                case 'A':
                    end[1]=0;
                    break;
                case 'B':
                    end[1]=1;
                    break;
                case 'C':
                    end[1]=2;
                    break;
                case 'D':
                    end[1]=3;
                    break;
                case 'E':
                    end[1]=4;
                    break;
                case 'F':
                    end[1]=5;
                    break;
                case 'G':
                    end[1]=6;
                    break;
                case 'H':
                    end[1]=7;
                    break;
                default:
                    printInvalidMove();
                    continue;
            }
            if (validMove(board,start[0],start[1],end[0],end[1]))
            {
                if ((board[start[0]][start[1]] == 6 && start[0] == 1) || (board[start[0]][start[1]] == -6 && start[0] == 6))
                    pawn_promotion(start[0], start[1]);
                if(makeMove(board,start[0],start[1],end[0],end[1]))
                {
                    // to know if the kings & rooks  moved befor or not for castling
                    switch(board[end[0]][end[1]])
                    {
                        case 5:
                        case -5:
                            if (!white)
                                whiteKingMoved = 1;
                            else
                                blackKingMoved = 1;
                            break;
                        case 1:
                        case -1:
                            if (start[0] == 0 && start[1] == 0)
                                black_rook1_moved = 1;
                            else if (start[0] == 0 && start[1] == 7)
                                black_rook2_moved = 1;
                            else if (start[0] == 7 && start[1] == 0)
                                white_rook1_moved = 1;
                            else if (start[0] == 7 && start[1] == 7)
                                white_rook2_moved = 1;
                            break;
                        default:
                            continue;
                    }
                    continue;
                }
                else
                    printInvalidMove();

                if (white) printf("\nWhite");
                else printf("\nBlack");
                printf(" king gets into check\n");
                }

            else
                printInvalidMove();
        }
        else
            printInvalidMove();
}
}
void undo(){
    if (numofmoves <= 1){
        printf("there is no movement to be undone\n");
    }
    else if(numofmoves == 2){
        numofmoves--;
        countundo++;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){

                board[i][j] = board2[i][j];}}
        }
    else{
            numofmoves--;
            countundo++;

           if(numofmoves == arr[numofmoves].moves){
          memcpy(board,arr[numofmoves-1].boardcpy,sizeof(board));}}
}

void redo(){
     if(countundo==0)
        {printf("there is no movement to be redone");
}
    else
    {numofmoves++;
     countundo--;
     memcpy(board,arr[numofmoves-2].boardcpy,sizeof(board));}}

void SAVE()
{
  saveload = fopen("saveload.txt","w");
  if(saveload==NULL)
  {printf("can`t open file");}
  else
    { for(int j=0;j<8;j++)
        {for(int i=0;i<8;i++)
            {   putw(board[j][i],saveload);
                }}
    putw(white,saveload);
    }
fclose(saveload);}

void LOAD()
{   saveload = fopen("saveload.txt","r");
    if(saveload==NULL){
      printf("can`t open file");
    }
    else
    { for(int j=0;j<8;j++)
        {for(int i=0;i<8;i++)
            { board[j][i] = getw(saveload);}
    }white =  getw(saveload);
    fclose(saveload);
    }
}


void printInvalidMove()
{   inactiveMoves--;
    printf("\nBe Attention\nInvalid move\n\n");
}

void printBoard()
{
    // TO DETERMINE THE TAKEN OUT PECIES
    int wp=8,wn=2,wk=1,wq=1,wb=2,wr=2;
    int bp=8,bn=2,bk=1,bq=1,bb=2,br=2;

    for (int r =0 ; r < 8; r++)
    {
        for (int c = 0; c<8 ; c++)
        {
            switch (board[r][c])
            {
            case 1:
                wr--;
                break;
            case 2:
                wn--;
                break;
            case 3:
                wb--;
                break;
            case 4:
                wq--;
                break;
            case 5:
                wk--;
                break;
            case 6:
                wp--;
                break;
            case -1:
                br--;
                break;
            case -2:
                bn--;
                break;
            case -3:
                bb--;
                break;
            case -4:
                bq--;
                break;
            case -5:
                bk--;
                break;
            case -6:
                bp--;
                break;

            }
        }
    }
    if(wn <0){
        wn = 0;
        wp--;
    }
    else if(wq <0){
        wq = 0;
        wp--;
    }
    else if(wb <0){
        wb = 0;
        wp--;
    }
    else if(wr <0){
        wr = 0;
        wp--;
    }
    else if(bn <0){
        bn = 0;
        bp--;
    }
    else if(bq <0){
        bq = 0;
        bp--;
    }
    else if(bb <0){
        bb = 0;
        bp--;
    }
    else if(br <0){
        br = 0;
        bp--;
    }
    printf ("The taken out pieces displayed :\n");
    printf ("For white player :%dp %dn %dk %dq %db %dr \n",wp,wn,wk,wq,wb,wr);
    printf ("For black player :%dP %dN %dK %dQ %dB %dR \n\n",bp,bn,bk,bq,bb,br);

    //TO form the shape of the board
    char col_name[8] = {'A','B','C','D','E','F','G','H'};
    printf("      %c ",col_name[0]);

    for (int i=0; i<8;i++)
        printf("    %c ",col_name[i+1]);
    printf("\n");
    for (int row = 0,p=8;row<8;row++,p--)
    {
        printf(" %d ",p);
        printf(" ");
        for (int col = 0;col<8;col++)
        {
            if(row%2==0){
                if (col%2==0)
                    printf("%c",45);
                else
                    printf("%c",46);
            }else {
                if (col%2==0)
                    printf("%c",46);
                else
                    printf("%c",45);
            }
            //to put the pieces
            switch (board[row][col])
            {
                case 0:
                    printf("   ");
                    break;
                case -1:
                    printf(" R ");
                    break;
                case -2:
                    printf(" N ");
                    break;
                case -3:
                    printf(" B ");
                    break;
                case -4:
                    printf(" Q ");
                    break;
                case -5:
                    printf(" K ");
                    break;
                case -6:
                    printf(" P ");
                    break;
                case 1:
                    printf(" r ");
                    break;
                case 2:
                    printf(" n ");
                    break;
                case 3:
                    printf(" b ");
                    break;
                case 4:
                    printf(" q ");
                    break;
                case 5:
                    printf(" k ");
                    break;
                case 6:
                    printf(" p ");

                    break;
                default:
                    break;
            }
               if(row%2==0){
                if (col%2==0)
                    printf("%c ",45);
                else
                    printf("%c ",46);
            }else {
                if (col%2==0)
                    printf("%c ",46);
                else
                    printf("%c ",45);

           }
        }
        printf(" ");
        printf(" %d ",p);
        printf("\n");
    }
    printf("      %c ",col_name[0]);
    for (int i=0; i<8;i++)
        printf("    %c ",col_name[i+1]);
    printf("\n");
}
int validMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    // To make sure that it is a valid move or not by check the moves of the pieces
    int pawn = Board[r1][c1];
    if ((white && pawn>0) || ((white == 0 )&& pawn<0))
    {
        switch (pawn)
        {
            case 6:
                if (whitePawns(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case -6:
                if (blackPawns(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 5:
            case -5:
                if (king(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 3:
            case -3:
                if (bishop(Board,r1,c1,r2,c2))return 1;
                return 0;
                break;
            case 2:
            case -2:
                if (knight(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 1:
            case -1:
                if (rooks(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 4:
            case -4:
                if (rooks(Board,r1,c1,r2,c2) || bishop(Board,r1,c1,r2,c2))
                    return 1;
                return 0;
                break;
        }
        //return 1;
    }
    return 0;
}

int makeMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    //to replace the places
    int temp;
    temp = Board[r2][c2];
    Board[r2][c2] = Board[r1][c1];
    Board[r1][c1] = 0;

    //to prevent the player from change any piece if the king in check
    if (!kingSafe(Board))
    {
        Board[r1][c1] = Board[r2][c2];
        Board[r2][c2] = temp;
        return 0;
    }
    else{
        // to replace the player in the next move
        if(white)
            white =0;
        else
            white =1;
        return 1;
    }
}

int whitePawns(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res;
    if (c1 == c2 )
    {
        if ((r1 == 6) && (Board[r2][c2] == 0) && (Board[r1 - 1][c2] == 0) &&  (r2==4 || r2==5))
            res = 1;
        else if ((r2+1) == r1 && (Board[r2][c2] == 0))
            res = 1;
        else
            res = 0;
    }
    else if ((Board[r2][c2]<0) && (r2 == (r1 - 1)) && (c2 == (c1 - 1) ||  c2 == (c1+1)))
        {
            res = 1;
        }
    else
        res = 0;
    return res;
}

int blackPawns(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res;
    if (c1 == c2 )
    {
        if ((r1 == 1) && (Board[r2][c2] == 0) && (Board[r1 + 1][c2] == 0) &&  (r2==3 || r2==2))
            res = 1;
        else if ((r2-1) == r1 && (Board[r2][c2] == 0))
            res = 1;
        else
            res = 0;
    }
    else if ((Board[r2][c2]>0) && (r2 == (r1 + 1)) && (c2 == (c1 - 1) ||  c2 == (c1+1)))
        {res = 1;
        }
    else
        res = 0;
    return res;
}
int knight(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res;
    if (white && Board[r2][c2]>0) return 0;
    else if (!white && Board[r2][c2]<0) return 0;
    if (((r2 == (r1+2)) || (r2 == (r1-2))) && ((c2 == (c1+1)) || (c2 == (c1-1))))
        res = 1;
    else if (((c2 == (c1+2)) || (c2 == (c1-2))) && ((r2 == (r1+1)) || (r2 == (r1-1))))
        res = 1;
    else
        res = 0;
    return res;
}
int rooks(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res = 1;
    if (white && Board[r2][c2]>0) return 0;
    else if (!white && Board[r2][c2]<0) return 0;
    if (r1 == r2)
    {
        if (c1>c2)
        {
            for(int i = (c1-1);i>c2;i--)
            {
                if (Board[r2][i] == 0) continue;
                res = 0;
                break;
            }
        }
        else if (c2>c1)
        {
            for(int i = (c1+1);i<c2;i++)
            {
                if (Board[r2][i] == 0) continue;
                res = 0;
                break;
            }
        }
        else
            return 0;
    }
    else if(c1 == c2)
    {
        if (r1>r2)
        {
            for(int i = (r1-1);i>r2;i--)
            {
                if (Board[i][c2] == 0) continue;
                res = 0;
                break;
            }
        }
        else if (r2>r1)
        {
            for(int i = (r1+1);i<r2;i++)
            {
                if (Board[i][c2] == 0) continue;
                res = 0;
                break;
            }
        }
        else
            return 0;
    }
    else
        return 0;
    return res;
}
int bishop(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res = 1;
    if (white)
    {
        if (Board[r2][c2]>0)
            return 0;
    }
    else
        if (Board[r2][c2]<0)
            return 0;
    if (r2>r1 && c2>c1)
    {
        if ((r2 - r1) == (c2 - c1))
        {
            for(int i = r1+1,j = c1+1;i<r2;i++,j++)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else if(r2>r1 && c2<c1)
    {
        if ((r2 - r1) == (c1 - c2))
        {
            for(int i = r1+1,j = c1-1;i<r2;i++,j--)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else if(r1>r2 && c2>c1)
    {
        if ((r1 - r2) == (c2 - c1))
        {
            for(int i = r1-1,j = c1+1;j<c2;i--,j++)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else if(r2<r1 && c2<c1)
    {
        if ((r1 - r2) == (c1 - c2))
        {
            for(int i = r1-1,j = c1-1;i>r2;i--,j--)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else
        res = 0;
    return res;
}
int king(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res = 0;
    if (r2 == r1 && !(c2 == c1 + 1 || c2 == c1 - 1))
        if (castling(Board,r1,c1,r2,c2))
        {
            castle(r1,c1,r2,c2);
            return 1;
        }
    if (white)
    {
        if (Board[r2][c2]>0)
            return 0;
    }
    else
        if (Board[r2][c2]<0)
            return 0;
    if ((r2 == r1 + 1 || r2 == r1 -1) &&  (c2 == c1 + 1 || c2 == c1 -1))
        res =  1;
    else if ((r2 == r1) && (c2 == c1 + 1 || c2 == c1 - 1) )
        res = 1;
    else if ((c2 == c1) && (r2 == r1 + 1 || r2 == r1 - 1) )
        res = 1;
    else
        res = 0;
    return res;
}

int castling(int Board[][8],int r1,int c1,int r2,int c2)
{
    if (!kingSafe(Board))
        return 0;
    int res = 0;
    if (r1 == 0 && c1 == 4)
    {
        if (blackKingMoved)
            return 0;
        if (c2 == 6 && !black_rook2_moved && (Board[0][7] == -1))
        {
            for (int i = c1+1;i<=6;i++)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
        else if (c2 == 2 && !black_rook1_moved && (Board[0][0] == -1))
        {
            for (int i = c1-1;i>=1;i--)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
    }
    else if (r1 == 7 && c1 == 4)
    {
        if (whiteKingMoved)
            return 0;
        if (c2 == 6 && !white_rook2_moved && (Board[7][7] == 1))
        {
            for (int i = c1+1;i<=6;i++)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
        else if (c2 == 2 && !white_rook1_moved  && (Board[7][0] == 1))
        {
            for (int i = c1-1;i>=1;i--)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
    }
    return res;
}

void castle(int r1,int c1,int r2,int c2)
{
    if (r1 == 0)
    {
        if (c2 == 6)
        {
            board[0][7] = 0;
            board[0][5] = -1;
        }
        if (c2 == 2)
        {
            board[0][0] = 0;
            board[0][3] = -1;
        }
    }
    else
    {
        if (c2 == 6)
        {
            board[7][7] = 0;
            board[7][5] = 1;
        }
        if (c2 == 2)
        {
            board[7][0] = 0;
            board[7][3] = 1;
        }
    }
}

void pawn_promotion(int r1, int c1)
{
    char ch;
    printf("Which pawn do you want to promote?\n ");
    if (white)
    {
        printf("Enter q for Queen\n\th for Horse\n\tr for Rook\n\tb for Bishop\n");
        fflush(stdin);
        scanf(" %c",&ch);
        switch (ch)
        {
            case 'q':
                board[r1][c1] = 4;
                break;
            case 'h':
                board[r1][c1] = 2;
                break;
            case 'r':
                board[r1][c1] = 1;
                break;
            case 'b':
                board[r1][c1] = 3;
                break;
            default:
                printf("Invalid input \nPlease enter a valid input\n");
                pawn_promotion(r1,c1);
        }
    }
    else  // for black player
    {
        printf("Enter Q for Queen\n\tH for Horse\n\tR for Rook\n\tB for Bishop\n");
        scanf(" %c",&ch);
        switch (ch)
        {
            case 'Q':
                board[r1][c1] = -4;
                break;
            case 'H':
                board[r1][c1] = -2;
                break;
            case 'R':
                board[r1][c1] = -1;
                break;
            case 'B':
                board[r1][c1] = -3;
                break;
            default:
                printf("Invalid input \nPlease enter a valid input\n");
                pawn_promotion(r1,c1);
        }
    }
}
int kingSafe(int Board[][8])
{
    int r = -1,c = -1;
    for(int i = 0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            if (((Board[i][j] == 5) && white) || ((Board[i][j] == -5) && !white) )
            {
                // to determine the king place
                r = i;
                c = j;
                i = 8;
                break;
            }
        }
    }
    if (white)
    {
        white = 0;
        for(int i = 0;i<8;i++)
        {
            for(int j = 0;j<8;j++)
            {
                if (Board[i][j]>=0)
                    continue;
                else if (validMove(Board,i,j,r,c))
                {
                    white = 1;
                    return 0;
                }
            }
        }
        white = 1;
    }
    else
    {
        white = 1;
        for(int i = 0;i<8;i++)
        {
            for(int j = 0;j<8;j++)
            {
                if (Board[i][j]<=0)
                    continue;
                else if (validMove(Board,i,j,r,c))
                {
                    white = 0;
                    return 0;
                }
            }
        }
        white = 0;
    }
    return 1;
}
int playerHasValidMove()
{
    pawnsNom = 0;
    int i,j;
    for (i = 0;i<8;i++)
        for(j = 0;j<8;j++)
        {
            tempboard[i][j] = board[i][j];
            if (board[i][j] != 0)
                pawnsNom++;
        }
    int r = -1,c = -1;
    for (r = 0;r<8;r++)
    {
        for(c = 0;c<8;c++)
        {
            if ((board[r][c] == 0) || (white && board[r][c]<0) || (!white && board[r][c]>0))
                continue;
            for (i = 0;i<8;i++)
                for(j = 0;j<8;j++)
                    if(validMove(board,r, c, i, j))
                    {
                        tempboard[i][j] = tempboard[r][c];
                        tempboard[r][c] = 0;
                        if(kingSafe(tempboard))
                        {
                            tempboard[i][j] = board[i][j];
                            tempboard[r][c] = board[r][c];
                            return 1;
                        }
                        tempboard[i][j] = board[i][j];
                        tempboard[r][c] = board[r][c];
                    }
        }
    }
    if (!kingSafe(board))
        checkmate = 1;
    else
        stalemate = 1;

    if(white)
            white =0;
        else
            white =1;
    return 0;
}
