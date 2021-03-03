#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////

int main(){

    //--------------- 

    cout << endl << "Converting rcslw_data text files to binary:";

    //--------------- 

    vector<string> filelist = {"co2_p0_1", "co2_p0_25", "co2_p0_5", "co2_p15_0", "co2_p1_0", 
                               "co2_p2_0", "co2_p30_0", "co2_p4_0", "co2_p50_0", "co2_p8_0", 
                               "co_p0_1",  "co_p0_25",  "co_p0_5",  "co_p15_0",  "co_p1_0", 
                               "co_p2_0",  "co_p30_0",  "co_p4_0",  "co_p50_0",  "co_p8_0",
                               "h2o_p0_1", "h2o_p0_25", "h2o_p0_5", "h2o_p15_0", "h2o_p1_0",
                               "h2o_p2_0", "h2o_p30_0", "h2o_p4_0", "h2o_p50_0", "h2o_p8_0", };

    //--------------- read data into vector data

    vector<float> data;
    ifstream ifile;
    float d;
    string fname;

    for (int i=0; i<filelist.size(); i++){
        data = vector<float>();
        fname = filelist[i]+".txt";
        cout << endl << "processing file: " << fname;
        ifile.open(fname);
        if(!ifile){
            cout << endl << "error opening file: " << fname << endl;
            exit(0);
        }
        for(;;) {
            ifile >> d;
            if (ifile.eof())
                break;
            data.push_back(d);
        }
        ifile.close();

        //--------------- write binary data file

        fname = filelist[i]+".bin";
        ofstream ofile;
        ofile.open(fname, ios::out | ios::binary | ios::trunc);
        if(!ofile){
            cout << endl << "error opening file: " << fname << endl;
            exit(0);
        }
        for(int i=0; i<data.size(); ++i)
            ofile.write((char *) &data[i], sizeof(data[i]));
        ofile.close();

    }
    cout << endl;

    return 0;
}

