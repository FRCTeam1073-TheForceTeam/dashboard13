//======================================================================================================================
// 2010 Copyright Mystic Lake Software
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//======================================================================================================================
//
//     Author: Rudyard Merriam
//
//      $Id: $
//
//======================================================================================================================
//
#include <string>
using namespace std;

#include "RR_API.h"
#include "RoboRealmVar.h"
#include "RoboRealmVars.h"
//---------------------------------------------------------------------------------------------------------------------
void RoboRealmVars::add(RoboRealmVarBase& var)
{
    mVarList.push_back(&var); 
    mDoRebuild = true;
}
//---------------------------------------------------------------------------------------------------------------------
void RoboRealmVars::buildList() 
{
    mNames.clear();

    size_t cnt = 0;

    for (var_vector::iterator pos = mVarList.begin(); pos != mVarList.end(); pos++)
    {
        RoboRealmVarBase& var = **pos;

        mNames += var.mName + ",";
        mResults[cnt] = &var.mBuf[0];
        cnt++;
        var.mIsOld = true;
    }
}
//---------------------------------------------------------------------------------------------------------------------
void RoboRealmVars::read()
{
    const int rows = mVarList.size();

    if (mDoRebuild)
    {
        delete [] mResults;
        mResults = new char*[rows];
        buildList();
        mDoRebuild = false;
    }

    mRR.getVariables(const_cast<char*>(mNames.c_str()), mResults, mBufSize, rows);
    markVarsOld();
}
//---------------------------------------------------------------------------------------------------------------------
void RoboRealmVars::markVarsOld()
{
    for (var_vector::iterator pos = mVarList.begin(); pos != mVarList.end(); pos++)
    {
        RoboRealmVarBase& var = **pos;
        var.mIsOld = true;
    }
}