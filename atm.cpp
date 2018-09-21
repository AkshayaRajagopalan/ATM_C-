# include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class ATM{
  public:
  void CreatingNewAccount(string newUName, string newUPass);
  void AccountLogin(string logUName, string logUPass);
  void DepositingMoney(double depMoney);
  void WithdrawingMoney(double withMoney);
  void SetAccLogin(int setAccLoc);
  void SetLastMove(int accID, double amt);
  void SetBegBal(int accID);
  void SetLastOp(int accID, char userinp);
  int GetAccLog() const;
  void AccMenu();
  double GetLastMove(int accID) const;
  double GetAccBal(int accID) const;
  double GetBegBal(int accID) const;
  char GetLastOp(int accID) const;
  string GetUsername(int accID) const;

  private:
  int LogLoc;
  double accBal;
  double begBal;
  double lastMove;
  char lastOp;
  string username;
  string password;

};

ATM account;

vector<ATM> AccList;

void AccMenu();
void UserMenu();

void ATM :: SetAccLogin(int setAccLoc){
  LogLoc = setAccLoc;
  return;
}

int ATM :: GetAccLog() const{
  return LogLoc;
}

void ATM :: CreatingNewAccount(string newUName, string newUPass){
  int AccListSize = AccList.size();

  AccList[AccListSize - 1].accBal = 0.0;
  AccList[AccListSize - 1].username = newUName;
  AccList[AccListSize - 1].password = newUPass;
}

void ATM :: AccountLogin(string logUName, string logUPass){
  int AccListSize = AccList.size();
  bool AccLogSucc = false;
  int accLoc = 0;

  for(int i = 0; i<AccListSize; i++){
    if(logUName == AccList[i].username){
      if(logUPass == AccList[i].password){
        AccLogSucc = true;
        accLoc = i;
      }
    }
  }
  if(AccLogSucc != true){
    std::cout << "--------------SORRY, LOGIN FAILED !-----------" << '\n';
    UserMenu();
  }
  else {
    SetAccLogin(accLoc);
    std::cout << "--------------LOGIN SUCCESSFUL !-----------" << '\n';
    AccMenu();
  }
  return;

}

void ATM::DepositingMoney(double depMoney){
  AccList[LogLoc].accBal += depMoney;
  return;
}

void ATM::WithdrawingMoney(double withMoney){
  AccList[LogLoc].accBal -= withMoney;
  return;
}

double ATM::GetAccBal(int accID) const{
  return AccList[LogLoc].accBal;
}

void ATM::SetLastMove(int accID, double amt){
  AccList[accID].lastMove = amt;
}

void ATM::SetBegBal(int accID){
  AccList[accID].begBal = AccList[LogLoc].accBal;
}

void ATM::SetLastOp(int accID, char userinp){
  AccList[accID].lastOp = userinp;
}

double ATM:: GetLastMove(int accID) const{
  return AccList[accID].lastMove;
}

double ATM::GetBegBal(int accID) const{
  return AccList[accID].begBal;
}

char ATM::GetLastOp(int accID) const{
  return AccList[accID].lastOp;
}

string ATM::GetUsername(int accID) const{
  return AccList[GetAccLog()].username;
}

void UserMenu(){

  char choice;
  string selUID;
  string selUPass;
  string UNameChk;
  string UPassChk;

  std::cout << "1 - To Login " << '\n';
  std::cout << "2 - To Create A New Account" << '\n';
  std::cout << "3 - To quit" << '\n';
  std::cout << "Please enter your choice: ";
  std::cin >> choice;

  if ( choice == '1'){
    std::cout << "Please enter your username :  " ;
    std::cin >> UNameChk;
    std::cout << "Please enter your password: ";
    std::cin >> UPassChk;

    account.AccountLogin(UNameChk, UPassChk);
  }
  else if( choice == '2'){
    std::cout << "Please enter your username: ";
    std::cin >> selUID;
    std::cout << "Please enter your password: ";
    std::cin >> selUPass;

    AccList.push_back(account);

    account.CreatingNewAccount(selUID, selUPass);

    std::cout << "Yaay!! Your account has been set-up" << '\n';

    UserMenu();
  }

  else if(choice == '3'){
    std::cout << "QUITTING ...... "<< '\n';
  }
  else{
    std::cout << "Please enter a valid choice please!" << '\n';
    UserMenu();
  }
  return;
}

void ATM::AccMenu(){
  char userinp;
  double depAmt;
  double withAmt;

  std::cout << "1 - To Deposit Money" << '\n';
  std::cout << "2 - To Withdraw Money" << '\n';
  std::cout << "3 - To Request Balance" << '\n';
  std::cout << "4 - To Logout" << '\n';
  std::cout << "5 - To Quit" << '\n';
  std::cout << "Please enter your choice here: ";
  std::cin >> userinp;

  if(userinp == '1'){
    SetBegBal(GetAccLog());
    while (true){
      std::cout << "Amount you want to deposit: $";
      std::cin >> depAmt;
      if(depAmt<0.0){
        std::cout << "Please enter a positive amount!!" << '\n';
      }
      else{
        break;
      }
    }
    SetLastMove(GetAccLog(), depAmt);
    SetLastOp(GetAccLog(), userinp);
    DepositingMoney(depAmt);
    AccMenu();
  }
  else if(userinp == '2'){
    while (true){
    std::cout << "Amount you want to wthdraw: $" ;
    std::cin >> withAmt;
    if (withAmt<0.0){
      std::cout << "Please enter a positive amount!!" << '\n';
    }
    else{
      break;
    }
  }

    if(withAmt > GetAccBal(GetAccLog())){
      std::cout << "--------------Insufficient Funds-----------" << '\n';
    }

    else{
      SetBegBal(GetAccLog());
      SetLastMove(GetAccLog(), withAmt);
      SetLastOp(GetAccLog(), userinp);
      WithdrawingMoney(withAmt);
    }
    AccMenu();
  }
  else if (userinp == '3'){
    std::cout << "Beginning Balance: $" << fixed<<setprecision(3)<< GetLastMove(GetAccLog())<<'\n';
    if (GetLastOp(GetAccLog()) == '1'){
      std::cout << "Deposited Money: $" <<fixed << setprecision(3)<<GetLastMove(GetAccLog())<< '\n';
    }
    else if (GetLastOp(GetAccLog()) == '2'){
      std::cout << "Withdrawn Money: $" <<fixed << setprecision(3)<<GetLastMove(GetAccLog())<< '\n';
    }
    std::cout << "Your current balance is: $" <<fixed << setprecision(3)<<GetAccBal(GetAccLog())<< '\n';
    AccMenu();
  }
  else if(userinp == '4'){
    std::cout << "You have successfully logged out of your account, " <<GetUsername(GetAccLog())<<"!"<< '\n';
    UserMenu();
  }
  else if(userinp == '5'){
    std::cout << "Thanks for Banking with CIFC, " <<GetUsername(GetAccLog())<< '\n';
  }
  else{
    std::cout << "Please enter a valid choice." << '\n';
    AccMenu();
  }
  return;
}


int main() {

    cout << "Welcome to COP2513.F16’s ATM Machine" << endl;
    cout << "Please select an option from the menu below: " << endl ;

    UserMenu();
}
