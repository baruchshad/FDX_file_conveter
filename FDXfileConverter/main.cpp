#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>

using namespace std;

ofstream outfile;
ifstream infile;

int main()
{
    string file, convfile,word;
    string copy ();
    int first;

    file = copy();
    convfile= file;
    convfile.insert((convfile.length()-4)," (converted)");

    infile.open(file.c_str());
    if(!infile.is_open()){
        cout<<"\nERROR: Unable to open file..."<<endl;
        system("pause");
        exit(0);
    }

    outfile.open(convfile.c_str());
    if(!outfile.is_open()){
        cout<<"\nERROR: Unable to create file..."<<endl;
        system("pause");
        exit(0);
    }
    cout<<"\nYour File is now being converted..."<<endl;
    infile>>word;

    while(!infile.eof()){

    //finds text between the <Text> and </Text>
        if((word.find("<Text>")!= string::npos)&&(word.find("</Text>")==string::npos)){
           word.erase(0,6);
           outfile<<word;
           first=infile.get();
           while(first!='<'){
                outfile.put(first);
                first=infile.get();
                }
           outfile<<'\n';
        }
        if((word.find("<Text>")!= string::npos)&&(word.find("</Text>")!=string::npos)){
            word.erase(0,6);
            word.erase((word.length()-7),7);
            outfile<<word;
        }

    //finds the Paragraph type
        if(word.find("<Paragraph")!= string::npos){
            getline(infile,word);
            if (word.find("Transition")!=string::npos){
                infile>>word;
                word.erase(0,6);
                outfile<<"\t\t\t\t\t\t\t\t\t\t\t\t";
                outfile<<word;
                first=infile.get();
                while(first!='<'){
                    outfile.put(first);
                    first=infile.get();
                }
            outfile<<'\n';

            }
        }

    //skips lines where they need be.
        if(word.find("</Paragraph>")!= string::npos){
            outfile<<'\n';
        }
        infile>>word;
    }

    cout<<"\nYour File was successfully converted!"<<endl;
    outfile.close();
    infile.close();
    system("pause");
    exit(0);
}

/*
* Function: copies input file to new file (for safety purposes)
* Called By: main
* Calls: n/a
*/
string copy ()
{
    int tryagain;
    string line, fileName,outputfile;
    bool openfile;

    do{
            openfile = false;
            cout<<"\nPlease enter the name of the file you want to convert:"<<endl;
            getline(cin,fileName);
            outputfile = fileName + ".txt";
            fileName += ".fdx";
            infile.open(fileName.c_str());
            if(!infile.is_open()){
                openfile=true;
                cout<< "ERROR: Unable to open file"<<endl;
                cout<< "Do you want to try again? \nEnter 0 for YES and 1 to EXIT..."<<endl;
                cin>>tryagain;
            }
           if (tryagain == 1){
               system("pause");
               exit(0);
           }
    }while(openfile!=false);

    outfile.open(outputfile.c_str());
    cout<<"\nYour file is being copied for backup purposes..."<<endl;
    while(!infile.eof()){
        getline(infile,line);
        outfile<< line <<endl;
    }
    cout<<"\nFile copied successfully!"<<endl;
    infile.close();
    outfile.close();
    return outputfile;
}
