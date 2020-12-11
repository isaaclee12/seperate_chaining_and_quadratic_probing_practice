#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <ctime>
#include "Video_Game.h"
#include "SeperateChaining.h"
#include "Probing.h"
#include "Node.h"
using namespace std;

unsigned long hornerHash(string key, unsigned long tableSize) {
    unsigned long hashVal = 0;
    for (char letter : key) {
        hashVal = hashVal * 37 + letter;
    }
    return hashVal % tableSize;
}

//sdbm taken from https://stackoverflow.com/questions/14409466/simple-hash-functions
unsigned long sdbmHash(string key, unsigned long tableSize) {
    unsigned long hashVal = 0;
    for (char letter : key){
        hashVal = letter + (hashVal << 6) + (hashVal << 16) - hashVal;
    }

    return hashVal % tableSize;
}

string videoGameKey(Video_Game vg) {
    return vg.getName();
}

string otherVideoGameKey(Video_Game vg) {
    return vg.getGenre();
}

int main() {
    //Establish header class and vector
    Video_Game project;
    vector<Video_Game> video_games;

    //Read csv file into vector
    project.readGamesFromFile("vgsales.csv",video_games);

    //TIME VARS
    clock_t start;
    double duration;


    //PARTS A & B

    /*
     * SEPERATE CHAINING
     */

    //Establish Hash Algorithms
    int size1 = 503;
    int size2 = 1009;
    int size3 = 10007;
    int size4 = 16573; //first prime number before video_games.size()
    int size5 = 46601; //first prime number after video_games.size()

    //Establish Hash Tables
    SeparateChaining<Video_Game> vgSepChain1(size1,videoGameKey);
    SeparateChaining<Video_Game> vgSepChain2(size2,videoGameKey);
    SeparateChaining<Video_Game> vgSepChain3(size3,videoGameKey);
    SeparateChaining<Video_Game> vgSepChain4(size4,videoGameKey);
    SeparateChaining<Video_Game> vgSepChain5(size5,videoGameKey);

    //Establish Alternate Hash Tables
    SeparateChaining<Video_Game> vgSepChainAltHash(size5,videoGameKey);
    SeparateChaining<Video_Game> vgSepChainAltKey(size5,otherVideoGameKey);
    SeparateChaining<Video_Game> vgSepChainAltHashAltKey(size5,otherVideoGameKey);

    //Establish Probing Tables
    Probing<Video_Game> vgProbing1(size1,videoGameKey);
    Probing<Video_Game> vgProbing2(size2,videoGameKey);
    Probing<Video_Game> vgProbing3(size3,videoGameKey);
    Probing<Video_Game> vgProbing4(size4,videoGameKey);
    Probing<Video_Game> vgProbing5(size5,videoGameKey);

    //Establish Alternate Probing Tables
    Probing<Video_Game> vgProbingAltHash(size5,videoGameKey);
    Probing<Video_Game> vgProbingAltKey(size5,otherVideoGameKey);
    Probing<Video_Game> vgProbingAltHashAltKey(size5,otherVideoGameKey);


    //Establish counters
    int numSepChain1Reads = 0;
    int numSepChain2Reads = 0;
    int numSepChain3Reads = 0;
    int numSepChain4Reads = 0;
    int numSepChain5Reads = 0;
    int numSepChain6Reads = 0;
    int numSepChain7Reads = 0;
    int numSepChain8Reads = 0;
    vector<int> sepChainReadsVector;

    // ************* 1 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgSepChain1.insert(video_games[i], numSepChain1Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size1 << " Seperate Chaining Inserts is: " << numSepChain1Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain1Reads);

    // ************* 2 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgSepChain2.insert(video_games[i], numSepChain2Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size2 << " 1009 Seperate Chaining Inserts is: " << numSepChain2Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain2Reads);

    // ************* 3 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgSepChain3.insert(video_games[i], numSepChain3Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size3 << " 10007 Seperate Chaining Inserts is: " << numSepChain3Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain3Reads);

    // ************* 4 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgSepChain4.insert(video_games[i], numSepChain4Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size4 << " Seperate Chaining Inserts is: " << numSepChain4Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain4Reads);

    // ************* 5 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgSepChain5.insert(video_games[i], numSepChain5Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " 16603 Seperate Chaining Inserts is: " << numSepChain5Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain5Reads);


    //SEPARATE CHAINING, DIFFERENT HASHING FUNCTION
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgSepChainAltHash.altInsert(video_games[i], numSepChain6Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " sbdm Hash Seperate Chaining Inserts is: " << numSepChain6Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain6Reads);

    //SEPARATE CHAINING, DIFFERENT KEY
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgSepChainAltKey.insert(video_games[i], numSepChain7Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " alt key Seperate Chaining Inserts is: " << numSepChain7Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain7Reads);

    //SEPARATE CHAINING, DIFFERENT HASHING FUNCTION, DIFFERENT KEY
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " sbdm Hash w/ alt key Seperate Chaining Inserts is: " << numSepChain8Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    sepChainReadsVector.push_back(numSepChain8Reads);



    /*
     * QUADRATIC PROBING
     */

    //Establish counters
    int numProbing1Reads = 0;
    int numProbing2Reads = 0;
    int numProbing3Reads = 0;
    int numProbing4Reads = 0;
    int numProbing5Reads = 0;
    int numProbing6Reads = 0;
    int numProbing7Reads = 0;
    int numProbing8Reads = 0;
    vector<int> probingReadsVector;

    // ************* 1 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbing1.insert(video_games[i], numProbing1Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size1 << " Probing Inserts is: " << numProbing1Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing1Reads);

    // ************* 2 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbing2.insert(video_games[i], numProbing2Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size2 << " Probing Inserts is: " << numProbing2Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing2Reads);

    // ************* 3 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbing3.insert(video_games[i], numProbing3Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size3 << " Probing Inserts is: " << numProbing3Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing3Reads);

    // ************* 4 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbing4.insert(video_games[i], numProbing4Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size4 << " Probing Inserts is: " << numProbing4Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing4Reads);

    // ************* 5 ************* //
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbing5.insert(video_games[i], numProbing5Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " Probing Inserts is: " << numProbing5Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing5Reads);

    //PROBING, DIFFERENT HASHING FUNCTION
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbingAltHash.altInsert(video_games[i], numProbing6Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " sbdm Hash Probing Inserts is: " << numProbing6Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing6Reads);

    //PROBING, DIFFERENT KEY
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbingAltKey.insert(video_games[i], numProbing7Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " alt key Probing Inserts is: " << numProbing7Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing7Reads);

    //PROBING, DIFFERENT HASHING FUNCTION, DIFFERENT KEY
    //Start Timer
    start = clock();
    //Insert all the things
    for (int i=0; i < video_games.size(); ++i) {
        vgProbingAltHashAltKey.altInsert(video_games[i], numProbing8Reads);
    }
    //PRINT TIME
    duration = 100*(( clock() - start ) / (double) CLOCKS_PER_SEC);
    cout << " The # of reads w/ " << size5 << " sbdm Hash w/ alt key Probing Inserts is: " << numProbing8Reads
         << ". DURATION: " << duration << "ms" << endl;
    //Push back into vector
    probingReadsVector.push_back(numProbing8Reads);

    /*
     * READS -> CSV FILES
     */
    ofstream readsFile;
    readsFile.open("../reads.csv");

    //Header
    readsFile << ",";
    readsFile << size1;
    readsFile << ",";
    readsFile << size2;
    readsFile << ",";
    readsFile << size3;
    readsFile << ",";
    readsFile << size4;
    readsFile << ",";
    readsFile << size5;
    readsFile << ",";
    readsFile << size5 << " w/ sdbm Hash,";
    readsFile << size5 << " w/ Alt Key,";
    readsFile << size5 << " w/ sdbm Hash and Alt Key";
    readsFile << endl; //end line

    //EACH ROW AFTER

    readsFile << "Separate Chaining" << ","; //Row Name

    for (int i=0; i < sepChainReadsVector.size(); ++i) {
        readsFile << sepChainReadsVector[i]; // add each entry
        if (i < sepChainReadsVector.size() - 1) {
            readsFile << ","; //add comma after each entry but the last
        }
    }
    readsFile << endl; //end line

    readsFile << "Probing" << ","; //Row Name

    for (int i=0; i < probingReadsVector.size(); ++i) {
        readsFile << probingReadsVector[i]; // add each entry
        if (i < probingReadsVector.size() - 1) {
            readsFile << ","; //add comma after each entry but the last
        }
    }
    readsFile << endl; //end line







    return 0;
}