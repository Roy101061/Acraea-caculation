#include <bits/stdc++.h>
#include <array>
#define LevelCount 5+1 //+1 for blank
#define SongCount 378+2 //+2 to sync with spreadsheet

using namespace std;

ifstream in;
ofstream out;
string LevelNames[LevelCount], SongList[500], Stringtemp;
float DB[SongCount][LevelCount];
int B30info[LevelCount+1];

void readfail(int n){
    if(in.fail()){
        cout<<"Input fail!";
        exit(n);
    }
}

void setupDB(){
    
    //song DB
    in.open("DB.csv");
    readfail(1);
    for(int i=0; i<LevelCount; i++){
        getline(in, LevelNames[i], ',');
    }

    int i=1;  //start from 2(1) due to spreadsheet
    while(i<SongCount){
        i++;
        getline(in, SongList[i], ',');
        for(int n=1; n<LevelCount; n++){
            getline(in, Stringtemp, ',');
            DB[i][n]=stof(Stringtemp);
        }
    }
	in.close();
    
    //B30info
    in.open("B30info.csv");
    readfail(2);
    for(int i=1; i<LevelCount+1; i++){
        getline(in, Stringtemp, ',');
        B30info[i]=stof(Stringtemp);
    }
    in.close();

    cout<<endl<<"DB read success!"<<endl;

    //R30 DB
    in.open("R30.csv");
    readfail(3);
    deque<pair <string,string> > R30Song;
    deque<array <float, 6> > R30Rec;
    while(!in.eof()){
        pair<string,string> nametemp;
        array<float, 6> numtemp;

        getline(in, nametemp.first, ',');
        getline(in, nametemp.second, ',');
        R30Song.push_back(nametemp);

        for(int n=0; n<6; n++){
            getline(in, Stringtemp, ',');
            numtemp[n]=stof(Stringtemp);
        }
        R30Rec.push_back(numtemp);
    }
	in.close();

    //B30 DB
    in.open("B30.csv");
    readfail(4);
    deque<pair <string,string> > B30Song;
    deque<array <float, 6> > B30Rec;
    i=0;
    while(i<B30info[6]){
        pair<string,string> nametemp;
        array<float, 6> numtemp;

        getline(in, nametemp.first, ',');
        getline(in, nametemp.second, ',');
        B30Song.push_back(nametemp);

        for(int n=0; n<6; n++){
            getline(in, Stringtemp, ',');
            numtemp[n]=stof(Stringtemp);
        }
        B30Rec.push_back(numtemp);
        i++;
    }
    in.close();

}

int main(){
    setupDB();
    string Song,Level;
    int Userdata[5], SongNum, LevelNum;
    float Diffuculty, ppt;

    //UI
    cout<<"Enter your score:"<<endl<<"(song,level,score,MaxPureCount,PureCount,FarCount,LostCount,)"<<endl;
    getline(cin, Song, ',');
    getline(cin, Level, ',');
    for(int i=0; i<5; i++){
        getline(cin, Stringtemp, ',');
        Userdata[i]=stof(Stringtemp);
    }
    cout<<'0';
    
    for(SongNum=2; Song!=SongList[SongNum]; SongNum++);
    for(LevelNum=2; Level!=LevelNames[LevelNum]; LevelNum++);
    Diffuculty=DB[SongNum][LevelNum];
    cout<<Diffuculty;

    return 0;
}
