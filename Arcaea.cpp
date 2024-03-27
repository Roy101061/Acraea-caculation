#include <bits/stdc++.h>
#define LevelCount 6 //5+1 for blank

using namespace std;

ifstream in;
ofstream out;
string LevelNames[LevelCount], SongList[500];
float DB[500][LevelCount];
int B30info[LevelCount];

void readfail(){
    if(in.fail()){
        cout<<"R30 input fail!";
        exit(1);
    }
}

void setupDB(){
    int i=1;  //start from 2(1) due to spreadsheet
    
    //song DB
    in.open("Arcaea Potential Cal.csv");
    readfail();
    for(int i=0; i<LevelCount; i++){
        in>>LevelNames[i];
    }
    while(!in.eof()){
        i++;
        in>>SongList[i];
        for(int n=1; n<LevelCount; n++){
            in>>DB[i][n];
        }
    }

    //R30 DB
    in.open("R30.csv");
    readfail();
    deque<string [2]> R30Song;
    deque<float [6]> R30Rec;
    while(!in.eof()){
        string nametemp[2];
        float numtemp[6];

        for(int n=0; n<2; n++)
            in>>nametemp[n];
        R30Song.push_back(nametemp);

        for(int n=0; n<6; n++)
            in>>numtemp[n];
        R30Rec.push_back(numtemp);
    }

    //B30 DB
    in.open("B30.csv");
    readfail();
    deque<string [2]> B30Song;
    deque<float [6]> B30Rec;
    while(!in.eof()){
        string nametemp[2];
        float numtemp[6];

        for(int n=0; n<2; n++)
            in>>nametemp[n];
        B30Song.push_back(nametemp);

        for(int n=0; n<6; n++)
            in>>numtemp[n];
        B30Rec.push_back(numtemp);
    }

    //B30info
    in.open("B30info.csv");
    readfail();
    for(int i=1; i<LevelCount; i++)
        in>>B30info[i];

}

int main(){
    setupDB();
    string song,level;
    int userdata[5];

    //UI
    cout<<"Enter your score:"<<endl<<"(song,level,score,MaxPureCount,PureCount,FarCount,LostCount)";
    cin>>song>>level;
    for(int i=0; i<5; i++)
        cin>>userdata[i];
    

    return 0;
}