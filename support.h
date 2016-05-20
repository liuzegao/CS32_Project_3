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


void copyScaffold(Scaffold& copyS,const Scaffold& s);

int minimax(Scaffold& copyS, int colorofsmartplayer, int m_N, int m_step);

int rating(Scaffold& copyS, int colorofsmartplayer,int m_N, int m_winner);

bool completed(Scaffold* m_Scaffold, int& winner,int m_N);

int opponentcolor(int colorofsmartplayer);

int findsmallest(int n_branch[], bool bool_branch[],int n);

int findlargest(int n_branch[], bool bool_branch[],int n);

#endif /* support_h */
