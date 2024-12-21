#include<bits/stdc++.h>
#include<sstream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;
string getUserInput(){
    cout<<"custom_t ";
    string input;
    getline(cin,input);
    return input;
}
//split the input into the command and arguments 
vector<string> parseInput(const string& input){
    istringstream iss(input);
    vector<string> tokens;
    string token;
    while(iss >> token){
        tokens.push_back(token);
    }
    return tokens;
}
void executeCommand(const vector<string>& args){
    if(args.empty()){
        return;
    }
    pid_t pid=fork();
    if(pid == 0){
        vector<char*> c_args;
        for(const auto& arg: args){
            c_args.push_back(const_cast<char*>(arg.c_str()));
        }
        c_args.push_back(nullptr);
        execvp(c_args[0],c_args.data());
        perror("execvp failed");
        exit(1);
    }
    else if(pid > 0){
        int status;
        waitpid(pid,&status,0);
    }
    else{
        perror("fork failed");
    }
}
int main(int argc,char* argv[]){
    if(argc == 1){
         system("gnome-terminal -- bash -c './terminal run; exec bash'");
         return 0;
    }
    while(true){
        string input=getUserInput();
        if(input == "exit"){
            break;
        }
        vector<string> args=parseInput(input);
        executeCommand(args);
    }
    return 0;
}