// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
//exam:Can I include <iostream> and <cstdlib>.
#include <iostream>

using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    cout << "Please input a number for the column number" << endl;
    int temp = 0;
    cin >> temp;
    //Check if the the move is winthin the range 1 to cols.
    while ( temp < 0 || temp > s.cols()|| s.checkerAt(temp,s.levels()) != -1)
    {
        cout << "Please input a valid number for the column number" << endl;
        cin >> temp;
    }
    return temp;
    
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //always go the left most not full columbn
    for(int i =1; i<= s.cols();i++)
        if(s.checkerAt(i, s.levels()) == -1)
            return i;
    
    //exam:What shall I do if all the columns are full;
    return -1;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //Copy the Scaffold so that you can move.
    Scaffold copyS = s;
    Scaffold copyS2 = s;

	int temp = copyS.cols();
	vector<int> n_branch;
	n_branch.resize(temp);
	vector<bool> bool_branch;
	bool_branch.resize(temp);

    //Initialize the n_branch with 0
    for(int i=0;i< copyS.cols();i++)
        n_branch[i] = false;
    
    for(int i = 0; i< copyS.cols(); i++)
    {
        if ( copyS.checkerAt(i+1, copyS.levels()) == VACANT)
        {
            copyS.makeMove(i+1,color);
            n_branch[i] = minimax(copyS, color,N,1);
            bool_branch[i] = true;
            copyS.undoMove();
           
        }
         copyS = copyS2;
    }
    

  
    
    int largest = findlargest(n_branch,  bool_branch, copyS.cols());
    
    
    //Find the position of the largest evaluations
    int position;
    for(int i = 0; i< copyS.cols(); i++)
        if(bool_branch[i])
        {   if (largest ==n_branch[i])
                { position = i+1;
                    break;
                }
        }
    
    //exam:delete
    //cerr << "Choice of Smartplayer is " << position << endl;
    
    //return the position
    return position;
    
}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{

    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
