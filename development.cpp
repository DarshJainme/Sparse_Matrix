#include<bits/stdc++.h>
#define ll long long
using namespace std;

class Sp_Mat;
class node {
    friend class Sp_Mat;
    public :
    node(){
        next=NULL;
        down=NULL;
    }
    node(int r,int c,ll val)
    {
        row=r,col=c,value=val;
    }
    private:
    int row=0,col=0;
    long long value=0;
    node *next=NULL;
    node *down=NULL;
};

class Sp_Mat{// sparse matrix
    public: 
    Sp_Mat(int r = 0, int c = 0) : no_row(r), no_col(c) {
        rows.resize(no_row);
        columns.resize(no_col);
    }
    void clearmatrix()
    {
        for (int i = 0; i < no_col; i++)
        {
            node * p=columns[i].first;
            while(p!=NULL)
            {
                // cout<<p->row<<','<<p->col<<" = "<<p->value<<endl;
                node *temp=p;
                p=p->down;
                delete(temp);
            }
        }
        rows.resize(0);
        columns.resize(0);
        no_row=0,no_col=0,k=0,c=1;
    }
    void read(string f )
    {
        // Sp_Mat mat
        ifstream inputFile(f);
        clearmatrix();
        
        no_row=0,no_col=0,k=0,c=0;// c is constant factor
        if(!inputFile.is_open())
        {
            cout<<"Couldn't open file"<<endl;
            return;
        }
        string ln;// for line
        Sp_Mat mat;
        while (getline(inputFile, ln))
        {
            ll is_constant=0;// if there is a scaling factor or not
            if(ln.size()!=0 && ln[0]!='#')
            {
                int ck=0;// for when to take n, m and k
                for (int i = 0; i < ln.size(); i++)
                {
                    if(ln[i]=='=')
                    {
                        ck++;
                    }
                    if(ck==1 && (ln[i]<='9' && ln[i]>='0') )
                    {
                        no_row*=10;// previous digits must be multiplied by 10
                        no_row+=(int)(ln[i]-'0');
                    }
                    if(ck==2 && (ln[i]<='9' && ln[i]>='0'))
                    { 
                        no_col*=10;// previous digits must be multiplied by 10
                        no_col+=(int)(ln[i]-'0');
                    }
                    if(ck==3 && (ln[i]<='9' && ln[i]>='0'))
                    {
                        k*=10;
                        k+=(ll)(ln[i]-'0');
                    }
                    if(ck==4 && (ln[i]<='9' && ln[i]>='0'))
                    {
                        is_constant=1;
                        c*=10;
                        c+=(ll)(ln[i]-'0');
                    }
                }                
                if(is_constant==0)
                {
                    c=1;
                }
                break;
            }
        }
        int x,y;
        ll z;
        char ch;
        rows.resize(no_row);
        columns.resize(no_col);
        // matrix_name[A]= Sp_Mat(no_row,no_col);
        // matrix_name[A].rows.resize(no_row);
        for (int i = 0; i < k; i++)
        {
            inputFile>>x>>ch>>y;
            inputFile>>ch>>z;
            // cout<<'x'<<x<<'y'<<y<<'z'<<z<<endl;
            if(z!=0)
            {
                insert(x, y, z);
            }
        }
        inputFile.close();
        
        // matrix_name.insert({A,mat});
    }
    
    void insert(int r, int c, int val )
    {
        node* newnode=new node(r, c, val);
        if(rows[r].first==NULL)
        {
            rows[r].first=newnode;
            rows[r].second=newnode;
        }
        else
        {
            rows[r].second->next=newnode;
            rows[r].second=newnode;

        }
        if(columns[c].first==NULL)
        {
            columns[c].first=newnode;
            columns[c].second=newnode;
        }
        else
        {
            columns[c].second->down=newnode;
            columns[c].second=newnode;
        }

    }
    void seemat()
    {
        cout<<"#matrix print "<<endl;;
        cout<<"m = "<<rows.size()<< " n = "<<columns.size() << ' '<<"numItems= "<<k<<endl;
        for (int i = 0; i < columns.size(); i++)
        {
            node *p=columns[i].first;
            while(p!=NULL)
            {
                cout<<p->row<<','<<p->col<<" = "<<p->value*c<<endl;
                p=p->down;
            }
        }
    }
    void const_mult(ll val)
    {
        c*=val;
    }
    void move(Sp_Mat &C)
    {
        clearmatrix();
        no_col=C.no_col;
        no_row=C.no_row;
        rows.resize(no_row);
        columns.resize(no_col);
        k=C.k;
        c=C.c;
        for (int i = 0; i < C.no_col; i++)
        {
            node *p=C.columns[i].first;
            while (p!=NULL)
            {
                insert(p->row,p->col,p->value);
                p=p->down;
            }
        }
        C.clearmatrix();
    }
    void add(Sp_Mat &B) 
    {
        if (no_row != B.no_row || no_col != B.no_col) {
            cout << "Matrix dimensions do not match for addition!" << endl;
            return;
        }
        Sp_Mat Mat_C(no_row,no_col);
        ll k_for_matC=0;
        for (int i = 0; i < no_col; i++)
        {
            node *ptr_A=columns[i].first, *ptr_B=B.columns[i].first;
            while (ptr_A!=NULL || ptr_B!=NULL)
            {
                if(ptr_A==NULL)
                {
                    Mat_C.insert(ptr_B->row,ptr_B->col,ptr_B->value*B.c);
                    ptr_B=ptr_B->down;
                    k_for_matC++;
                }
                else if(ptr_B==NULL)
                {
                    Mat_C.insert(ptr_A->row,ptr_A->col,ptr_A->value*c);
                    ptr_A=ptr_A->down;
                k_for_matC++;
                }
                else if(ptr_A->row==ptr_B->row)
                {
                    if(ptr_A->value*c+ptr_B->value*B.c)
                    {
                        Mat_C.insert(ptr_A->row,ptr_A->col,ptr_A->value*c+ptr_B->value*B.c);
                        k_for_matC++;
                    }
                    ptr_A=ptr_A->down;
                    ptr_B=ptr_B->down;
                }
                else if (ptr_A->row<ptr_B->row)
                {
                    Mat_C.insert(ptr_A->row,ptr_A->col,ptr_A->value*c);
                    ptr_A=ptr_A->down;
                k_for_matC++;
                }
                else
                {
                    Mat_C.insert(ptr_B->row,ptr_B->col,ptr_B->value*B.c);
                    ptr_B=ptr_B->down;
                    
                k_for_matC++;
                }
            }
        }
        Mat_C.k=k_for_matC;
        move(Mat_C);
    }
    void write(string f)
    {
        ofstream outputFile(f);
        if(!outputFile.is_open())
        {
            cout<<"Couldn't open file"<<endl;
            return;
        }
        outputFile<<"#matrix print "<<endl;;
        outputFile<<"m = "<<rows.size()<< " n = "<<columns.size() << ' '<<"numItems= "<<k<<endl;
        for (int i = 0; i < columns.size(); i++)
        {
            node * p=columns[i].first;
            while(p!=NULL)
            {
                outputFile<<p->row<<','<<p->col<<" = "<<p->value*c<<endl;
                p=p->down;
            }
        }
        outputFile.close();
    }
    void mult(Sp_Mat &A, Sp_Mat &B)// stored in the currect matrix
    {
        cout<<A.no_col<<'-'<<B.no_row<<endl;;
        if(A.no_col!=B.no_row)
        {
            cout<<"Matrix multiplication not possible"<<endl;
            return;
        }
        clearmatrix();
        ll k_for_matC=0;
        no_row= A.no_row ;
        no_col= B.no_col ;
        rows.resize(no_row);
        columns.resize(no_col);
        for (int j = 0; j < B.no_col; j++)
        {
            for (int i = 0; i < A.no_row; i++)
            {
                // first we do for each column then for each row
                ll sum=0;
                node *ptr_A= A.rows[i].first, *ptr_B=B.columns[j].first;
                // row wise in A and column wise in B
                cout<<i<<j<<endl;
                while (ptr_A!=NULL && ptr_B!=NULL)
                {
                    if(ptr_A->col== ptr_B->row)
                    {
                        sum+=ptr_A->value*ptr_B->value;
                        ptr_B=ptr_B->down;
                        ptr_A=ptr_A->next;
                        
                    }
                    else if (ptr_A->col>ptr_B->row)
                    {
                        ptr_B=ptr_B->down;// B will go row wise and A will go column wise
                    }
                    else
                    {
                        ptr_A=ptr_A->next;
                    }
                }
                if(sum!=0)
                {
                    insert(i,j,sum);
                    k_for_matC++;
                }
            } 
        }
        k=k_for_matC;
        c=A.c*B.c;
        // for that constant term to be multiplied
    }
    private:
    ll c=1;
    ll k=0;
    int no_row=0,no_col=0;// number of rows and columns
    vector<pair<node*,node*>>rows,columns;
    // k is the number of terms 
    // one node for head and other for tail
};
int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    Sp_Mat matA, matB, matC, matD;
    map<int, Sp_Mat> mat_number;
    mat_number[1]=matA;
    mat_number[2]=matB;
    mat_number[3]=matC;
    mat_number[4]=matD;
    int mat_no1=0,mat_no2=0,mat_no3=0,constant=0;
    while (true)
    {
        cout<<"Tell the function you want to perform:"<<endl;;
        cout<<"1. Read matrix from file.\n2. Multiply by the constant.\n3. Add two matrices.\n4. Multiply two matrices and store in third matrix.\n5. Write a matrix to a file.\n6. See matrix.\n7. Exit."<<endl;;
        string s;
        // getline(cin,s);
        cin>>s;
        if(s=="1")//Read
        {
            cout<<"Enter the matrix number you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no1;
            cout<<"Enter file name"<<endl;
            cin>>s;
            if(mat_no1<=4 && mat_no1>=1)
            {
                mat_number[mat_no1].read(s);
            }
            else
            {
                cout<<"Incorrect matrix number"<<endl;
            }
        }
        // Constant Multiply
        else if (s=="2")
        {
            cout<<"Enter the constant with which you want to multiply matrix:"<<endl;
            cin>>constant;
            cout<<"Enter the matrix number you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no1;
            if(mat_no1<=4 && mat_no1>=1)
            {
                mat_number[mat_no1].const_mult(constant);
            }
            else
            {
                cout<<"Incorrect matrix number"<<endl;
            }
        }
        // Add
        else if (s=="3")
        {
            cout<<"Enter the matrix number for first matrix you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no1;
            cout<<"Enter the matrix number for second matrix you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no2;
            if(mat_no1<=4 && mat_no1>=1 && mat_no2<=4 && mat_no2>=1)
            {
                mat_number[mat_no1].add(mat_number[mat_no2]);
            }
            else
            {
                cout<<"Incorrect matrix number"<<endl;
            }
        }
        //multiply matrices
        else if (s=="4")
        {
            cout<<"Enter the matrix number for first matrix you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no1;
            cout<<"Enter the matrix number for second matrix you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no2;
            cout<<"Enter the matrix number for matrix you want to save the result:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no3;
            if(mat_no1<=4 && mat_no1>=1 && mat_no2<=4 && mat_no2>=1 && mat_no3<=4 && mat_no3>=1)
            {
                if(mat_no1==mat_no3|| mat_no2==mat_no3)
                {
                    cout<<"Please enter different matrix numbers";
                    continue;
                }
                else
                {
                    mat_number[mat_no3].mult(mat_number[mat_no1],mat_number[mat_no2]);
                }
            }
            else
            {
                cout<<"Incorrect matrix number"<<endl;
            }
        }
        // write
        else if (s=="5")
        {
            cout<<"Enter the matrix number you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no1;
            cout<<"Enter file name"<<endl;;
            cin>>s;
            if(mat_no1<=4 && mat_no1>=1)
            {
                mat_number[mat_no1].write(s);
            }
            else
            {
                cout<<"Incorrect matrix number"<<endl;
            }
        }
        // seematrix
        else if(s=="6")
        {
            cout<<"Enter the matrix number you want:\n1. MatA\n2. MatB\n3. MatC\n4. MatD"<<endl;
            cin>>mat_no1;
            if(mat_no1<=4 && mat_no1>=1)
            {
                mat_number[mat_no1].seemat();
            }
            else
            {
                cout<<"Incorrect matrix number"<<endl;
            }
        }
        else if (s=="7")
        {
            break;
        }
        
        else
        {
            cout<<"Error!"<<endl;;
            break;
        }
        cout<<"***********************************"<<endl;
    }
    cout<<endl;
    return 0;
}