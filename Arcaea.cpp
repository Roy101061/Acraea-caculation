#include <bits/stdc++.h>
#include <array>
#define LevelCount 5+1 //+1 for blank
#define SongCount 378+2+1 //+2 to sync with spreadsheet, +1 for search fail

using namespace std;

ifstream in;
ofstream out;
string LevelNames[LevelCount], SongList[500], Stringtemp;
float DB[SongCount][LevelCount];
int B30info[LevelCount+1];
deque<pair <string,string> > R30Song, B30Song;
deque<array <float, 6> > R30Rec, B30Rec;

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
        in.ignore();
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
        in.ignore();
    }
	in.close();

    //B30 DB
    in.open("B30.csv");
    readfail(4);
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
        in.ignore();
    }
    in.close();

}

int main(){
    setupDB();
    string Song,Level;
    int Userdata[5], SongNum, LevelNum, SearchRec, SearchEnd, temp;
    float Diffuculty, ppt;
    bool recB30, recR10;
    pair<string, string> addSong;
    array<float, 6> addRec;

    //UI
    cout<<"Enter your score:"<<endl<<"(song,level,score,MaxPureCount,PureCount,FarCount,LostCount,)"<<endl;
    getline(cin, Song, ',');
    getline(cin, Level, ',');
    for(int i=0; i<5; i++){
        getline(cin, Stringtemp, ',');
        Userdata[i]=stof(Stringtemp);
    }
    
    for(SongNum=2; Song!=SongList[SongNum] && SongNum<SongCount; SongNum++);
    for(LevelNum=1; Level!=LevelNames[LevelNum] && LevelNum<LevelCount; LevelNum++);
    Diffuculty=DB[SongNum][LevelNum];
    for(int i=0; i<6; i++)
        addRec[i]=Userdata[i];
    addSong.first=Song;
    addSong.second=Level;

    
    if(Diffuculty!=0){
        if(Userdata[0]>=10000000){
            ppt=Diffuculty+2;
        }
        else if(Userdata[0]>=9800000){
            ppt=Diffuculty+1+((float(Userdata[0])-9800000)/200000);
        }
        else{
            ppt=Diffuculty+((float(Userdata[0])-9500000)/300000);
        }
        cout<<"ppt search result: "<<ppt<<endl<<"Add B30/R10 record?"<<endl;
        cin>>recB30;
        cin.ignore();
        cin>>recR10;
        if(recB30){
            SearchRec=0; SearchEnd=0;
            for(temp=0; temp<LevelNum; temp++){
                SearchRec+=B30info[temp];
                SearchEnd+=B30info[temp];
            }
            SearchEnd+=B30info[temp];

            for(temp=SearchRec; temp<SearchEnd; temp++){
                if(B30Song[temp].first==Song)
                    break;
            }

            if(temp==SearchEnd){  //no rec found
                    B30Song.insert(B30Song.begin()+temp, addSong);
                    B30Rec.insert(B30Rec.begin()+temp, addRec);
                    cout<<"New record added!"<<endl;
                }
                else{
                    if(B30Rec[temp][0]<=Userdata[0]){
                        for(int i=0; i<6; i++){
                            B30Rec[temp][i]=Userdata[i];
                            cout<<"Record exist! PB updated."<<endl;
                        }
                    }
                    else   
                        cout<<"Record exist, but not PB."<<endl;
                }

        }
        if(recR10){
            if(R30Rec.size()==30){
                R30Rec.pop_front();
                R30Song.pop_front();
            }
            R30Rec.push_back(addRec);
            R30Song.push_back(addSong);
            cout<<"R10 updated!"<<endl;
        }
    }
    else{
        cout<<"Can't found Song/Level.";
    }

    return 0;
}
