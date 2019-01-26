#include"Game.hpp"

int main(int argc, char const *argv[])
{
    Game adventure;
    string input;
    vector<string> words;
    cout<<"Welcome!\n";
    while(1){
        cout<<adventure.retDescription();
        cout<<adventure.retDialogue();
        adventure.checkKeyPointAndDo();
        if(adventure.checkWinOrLose())
                break;
        while(1){
            int check = 1;
            getline(cin, input);
            while(input.find(" ") != string::npos){
                words.push_back(input.substr(0,input.find(" ")));
                input.erase(0, input.find(" ")+1);
            }
            words.push_back(input);
            if(words[0] == "help")
                cout<<adventure.retHelp()<<endl;
            else if(words[0] == "go"){
                if(!adventure.moveCharacter("Player", words[1])){
                    cout<<"Unexited exit! Please reinput!\n";
                    check = -1;
                }
                else
                    adventure.moveCharacter("Monster", "Random");
            }
            else if(words[0] == "stay"){
                adventure.moveCharacter("Monster", "Random");
            }
            else if(words[0] == "bye")
                goto END;
            else{
                cout<<"What? Please reinput!\n"<<"If you don't know what to input, you carn type \"help\" to get help information\n";
                check = -1;
            }
            words.clear();
            input.clear();
            if(check != -1)
                break;
        }
        cout<<endl<<endl<<endl;
    }
    END:
    return 0;
}