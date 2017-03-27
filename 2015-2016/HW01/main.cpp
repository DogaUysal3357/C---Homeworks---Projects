/*
 * File:   main.cpp
 * Author: aliyasineser
 *
 * Created on September 16, 2015, 1:33 AM
 */

#include <cstdlib>
#include <iostream>
#include <ctype.h>

using namespace std;


typedef struct{
    int change_count,
        coor_x,
        coor_y;
}move_t;


const int MIN_SIZE = 4;
const int MAX_SIZE = 20;
const int NOT_LEGAL_MOVE = 0;
const int LEGAL_MOVE = 1;
const int IS_DOUBLE_CHECK = 2;
const int START_POINT = 0;
const int IS_MIDDLE_CHECK = 2;
const int DELTA_ONE = 1;
const int FIX_TABLE_SHIFT = 10; // Cift haneli sayilarda tablonun kaymaması icin eklenmis kod icin
const int ERROR = 1;
const int NO_ERROR = 0;
const int ARRAY_FIX = 1;
const int BOTH_CANNOT_MOVE = 2; // Hem user hem computer hamle yapamazsa oyun biter
const int ZERO = 0;
const int STR_LENGTH = 80;


void print_game_board( char last_game_board[MAX_SIZE][MAX_SIZE], int arr_size);
bool* before_legal_check(char arr_board[][MAX_SIZE], bool arr_bool[][MAX_SIZE], int size);

int vertical_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size, int x_axis, int y_axis, int is_the_one, char my_turn, char look_for);
int horizontal_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size, int x_axis, int y_axis, int is_the_one, char my_turn, char look_for);
int diagonal_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size, int x_axis, int y_axis, int is_the_one, char my_turn, char look_for);

bool* clear_move_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size ,char my_turn, char look_for);

int diagonal_count( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y, int stone_count );
int horizontal_count( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y, int stone_count );
int vertical_count( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y, int stone_count );


void update_table( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y );
void horizontal_update( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y );
void vertical_update( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y );
void diagonal_update( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y );

move_t max_move_of_computer( char game_board[MAX_SIZE][MAX_SIZE], bool bool_board[MAX_SIZE][MAX_SIZE],  int size, char player_ch, char target_ch );
void take_input( int* row_coor, int* col_coor, int size );

void print_the_final_score( char game_board[MAX_SIZE][MAX_SIZE], int size, char comp_ch, char user_ch );
int final_score( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_symbol );


int main(int argc, char** argv)
{
    int size_of_board, i=START_POINT, j=START_POINT, at_least_one_legal = NOT_LEGAL_MOVE, x_coor, y_coor;
    char game_board[MAX_SIZE][MAX_SIZE], computer_mark= 'X', user_mark= 'O';
    bool bool_board[MAX_SIZE][MAX_SIZE], *clear_board;
    move_t comp_move;

    cout << "Welcome to game of reversi, a.k.a. \"Othello\" " << endl;

    do
    {
      cout << "What is the size you want for the game?" << "\n"
              << "It can be any double sizes from 4x4 to 20x20." << endl;

      cin >> size_of_board;

      if( (size_of_board < MIN_SIZE) || (size_of_board > MAX_SIZE))
      {
        cout << "You have to choose the size of the board between 4x4 and 20x20" << endl;
      }
      else if( size_of_board % IS_DOUBLE_CHECK != 0 )
      { cout << "You have to choose a double number for board, try again please" << endl;
      }
    }
    while(((size_of_board < MIN_SIZE) || (size_of_board > MAX_SIZE)) || (size_of_board % IS_DOUBLE_CHECK != ZERO));


    for( i=START_POINT ; i<size_of_board; i++)
    {
        for( j=START_POINT; j<size_of_board; j++)
        {
            game_board[i][j] = '.';
        }
    }

    cout << "Creating a " << size_of_board << "x" << size_of_board << " board now" << endl;


    game_board[(size_of_board/IS_MIDDLE_CHECK)-DELTA_ONE][(size_of_board/IS_MIDDLE_CHECK)-DELTA_ONE] = 'X';
    game_board[(size_of_board/IS_MIDDLE_CHECK)][(size_of_board/IS_MIDDLE_CHECK)] = 'X';
    game_board[(size_of_board/IS_MIDDLE_CHECK)-DELTA_ONE][(size_of_board/IS_MIDDLE_CHECK)] = 'O';
    game_board[(size_of_board/IS_MIDDLE_CHECK)][(size_of_board/IS_MIDDLE_CHECK)-DELTA_ONE] = 'O';



    print_game_board( game_board , size_of_board );


    int no_move_count = START_POINT;
    while( no_move_count < BOTH_CANNOT_MOVE )
    {

                                /* User's turn */
        if( no_move_count < BOTH_CANNOT_MOVE )
        {

            before_legal_check( game_board, bool_board, size_of_board );
            clear_move_check( bool_board, game_board, size_of_board , user_mark, computer_mark );

            for(i=START_POINT; i < size_of_board; i++)
            {
                for(j=START_POINT; j < size_of_board; j++)
                {
                    if( at_least_one_legal == NOT_LEGAL_MOVE )
                        if( bool_board[i][j] == true )
                            at_least_one_legal++;
                }
            }




            if( at_least_one_legal != NOT_LEGAL_MOVE )
            {
                no_move_count = START_POINT;
                do
                {
                take_input( &x_coor, &y_coor, size_of_board );
                if( bool_board[x_coor][y_coor] != true )
                    cout << "Your move is not legal, enter a legal move please" << endl;
                }while( bool_board[x_coor][y_coor] != true );


                update_table( game_board, size_of_board, user_mark, computer_mark, x_coor, y_coor);
                print_game_board( game_board , size_of_board );
                cout << endl << endl;
            }
            else
            {
                cout << "No legal move for user" << endl;
                no_move_count++;
            }

            at_least_one_legal = NOT_LEGAL_MOVE;
        }


            /* Computer's Turn */

        if( no_move_count < BOTH_CANNOT_MOVE )
        {

            before_legal_check( game_board, bool_board, size_of_board );
            clear_move_check( bool_board, game_board, size_of_board , computer_mark, user_mark );

            for(i=START_POINT; i < size_of_board; i++)
            {
                for(j=START_POINT; j < size_of_board; j++)
                {
                    if( at_least_one_legal == NOT_LEGAL_MOVE )
                        if( bool_board[i][j] == true )
                            at_least_one_legal++;
                }
            }

            if( at_least_one_legal != NOT_LEGAL_MOVE )
            {
                no_move_count = START_POINT;

                comp_move =  max_move_of_computer( game_board, bool_board, size_of_board, computer_mark, user_mark );

                if( comp_move.change_count != START_POINT )
                {
                update_table( game_board, size_of_board, computer_mark, user_mark, comp_move.coor_x ,comp_move.coor_y);
                print_game_board( game_board , size_of_board );
                cout << endl << endl;
                }
            }
            else
            {
                cout << "No legal move for computer" << endl;
                no_move_count++;
            }
            at_least_one_legal = NOT_LEGAL_MOVE;
        }



    }
    print_the_final_score( game_board, size_of_board, computer_mark, user_mark );



    return 0;
}



///////////////////////////////////////////////////////////////////////////////




int vertical_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size, int x_axis, int y_axis, int is_the_one, char my_turn, char look_for)
{
    int row_temp, col_temp, count_last, dif_one=1;

    /*From bottom to top*/
    if(is_the_one == NOT_LEGAL_MOVE)
    {
        if( x_axis-dif_one >= START_POINT && x_axis-dif_one < size)
        {
            row_temp = x_axis-dif_one;

            if( ch_game_board[row_temp][y_axis] == look_for)
            {
                for(count_last=1; row_temp-count_last >= START_POINT;
                    count_last++)
                {
                    if(ch_game_board[row_temp-count_last][y_axis] == '.')
                        break;
                    if (ch_game_board[row_temp-count_last][y_axis] == my_turn)
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }


    /*From top to bottom*/
    if(is_the_one == NOT_LEGAL_MOVE)
    {
        row_temp = x_axis+dif_one;
        if( row_temp >= START_POINT && row_temp < size )
        {
            if( ch_game_board[row_temp][y_axis] == look_for )
            {
                for(row_temp += dif_one; row_temp < size;
                    row_temp += dif_one)
                {
                    if(ch_game_board[row_temp][y_axis] == '.')
                        break;
                    if (ch_game_board[row_temp][y_axis] == my_turn )
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }




    return is_the_one;

}



int horizontal_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size, int x_axis, int y_axis, int is_the_one, char my_turn, char look_for)
{
    int row_temp, col_temp, count_last, dif_one=1, i;



    /*From left to right*/
    if(is_the_one == NOT_LEGAL_MOVE)

    {
        if( y_axis+dif_one >= START_POINT && y_axis+dif_one < size )
        {
            col_temp = y_axis+dif_one;
            if( ch_game_board[x_axis][col_temp] == look_for)
            {
                for(count_last=1; col_temp+count_last < size;
                    count_last++)
                {
                    if(ch_game_board[x_axis][col_temp+count_last] == '.')
                        break;
                    if (ch_game_board[x_axis][col_temp+count_last] == my_turn)
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }


    /*From right to left*/

    if(is_the_one == NOT_LEGAL_MOVE)
    {
        if( y_axis-dif_one >= START_POINT && y_axis-dif_one < size)
        {
            col_temp = y_axis-dif_one;
            if( ch_game_board[x_axis][col_temp] == look_for)
            {
                for(count_last=1; col_temp-count_last >= START_POINT;
                    count_last++)
                {
                    if(ch_game_board[x_axis][col_temp-count_last] == '.')
                        break;
                    if (ch_game_board[x_axis][col_temp-count_last] == my_turn)
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }



return is_the_one;
}



int diagonal_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size, int x_axis, int y_axis, int is_the_one, char my_turn, char look_for)
{
    int row_temp, col_temp, count_last, dif_one=1;

    /*From right-down to left-up*/
    if(is_the_one == NOT_LEGAL_MOVE)
    {
        if( x_axis-dif_one >= START_POINT && x_axis-dif_one < size &&
            y_axis-dif_one >= START_POINT && y_axis-dif_one < size)
        {
            row_temp = x_axis-dif_one;
            col_temp = y_axis-dif_one;
            if( ch_game_board[row_temp][col_temp] == look_for)
            {
                for(count_last=1; row_temp-count_last >= START_POINT &&
                    col_temp-count_last >= START_POINT ;
                    count_last++)
                {
                    if(ch_game_board[row_temp-count_last][col_temp-count_last] == '.')
                        break;
                    if (ch_game_board[row_temp-count_last][col_temp-count_last] == my_turn )
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }


    /*From left-down to right-up*/
    if(is_the_one == NOT_LEGAL_MOVE)
    {
        if( x_axis-dif_one >= START_POINT && x_axis-dif_one < size &&
            y_axis+dif_one >= START_POINT && y_axis+dif_one < size)
        {
            row_temp = x_axis-dif_one;
            col_temp = y_axis+dif_one;
            if( ch_game_board[row_temp][col_temp] == look_for)
            {
                for(count_last=1; row_temp-count_last >= START_POINT &&
                    col_temp+count_last < size;
                    count_last++)
                {
                    if(ch_game_board[row_temp-count_last][col_temp+count_last] == '.')
                        break;
                    if (ch_game_board[row_temp-count_last][col_temp+count_last] == my_turn)
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }

    /*From right-up to left-down*/
    if(is_the_one == NOT_LEGAL_MOVE)
    {
        if( x_axis+dif_one >= START_POINT && x_axis+dif_one < size &&
            y_axis-dif_one >= START_POINT && y_axis-dif_one < size)
        {
            row_temp = x_axis+dif_one;
            col_temp = y_axis-dif_one;
            if( ch_game_board[row_temp][col_temp] == look_for)
            {
                for(count_last=1; row_temp+count_last < size && col_temp-count_last >= START_POINT;
                    count_last++)
                {
                    if(ch_game_board[row_temp+count_last][col_temp-count_last] == '.')
                        break;
                    if (ch_game_board[row_temp+count_last][col_temp-count_last] == my_turn)
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }


    /*From left-up to right-down*/
    if(is_the_one == NOT_LEGAL_MOVE)
    {
        if( x_axis+dif_one >= START_POINT && x_axis+dif_one < size &&
            y_axis+dif_one >= START_POINT && y_axis+dif_one < size )
        {
            row_temp = x_axis+dif_one;
            col_temp = y_axis+dif_one;
            if( ch_game_board[row_temp][col_temp] == look_for)
            {
                for(count_last=1; row_temp+count_last < size &&
                    col_temp+count_last < size;
                    count_last++)
                {
                    if(ch_game_board[row_temp+count_last][col_temp+count_last] == '.')
                        break;
                    if (ch_game_board[row_temp+count_last][col_temp+count_last] == my_turn)
                    {
                        is_the_one = LEGAL_MOVE;
                    }
                }
            }
        }
    }






return is_the_one;
}



bool* clear_move_check(bool bool_game_board[MAX_SIZE][MAX_SIZE], char ch_game_board[MAX_SIZE][MAX_SIZE], int size, char my_turn, char look_for)
{
    int i,j, dif_one=1, row_temp, col_temp, is_the_one = NOT_LEGAL_MOVE, count_last;

    for(i=START_POINT; i<size; i++)
    {
        for(j=START_POINT; j<size; j++)
        {

            is_the_one = vertical_check(bool_game_board, ch_game_board, size, i, j, is_the_one, my_turn, look_for);

            is_the_one = horizontal_check(bool_game_board, ch_game_board, size, i, j, is_the_one, my_turn, look_for);

            is_the_one = diagonal_check(bool_game_board, ch_game_board, size, i, j, is_the_one, my_turn, look_for);



            if( bool_game_board[i][j] == true)
            {

                if( is_the_one == NOT_LEGAL_MOVE )
                {
                    bool_game_board[i][j] = false;
                }

            }
            is_the_one = NOT_LEGAL_MOVE;
        }

    }
    return &bool_game_board[START_POINT][START_POINT];
}




void print_game_board( char last_game_board[MAX_SIZE][MAX_SIZE], int arr_size)
{
    cout << "   ";
    for(int letter_count=START_POINT; letter_count < arr_size; letter_count++)
    {
        cout << char((int)'a'+letter_count) << " " ;

    }
    cout << endl;

    for(int i=START_POINT; i<arr_size; i++)
    {
        if(i+DELTA_ONE < FIX_TABLE_SHIFT)
        {
            cout << i+DELTA_ONE << "  " ;
        }
        else
        {
            cout << i+DELTA_ONE << " ";
        }
        for(int j=START_POINT; j<arr_size; j++)
        {
            cout << last_game_board[i][j] << " " ;
        }
        cout << endl;
    }

}

bool* before_legal_check(char arr_board[][MAX_SIZE], bool arr_bool[][MAX_SIZE], int size)
{
    for( int i=START_POINT; i<size; i++ )
    {
        for( int j=START_POINT; j<size; j++)
        {
            if( arr_board[i][j] == '.')
            {
                arr_bool[i][j] = true;
            }
            else
            {
                arr_bool[i][j] = false;
            }

        }
    }

 return &arr_bool[START_POINT][START_POINT];

}



void take_input( int* row_coor, int* col_coor, int size )
{
    int error_flag;
    char thrash, i;
    do
    {
    error_flag = NO_ERROR;
    cout << "Please enter row number that you want to move: " ;
    cin >> *row_coor;
    if( cin.fail() || *row_coor < START_POINT  || *row_coor > size)
    {
        cout << "Wrong row number or format, check again!" << endl;
        cin.clear();
        cin.ignore(80, '\n');
        error_flag = ERROR;
    }
}while( error_flag==ERROR );
    *row_coor -= ARRAY_FIX; // Array'ler sifirdan baslar, kullaniciya zorluk cikarmamak adina eklendi

    char temp_letter;

    do
    {
    error_flag = NO_ERROR;
    cout << "Please enter column letter that you want to move: ";
    cin >> temp_letter;
    temp_letter = tolower(temp_letter);
    if( isalpha(temp_letter) && temp_letter > 't' )
    {
        cout << "Out of range or letter format, check again!" << endl;
        cin.clear();
        cin.ignore(STR_LENGTH, '\n');
        error_flag = ERROR;
    }

    if( isalpha(temp_letter) )
        *col_coor = (int)temp_letter - (int)'a';

    }while( error_flag == ERROR );

}







void horizontal_update( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y )
{
    int delta_one=1, i;

    for(  i=coor_x-delta_one; game_board[i][coor_y] == target_ch && i >= START_POINT; i -= (delta_one) );

    if( game_board[i][coor_y] == player_ch )
        for( i=coor_x-delta_one; game_board[i][coor_y] == target_ch && i >= START_POINT; i -= (delta_one) )
            game_board[i][coor_y] = player_ch;

    for(  i=coor_x+delta_one; game_board[i][coor_y] == target_ch && i < size; i += (delta_one) );

    if( game_board[i][coor_y] == player_ch )
        for( i=coor_x+delta_one; game_board[i][coor_y] == target_ch && i < size; i += (delta_one) )
            game_board[i][coor_y] = player_ch;
}


void vertical_update( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y )
{
    int delta_one=1, j;

    for(  j=coor_y-delta_one; game_board[coor_x][j] == target_ch && j >= START_POINT; j -= (delta_one) );

    if( game_board[coor_x][j] == player_ch )
        for( j=coor_y-delta_one; game_board[coor_x][j] == target_ch && j >= START_POINT; j -= (delta_one) )
            game_board[coor_x][j] = player_ch;

    for(  j=coor_y+delta_one; game_board[coor_x][j] == target_ch && j < size; j += (delta_one) );

    if( game_board[coor_x][j] == player_ch )
        for( j=coor_y+delta_one; game_board[coor_x][j] == target_ch && j < size; j += (delta_one) )
            game_board[coor_x][j] = player_ch;

}





void diagonal_update( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y )
{
    int delta_one=1, i, j;

            /* Left and Up */
    for( i=coor_x-delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i >= START_POINT && j >= START_POINT  ; i -= (delta_one), j -= (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x-delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i >= START_POINT && j >= START_POINT; i -= (delta_one), j -= (delta_one) )
            game_board[i][j] = player_ch;

            /*Right and Up*/
    for( i=coor_x-delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i >= START_POINT && j < size; i -= (delta_one), j += (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x-delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i >= START_POINT && j < size; i -= (delta_one), j += (delta_one) )
            game_board[i][j] = player_ch;

            /* Right and Down */
    for( i=coor_x+delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i < size && j < size; i += (delta_one), j += (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x+delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i < size && j < size; i += (delta_one), j += (delta_one) )
            game_board[i][j] = player_ch;

            /* Left and Down */
    for( i=coor_x+delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i < size && j >= START_POINT; i += (delta_one), j -= (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x+delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i < size && j >= START_POINT; i += (delta_one), j -= (delta_one) )
            game_board[i][j] = player_ch;

}








int horizontal_count( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y, int stone_count )
{
    int i, j, delta_one = 1;

    for(  i=coor_x-delta_one; game_board[i][coor_y] == target_ch && i >= START_POINT; i -= (delta_one) );

    if( game_board[i][coor_y] == player_ch )
        for( i=coor_x-delta_one; game_board[i][coor_y] == target_ch && i >= START_POINT; i -= (delta_one) )
            stone_count++;

    for(  i=coor_x+delta_one; game_board[i][coor_y] == target_ch && i < size; i += (delta_one) );

    if( game_board[i][coor_y] == player_ch )
        for( i=coor_x+delta_one; game_board[i][coor_y] == target_ch && i < size; i += (delta_one) )
            stone_count++;

    return stone_count;
}






int vertical_count( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y, int stone_count )
{
    int i, j, delta_one = 1;

    for(  j=coor_y-delta_one; game_board[coor_x][j] == target_ch && j >= START_POINT; j -= (delta_one) );

    if( game_board[coor_x][j] == player_ch )
        for( j=coor_y-delta_one; game_board[coor_x][j] == target_ch && j >= START_POINT; j -= (delta_one) )
            stone_count++;

    for(  j=coor_y+delta_one; game_board[coor_x][j] == target_ch && j < size; j += (delta_one) );

    if( game_board[coor_x][j] == player_ch )
        for( j=coor_y+delta_one; game_board[coor_x][j] == target_ch && j < size; j += (delta_one) )
            stone_count++;

    return stone_count;
}



int diagonal_count( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y, int stone_count )
{
    int i, j, delta_one = 1;

        /* Left and Up */
    for( i=coor_x-delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i >= START_POINT && j >= START_POINT  ; i -= (delta_one), j -= (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x-delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i >= START_POINT && j >= START_POINT; i -= (delta_one), j -= (delta_one) )
            stone_count++;

        /*Right and Up*/
    for( i=coor_x-delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i >= START_POINT && j < size; i -= (delta_one), j += (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x-delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i >= START_POINT && j < size; i -= (delta_one), j += (delta_one) )
            stone_count++;

        /* Right and Down */
    for( i=coor_x+delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i < size && j < size; i += (delta_one), j += (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x+delta_one, j=coor_y+delta_one; game_board[i][j] == target_ch && i < size && j < size; i += (delta_one), j += (delta_one) )
            stone_count++;

        /* Left and Down */
    for( i=coor_x+delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i < size && j >= START_POINT; i += (delta_one), j -= (delta_one) );

    if( game_board[i][j] == player_ch )
        for( i=coor_x+delta_one, j=coor_y-delta_one; game_board[i][j] == target_ch && i < size && j >= START_POINT; i += (delta_one), j -= (delta_one) )
            stone_count++;
}

move_t max_move_of_computer( char game_board[MAX_SIZE][MAX_SIZE], bool bool_board[MAX_SIZE][MAX_SIZE],  int size, char player_ch, char target_ch )
{
    int i, j;
    move_t best_move = { .change_count = START_POINT, .coor_x = START_POINT, .coor_y = START_POINT }, temp_move;


    for(i=START_POINT ; i < size; i++)
    {
        for(j=START_POINT; j < size; j++)
        {
            if( bool_board[i][j] == true )
            {
                temp_move.change_count = START_POINT;
                temp_move.coor_x = i;
                temp_move.coor_y = j;

                temp_move.change_count += horizontal_count( game_board, size, player_ch, target_ch, i, j, temp_move.change_count );
                temp_move.change_count += vertical_count( game_board, size, player_ch, target_ch, i, j, temp_move.change_count );
                temp_move.change_count += diagonal_count( game_board, size, player_ch, target_ch, i, j, temp_move.change_count );

                if( temp_move.change_count > best_move.change_count )
                    best_move = temp_move;
            }
        }
    }
    return best_move;
}





void update_table( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_ch, char target_ch, int coor_x, int coor_y )
{
    game_board[coor_x][coor_y] = player_ch;

    horizontal_update( game_board, size, player_ch, target_ch, coor_x, coor_y );
    vertical_update( game_board, size, player_ch, target_ch, coor_x, coor_y );
    diagonal_update( game_board, size, player_ch, target_ch, coor_x, coor_y );
}


void print_the_final_score( char game_board[MAX_SIZE][MAX_SIZE], int size, char comp_ch, char user_ch )
{


    cout << "Game over! The final score is:" << endl;

    cout << "User Score: " << final_score( game_board, size, user_ch ) << endl;
    cout << "Computer Score: " << final_score( game_board, size, comp_ch ) << endl;

}





int final_score( char game_board[MAX_SIZE][MAX_SIZE], int size, char player_symbol )
{
    int i, j, count=START_POINT;

    for( i=START_POINT; i < size; i++ )
    {
        for(j=START_POINT; j < size; j++)
        {
            if( game_board[i][j] == player_symbol )
            {
                count++;
            }
        }
    }

    return count;
}
