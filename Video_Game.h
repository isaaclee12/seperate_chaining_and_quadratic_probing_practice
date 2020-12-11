//
// Created by isaac on 9/2/2019.
//

#ifndef LECTURER_ISAAC_LEE_CS124A_PROJECT_1_H
#define LECTURER_ISAAC_LEE_CS124A_PROJECT_1_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Video_Game {

    private:
        //Debug Var for .readGamesFromFile (There was a bug where # vector elements != rows in csv)
        int ct=0;

        //Variables for each attribute, in same order as csv

        //ints used for rank and year for cpu efficiency
        int rank;
        string name, platform;
        int year;
        string genre, publisher;

        //doubles used for sales because they have decimal values
        double NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales;

    public:
        //Default Constructor
        Video_Game() {
            rank = 0;
            name = "null";
            platform = "null";
            year = 0;
            genre = "null";
            publisher = "null";
            NA_Sales = 0;
            EU_Sales = 0;
            JP_Sales = 0;
            Other_Sales = 0;
            Global_Sales = 0;
        }

        //Main Constructor
        Video_Game(int rank, string name, string platform, int year, string genre, string publisher,
                double NA_Sales, double EU_Sales, double JP_Sales, double Other_Sales, double Global_Sales) {
            this->rank = rank;
            this->name = name;
            this->platform = platform;
            this->year = year;
            this->genre = genre;
            this->publisher = publisher;
            this->NA_Sales = NA_Sales;
            this->EU_Sales = EU_Sales;
            this->JP_Sales = JP_Sales;
            this->Other_Sales = Other_Sales;
            this->Global_Sales = Global_Sales;
        }

        //GETTERS
        int getRank() {
            return rank;
        }
        string getName() {
            return name;
        }
        string getPlatform() {
            return platform;
        }
        int getYear() {
            return year;
        }
        string getGenre() {
            return genre;
        }
        string getPublisher() {
            return publisher;
        }
        double getNA_Sales() {
            return NA_Sales;
        }
        double getEU_Sales() {
            return EU_Sales;
        }
        double getJP_Sales() {
            return JP_Sales;
        }
        double getOther_Sales() {
            return Other_Sales;
        }
        double getGlobal_Sales() const {
            return Global_Sales;
        }

        //SETTERS
        void setRank(int rank) {
            this->rank = rank;
        }
        void setYear(int year) {
            this->year = year;
        }
        void setNA_Sales(double NA_Sales) {
            this->NA_Sales = NA_Sales;
        }
        void setEU_Sales(double EU_Sales) {
            this->EU_Sales = EU_Sales;
        }
        void setJP_Sales(double JP_Sales) {
            this->JP_Sales = JP_Sales;
        }
        void setOther_Sales(double Other_Sales) {
            this->Other_Sales = Other_Sales;
        }
        void setGlobal_Sales(double Global_Sales) {
            this->Global_Sales = Global_Sales;
        }


    //Reads in data from .csv file into a vector
    void readGamesFromFile (string filename, vector<Video_Game> &video_games) {
        //Establish File Object, open file w/ "filename"
        ifstream F_In;
        F_In.open("../" + filename);

        //Skip the first line/header
        if (F_In) {
            string header = "";
            getline(F_In, header);
        }


        //Loop through each row until end of file
        while (F_In && F_In.peek() != EOF) {

            //Establish vars to push into vector, these also reset the values with each loop
            int rank = 0, year = 0;
            double NA_Sales = 0, EU_Sales = 0, JP_Sales = 0, Other_Sales = 0, Global_Sales = 0;
            string name = "", platform = "", genre = "", publisher = "";

            //Chars to split inputs at
            char comma = ',';
            char quote = '"';

            //Rank Reader
            F_In >> rank;
            if (!F_In) { //If the data is bad/not a double...
                rank = 0; // ..set it to 0
                F_In.clear(); //And clear the data
            }
            F_In >> comma; //Split @ comma, then skip the comma

            //Name Reader
            if (F_In.peek()==quote) {
                F_In >> quote; //If you hit a quote,
                getline(F_In, name, '"'); //Read in characters until the next quote
                F_In >> comma; //Split @ comma, then skip the comma
            } else {
                getline(F_In, name, ','); //Otherwise, just read in until the next comma
            }

            //Platform Reader - Works same as Name Reader
            if (F_In.peek()==quote) {
                F_In >> quote;
                getline(F_In, platform, '"');
                F_In >> comma;
            } else {
                getline(F_In, platform, ',');
            }

            //Year Reader - Works same as Rank Reader
            F_In >> year;
            if (!F_In) {
                year = 0; // if not reading a double, set it to 0
                F_In.clear();
            }
            F_In >> comma;

            //Genre Reader - Works same as Name Reader
            if (F_In.peek()==quote) {
                F_In >> quote;
                getline(F_In, genre, '"');
                F_In >> comma;
            } else {
                getline(F_In, genre, ',');
            }

            //Publisher Reader - Works same as Name Reader
            if (F_In.peek()==quote) {
                F_In >> quote;
                getline(F_In, publisher, '"');
                F_In >> comma;
            } else {
                getline(F_In, publisher, ',');
            }

            //NA Sales Reader - Works same as Rank Reader
            F_In >> NA_Sales;
            if (!F_In) {
                NA_Sales = 0; // if not reading a double, set it to 0
                F_In.clear();
            }
            F_In >> comma;

            //EU Sales Reader - Works same as Rank Reader
            F_In >> EU_Sales;
            if (!F_In) {
                EU_Sales = 0; // if not reading a double, set it to 0
                F_In.clear();
            }
            F_In >> comma;

            //JP Sales Reader - Works same as Rank Reader
            F_In >> JP_Sales;
            if (!F_In) {
                JP_Sales = 0; // if not reading a double, set it to 0
                F_In.clear();
            }
            F_In >> comma;

            //Other Sales Reader - Works same as Rank Reader
            F_In >> Other_Sales;
            if (!F_In) {
                Other_Sales = 0; // if not reading a double, set it to 0
                F_In.clear();
            }
            F_In >> comma;

            //Global Sales Reader - Works same as Rank Reader
            F_In >> Global_Sales;
            if (!F_In) {
                Global_Sales = 0; // if not reading a double, set it to 0
                F_In.clear();
            }

            //Print for Debug (don't run this it takes like 2 minutes)
            /*ct++;
            cout << ct << "," << rank << ", " << name << ", " << platform << ", " << year << ", " << genre << ", " << publisher
                    << ", " << year << ", " << genre << ", " << publisher << ", " << NA_Sales << ", " << EU_Sales
                    << ", " << JP_Sales << ", " << Other_Sales << ", " << Global_Sales << endl;*/

            // Push variables into a new Video_Game object, then push that Video_Game into the vector.
            video_games.push_back(Video_Game(rank, name, platform, year, genre, publisher,
                                             NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales));

        }

        //Close file after loop
        F_In.close();
    }

    friend bool operator == (const Video_Game &vg1, const Video_Game &vg2) {
        if (vg1.getGlobal_Sales() == vg2.getGlobal_Sales()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator < (const Video_Game &vg1, const Video_Game &vg2) {
        if (vg1.getGlobal_Sales() < vg2.getGlobal_Sales()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator > (const Video_Game &vg1, const Video_Game &vg2) {
        if (vg1.getGlobal_Sales() > vg2.getGlobal_Sales()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator <= (const Video_Game &vg1, const Video_Game &vg2) {
        if (vg1.getGlobal_Sales() <= vg2.getGlobal_Sales()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator >= (const Video_Game &vg1, const Video_Game &vg2) {
        if (vg1.getGlobal_Sales() >= vg2.getGlobal_Sales()) {
            return true;
        } else {
            return false;
        }
    }

    friend ostream& operator << (ostream &o, const Video_Game &vg) {
            o << vg.getGlobal_Sales() << endl;
            return o;
    }

    /*void Video_Game& operator << (const Video_Game &vg1, const Video_Game &vg2) {
        if (vg1.getGlobal_Sales() > vg2.getGlobal_Sales()) {
            return true
        } else {
            return false;
        }
    }*/

};



#endif //LECTURER_ISAAC_LEE_CS124A_PROJECT_1_H
