#ifndef RoboRealmVar_h__
#define RoboRealmVar_h__
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
#pragma warning(disable:4351)   // warning about arrays being initialized in constructor now

class RoboRealmVars;
//======================================================================================================================
class RoboRealmVarBase 
{ 
    friend class RoboRealmVars;
public:
    RoboRealmVarBase(const string& name) : mName(name), mIsOld(false), mBuf() { }

    const string name() const { return mName; }

protected:
    string mName;
    bool mIsOld;
    static const int buf_size = 64;
    char mBuf[buf_size];
};
//======================================================================================================================
template <typename  T, T F(const char *)>
class RoboRealmVar : public RoboRealmVarBase
{
public:
    RoboRealmVar(const string& name, RR_API& rr);

    const T operator()() { return value(); }

protected:
    void convert() { mValue = F(mBuf); }
    void read();
    const T value() { if (mIsOld) { convert(); mIsOld = false; } return mValue; }

private:
    T mValue;
    RR_API& mRR;
};
//---------------------------------------------------------------------------------------------------------------------
typedef RoboRealmVar<int, &atoi> rrIntVar;
typedef RoboRealmVar<double, &atof> rrFloatVar;

inline string atos(const char* c) { return string(c); }
typedef RoboRealmVar<string, &atos> rrStrVar;

//======================================================================================================================
template <typename  T, T F(const char *)>
RoboRealmVar<T, F>::RoboRealmVar(const string& name, RR_API& rr) : RoboRealmVarBase(name), mValue(),  mRR(rr)
{
}
//---------------------------------------------------------------------------------------------------------------------
template <typename  T, T F(const char *)>
void RoboRealmVar<T, F>::read()
{
    mRR.getVariable(const_cast<char*>(mName.c_str()), mBuf, buf_size); 
    mIsOld = true;
}
#endif // RoboRealmVar_h__
