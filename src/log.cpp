#include "Log.h"

vector<string> vectorLog;

void LogPush(string text){
    if(SHOW_LOG || MAKE_LOG){
        time_t t = time(0);
        tm* now = localtime(&t);
        //text = asctime(now->)+text;
    }
    if(SHOW_LOG){
        cout<<text<<endl;
    }
    if(MAKE_LOG){
        vectorLog.push_back(text);
    }
}

void LogWrite(){
    if(MAKE_LOG){
        ofstream file;
        string line;

        file.open("log.log");

        // get actual date
        time_t t = time(0);
        tm* now = localtime(&t);
        file<<asctime(now)<<endl;

        for(int i = 0; i < vectorLog.size(); ++i){
            file<<vectorLog[i]<<endl;
        }
        file.close();
    }
}
