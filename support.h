//
//  support.h
//  CS32_Project_3
//
//  Created by Zegao Liu on 16/5/14.
//  Copyright © 2016年 Zegao Liu. All rights reserved.
//

#ifndef support_h
#define support_h
#include "provided.h"



int minimax(Scaffold& copyS, int colorofsmartplayer, int m_N, int m_step);

bool completed(Scaffold* m_Scaffold, int& winner,int m_N);

int opponentcolor(int colorofsmartplayer);

int findsmallest(vector<int> n_branch, vector<bool> bool_branch,int n);

int findlargest(vector<int> n_branch, vector<bool> bool_branch,int n);

#endif /* support_h */
