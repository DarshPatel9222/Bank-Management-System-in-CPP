#include <iostream>
using namespace std;

class Account{
    protected:
    static int nextaccno;
    int acc_no;
    string name;
    double balance;
    string acc_type;
    int transactions;

    public:
    Account(){
        acc_no=0;
        name="";
        balance=0;
        acc_type="";
        transactions=0;
    }
    virtual void deposit(double x)=0;
    virtual void withdraw(double y)=0;
    virtual void display()=0;
    virtual double calcInterest()=0;

    void transfer(Account &other,double amt){
        if(balance<amt){
            cout<<"Not enough balance to transfer"<< endl;
        }
        else{
            balance=balance-amt;
            other.balance=other.balance+amt;
            transactions++;
            other.transactions++;
            cout<<"Transfer successful"<<endl;
            cout<<"Your New Balance="<<balance<<endl;
        }
    }

    void miniStatement(){
        cout<<"Account No: "<<acc_no<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Balance: "<<balance<<endl;
        cout<<"Transactions: "<<transactions<<endl;
    }

    int getAccNo(){
        return acc_no;
    }
    string getName(){
        return name;
    }
    double getBalance(){
        return balance;
    }
};

class SavingsAccount:public Account{
    double interestRate;
    int minBalance;

    public:
    SavingsAccount(){
        acc_type     = "Savings";
        interestRate = 4.5;
        minBalance   = 500;
    }

    void create(){
        acc_no=nextaccno++;
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Initial Balance: ";
        cin>>balance;

        if(balance<minBalance){
            cout<<"Minimum balance is 500. Setting to 500."<<endl;
            balance=500;
        }
        cout<<"Savings Account created"<<endl;
        cout<<"Your Account Number: "<<acc_no<<endl;
    }

    void deposit(double x){
        balance=balance+x;
        transactions++;
        cout<<"New Balance= "<<balance<<endl;
    }

    void deposit(double x,string msg){
        balance=balance+x;
        transactions++;
        cout<<msg<<" | New Balance= "<<balance<<endl;
    }

    void withdraw(double y){
        if(balance-y<minBalance){
            cout<<"Cannot withdraw Min balance of "<<minBalance<<" required."<<endl;
        }
        else{
            balance=balance-y;
            transactions++;
            cout<<"New Balance= "<<balance<<endl;
        }
    }

    double calcInterest(){
        double interest=(balance*interestRate)/100;
        return interest;
    }

    void applyInterest(){
        double interest=calcInterest();
        deposit(interest,"Interest applied");
    }

    void display(){
        cout<<"---- Savings Account ----"<<endl;
        cout<<"Account No: "<<acc_no<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Balance: "<<balance<<endl;
        cout<<"Interest Rate: "<<interestRate<<"%"<<endl;
        cout<<"Min Balance: "<<minBalance<<endl;
        cout<<"Transactions: "<<transactions<<endl;
    }
};

class CurrentAccount:public Account{
    double overdraftLimit;

    public:
    CurrentAccount(){
        acc_type="Current";
        overdraftLimit=10000;
    }

    void create(){
        acc_no=nextaccno++;
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Initial Balance: ";
        cin>>balance;
        cout<<"Current Account created"<<endl;
        cout<<"Your Account Number: "<<acc_no<<endl;
    }

    void deposit(double x){
        balance=balance+x;
        transactions++;
        cout<<"New Balance= "<<balance<<endl;
    }

    void deposit(double x,string msg){
        balance=balance+x;
        transactions++;
        cout<<msg<<" |New Balance= "<<balance<<endl;
    }

    void withdraw(double y){
        if(y>balance+overdraftLimit){
            cout<<"Exceeds overdraft limit of "<<overdraftLimit<<endl;
        }
        else{
            balance=balance-y;
            transactions++;
            cout<<"New Balance= "<<balance<<endl;
        }
    }

    double calcInterest(){
        return 0;
    }

    void display(){
        cout<<"---- Current Account ----"<< endl;
        cout<<"Account No: "<<acc_no<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Balance: "<<balance<<endl;
        cout<<"Overdraft Limit: "<<overdraftLimit<<endl;
        cout<<"Transactions: "<<transactions<<endl;
    }
};
    int Account::nextaccno=1001;

int main(){
    SavingsAccount sa[5];
    CurrentAccount ca[5];
    int stotal=0;
    int ctotal=0;
    int choice;

    do {
        cout<<"\n---- Bank Management System ----"<<endl;
        cout<<"1.  Create Savings Account"<<endl;
        cout<<"2.  Create Current Account"<<endl;
        cout<<"3.  Deposit"<<endl;
        cout<<"4.  Withdraw"<<endl;
        cout<<"5.  Display Account"<<endl;
        cout<<"6.  Display All Accounts"<<endl;
        cout<<"7.  Transfer Money"<<endl;
        cout<<"8.  Apply Interest (Savings)"<<endl;
        cout<<"9.  Mini Statement"<<endl;
        cout<<"10. Search by Name"<<endl;
        cout<<"0.  Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;

        if (choice==1){
            if(stotal>=5){
                cout<<"Savings account limit reached"<<endl;
            }
            else{
                sa[stotal].create();
                stotal++;
            }
        }

        else if(choice==2){
            if(ctotal>=5){
                cout<<"Current account limit reached"<<endl;
            }
            else{
                ca[ctotal].create();
                ctotal++;
            }
        }

        else if(choice==3){
            int n;double amt;
            cout<<"Enter Account Number: ";
            cin>>n;

            bool found=false;
            for(int i=0;i<stotal;i++){
                if(sa[i].getAccNo()==n){
                    cout<<"Enter Deposit Amount: ";
                    cin>>amt;
                    sa[i].deposit(amt);
                    found=true;
                }
            }
            for(int i=0;i<ctotal;i++){
                if(ca[i].getAccNo()==n){
                    cout<<"Enter Deposit Amount: ";
                    cin>>amt;
                    ca[i].deposit(amt);
                    found=true;
                }
            }
            if(!found){
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==4){
            int n;
            double amt;
            cout<<"Enter Account Number: ";
            cin>>n;

            bool found=false;
            for(int i=0;i<stotal;i++){
                if(sa[i].getAccNo()==n){
                    cout<<"Enter Withdraw Amount: ";
                    cin>>amt;
                    sa[i].withdraw(amt);
                    found=true;
                }
            }
            for(int i=0;i<ctotal;i++){
                if(ca[i].getAccNo()==n){
                    cout<<"Enter Withdraw Amount: ";
                    cin>>amt;
                    ca[i].withdraw(amt);
                    found=true;
                }
            }
            if(!found){
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==5){
            int n;
            cout<<"Enter Account Number: ";
            cin>>n;

            bool found=false;
            for(int i=0;i<stotal;i++){
                if(sa[i].getAccNo()==n){
                    sa[i].display();
                    found = true;
                }
            }
            for(int i=0;i<ctotal;i++){
                if(ca[i].getAccNo()==n){
                    ca[i].display();
                    found=true;
                }
            }
            if(!found){
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==6){
            cout<<"\n== All Savings Accounts =="<<endl;
            for(int i=0;i<stotal;i++){
                sa[i].display();
                cout<<endl;
            }

            cout<<"== All Current Accounts =="<<endl;
            for(int i=0;i<ctotal;i++){
                ca[i].display();
                cout<<endl;
            }
            
        }

        else if(choice==7){
            int from,to;double amt;
            cout<<"From Account No: ";
            cin>>from;
            cout<<"To Account No: ";
            cin>>to;
            cout<<"Amount: ";
            cin>>amt;

            Account *src=NULL,*dst=NULL;

            for(int i=0;i<stotal;i++){
                if(sa[i].getAccNo()==from){
                    src=&sa[i];
                }
                if(sa[i].getAccNo()==to){
                    dst=&sa[i];
                }
            }
            for(int i=0;i<ctotal;i++){
                if(ca[i].getAccNo()==from){
                    src=&ca[i];
                }
                if(ca[i].getAccNo()==to){
                    dst=&ca[i];
                }
            }

            if(src==NULL || dst==NULL){
                cout<<"Account not found!"<<endl;
            }
            else{
                src->transfer(*dst,amt);
            }
        }

        else if(choice==8){
            if(stotal==0){
                cout<<"No savings accounts found"<<endl;
            }
            else{
                for(int i=0;i<stotal;i++){
                    cout<<sa[i].getName()<<" -> ";
                    sa[i].applyInterest();
                }
            }
        }

        else if(choice==9){
            int n;
            cout<<"Enter Account Number: ";
            cin>>n;

            bool found=false;
            for(int i=0;i<stotal;i++){
                if(sa[i].getAccNo()==n){
                    sa[i].miniStatement();
                    found=true;
                }
            }
            for(int i=0;i<ctotal;i++){
                if(ca[i].getAccNo()==n){
                    ca[i].miniStatement();
                    found=true;
                }
            }
            if(!found){
                cout<<"Account not found!"<<endl;
            }
        }

        else if(choice==10){
            string n;
            cout<<"Enter Name to search: ";
            cin>>n;

            bool found=false;
            for(int i=0;i<stotal;i++){
                if(sa[i].getName()==n){
                    sa[i].display();
                    found=true;
                }
            }
            for(int i=0;i<ctotal;i++){
                if(ca[i].getName()==n){
                    ca[i].display();
                    found=true;
                }
            }
            if(!found){
                cout<<"No account found with name: "<<n<<endl;
            }
        }

    }while(choice!=0);

    cout<<"Thank you"<<endl;
}