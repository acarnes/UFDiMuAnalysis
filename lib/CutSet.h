//CutSet.h

#ifndef ADD_CUTSET
#define ADD_CUTSET

#include "VarSet.h"
#include "TString.h"

class CutInfo
{
    public:

        CutInfo(){};
        CutInfo(TString tstring, TString name, int id)
        {
            this->tstring = tstring;
            this->name = name;
            this->id = id;
        }

        TString tstring = ""; // represent the set of cuts as a tstring
        TString name = "";    // the name of the cut, useful when plotting
        bool passed = true;   // flag whether the event passed the cut or not
        int id = -1;          // the number of the cut in the cutset vector
        bool on = 1;          // whether to use the cut in the N-1 plots
        float value = -9999;  // the value of the variable that was cut on
        int bins = 50;        // the number of bins needed for the histogram
        float min = 0;        // the minimum value for the histogram
        float max = 200;      // the maximum value for the histogram
      
        CutInfo operator&&(const CutInfo& c)
        {
           CutInfo cutinfo;
           cutinfo.tstring = this->name + " && " + c.name; 
           cutinfo.name = this->name + " and " + c.name; 
           cutinfo.passed = this->passed && c.passed;
           return cutinfo;
        }

        
};

class CutSet
{
    public:

        CutInfo cutinfo;                         // represent the set of cuts as a tstring
        std::vector<CutInfo> cuts;               // the collection of cuts

        void concatenate(std::vector<CutInfo>& cuts)         // see whether the event passes the set of cuts
        {
            CutInfo cutinfo;
            // set cutinfo to the first active cut
            for(unsigned int i=1; i<cuts.size(); i++)
            {
                if(cuts[i].on)
                {
                    cutinfo = cuts[i];
                    break;
                }
            } 

            // concatenate active cuts together
            for(unsigned int i=1; i<cuts.size(); i++)
            {
                if(cuts[i].on)
                    cutinfo = cutinfo && cuts[i];
            } 
        }

        void turnOnCut(int i)
        {
            cuts[i].on = true;
        }
};

#endif