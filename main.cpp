//
//  main.cpp
//  CS32_Project_3
//
//  Created by Zegao Liu on 16/5/17.
//  Copyright © 2016年 Zegao Liu. All rights reserved.
//

// main.cpp

#include "provided.h"
#include <iostream>
#include <cassert>
//exam: delete
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

void doScaffoldTests()
{
    Scaffold s(3, 2);
    assert(s.cols() == 3  &&  s.levels() == 2  &&
           s.numberEmpty() == 6);
    assert(s.makeMove(1, RED));
    assert(s.makeMove(1, BLACK));
    assert(!s.makeMove(1, RED));
    assert(s.numberEmpty() == 4);
    assert(s.checkerAt(1, 1) == RED  &&  s.checkerAt(1, 2) == BLACK);
    assert(s.checkerAt(2, 1) == VACANT);
    s.display();
}

int main()
{
    HumanPlayer bp("Homer");
    SmartPlayer hp("Marge");
    Game g(7, 6, 4, &bp, &hp);
    g.play();

}
