// Scaffold.cpp

#include "provided.h"
#include <iostream>
using namespace std;


class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
    ~ScaffoldImpl();
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
private:
    int m_cols;
    int m_lvls;
    int m_cols_d;
    int m_lvls_d;
    //-1 Vacnt, 0 Red, 1 Black.
    int** m_con; //condition of positions
    
    char** m_draw; //draw condition of positions
    
    
    stack<pair<int,int>> track;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    m_cols = nColumns;
    m_lvls = nLevels;
    
    //Creat a matrx to record the condition of the position
    m_con = new int*[m_cols];
    for (int i = 0; i < m_cols; i++)
        m_con[i] = new int[m_lvls];
    
    //Initialize all the position with -1 meaning nothing is in the positions
    for (int i = 0; i < m_cols; i++)
        for (int j=0; j< m_lvls; j++)
            m_con[i][j] = -1;
    
    //What the program atually needs to draw
    m_cols_d = 2*m_cols+1;
    m_lvls_d = m_lvls+1;
    
    //reat a matrx to record the drawing of the position
    m_draw = new char*[m_cols_d];
    for (int i = 0; i < m_cols_d; i++)
        m_draw[i] = new char[m_lvls_d];
    
    
    //Initialize all the position with -1 meaning nothing is in the positions
    for (int i = 0; i < m_cols_d; i++)
        for (int j=0; j< m_lvls_d; j++)
        {
            //odd
            if (( i%2 == 1 ) && (j == m_lvls_d-1))
                m_draw[i][j] = '-';
            else if ( i%2 == 0 )
                {if (j == m_lvls_d-1)
                    m_draw[i][j] = '+';
                else
                    m_draw[i][j] = '|';
                }
            else
             m_draw[i][j] = ' ';
            
        }
        
}

ScaffoldImpl::~ScaffoldImpl()
{
    //exam:is it okay to delete the 2d like this?
    delete m_con;
    delete m_draw;
}

int ScaffoldImpl::cols() const
{
    return  m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_lvls;
}

int ScaffoldImpl::numberEmpty() const
{
    //temporary
    int n =0;
    
    //search through all the positions and see if any is -1
    for (int i = 0; i < m_cols; i++)
        for (int j=0; j< m_lvls; j++)
            if(m_con[i][j] == -1)
                n++;

    //return n
    return n;
    
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    //Convert the column to column -1 and convert level upsdie down
    column = column -1;
    level = m_lvls - level;
    
    
    if(m_con[column][level] == -1)
            return VACANT;
    else if(m_con[column][level] == 0)
            return RED;
    else if(m_con[column][level] == 1)
            return BLACK;
    
    
    //If not anything, default return VACANT
    return VACANT;
}

void ScaffoldImpl::display() const
{
    //exam: make the new m_con into the m_draw;
    for (int j=0; j< m_lvls_d; j++)
        for (int i = 0; i < m_cols_d; i++)
            if (( i%2 == 1 ) && (j < m_lvls_d-1))
            {
                if (m_con[(i-1)/2][j] == -1)
                    m_draw[i][j] = ' ';
                if (m_con[(i-1)/2][j] ==  0 )
                    m_draw[i][j] = 'R';
                if (m_con[(i-1)/2][j] ==  1 )
                    m_draw[i][j] = 'B';
                
                    
            }
    
            
        for (int j=0; j< m_lvls_d; j++)
                for (int i = 0; i < m_cols_d; i++)
        { if (i == m_cols_d-1)
            cout << m_draw[i][j] << endl;
        else
            cout << m_draw[i][j];
        }
}


bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column < 1 || column > cols())
        return false;
    //if the top of the column is not empty, return false
    //if(m_con[column-1][0] != VACANT)
    //{
    //    cerr << column << endl;
    //    return false;
    //}
    
    //If color is not black or red, return false
    if(color != RED && color != BLACK)
        return false;
    
    for( int i = levels()-1; i >= 0; i--)
        //exam:???
        if(m_con[(column-1)][i] == VACANT)
        {
           m_con[(column-1)][i] = color;
            
            
            //p1.first == column-1, p1.second == i
            pair<int,int> p1(column-1,i);
            track.push(p1);
            return true;
        }
    
    return false;
}

int ScaffoldImpl::undoMove()
{
    if(track.empty())
        return 0;
    //Record the position of the top of the track stack
    pair<int,int> temp = track.top();
    //Pop it after taking it
    track.pop();
    //Change it to -1 meaning no checker in this position
    m_con[temp.first][temp.second] = -1;
    //Return the column number 
    return temp.first;
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
