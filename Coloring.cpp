#include<iostream>
#include<limits>
using namespace std;
class adlist;
class nlist;
class nlist                //List of neighbours on the Adjacency List
{
  public:
    char nname;
    nlist *nxt;
    adlist *addr;
    nlist()
    {
        nname=' ';
        nxt=NULL;
        addr=NULL;
    }
};
class adlist                //Adjacency List
{
 public:
    char vname;
    int degree;
    adlist *next;
    int col;
    nlist *node;
    adlist()
    {
        vname=' ';
        next=NULL;
        col= -1;
        node=new(nlist);
    }
};
adlist *searchl(adlist *st,char c);
adlist *order(adlist *st,int n);
void printlist(adlist *st,int n);
void printlist(adlist *st,int n);
adlist *makelist(adlist *st,int n);
adlist *addnbr(adlist *st);
adlist *color(adlist *start, int n);
int searchn(nlist *nb,int c,int d);
adlist *colorI(adlist *start, int n);

int main()
{
    adlist *A,*B,*start=NULL;
    int n;
    cout<<"Program for generating a coloring of a graph"<<endl;
    cout<<"\nEnter Number of Vertices in the Graph:";
    while(!(cin>>n))
     {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
         cout<<"Please enter Integer values"<<endl;
     }
     
    start=makelist(start,n);
    start=addnbr(start);
    cout<<"\nPrinting the generated list:\n";
    printlist(start,n);
    start=order(start,n);
    cout<<"\nPrinting the ordered list:\n";
    printlist(start,n);
    start=color(start,n);
    cout<<"\nPrinting the colored list:\n";
    printlist(start,n);
    return 0;
}

adlist *order(adlist *st, int s)//Sorts a singly linked list
{
    int x,swapped;
    adlist *current=st;
    adlist *n;
    adlist *prev;
    for(int i=0;i<s;i++)
    {
      while(current->next!=NULL)
      {
        n=current->next;
       if(current->degree<n->degree) //Change sign here to reverse ordering
       {
           swapped=1;
           current->next=n->next;
           n->next=current;
           if(prev!=NULL)
              prev->next=n;
           prev=n;
           if(st==current)
              st=n;
       }
        else
        {
           prev=current;
           current=current->next;
        }
     }
       if(swapped==0)
        break;
       else
       {
           prev=NULL;
           current=st;
           swapped=0;
       }
   }
return st;
}

adlist *searchl(adlist *st,char c)
{
    adlist *A=st;
    while(A!=NULL)
    {
        if(A->vname==c)
            return A;
        A=A->next;
    }
    return NULL;
}

adlist *makelist(adlist *st,int n)
{
  adlist *A;
  char c;
  for(int i=0;i<n;i++)
  {
     A=new adlist();
     if(st==NULL)
     {
         st=A;
         cout<<"Enter Vertex Name (letters) : ";
         cin>>c;
         A->vname=c;
     }
     else
     {
      while(true)
      {
        cout<<"Enter Vertex Name (letters) : ";
        cin>>c;
        if(searchl(st,c)!=NULL)
            cout<<"Vertex "<<c<<" already exists, please enter a different name."<<endl;
        else
         break;
      }
      A->vname=c;
      A->next=st;
      st=A;
     }
   }
  return st;
}

adlist *addnbr(adlist *st)
{
   adlist *A=st;
   int d;
   char c;
   while(A!=NULL)
   {
     cout<<"Enter Degree of Vertex "<<A->vname<<" : ";
     while(!(cin>>d))
     {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
         cout<<"Please enter Integer values for degree"<<endl;
     }
     A->degree=d;
     nlist *B=A->node;
     cout<<"Enter neighbours for "<<A->vname<<" vertex"<<endl;
     do{
              cin>>c;
              adlist *X=searchl(st,c);
              if(c==A->vname||(X==NULL))
              {
                cout<<"Invalid vertex name"<<endl;
                continue;
              }
              else
              {
               nlist *C=new(nlist);
                C->addr=X;
                C->nname=c;
                if(A->node==NULL)
                  A->node=C;
                else
                {
                    B->nxt=C;
                    B=B->nxt;
                }
              }
              d--;
         }while(d>0);
            A=A->next;
      }
   return st;
}

void printlist(adlist *st,int n)
{
    cout<<"\n*****Printing*****\n";
    adlist *V=st;
    nlist *N;
    int i=0;
    while(i<n)
    {
        N=V->node;
        cout<<"\nVertex "<<V->vname<<endl;
        cout<<"\nColor: ";
        cout<<V->col<<endl;
        cout<<"Neighbours:\t";
        for(int j=0;j<=V->degree;j++)
        {
            cout<<N->nname<<"\t";
            N=N->nxt;
        }
        cout<<endl;
        V=V->next;
        i++;
    }
    char c;
    cin>>c;
}

adlist *color(adlist *start, int n)//Make changes in prototype function call
{
  char c;
  adlist *A=start;
  nlist *N;
  int clr=0;
  
  for(int w=1;w<=n;w++)
  {
    N=A->node;
    
    N=N->nxt;
    A->col=0;
    while(searchn(N,A->col,A->degree)==1)
    {
       A->col++;
    }
    
    if(A->col>clr)
         clr=A->col;

    
   
    A=A->next;
  }
  cout<<"\nColors used: "<<++clr<<endl;
  return start;
}

int searchn(nlist *nb,int c,int d)
{
    
    adlist *A;

    for(int i=0;i<d;i++)
    {
        A=nb->addr;
        if(A->col==-1)
        {
            nb=nb->nxt;
          continue;
        }
        if(A->col==c)
            return 1;

        nb=nb->nxt;
    }
    return 0;
}
