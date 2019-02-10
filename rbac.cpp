#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(){
    cout << "WELCOME TO CAL STATE FULLERTON" << endl;
    multimap<string,string> rbac;
    multimap<string,string>::iterator it;

    fstream URA;
    URA.open("URA.txt");
    if(URA.is_open()){
        string name, role;
        while(!URA.eof()){
        URA >> name >> role;
        rbac.insert(pair<string,string>(name,role));
        }
        URA.close();
    }

    string user;
    vector<string> user_role;
    bool loggedin = false;
    while(loggedin == false){
        cout << "login: ";
        cin >> user;
        for(it=rbac.begin(); it!=rbac.end(); it++){
            if(it->first == user){
                cout << "Welcome " << user << endl;
                pair<multimap<string,string>::iterator, multimap<string,string>::iterator>  role_range = rbac.equal_range(user);
                for(multimap<string,string>::iterator itr = role_range.first; itr != role_range.second; itr++){
                    user_role.push_back(itr->second);  
                }
                loggedin = true;
                break;
            }
        }
        if(!loggedin){
            cout << "ERROR: user " << user << " is not in the database" << endl;
        }
        
    }
   

    multimap<string,string> role_action;
    multimap<string,string>::iterator it2;
    fstream PRA;
   
    PRA.open("PRA.txt");
    string action, role, object;
    if(PRA.is_open()){
        while(!PRA.eof()){
        PRA >> role >> action >> object;
        role_action.insert(pair<string,string>(role,action+object));
        }
        PRA.close();
    }
     
     fstream HR;
     vector<string> hr_action;
     int num =0;
    
     int count =0;
     HR.open("HR.txt");
     if(HR.is_open()){
         string s_role, j_role;
         
         
         do{ 
            while(!HR.eof()){
                HR >> s_role >> j_role;
                num++;
                pair<multimap<string,string>::iterator, multimap<string,string>::iterator>  action_range = role_action.equal_range(j_role);
                for(multimap<string,string>::iterator ita = action_range.first; ita != action_range.second; ita++){
                    hr_action.push_back(ita->second);
                }
                for(auto a : hr_action){
                    role_action.insert(pair<string,string>(s_role,a));
                }
                hr_action.clear();
            }
            HR.clear();
            HR.seekg(0) ;
            count++;
            
         }while( count < (num-(count-1)*num));
         HR.close();
    }
    string command;
    while(true){
        bool access = false;
        cout << "give command  (\"exit program\") to exit " << endl;
        cin >> action >> object;
        command = action + object;
        if(command == "exitprogram") break;
        vector<string> permit_role;
        for(multimap<string,string>::iterator it = role_action.begin(); it != role_action.end(); it++){
            if(it->second == command){
                permit_role.push_back(it->first);
            }
        }
        vector<string> match_role;
        bool t = false;
        for(string pr : permit_role){
            for(string ur: user_role){
                if(pr == ur){
                    for( string x : match_role){
                        if(x == ur && match_role.size() != 0) t = true;
                    }
                    if(!t) match_role.push_back(ur);
                    
                    access = true;
                    break;
                }
            //if(access == true) break;
            }
        

        }
        if(access == false) cout << "ACCESS DENIED: you are not authorized to perform this action!" << endl;
        else {
            cout << "Access granted by virtue of roles: ";
            for(auto i : match_role) {
                cout << i << " ";
            }
            cout << endl; 
        }
    }
    
}