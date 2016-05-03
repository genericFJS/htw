// farm.cpp : Defines the entry point for the console application.
//

//////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////

struct IObject
{
  virtual ~IObject() {}
};

//////////////////////////////////////////////////

struct IObjectBase : virtual public IObject
{
};

//////////////////////////////////////////////////

struct IAnimal : public IObjectBase
{
  virtual void Cry() = 0;
};

//////////////////////////////////////////////////

struct IMovement : public IObjectBase
{
  virtual void Move() = 0;
};

//////////////////////////////////////////////////

struct IName : public IObjectBase
{
public:
  virtual void SetName(const char *pszName) = 0;
  virtual const char *GetName() = 0;
};

//////////////////////////////////////////////////

class INameImpl : public IName
{
  char szName[32];
public:
  INameImpl() { szName[0] = 0; }
  const char *GetName() { return szName; }
  virtual void SetName(const char *pszName) { strcpy(szName, pszName); }
};

//////////////////////////////////////////////////

class CDog : public IAnimal, public INameImpl
{
public:
  CDog(const char *pszName) { SetName(pszName); }
  void Cry() { cout << "Wuff" << endl; }
};

//////////////////////////////////////////////////

class CCat : public IAnimal, public INameImpl
{
public:
  CCat(const char *pszName) { SetName(pszName); }
  void Cry() { cout << "Miau" << endl; }
};

//////////////////////////////////////////////////

class CHorse : public IAnimal, public INameImpl, public IMovement
{
public:
  CHorse(const char *pszName) { SetName(pszName); }
  void Cry() { cout << "Iehh" << endl; }
  void Move()
  {
    for(int i=0; i<9; i++)
    {
      cout << " galopp" << flush;
      Sleep(500);
    }
    cout << endl;
  }
};

//////////////////////////////////////////////////

class CChicken : public IAnimal
{
public:
  void Cry() { cout << "Goak" << endl; }
};

//////////////////////////////////////////////////

class CTractor : public IMovement
{
public:
  void Move()
  {
    for(int i=0; i<15; i++)
    {
      cout << " tok" << flush;
      Sleep(500);
    }
    cout << endl;
  }
};

//////////////////////////////////////////////////

class CCar : public IMovement, public INameImpl
{
public:
  CCar(const char *pszName) { SetName(pszName); }
  void Move()
  {
    cout << " b" << flush;
    for(int i=0; i<58; i++)
    {
      cout << "r" << flush;
      Sleep(20);
    }
    cout << endl;
  }
};

//////////////////////////////////////////////////

class CFarm
{
  vector<IObject *> m_objects;

public:
  ~CFarm()
  {
    for(int i=0; i<m_objects.size(); i++) delete m_objects[i];
  }

  void Add(IObject *pObject)
  {
    m_objects.push_back(pObject);
  }
  void Work()
  {
    for(int i=0; i<m_objects.size(); i++)
    {
      cout << "----------" << endl;

      const type_info & ti = typeid(*m_objects[i]);
      cout << ti.name() << endl;

      IName *pName = dynamic_cast<IName *>(m_objects[i]);
      if(NULL != pName)
        cout << pName->GetName() << endl;

      IAnimal *pAnimal = dynamic_cast<IAnimal *>(m_objects[i]);
      if(NULL != pAnimal)
        pAnimal->Cry();

      IMovement *pMovement = dynamic_cast<IMovement *>(m_objects[i]);
      if(NULL != pMovement)
        pMovement->Move();
    }
  }
};

//////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  CFarm theFarm;

  theFarm.Add(new CCat("fritz"));
  theFarm.Add(new CDog("hasso"));
  theFarm.Add(new CHorse("fury"));
  theFarm.Add(new CChicken);
  theFarm.Add(new CCar("BMW"));
  theFarm.Add(new CTractor);

  theFarm.Work();
  cin.get();
  return 0;
}

//////////////////////////////////////////////////

