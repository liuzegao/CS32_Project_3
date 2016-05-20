// Game.cpp

#include "provided.h"

//exam:Can I add iostream?
#include <iostream> 
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    ~GameImpl();
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
  private:
    Scaffold* m_Scaffold;
    int m_N;
    Player* m_Redplayer;
    Player* m_Blackplayer;
    int m_turn;
    //-2 no winner, -1 the game wins, 0 red wins, 1 blackwins
    int m_winner;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_Scaffold = new Scaffold(nColumns,nLevels);
    m_N = N;
    m_Redplayer = red;
    m_Blackplayer = black;
    m_turn = RED;
    m_winner = -2;
    
}

//exam:Can I write destrcutor?
GameImpl::~GameImpl()
{
    delete m_Scaffold;
}


bool GameImpl::completed(int& winner) const
{
    //Do the complete check for every checkers in the game
    for (int i = 1; i <= m_Scaffold->cols(); i++)
        for (int j=1; j<= m_Scaffold->levels(); j++)
        //Do the check only when there is a checker
        if(m_Scaffold->checkerAt(i,j)!=  -1)
        {
            //For all condition
                //check up
                int k = 1;
                //Sort while the next position is the same and the sorting number is smaller than m_N and the total length j+k is equal or smaller than levles()-1, k must be smaller than m_N
                while(j+k <= m_Scaffold->levels() && k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i,j+k))
                        k++;
                    else
                        break;
                }
                if (k == m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                    return true;
                }
                //check down
                k = 1;
                //Sort while the next checkers is the same and the sorting number is smaller than m_N and the total length j-k is equal or larger than 0
                while(j-k > 0 && k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i,j-k))
                        k++;
                    else
                        break;
                }
                if (k ==m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                    return true;
                }
                //check left
                k = 1;
                //Sort while the next checkers is the same and the sorting number is smaller than m_N and the total length i-k is equal or larger than 0
                while( i-k > 0  && k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i-k,j))
                        k++;
                    else
                        break;
                }
                if (k ==m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                    return true;
                }
                //check left
                k = 1;
                //Sort while the next checkers is the same and the sorting number is smaller than m_N and the total length i-k is equal or larger than 0
                while( i+k <= m_Scaffold->cols() && k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i+k,j))
                        k++;
                    else
                        break;
                }
                if (k ==m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                    return true;
                }
            
                //Check right up
                k = 1;
                while( i+k <= m_Scaffold->cols() && j+k <= m_Scaffold->levels() &&  k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i+k,j+k))
                        k++;
                    else
                        break;
                }
                if (k ==m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                return true;
                }
                 //Check right down
                k = 1;
                while( i+k <= m_Scaffold->cols() && j-k > 0 &&  k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i+k,j-k))
                        k++;
                    else
                        break;
                }
                if (k ==m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                    return true;
                }
                //Check left up
                k = 1;
                while( i-k > 0 && j+k > m_Scaffold->levels() &&  k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i-k,j+k))
                        k++;
                    else
                        break;
                }
                if (k ==m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                    return true;
                }
                //Check left down
                k = 1;
                while( i-k > 0 && j-k > 0 &&  k < m_N )
                {
                    if(m_Scaffold->checkerAt(i,j) == m_Scaffold->checkerAt(i-k,j-k))
                        k++;
                    else
                        break;
                }
                if (k ==m_N)
                {
                    if (m_Scaffold->checkerAt(i,j) == RED)
                    {
                        winner = RED;
                        //cout << "Winner is RED" << endl;
                    }
                    if (m_Scaffold->checkerAt(i,j) == BLACK)
                    {
                        winner = BLACK;
                        //cout << "Winner is BLACK" << endl;
                    }
                    return true;
                }

        }
    
    //All full and there is no N connect, the game wins
    if (m_Scaffold->numberEmpty() == 0)
    {
        winner = -1;
        cout << "Winner is THE_GAME" << endl;
        return true;
    }
    
    //Not full and no N connect, return false
    winner = -2;
    return false;
}

bool GameImpl::takeTurn()
{
    //If completed return false
    if(completed(m_winner))
    {
        if (m_winner == RED)
            cout << "Winner is RED" << endl;
        if (m_winner == BLACK)
            cout << "Winner is BLACK" << endl;
        return false;
    }
    else
    {
        if(m_turn == RED)
        {   //exam:Can I do this *m_Scaffold?
            m_Scaffold->makeMove(m_Redplayer->chooseMove(*m_Scaffold, m_N, RED),RED);
            m_turn = BLACK;
            return true;
        }
        if(m_turn == BLACK)
        {   m_Scaffold->makeMove(m_Blackplayer->chooseMove(*m_Scaffold, m_N, BLACK),BLACK);
            m_turn = RED;
            return true;
        }
        
    }
    return false;
}

void GameImpl::play()
{
    if(takeTurn())
    {
        if(m_turn == RED)
            if(m_Redplayer->isInteractive())
                m_Scaffold->display();
        if(m_turn == BLACK)
            if(m_Blackplayer->isInteractive())
                m_Scaffold->display();
        play();
    }

    return;
}

int GameImpl::checkerAt(int c, int r) const
{
    if(m_Scaffold->checkerAt(c, r) == RED)
        return RED;
    if(m_Scaffold->checkerAt(c, r) == BLACK)
        return BLACK;
    return VACANT;  //  This is not always correct; it's just here to compile
} 

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
