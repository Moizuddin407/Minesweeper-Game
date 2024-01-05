#include <iostream>
#include <string>
//used for random number generation process.
#include <cstdlib>
#include <ctime>
using namespace std;
class player
{
    string name;
    int score;
    int attempts;

public:
    player()
    {
        score = 0;
        name = "\0";
        attempts = 0;
    }
    //this whole class has setter getter functions
    //to update values and use them in gameplay class.
    void setname(string namee)
    {
        name = namee;
    }

    void incrementscore()
    {
        score = score + 1;
    }

    void incrementattempts()
    {
        attempts = attempts + 1;
    }

    int getscore()
    {
        return score;
    }

    int getattempts()
    {
        return attempts;
    }

    string getname()
    {
        return name;
    }
};
class menu
{
public:
    void instructions()
    {
        cout << "<---------------------------------->\n";
        cout << "Welcome ! You are now on a Mission\n";
        cout << "To Find the keys to the treasure !\n";
        cout << "\n";
        cout << "Enter co-ordinates in form of x,y\n";
        cout << "To select a box. Find all keys to win.\n";
        cout << "Beware of the Mines ! ! !\n";
        cout << "<---------------------------------->\n";
    }
};
class gameplay : public menu
{
    string playername;
    int grid_size;
    int** grid_arr;
    int** data_arr;
    int input_user_x;
    int input_user_y;
    bool** check_arr;
    bool flag;
    player p1;
public:
    gameplay(int size1)
    {
        //three arrays declared. Data_arr to store mines and keys at back end.
        //check_arr to check corresponding positions and generate results.
        //grid_arr to correspondingly show grid on screen as only front end
        // and hiding workings of back end.
        flag = false;
        input_user_x = 0;
        input_user_y = 0;
        grid_size = size1;
        //arrrays initialized with total size = size1 * size1. 
        data_arr = new int* [size1];
        for (int i = 0; i < size1; i++)
        {
            data_arr[i] = new int[size1];
        }
        grid_arr = new int* [size1];
        for (int i = 0; i < size1; i++)
        {
            grid_arr[i] = new int[size1];
        }
        check_arr = new bool* [size1];
        for (int i = 0; i < size1; i++)
        {
            check_arr[i] = new bool[size1];
        }
        //to generate new data in array.
        populate();
    }

    void populate()
    {
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                check_arr[i][j] = false;
            }
        }
        //for new generation of number everytime otherwise.
        //same number will be returned multiple times.
        srand(time(nullptr));

        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                int temp = generateRandomNumbers();
                data_arr[i][j] = temp;
            }
        }
    }

    int generateRandomNumbers()
    {
        //generates a number between 0 and 2.
        int randomNum = rand() % 3;
        return randomNum;
    }

    void displayGrid()
    {
        //checks using check_arr to see if a co-ordinate has been
        //cehecked. Values are updated accordingly in grid_arr.
        cout << "Grid:" << endl;
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (check_arr[i][j] == true)
                    cout << "*\t";
                else
                    cout << "!\t";
            }
            cout << endl;
        }
    }

    void gameplayy()
    {
        cout << "Enter your name: " << endl;
        cin >> playername;
        p1.setname(playername);
        cout << "Welcome to the game, " << playername << "!" << endl << endl;
        instructions();
        while (flag == false)
        {
            //system("cls");
            //to use grid as Front end of gameplay.
            displayGrid();
            
            cout << "Enter coordinates to find key: " << endl;
            cin >> input_user_x;
            cin >> input_user_y;

            //to make values in a more user friendly format e.g.
            //user enters co-ordinates 1,1 will be treated as 0,0.
            input_user_x = input_user_x - 1;
            input_user_y = input_user_y - 1;

            //first check to see if co-ordinates don't generate error
            //of array out of bounds.
            if (input_user_x < grid_size && input_user_y < grid_size)
            {
                //Check to see if co-ordinates are being repeated.
                if (check_arr[input_user_x][input_user_y] == true)
                {
                    cout << "Enter again! Already used!" << endl;
                }
                else
                {
                    //for keys.
                    if (data_arr[input_user_x][input_user_y] == 1)
                    {
                        p1.incrementscore();
                        p1.incrementattempts();
                        check_arr[input_user_x][input_user_y] = true;
                        cout << "Congratulations! You found a key!" << endl;
                    }
                    //for neither keys nor mine.
                    if (data_arr[input_user_x][input_user_y] == 2)
                    {
                        p1.incrementattempts();
                        check_arr[input_user_x][input_user_y] = true;
                        cout << "Eh! Good luck on the next move!" << endl;
                    }
                    //for mine.
                    if (data_arr[input_user_x][input_user_y] == 0)
                    {
                        p1.incrementattempts();
                        cout << "MINE! Game Over!" << endl;
                        flag = true;
                    }
                    //check to see if user won by checking all places having value 1.
                    bool allChecked = true;
                    for (int i = 0; i < grid_size; i++)
                    {
                        for (int j = 0; j < grid_size; j++)
                        {
                            if (data_arr[i][j] == 1 && check_arr[i][j] == false)
                            {
                                allChecked = false;
                                break;
                            }
                        }
                        if (!allChecked)
                        {
                            break;
                        }
                    }

                    if (allChecked)
                    {
                        flag = true;
                        cout << "Congratulations! You have won the game!" << endl;
                    }
                }
            }
            else
            {
                cout << "Eh! Wrong co-ordinates! Enter again\n";
            }
            
        }
        //Declare result in both winning and loosing case.
        if (flag == true)
        {
            result();
        }
    }

    void result()
    {
        //recieves values from player class to declare results.
        cout << endl;
        cout << "Player name: " << p1.getname() << endl;
        cout << "Score: " << p1.getscore() << endl;
        cout << "Attempts: " << p1.getattempts() << endl;
    }
};
int main()
{
    //adding color for better interface.
    system("Color 02");
    int x = 0;
    cout << "Enter grid size\n";
    cin >> x;
    gameplay a(x);
    a.gameplayy();
    system("pause");
    return 0;
}