#include <bits/stdc++.h>
#define LevelCount 5 //4+1 for blank

using namespace std;

int main(){
    string LevelNames[LevelCount], SongList[500];
    float DB[500][LevelCount];
    int i=2;  //start from 2 due to spreadsheet 

    ifstream in;
    ofstream out;
    in.open("Arcaea Potential Cal.csv");
    if(in.fail()){
        cout<<"DB input fail!";
        exit(1);
    }
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

    in.open("R30.csv");
    if(in.fail()){
        cout<<"R30 input fail!";
        exit(1);
    }
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



    return 0;
}