// Scaffold.cpp

#include "provided.h"
#include <iostream>
using namespace std;


class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
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
    vector<vector<int>> m_con; //condition of positions
    
    
    
    stack<pair<int,int>> track;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    m_cols = nColumns;
    m_lvls = nLevels;
    m_con.resize(nLevels);
    for(int i = 0; i< nLevels; i++)
        m_con[i].resize(nColumns);
    
    
    //Initialize all the position with -1 meaning nothing is in the positions
    for (int i = 0; i < m_cols; i++)
        for (int j=0; j< m_lvls; j++)
            m_con[j][i] = -1;
    
        
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
            if(m_con[j][i] == -1)
                n++;

    //return n
    return n;
    
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    //Convert the column to column -1 and convert level upsdie down
    column = column -1;
    level = level-1;
    
    
    if(m_con[level][column] == -1)
            return VACANT;
    else if(m_con[level][column] == 0)
            return RED;
    else if(m_con[level][column] == 1)
            return BLACK;
    
    
    //If not anything, default return VACANT
    return VACANT;
}

void ScaffoldImpl::display() const
{
    for(int lev = m_lvls -1;lev>= 0 ; lev--)
    {    for(int col = 0; col < m_cols; col++)

    {
        cout << '|';
        if(m_con[lev][col] == RED)
            cout << 'R';
        if(m_con[lev][col]== BLACK)
            cout << 'B';
        if(m_con[lev][col]== VACANT)
            cout << ' ';
    }
    cout<<'|'<<endl;
    }
    for(int col = 0; col< m_cols; col++)
        cout<<"+-";
    cout << "+" << endl;
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
    
    for( int i = 0; i < m_lvls; i++)
        //exam:???
        if(m_con[i][(column-1)] == VACANT)
        {
           m_con[i][(column-1)] = color;
            
            
            //p1.first == column-1, p1.second == i
            pair<int,int> p1(i,column-1);
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
    m_con[temp.first][temp.second] = VACANT;
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
