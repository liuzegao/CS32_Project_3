//
//  support.cpp
//  CS32_Project_3
//
//  Created by Zegao Liu on 16/5/14.
//  Copyright © 2016年 Zegao Liu. All rights reserved.
//


#include "support.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <climits>
using namespace std;


int opponentcolor(int colorofsmartplayer)
{
    if(colorofsmartplayer ==BLACK)
        return RED;
    else if(colorofsmartplayer ==RED)
        return BLACK;
    
    return -1;
}


int findlargest(int n_branch[], bool bool_branch[],int n)
{
    int large = 0;
    //Put the first value in branch into small;
    for(int i = 0; i<n; i++)
        if(bool_branch[i])
        {   large = n_branch[i];
            break;
        }
    
    for(int i = 0; i<n; i++)
        if(bool_branch[i])
        {
            if(n_branch[i] > large)
                large =n_branch[i] ;
        }
    
    return large;
}

int findsmallest(int n_branch[], bool bool_branch[],int n)
{
    int small = 0;
    //Put the first value in branch into small;
    for(int i = 0; i<n; i++)
        if(bool_branch[i])
        {   small = n_branch[i];
            break;
        }
    
    for(int i = 0; i<n; i++)
        if(bool_branch[i])
        {
            if(n_branch[i] < small)
                small =n_branch[i] ;
        }
    
    return small;
}

//Minimax algorithme which returns the evaluations numbers
int minimax(Scaffold& copyS, int colorofsmartplayer,int m_N,int m_step)
{
    copyS.display();
    
    //Find which color is the opponent color
    int opponent = opponentcolor(colorofsmartplayer);
    
    //-2 no winner, -1 the game wins, 0 red wins, 1 blackwins
    int m_winner;
    
    
    //Stopping condition
    if (completed(&copyS, m_winner, m_N))
    {   if(m_winner == colorofsmartplayer)
        return INT_MAX-m_step;
        
    else if(m_winner == opponent)
        
        return INT_MIN+m_step;
    else if(m_winner == -1)
        //Return m_step because more step is better since I do not make mistake but the opponent might make one
        return m_step;
    }
    
    
    
///////////////////////////////////////////////////////////////////////
//Middle condition
///////////////////////////////////////////////////////////////////////
    

    //Find the color of the current move
    int currentcolor;
    //Determine what's the color of the current player
    if(m_step%2 == 1) //Odd number, turn of smartplayer
        currentcolor = opponent;
    else
        currentcolor = colorofsmartplayer;

    int n_branch[copyS.cols()];
    bool bool_branch[copyS.cols()];
    
    //Initialize the n_branch with 0
    for(int i=0;i< copyS.cols();i++)
        n_branch[i] = false;
    
    //Rrecursion part
    for(int i = 0; i< copyS.cols(); i++)
    {
        if ( copyS.checkerAt(i+1, copyS.levels()) == VACANT)
        {
            copyS.makeMove(i+1,currentcolor);
            n_branch[i] = minimax(copyS, colorofsmartplayer,m_N, m_step+1);
            n_branch[i] = true;
            copyS.undoMove();
        }
    }
    
    
    //Find the largest value in the vector n_branch, (which is evalualtion of all the moves)
    if( currentcolor == colorofsmartplayer)
    {
        return findlargest(n_branch,  bool_branch, copyS.cols());
    }
    else
        return findsmallest(n_branch,  bool_branch, copyS.cols());

    
    return 0;
}


bool completed(Scaffold* m_Scaffold, int& winner, int m_N)
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
                //Sort while the next checkers is the same and the sorting number is smaller than m_N and the total length j+k is equal or smaller than levles()-1
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
        //cout << "Winner is THE_GAME" << endl;
        return true;
    }
    
    //Not full and no N connect, return false
    winner = -2;
    return false;
}





