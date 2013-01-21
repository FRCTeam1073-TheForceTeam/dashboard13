#ifndef RoboRealmVars_h__
#define RoboRealmVars_h__
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
#include <vector>
using namespace std;

class RoboRealmVars
{
public:
    RoboRealmVars(RR_API& rr) : mDoRebuild(true), mNames(), mResults(), mRR(rr) { }
    void add(RoboRealmVarBase& var);

    void operator()() { read(); }

protected:
    void buildList();
    void read();
    void markVarsOld();

private:
    static const int mBufSize = 64;
    
    typedef vector<RoboRealmVarBase*> var_vector;
    var_vector mVarList;

    bool mDoRebuild;
    string mNames;
    
    // mResults is an array of pointers to the char buffers where the data from RR is stored.
    // it is dynamically allocated based on the number of variables in the list.
    //  mResults[n] ===> var.mBuf (actually &var.mBuf[0])
    char** mResults;

    RR_API& mRR;

};

#endif // RoboRealmVars_h__
