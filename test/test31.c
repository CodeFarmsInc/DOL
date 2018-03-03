// This is a simple ring of Employees that have Date as member
// The ring is being stored/restored depending on the option selected.
#include <stdio.h>
#include <stdlib.h>
#define ZZmain
#define ZZascii
#include "zzincl.h"

class Date{
  ZZ_EXT_Date
public:
  Date() {ZZ_INIT(Date);}
  Date(int mm, int dd, int yy) { SetDate(mm, dd, yy); }
  ~Date() {ZZ_CHECK(Date);}
  void Print(char *buf) { sprintf(buf,"%02d/%02d/%04d", Month, Day, Year); }
  void SetDate(int mm, int dd, int yy) { Month=mm; Day=dd; Year=yy; }
  void save(const char *filename){ZZ_STORE(Date,filename);}
  int Month;
  int Day;
  int Year;
};
ZZ_FORMAT(Date,"%d %d %d, Month, Day, Year");

class Employee{
  ZZ_EXT_Employee
public:
  Employee() {ZZ_INIT(Employee);}
  ~Employee() {ZZ_CHECK(Employee);}
  int IEmployee(char *buf);
  void Print(char *buf);
  void save(const char *filename){ZZ_STORE(Employee,filename);}
private:
  float Salary;
  Date BirthDate;
};
ZZ_FORMAT(Employee,"%f, Salary");

ZZ_HYPER_UTILITIES(util);
ZZ_HYPER_SINGLE_RING(all,Employee);

int Employee::IEmployee(char *buf)
{
  int i;
  // since buff was obtained through getf, the last character is \0
  for(i=0;buf[i]!='\0';i++){if(buf[i]=='/' || buf[i]=='\t')buf[i]=' ';}
  sscanf(buf,"%d %d %d %f",&(BirthDate.Month),&(BirthDate.Day),
                           &(BirthDate.Year), &Salary);
  return 0;
}

void Employee::Print(char *buf)
{
  char DateBuf[30];

  BirthDate.Print(DateBuf);
  sprintf(buf, "%s %10.2f",
          DateBuf,
          Salary);
}

void PrintRing(Employee *tail)
{
  Employee *CurEmp;
  char buf[132];

  printf("Ring:\n");
  all_iterator it(tail);   // iterator points to tail of ring
  // start printing from head of ring
  for (CurEmp = ++it; CurEmp; CurEmp = ++it)
  {
    CurEmp->Print(buf);
    printf("%s\n", buf);
  }
}

Employee *ClearRing(Employee *tail)
{
  Employee *CurEmp;

  printf("Clearing ring from memory\n");
  all_iterator it(tail);   // iterator points to tail of ring
  // start deleting from head of ring
  for (CurEmp = ++it; CurEmp; CurEmp = ++it)
  {
    tail = all.del(tail, CurEmp);
    delete CurEmp;
  }

  return tail;
}

int main(int argc, char *argv[])
{
  Employee *CurEmp,*tail = NULL;
  char buf[132];                         
  char *v[10],*t[10];
  all_iterator it(tail);   // iterator points to tail of ring

  if (argc < 2)
  {
    printf("usage: ringtest <r|w> [d]\n");
    exit(1);
  }

  switch ( *(argv[1]) )
  {
  case 'w':
    // read ring from stdin
    printf("Reading ring from stdin\n");
    tail = NULL;
    while ( gets(buf) )
    {
      if ( (CurEmp = new Employee) == NULL)
        exit (1);
      CurEmp->IEmployee(buf);
      tail = all.add(tail, CurEmp);
      tail = CurEmp;         // tail points to tail of ring
    }
    PrintRing(tail);

    // save ring to ring1.out (individual elements)
    printf("Saving ring to ring1.out (individual elements)\n");
    tail->save("ring1.out"); // store the tail as the key entry
    it.start(tail);          // iterator points to tail of ring
    // start saving from head of ring
    for (CurEmp = ++it; CurEmp; CurEmp = ++it)
      CurEmp->save("ring1.out");
    util.close("ring1.out");

    // save ring to ring2.out ( using util.save() ) and clear the ring
    printf("Saving ring to ring2.out ( using util.save() )\n");
    v[0] = (char *) tail;    // key entry is tail of ring
    t[0] = (char*)"Employee";
    util.save("ring2.out",1,v,t);

    // clear ring before exit
    tail = ClearRing(tail);
    PrintRing(tail);
    break;

  case 'r':
    // read ring from ring1.out
    printf("Reading ring from ring1.out\n");
    v[0]= NULL;
    util.open("ring1.out",1,v,t);
    tail=(Employee *)v[0];   // tail points to key entry, which is tail of ring
    PrintRing(tail);
    if ( (argc == 3) && (*(argv[2]) == 'd') )
      util.debug((char *)tail,(char*)"Employee");
    // clear ring
    tail = ClearRing(tail);
    PrintRing(tail);


    // read ring from ring2.out
    printf("Reading ring from ring2.out\n");
    v[0]= NULL;
    util.open("ring2.out",1,v,t);
    tail=(Employee *)v[0];   // tail points to key entry, which is tail of ring
    PrintRing(tail);
    if ( (argc == 3) && (*(argv[2]) == 'd') )
      util.debug((char *)tail,(char*)"Employee");
    // clear ring
    tail = ClearRing(tail);
    PrintRing(tail);
    break;

  default:
    printf("usage: ringtest [r|w]\n");
    exit(1);
  }
  return(0);
}

#include "zzfunc.c"
