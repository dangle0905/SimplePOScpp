#include <map>
#include <iostream>
#include "Item.h"
#include "readRetailStoreItemDataFile.h"

//this function reads the files
void readRetailStoreItemDataFile(map<string, Item>& inventory) {
    ifstream myfile;
    myfile.open("RetailStoreItemData.txt");

    int lineNo = 0;
    size_t pos = 0;
    //char we are looking for to split
    string delimiter = ",";
    vector<string> values;

    while (myfile)
    {

        string myLineOfString;
        //first argument is our file, second argument is the first line of string
        getline(myfile, myLineOfString);
        if (lineNo > 0)
        {
            
            while ((pos = myLineOfString.find(delimiter)) != string::npos)
            {

                for (int i = 0; i < 7; i++)
                {
                    //for i = 1 we check because some descriptions have commas so we they are in double quotations so our delimiter for when i = 1 is the last quotation + 1;
                    if (i == 1)
                    {
                        if (myLineOfString.at(0) == '"') {
                            //find the next delimiter
                            pos = myLineOfString.find_last_of('"');
                            pos = pos + 1;
                        }

                    }
                    values.push_back(myLineOfString.substr(0, pos));
                    //now we erase it from our string
                    myLineOfString.erase(0, pos + delimiter.length());
                    pos = myLineOfString.find(delimiter);

                }

                inventory.insert({ values[0], Item(values[0], values[1], values[2], values[3], values[4], values[5], values[6]) });
                values.clear();
                break;
            }
        }
        lineNo++;
    }
}