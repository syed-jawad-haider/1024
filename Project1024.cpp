#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
/*[JAWAD NAQVI 21L-7509]
Note :
1. I am adding extra features as a long term use so if I make a setup.exe of this 
game, it should be interactive and user friendly with not a boring old look,close to
a windows form application.
2. The only thing I used which was not taught uptill now in University(and maybe won't be taught later also) was Color changing using
an abstract reference to a resources managed by OS(i.e. Display/font and back Colours), I used in 
A levels but did not know the C++ equivalent so reffered Internet for HANDLES,(understood not copied) as I did EVENT HANDLING
of button clicks in WFP previously, else Everything in this code is created from logic of the group members embedded in this 
single program as taught.
3.Our program create and updates files itself for score and continue, it is made intelligent...
*/
/*Use of colours:Previously in a Game Bingo I made in VB.NET,used colours and Files to store random score
As far I haven't done so in C++ but I learned color handling for better UI */
using namespace std;
const int rows = 4, columns = 4;
int board[rows][columns] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };//I used Global Declaration for time management.
int r_loc[rows];
int current_loc_row, current_loc_col;
char Choice_Menu;
bool rand_possibility = true;
int total = 0;//SJNAQVI-Add on
HANDLE Console_1024_score = GetStdHandle(STD_OUTPUT_HANDLE);//A touch of colours to distinguish degree of score
//In real life developing,there are no limits of exploration..as told in Highschool,where we had restrictions
//As now we have freedom of implementing features until and unless not stated in question
//So being a person of art, I used this type of pointer(HANDLE) with invisible value in background<<<Syed Jawad Naqvi
void Random_loc() {
 //Random
   if(rand_possibility){
    do {
        current_loc_row = rand() % rows;
        current_loc_col = rand() % columns;
    } while (board[current_loc_row][current_loc_col] != 0 );
    board[current_loc_row][current_loc_col] =32;//1 or 2 as newly generated
}
}
void movectrl(char c) {
	if (c == 'l' || c == 'L')//A plenty of time dry running and creating universal logic for one move moves helps later on with others.
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (board[i][j] != 0 && board[i][j - 1] == 0 && j - 1 >= 0)
				{
					rand_possibility = true;
					board[i][j - 1] = board[i][j];
					board[i][j] = 0;	
				
					if (board[i][j - 2] == 0 && j - 2 >= 0)
					{
						board[i][j - 2] = board[i][j - 1];
						board[i][j - 1] = 0;
						if (board[i][j - 3] == 0 && j - 3 >= 0)
						{
							board[i][j - 3] = board[i][j - 2];
							board[i][j - 2] = 0;
						}
						else if (board[i][j - 3] == board[i][j - 2] && j - 3 >= 0)
						{
							board[i][j - 3] = board[i][j - 2] * 2;
							board[i][j - 2] = 0;
						}
					}
					else if (board[i][j - 2] == board[i][j - 1] && j - 2 >= 0)	
					{
					
						board[i][j - 2] = board[i][j - 1] * 2;
						board[i][j - 1] = 0;
						total += board[i][j - 2];//An add-on for a featured game,would have included best score in a file if had some more time
						if (board[i][j - 3] == 0 && j - 3 >= 0)//but it would be a waste of file for a single score,I'll try to store in same file afterwards.
						{
							board[i][j - 3] = board[i][j - 2];
							board[i][j - 2] = 0;
							
						}
						else if (board[i][j - 3] == board[i][j - 2] && j - 3 >= 0)
						{
							board[i][j - 3] = board[i][j - 2] * 2;
							board[i][j - 2] = 0;
							total += board[i][j - 3];
						}
					}
				}
				else if (board[i][j] != 0 && board[i][j - 1] == board[i][j] && j - 1 >= 0)
				{
					rand_possibility = true;
					board[i][j - 1] = board[i][j] * 2;
					board[i][j] = 0;	
					total += board[i][j - 1];
					if (board[i][j - 2] == 0 && j - 2 >= 0)
					{
						board[i][j - 2] = board[i][j - 1];
						board[i][j - 1] = 0;
						if (board[i][j - 3] == 0 && j - 3 >= 0)
						{
							board[i][j - 3] = board[i][j - 2];
							board[i][j - 2] = 0;
						}
						else if (board[i][j - 3] == board[i][j - 2] && j - 3 >= 0)
						{
							board[i][j - 3] = board[i][j - 2] * 2;
							board[i][j - 2] = 0;
							total += board[i][j - 3];
						}
					}
					else if (board[i][j - 2] == board[i][j - 1] && j - 2 >= 0)
					{
						board[i][j - 2] = board[i][j - 1] * 2;
						board[i][j - 1] = 0;
						total += board[i][j - 2];
						if (board[i][j - 3] == 0 && j - 3 >= 0)
						{
							board[i][j - 3] = board[i][j - 2];
							board[i][j - 2] = 0;
						}
						else if (board[i][j - 3] == board[i][j - 2] && j - 3 >= 0)
						{
							board[i][j - 3] = board[i][j - 2] * 2;
							board[i][j - 2] = 0;
							total += board[i][j - 3];
						}
					}
				}
				else if (board[i][j] != 0 && board[i][j - 1] != board[i][j] && j - 1 >= 0)
					rand_possibility = false;
			}
		}
	}
	else if (c == 'r' || c == 'R')
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = columns; j >= 0;j--)//Starting from end is the key of shifting right else if 1 2 0 0, it will be 1 0 0 2;1 won't be checked
			{
				if (board[i][j] != 0 && board[i][j + 1] == 0 && j + 1 <= 3)
				{
					rand_possibility = true;
					board[i][j + 1] = board[i][j];
					board[i][j] = 0;
					
					if (board[i][j + 2] == 0 && j + 2 <= 3)
					{
						board[i][j + 2] = board[i][j + 1];
						board[i][j + 1] = 0;
						if (board[i][j + 3] == 0 && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2];
							board[i][j + 2] = 0;
						}
						else if (board[i][j + 3] == board[i][j + 2] && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2] * 2;
							board[i][j + 2] = 0;
							total += board[i][j + 3];
						}
					}
					else if (board[i][j + 2] == board[i][j + 1] && j + 2 <= 3) {

						board[i][j + 2] = board[i][j + 1] * 2;
						board[i][j + 1] = 0;
						total += board[i][j+2];
						if (board[i][j + 3] == 0 && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2];
							board[i][j + 2] = 0;
						}
						else if (board[i][j + 3] == board[i][j + 2] && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2] * 2;
							board[i][j + 2] = 0;
							total += board[i][j + 3];
						}
					}
				}
				else if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && j + 1 <= 3) {
					rand_possibility = true;
					board[i][j + 1] = board[i][j] * 2;
					board[i][j] = 0;
					total += board[i][j+1];
					if (board[i][j + 2] == 0 && j + 2 <= 3)
					{
						board[i][j + 2] = board[i][j + 1];
						board[i][j + 1] = 0;
						if (board[i][j + 3] == 0 && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2];
							board[i][j + 2] = 0;
						}
						else if (board[i][j + 3] == board[i][j + 2] && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2] * 2;
							board[i][j + 2] = 0;
							total += board[i][j + 3];
						}
					}
					else if (board[i][j + 2] == board[i][j + 1] && j + 2 <= 3) {
						board[i][j + 2] = board[i][j + 1] * 2;
						board[i][j + 1] = 0;
						total += board[i][j + 2];
						if (board[i][j + 3] == 0 && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2];
							board[i][j + 2] = 0;
						}
						else if (board[i][j + 3] == board[i][j + 2] && j + 3 <= 3)
						{
							board[i][j + 3] = board[i][j + 2] * 2;
							board[i][j + 2] = 0;
							total += board[i][j + 3];
						}
					}
				}
				else if (board[i][j] != 0 && board[i][j] != board[i][j + 1] && j + 1 <= 3)
					rand_possibility = false;
			}
		}
	}
	else if (c == 'u' || c == 'U')
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (board[i][j] != 0 && board[i - 1][j] == 0 && i - 1 >= 0)
				{
					rand_possibility = true;
					board[i - 1][j] = board[i][j];
					board[i][j] = 0;
					if (board[i - 2][j] == 0 && i - 2 >= 0)
					{
						board[i - 2][j] = board[i - 1][j];
						board[i - 1][j] = 0;
						if (board[i - 3][j] == 0 && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j];
							board[i - 2][j] = 0;
						}
						else if (board[i - 3][j] == board[i - 2][j] && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j] * 2;
							board[i - 2][j] = 0;
							total += board[i-3][j];
						}
					}
					else if (board[i - 2][j] == board[i - 1][j] && i - 2 >= 0)
					{
						board[i - 2][j] = board[i - 1][j] * 2;
						board[i - 1][j] = 0;
						total += board[i - 2][j];
						if (board[i - 3][j] == 0 && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j];
							board[i - 2][j] = 0;
						}
						else if (board[i - 3][j] == board[i - 2][j] && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j] * 2;
							board[i - 2][j] = 0;
							total += board[i - 3][j];
						}
					}
				}
				else if (board[i][j] != 0 && board[i][j] == board[i - 1][j] && i - 1 >= 0) {
					rand_possibility = true;
					board[i - 1][j] = board[i][j] * 2;
					board[i][j] = 0;
					total += board[i - 1][j];
					if (board[i - 2][j] == 0 && i - 2 >= 0)
					{
						board[i - 2][j] = board[i - 1][j];
						board[i - 1][j] = 0;
						if (board[i - 3][j] == 0 && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j];
							board[i - 2][j] = 0;
						}
						else if (board[i - 3][j] == board[i - 2][j] && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j] * 2;
							board[i - 2][j] = 0;
						    total += board[i - 3][j];
						}
					}
					else if (board[i - 2][j] == board[i - 1][j] && i - 2 >= 0)
					{
						board[i - 2][j] = board[i - 1][j] * 2;
						board[i - 1][j] = 0;
						total += board[i - 2][j];
						if (board[i - 3][j] == 0 && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j];
							board[i - 2][j] = 0;
						}
						else if (board[i - 3][j] == board[i - 2][j] && i - 3 >= 0)
						{
							board[i - 3][j] = board[i - 2][j] * 2;
							board[i - 2][j] = 0;
							total += board[i - 3][j];
						}
					}
				}
				else if (board[i][j] != 0 && board[i][j] != board[i - 1][j] && i - 1 >= 0)
					rand_possibility = false;
			}
		}

	}
	else if (c == 'd' || c == 'D')//Different logic used for down
	{
		for (int j = 0; j < columns; j++)
		{
			for (int x = 0;x <= rows - 2;x++) {//1st time for swap,2nd time for comparing and adding
				for (int i = rows - 2; i >= 0; i--) {
					if (board[i][j] != 0 && board[i + 1][j] == 0)
					{
						rand_possibility = true;
						board[i + 1][j] = board[i][j];
						board[i][j] = 0;
					}
					else if (board[i][j] != 0 && board[i][j] == board[i + 1][j])
					{
						rand_possibility = true;
						board[i + 1][j] = board[i][j] * 2;
						board[i][j] = 0;
						total += board[i+1][j];
					}
					else if (board[i][j] != 0 && board[i + 1][j] != board[i][j])
						rand_possibility = false;
				}
			}
		}
	}
}
bool Board_full() {
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if(board[i][j]==0)
            return false;
        }
    }
    return true;
}
bool Win_Check() {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (board[i][j] == 1024)
				return true;
		}
	}
	return false;
}
void Score_Color_Distinguish(int r,int c) {//Color coulds from 0 to 255 with variations have been used
    if (board[r][c] == 0)
        SetConsoleTextAttribute(Console_1024_score, 8);//Grey if 0
    else if(board[r][c]==1)
    SetConsoleTextAttribute(Console_1024_score, 14);//Yellow if 1
    else if(board[r][c] == 2)
        SetConsoleTextAttribute(Console_1024_score, 10);//Green if 2
    else if (board[r][c] == 4)
        SetConsoleTextAttribute(Console_1024_score, 11);//Cyan if 4
    else if (board[r][c] == 8)
        SetConsoleTextAttribute(Console_1024_score, 13);//Indigo if 8
    else if (board[r][c] == 16)
        SetConsoleTextAttribute(Console_1024_score, 12);//RED if 16
    else if (board[r][c] == 32)
        SetConsoleTextAttribute(Console_1024_score,31);//Fore : White Back : Dark Blue if 32
    else if (board[r][c] == 64)
        SetConsoleTextAttribute(Console_1024_score, 47);//Fore: White Back : Green if 64
    else if (board[r][c] == 128)
        SetConsoleTextAttribute(Console_1024_score, 71);//Fore: White Back : Red if 128
    else if (board[r][c] == 256)
        SetConsoleTextAttribute(Console_1024_score, 63);//Fore: White Back : Cyan if 256
    else if (board[r][c] == 512)
        SetConsoleTextAttribute(Console_1024_score, 80);//Fore: Black Back : Indigo if 512
    else if (board[r][c] == 1024)
        SetConsoleTextAttribute(Console_1024_score, 100);//Fore: Yellow/GOLD Back : Red if 1024
}
int space_display_calculate(int r,int c) {//Calculate spaces for each no. for a better organized board
    int count=0;
    if (board[r][c] >= 0 && board[r][c] < 10)
        count = 1;
    else if (board[r][c] > 9 && board[r][c] < 100)
        count = 2;
    else if (board[r][c] > 99 && board[r][c] < 1000)
        count = 3;
    else if (board[r][c] > 999 && board[r][c] < 10000)
        count = 4;
    return count;
}
void display_Board() {
    SetConsoleTextAttribute(Console_1024_score, 15);//White for borders
    cout << ")}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}( \t<<\t\t}{\t\t>>\n";
         
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {    
            SetConsoleTextAttribute(Console_1024_score, 15);//White for borders
            cout<< ")}{( ";
            for (int k = 0;k < (columns-space_display_calculate(i,j));k++) 
                cout << " ";
             Score_Color_Distinguish(i,j);
            cout << board[i][j];
        }
        SetConsoleTextAttribute(Console_1024_score, 15);//White for borders
        cout <<" )}{(  \t\t}{\t\t}{\n)}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}( \t<<\t\t}{\t\t>>"<< endl;
    }
	
		cout << "\n\t\t\t\t<<<<<<<<< Total Score : " <<setw(5)<<left<<total<<" >>>>>>>>>\n\n";
}
void save_progress() {
	ofstream scoreout;
	ofstream progwriter;
	progwriter.open("Continue_1024.txt");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			progwriter<<board[i][j]<<" ";
		}
		progwriter << endl;
	}
	progwriter.close();
	scoreout.open("Score_1024.txt");
	scoreout<< total;
	scoreout.close();
}
void New_Game() {
	total = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            board[i][j] = 0;
        }
    }
	rand_possibility = true;
    Random_loc();
}
void continue_game() {
	Random_loc();//A new no. also generated if continued in this version
	int check_if_no_record_count=0;//count of ones,if only one then it is new game,no continuation as no record.
	ifstream scorein;
	ifstream progreader;
	scorein.open("Score_1024.txt");
	if (scorein.is_open())
		scorein >> total;
	else
		total = 0;
	scorein.close();
	progreader.open("Continue_1024.txt");
	if (progreader.is_open()) {

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0;j < columns;j++)
				progreader >> board[i][j];
		}progreader.close();
	}
	else
		New_Game();
}
void Help_Console() {
    system("CLS");  
    for (int b = 4;b > 0;b--) {
        for (int c = 1;c <= 3 - b;c++) {
            cout << " ";
        }
        for (int d = 1;d <= 2 * b - 1;d++) {
            cout << "}{3<<1>>3}{";
        }
        cout << endl;
    }
    cout << "\n\t]]]]}}}}}})><<<CONTROLS>>><({{{{{{[[[[[\n\n"
        << "\tl : Swipe Left\n\tr : Swipe Right\n\tu : Swipe Up\n\td : Swipe Down\n\n\tEnter Q to directly Exit the Game.(Only then progress will be saved)\n\n"
        << "\tEnter P to directly go in the New Game.(All previous progress,if any will be LOST.) \n\n"
        << "\tEnter C to directly Continue Game.(Only if saved else NEW GAME will open)\n\n\tEnter any other key to go back to Menu.\n\n"
        << "\t]]]]}}}}}})><<<CONTROLS>>><({{{{{{[[[[[\n"; 
    for (int x = 0;x <= 4;x++) {
        for (int y = 1;y <= 4 - x;y++) {
            cout << " ";
        }
        for (int a = 1;a <= 2 * x - 1;a++) {
            cout << "}{3<<1>>3}{";
        }
        cout << endl;
    }
    cin >> Choice_Menu;
}

void Main_Menu() {
    system("CLS");
    system("Color 61");
	cout << "\t\t)}{}{( SJ Studios )}{}{(\n  )}{}{(The journey of a thousand miles begins with one step)}{}{(";
	
    cout << "\n\n\t      |<<>>>`---_^_#:!}{!:#_^_---'<<<><<|";
    cout << "\n\t    |<<>>>`---_^_#:!}{!:#_^_---'<<<><<| |]]]]]]]]]]]]]4";
    cout << "\n\t  |<<>>>`---_^_#:!}{!:#_^_---'<<<><<| | |\t    2";
    cout << "\n\t]]]]}}}}}})><<<1024>>><({{{{{{[[[[[ | | |         0\n"
        << "\t]]          Main Menu            [[[[[[[[[[[[[[[1]]]]]4\n\t]]\t\t\t\t [[ | | |\t    2\n"
        << "\t]] >>Enter P to Play             [[ | | |         0\n"
        << "\t]] >>Enter Q to Quit anytime     [[[[[[[[[[[[[[[1]]]]]4\n"
        << "\t]] >>Enter H for Controls/Help   [[ | | |\t    2\n"
		<< "\t]] >>Enter C to Continue \t [[ | | |         0\n"
		<< "\t]](if last game quit during play)[[[[[[[[[[[[[[[1]]]]]4\n"
        << "\t]]\t\t\t\t [[ | | |\t    2\n\t]] Credits : Syed Jawad Naqvi    [[ | | |         0\n"
        << "\t]] Track : Adrian Von Ziegler    [[[[[[[[[[[[[[[1\n"
        << "\t]]\t\t\t\t [[ |_|\n\t]]\t\t\t\t [[_|\n"
        << "\t]]]]}}}}}})><<<1024>>><({{{{{{[[[[[\n";
  
    cin >> Choice_Menu;
    if (Choice_Menu == 'H'|| Choice_Menu=='h')
        Help_Console();
}

int main(){
	bool play= PlaySound(TEXT("Japanese Fantasy Music  Isan.wav"), NULL, SND_FILENAME | SND_ASYNC);
    char replay=' ';//Default initialization 
    char Command;
    do {
        Main_Menu();
		if (Choice_Menu == 'q' || Choice_Menu == 'Q') {
			system("CLS");
			return 0;
		}//Terminating if quit.
	
    } while ((Choice_Menu != 'p' && Choice_Menu != 'P' ) && Choice_Menu != 'C' && Choice_Menu != 'c');
	if (Choice_Menu == 'c' || Choice_Menu == 'C'){
	 continue_game();
	}
	else if(Choice_Menu == 'P' || Choice_Menu == 'p')
		New_Game();
    do{
        system("CLS");
        Random_loc();
		rand_possibility = false;
        display_Board();
        cout << "Command : ";
        cin >> Command;
		if (Command == 'q' || Command == 'Q'){
			save_progress();
            break;
		}
        else
            movectrl(Command);
        if (Board_full() && !Win_Check()) {
       system("Color 4");
        cout << "GAME OVER! Better Luck Next time...\nWant to Play Again?\n(Any other key to replay/N for Exiting the game) : ";
        cin >> replay;
        if (replay != 'n'){
            New_Game();
			save_progress();
		   }
         }
		else if(Win_Check()){
			system("Color 6");
			cout << "Congratulations!!!$$$ You have won the game $$$";
		}
      //  Shift_Ctrl(Command);
    } while (replay!='n' && !Win_Check());

	return 0;
	}
