//LOGIN AND REGISTRATION SERIOUS : )

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
    using namespace std;
    
class start {

    public:
        string username,password,securityQuestion,answer;
        char choice;

    void display_SuccessfulLogin(){
            cout<<"TAHNIAH ANDA BERJAYA DAN KODING INI BERFUNGSI";
    }
    //DISPLAY THE FUNCTIONS INTERFACE
    void display(){
        cout<<"----------WELCOME TO FACEBOOK----------"<<endl;
        cout<<"__________________________________________"<<endl;
        cout<<"|"<<"1. Login"<<setw(33)              <<"|"<<endl;
        cout<<"|"<<"2. Register"<<setw(30)           <<"|"<<endl;
        cout<<"|"<<"3. Forgot Password"    <<setw(23)<<"|"<<endl;
        cout<<"|"<<"4. Exit"<<setw(34)               <<"|"<<endl;
        cout<<"|________________________________________|"<<endl;
        do{
        cout<<"SELECT : ";cin>>choice;
        cin.ignore();
        if(Selection(choice)){
            cout<<"Invalid key"<<endl;
            cout<<"PLEASE TRY AGAIN"<<endl;
            Sleep(800);
            system("cls");
            //RECURSION BABY
            display();
            }
        }while(Selection(choice));
        Controller(choice);
    }

    void login(){
        string name,pass;
        int count = 0;
        cout<<"---------LOGGING IN---------"<<endl;
        cout<<"Username : ";getline(cin,username);
        cout<<"Password : ";getline(cin,password);
        ifstream masuk("database.txt");
        password = Cypher_And_Decypher(password,'n');
        while(masuk>>name>>pass>>securityQuestion){
            getline(masuk,answer);
            if(name == username && pass == password){
                count = 1;
                break;
            }
        }
        if(count == 1){display_SuccessfulLogin();return;} 
        else{cout<<"Wrong username or password"<<endl;Sleep(800);system("cls");display();return;}   
    }


    void Register(){
        string answer;
        char question;
        do{
        cout<<"-----REGISTRATION-----"<<endl;
        cout<<"Username : ";getline(cin,username);
        if(int(username.find(" ")) != -1 || username.empty()){
        cout<<"The username cannot have any spaces or cannot be empty!!";
        Sleep(800);
        system("cls");
        Register();
        }
        }while(int(username.find(" ")) != -1 || username.empty());
        //BLOCK #1 SO THERE ARE NO ACCOUNTS WITH THE SAME USERNAME
        if(AccExist(username) == true){
            cout<<"An account with that username already exist"<<endl;
            cout<<"Do you want to try again ? "<<endl;
            cout<<"Enter choice (Y/y = yes , N/n = no):";cin>>choice;
            cin.ignore();
               //ASK THE USER IF HE WANTS TO TRY AGAIN
        if(toupper(choice) == 'Y'){
            system("cls");
            Register();
        }
        else{
            
            system("cls");
            display();
             }
        }
        else{
        do{
        cout<<"Password : ";getline(cin,password);
        if(password == "exit"){exit(0);}
        if(int(password.find(" ")) != -1 || password.empty()){
            cout<<"Password cannot have any spaces or it cannot be empty";
            Sleep(800);
            system("cls");
            cout<<"-----REGISTRATION-----"<<endl;
            cout<<"Username : "<<username<<endl;
        }
        }while(int(password.find(" ")) != -1 || password.empty()); 
        cout<<"\n_____________________\n|                   |\n| Security Question |\n|___________________|\n| 1.Your birthdate  |\n| 2.Your hometown   |\n| 3.Your secret     |\n|___________________|\n\nPick one :";cin>>question;
        cin.ignore();
        switch (question)
        {
        case '1' : cout<<"Your birthdate ?";break;
        case '2' : cout<<"Your hometown ?";break;
        case '3' : cout<<"Your secret ?";break;
        default: cout<<"Pls pick the right choices next time"; Sleep(800); system("cls");display();return;
        }
        do{
        cout<<"\nAnswer : ";getline(cin,answer);
        if(answer.empty()){
            cout<<"Pls put an answer !"<<endl;
        }
        }while(answer.empty());
        //STORE THE ACCOUNT
        ofstream isi("database.txt",ios::app);
        isi<<username<<" "<<Cypher_And_Decypher(password,'n')<<" "<<question<<" "<<answer<<endl;
        }
        cout<<"\n\nRegistration is successful !!"<<endl;
        Sleep(800);
        system("cls");
        display();
        return;


    }

    void Forgot(){
        string name,question,jawapan;
        int exist = 0;
        cout<<"==========FORGOT PASSWORD=========="<<endl;
        cout<<"Username : ";cin>>username;
        cin.ignore();
        ifstream data("database.txt");
        while(data>>name>>password>>securityQuestion>>answer){
            if(username == name){
                exist = 1;
                if(securityQuestion == "1"){question = "Your birthday ?";}
                if(securityQuestion == "2"){question = "Your hometown ?";}
                if(securityQuestion == "3"){question = "Your secret   ?";}
                cout<<"Your question is : "<<question<<endl;
                cout<<"Answer : ";getline(cin,jawapan);
                if(jawapan == answer){
                    cout<<"Your password is : "<<Cypher_And_Decypher(password,'d');
                }
                else{
                    cout<<"Wrong answer";Sleep(800);system("cls");display();return;
                }
                break;
            }
            

        }
        if(exist == 0){
            cout<<"That acc doesnt exist !";
            system("cls");
            Sleep(800);
            display();
            return;
        }


    }
    //CONTROL WHERE TO GO
    void Controller(char tentu){
        system("cls");
        if(tentu == '1'){login();}
        if(tentu == '2'){Register();}
        if(tentu == '3'){Forgot();}
        if(tentu == '4'){cout<<"Program has exited\nThank you for using this program";exit(0);}
 
}
//CHECK IF ACCOUNT WITH THE NAME EXIST (USED IN Register() Function)
bool AccExist(string accname){
    string name;
    bool res = false;
    ifstream baca("database.txt");
    while(baca>>name>>password>>securityQuestion>>answer){
        if(accname == name){
            res = true;
        }
    }
    return res;
}
//ENCRYPT AND DECRYPT THE PASSWORD
string Cypher_And_Decypher(string a,char decide){
    int bump = 1;
    int c = bump / 26;
    bump = bump - 26 * c;
    if( decide == 'd'){
         bump = 26 - bump;
    }
  string res = "";
  for(int i = 0;i < a.length();i++){
    int b = (int)a[i];
      //HURUF BESAR
    if(b >= 65 && b <= 90){
      b = b + bump;
      if(b > 90){
        b = b - 26;
        }
      }
      //HURUF KECIL
    if(b >= 97 && b <= 122){
      b = b + bump;
      if(b > 122){
        b = b - 26;
          }
        }
    res = res + (char)b;
    }
    return res;
  }
bool Selection(char Select){ return Select != '1' && Select != '2' && Select != '3' && Select != '4';}

};
int main(){
    start obj;
    obj.display();
    return 0;
  }

  
