#include <bits/stdc++.h>
#include <array>
#define LevelCount 6 //5+1 for blank

using namespace std;

ifstream in;
ofstream out;
string LevelNames[LevelCount], SongList[500];
float DB[500][LevelCount];
int B30info[LevelCount];

void readfail(int n){
    if(in.fail()){
        cout<<"Input fail!";
        exit(n);
    }
}

void setupDB(){
    int i=1;  //start from 2(1) due to spreadsheet
    
    //song DB
    in.open("Arcaea Potential Cal.csv");
    readfail(1);
    for(int i=0; i<LevelCount; i++){
        in>>LevelNames[i];
    }
    while(!in.eof()){
        i++;
        in>>SongList[i];
        for(int n=1; n<LevelCount; n++){
            in>>DB[i][n];
        }
        cout<<i<<endl;
    }
	in.close();

    //R30 DB
    in.open("R30.csv");
    readfail(2);
    deque<pair <string,string> > R30Song;
    deque<array <float, 6> > R30Rec;
    while(!in.eof()){
        pair<string,string> nametemp;
        array<float, 6> numtemp;

        in>>nametemp.first;
        in>>nametemp.second;
        R30Song.push_back(nametemp);

        for(int n=0; n<6; n++)
            in>>numtemp[n];
        R30Rec.push_back(numtemp);
    }
	in.close();

    //B30 DB
    in.open("B30.csv");
    readfail(3);
    deque<pair <string,string> > B30Song;
    deque<array <float, 6> > B30Rec;
    while(!in.eof()){
        pair<string,string> nametemp;
        array<float, 6> numtemp;

        in>>nametemp.first;
        in>>nametemp.second;
        B30Song.push_back(nametemp);

        for(int n=0; n<6; n++)
            in>>numtemp[n];
        B30Rec.push_back(numtemp);
    }
    in.close();

    //B30info
    in.open("B30info.csv");
    readfail(4);
    for(int i=1; i<LevelCount; i++)
        in>>B30info[i];
    in.close();

    cout<<"DB read success!";
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
