#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

#define scramblelenght 25
#define numberofstickers 24
#define numberofpieces_edges 12
#define numberofpieces_corners 8

typedef int array24 [numberofstickers];
typedef int matrix6by8 [6][8];
typedef int matrix6by12 [6][12];
const string parity_path="src/parityAlgs.csv";
const string corners_path="src/cornerAlgs.csv";
const string edges_path="src/edgeAlgs.csv";
const string emptyscramble="";
const string scramblemoves[3][6]= {{"U ","U2 ","U' ","D ","D2 ","D' "},{"F ","F2 ","F' ","B ","B2 ","B' "},{"R ","R2 ","R' ","L ","L2 ","L' "}};
const array24 solvedstate_corners= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
const matrix6by12 stickerspermutations_corners ={{0,3,9,6,1,4,10,7,2,5,11,8},{12,15,18,21,13,16,19,22,14,17,20,23},{0,17,12,5,1,15,13,3,2,16,14,4},{6,10,21,19,7,11,22,20,8,9,23,18},{0,7,18,16,1,8,19,17,2,6,20,15},{3,14,21,11,4,12,22,9,5,13,23,10}};
const string letters_corners= "0SFMXBRVPUNLITCOYJEKDAHZ";
const array24 alphabet_corners={23,16,5,11,22,1,15,19,14,18,12,10,8,17,2,13,20,6,4,9,3,0,7,21};
const array24 solvedstate_edges= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
const matrix6by8 stickerspermutations_edges {{0,4,6,2,1,5,7,3},{12,14,18,16,13,15,19,17},{0,9,12,11,1,8,13,10},{6,23,18,21,7,22,19,20},{2,20,14,8,3,21,15,9},{4,10,16,22,5,11,17,23}};
const string letters_edges= "0XRSMNUVFJCBIYOKATEHDPLZ";
const array24 alphabet_edges={23,22,15,16,11,12,18,19,5,6,2,1,8,20,13,9,0,17,4,7,3,14,10,21};

int main(int argc, char*argv[]){

    char option;
    string aux;
    int seed1, seed2;
    int turniterator, turnlayer;
    string scramble;
    array24 scrambledstate_corners, scrambledstate_edges;
    int numbersolved_corners, newtarget_corners, cyclepiece_corners, aux_corners;
    bool issolved_corners[numberofpieces_corners];
    vector <int> path_corners;
    vector <int> twist_corners;
    int numbersolved_edges, newtarget_edges, cyclepiece_edges, aux_edges;
    bool issolved_edges[numberofpieces_edges];
    vector <int> path_edges;
    vector <int> twist_edges;   
    vector <int> parity;
    bool hasparity, hastwists_corners, hastwists_edges, isdirect_parity;

    //parsing letter pairs
    string letterpairs[529];
    if (argc > 1) {
        ifstream letterPairsFile (argv[1]);
            for (int i=0; i<529; i++){
                getline(letterPairsFile,aux,',');
                letterpairs[i] = aux;
            }
    } 
    
    //parsing algs
    string algorithms_parity[42];
    ifstream parityFile (parity_path);
        for (int i=0; i<42; i++){
            getline(parityFile,aux,',');
            algorithms_parity[i] = aux;
        }
    string algorithms_corners[441];
    ifstream cornerFile (corners_path);
        for (int i=0; i<441; i++){
            getline(cornerFile,aux,',');
            algorithms_corners[i] = aux;
        }
    string algorithms_edges[484];
    ifstream edgeFile (edges_path);
        for (int i=0; i<484; i++){
            getline(edgeFile,aux,',');
            algorithms_edges[i] = aux;
        }

    setlocale(LC_ALL, "");
    srand(time(NULL));
    while (option != 'n'){
        //reset
        scramble= emptyscramble;
        for(int i=0; i<numberofstickers; i++){
            scrambledstate_corners[i]= solvedstate_corners[i];
            scrambledstate_edges[i]= solvedstate_edges[i];
        }
        numbersolved_corners=0;
        for (int i=0; i<numberofpieces_corners; i++){
            issolved_corners[i]=false;
        }
        path_corners.clear();
        twist_corners.clear();
        numbersolved_edges=0;
        for (int i=0; i<numberofpieces_edges; i++){
            issolved_edges[i]=false;
        }
        path_edges.clear();
        twist_edges.clear();
        parity.clear();
        hasparity=false;
        hastwists_corners=false;
        hastwists_edges=false;
        isdirect_parity=false;

        //generate scramble
        seed1=rand()%3;
        for(int i= 0; i<scramblelenght; i++){
            seed1= (seed1+(rand()%2)+1)%3;
            seed2= rand()%6;
            scramble+= scramblemoves[seed1][seed2];
        //do scramble
            turniterator= 1+(seed2%3);       
            turnlayer= 2*seed1+floor(seed2/3);
            for(int j= 0; j<turniterator; j++){
                int aux_corners, aux_edges;
                aux_corners=scrambledstate_corners[stickerspermutations_corners[turnlayer][0]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][0]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][3]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][3]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][2]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][2]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][1]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][1]]=aux_corners;
                aux_corners=scrambledstate_corners[stickerspermutations_corners[turnlayer][4]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][4]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][7]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][7]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][6]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][6]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][5]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][5]]=aux_corners;
                aux_corners=scrambledstate_corners[stickerspermutations_corners[turnlayer][8]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][8]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][11]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][11]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][10]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][10]]=scrambledstate_corners[stickerspermutations_corners[turnlayer][9]];
                scrambledstate_corners[stickerspermutations_corners[turnlayer][9]]=aux_corners;
                
                aux_edges=scrambledstate_edges[stickerspermutations_edges[turnlayer][0]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][0]]=scrambledstate_edges[stickerspermutations_edges[turnlayer][3]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][3]]=scrambledstate_edges[stickerspermutations_edges[turnlayer][2]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][2]]=scrambledstate_edges[stickerspermutations_edges[turnlayer][1]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][1]]=aux_edges;
                aux_edges=scrambledstate_edges[stickerspermutations_edges[turnlayer][4]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][4]]=scrambledstate_edges[stickerspermutations_edges[turnlayer][7]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][7]]=scrambledstate_edges[stickerspermutations_edges[turnlayer][6]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][6]]=scrambledstate_edges[stickerspermutations_edges[turnlayer][5]];
                scrambledstate_edges[stickerspermutations_edges[turnlayer][5]]=aux_edges;
            }
        }

        //generate corner targets vector
        for (int i=0; i<numberofpieces_corners; i++){
            //if its solved
            if(scrambledstate_corners[3*i]==solvedstate_corners[3*i]){
                issolved_corners[i]=true;
                numbersolved_corners++;
            }
            //if its pasive
            else {
                if (scrambledstate_corners[3*i]==solvedstate_corners[3*i+1]){
                    issolved_corners[i]=true;
                    numbersolved_corners++;
                    if (i!=0){
                        twist_corners.push_back(scrambledstate_corners[3*i+1]);
                        twist_corners.push_back(scrambledstate_corners[3*i+2]);
                        hastwists_corners=true;
                    }
                } else if (scrambledstate_corners[3*i]==solvedstate_corners[3*i+2]){
                    issolved_corners[i]=true;
                    numbersolved_corners++;
                    if (i!=0){
                        twist_corners.push_back(scrambledstate_corners[3*i+2]);
                        twist_corners.push_back(scrambledstate_corners[3*i+1]);
                        hastwists_corners=true;
                    }
                }
            }
        }
        while (numbersolved_corners<numberofpieces_corners){
            for(int i=0; i<numberofpieces_corners; i++){
                //pick buffer
                if(scrambledstate_corners[3*i]!=0&&scrambledstate_corners[3*i]!=1&&scrambledstate_corners[3*i]!=2&&!issolved_corners[i]){
                    newtarget_corners=scrambledstate_corners[3*i];
                    cyclepiece_corners=i;
                    //if its not default buffer
                    if (cyclepiece_corners!=0){
                        path_corners.push_back (3*i);
                    }
                    issolved_corners[cyclepiece_corners]=true;
                    numbersolved_corners++;
                    break;
                }
            }
            //exhaust cycle
            while (floor(newtarget_corners/3)!=cyclepiece_corners){
                path_corners.push_back (newtarget_corners);
                aux_corners=floor(newtarget_corners/3);
                issolved_corners[aux_corners]=true;
                newtarget_corners= scrambledstate_corners[newtarget_corners];
                numbersolved_corners++;
                //if its not default buffer
                if (floor(newtarget_corners/3)==cyclepiece_corners && cyclepiece_corners!=0){
                    path_corners.push_back (newtarget_corners);
                }
            } 
        }
        //generate edge targets vector
        for (int i=0; i<numberofpieces_edges; i++){
            //if its solved
            if(scrambledstate_edges[2*i]==solvedstate_edges[2*i]){
                issolved_edges[i]=true;
                numbersolved_edges++;
            }
            //if its pasive
            else if(scrambledstate_edges[2*i]==solvedstate_edges[2*i+1]){
                issolved_edges[i]=true;
                numbersolved_edges++;
                if (i!=0){
                    twist_edges.push_back(scrambledstate_edges[2*i]);
                    twist_edges.push_back(scrambledstate_edges[2*i+1]);
                    hastwists_edges=true;
                }
            }
        }
        while (numbersolved_edges<numberofpieces_edges){
            for(int i=0; i<numberofpieces_edges; i++){
                //pick buffer
                if(scrambledstate_edges[2*i]!=0&&scrambledstate_edges[2*i]!=1&&!issolved_edges[i]){
                    newtarget_edges=scrambledstate_edges[2*i];
                    cyclepiece_edges=i;
                    //if its not default buffer
                    if (cyclepiece_edges!=0){
                        path_edges.push_back (2*i);
                    }
                    issolved_edges[cyclepiece_edges]=true;
                    numbersolved_edges++;
                    break;
                }
            }
            //exhaust cycle
            while (floor(newtarget_edges/2)!=cyclepiece_edges){
                path_edges.push_back (newtarget_edges);
                aux_edges=floor(newtarget_edges/2);
                issolved_edges[aux_edges]=true;
                newtarget_edges= scrambledstate_edges[newtarget_edges];
                numbersolved_edges++;
                //if its not default buffer
                if (floor(newtarget_edges/2)==cyclepiece_edges && cyclepiece_edges!=0){
                    path_edges.push_back (newtarget_edges);
                }
            } 
        }

        //generate party
        if (path_corners.size()%2!=0){
            hasparity=true;
            parity.push_back(path_corners.back());
            path_corners.erase(path_corners.end()-1);
            parity.push_back(path_edges.front());
            path_edges.erase(path_edges.begin());
        }

        //print
        cout<< "\nscramble\n"<< scramble;
        cout<< "\ncorners\n";
        for (int i= 0; i<path_corners.size()/2; i++){
            cout<< letterpairs[ (23*alphabet_corners[path_corners[2*i]])+(alphabet_corners[path_corners[2*i+1]])]; 
            cout<<" (" << letters_corners[path_corners[2*i]] <<","<< letters_corners[path_corners[2*i+1]] << ")"<<"\n";
            cout<< algorithms_corners[((path_corners[2*i]-3)*21)+ (path_corners[2*i+1]-3)]<< "\n";
        }
        if(hasparity){
            if(parity[1]==2 || parity[1]==3){
                isdirect_parity=true;
            }
            cout<< "parity\n";
            cout<< letterpairs[ (23*alphabet_corners[parity[0]])+(alphabet_edges[parity[1]])]; 
            cout<<" (" << letters_corners[parity[0]] <<","<< letters_edges[parity[1]] <<")" <<"\n";
            if (parity[1]==3){
                cout<< algorithms_parity[21+ (parity[0]-3)]<<"\n";
            } else {
                cout<< algorithms_parity[(parity[0]-3)]<<"\n";
            }
            if (!isdirect_parity){
                cout<< algorithms_edges[(parity[1]-2)]<<"\n";
            }
        }
        cout<< "edges\n";
        for (int i= 0; i<path_edges.size()/2; i++){
            cout<< letterpairs[ (23*alphabet_edges[path_edges[2*i]])+(alphabet_edges[path_edges[2*i+1]])]; 
            cout<<" (" << letters_edges[path_edges[2*i]] <<","<< letters_edges[path_edges[2*i+1]] <<")"<<"\n";
            cout<< algorithms_edges[((path_edges[2*i]-2)*22)+ (path_edges[2*i+1]-2)]<< "\n";
        }
        if (hastwists_corners){
            cout <<"corner twists\n";
            for(int i=0; i<twist_corners.size()/2; i++){
                cout<< letterpairs[ (23*alphabet_corners[twist_corners[2*i]])+(alphabet_corners[twist_corners[2*i+1]])]; 
                cout<<" (" << letters_corners[twist_corners[2*i]] <<","<< letters_corners[twist_corners[2*i+1]] <<")"<<"\n";
                cout<< algorithms_corners[((twist_corners[2*i]-3)*21)+ (twist_corners[2*i+1]-3)]<< "\n";
            }
        }
        if (hastwists_edges){
            cout <<"edge flips\n";
            for(int i=0; i<twist_edges.size()/2; i++){
                cout<< letterpairs[ (23*alphabet_edges[twist_edges[2*i]])+(alphabet_edges[twist_edges[2*i+1]])]; 
                cout<<" (" << letters_edges[twist_edges[2*i]] <<","<< letters_edges[twist_edges[2*i+1]] <<")"<<"\n";
                cout<< algorithms_edges[((twist_edges[2*i]-2)*22)+ (twist_edges[2*i+1]-2)]<< "\n";
            }
        }
        cout<< "Again? [Y/n]\n";
        cin >> option;
    }
    return 0;
}