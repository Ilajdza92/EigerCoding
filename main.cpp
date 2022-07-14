// Author: Ilija Pantic 13.07.2022

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>


long long baseHashing(std::string s)
{
    long long hashValue = 0;
    long long baseNum = 5;
    long long size = s.size()-1;

    for(char c: s)
    {
        hashValue = hashValue + c*(pow(baseNum, size));
        size--;
    }

    return hashValue;
}

long long rollingHashing(std::string prev, std::string next)
{
    long long baseNum = 5;
    long long prevHash= baseHashing(prev);
    long long size = prev.size()-1;

    long long rolingHash = (prevHash - prev[0]*(pow(baseNum, size)))*baseNum + next[0];

    return rolingHash;
}

void findString(std::string find, std::string text)
{
    long long size = text.size() - find.size() + 1;
    long long findSize = find.size();

    long long baseHash = baseHashing(find);
    std::cout<<"Base string hashed: "<< baseHash<<std::endl;

    std::cout<<"size: "<< size<<std::endl;
    std::cout<<"findSize: "<< findSize<<std::endl;

    long long rollingHash = 0;
    for(int i = 0; i<size; i++)
    {   
        std:: string prev = text.substr(i, findSize);
        std:: string next = (text.substr(findSize, findSize+1)).c_str();

        std::cout<<"prev: "<< prev<<std::endl;
        std::cout<<"next: "<< next<<std::endl;

        rollingHash = rollingHashing(prev, next);
        std::cout<<"rollingHash: "<< rollingHash<<std::endl;

        findSize++;

        if(rollingHash == baseHash)
        {
            std::cout<<"nasli smo: "<<rollingHash<<std::endl;
        }
    }
    std::cout<<"ILIJA"<<std::endl;
    std::ofstream chunkFile("chunkDifferences.txt");
    std::cout << text.substr(findSize, text.size())<<std::endl;

    chunkFile.close();


}

std::string readFile(std::string nameOfFile)
{
    std::ifstream myfile;
    myfile.open(nameOfFile);
    std::string myline;
    if ( myfile.is_open() ) 
    {
        while ( myfile ) 
        {
            std::getline (myfile, myline);
        }
    }
    else
    {
        std::cout<<"File "<< nameOfFile <<" cannot be opened"<<std:: endl;
        return "";
    }

    return myline;
}



int main(const int argc, const char *argv[])
{
    std::string myFileOriginal = readFile("original.txt");
    std::string myFileUpdated = readFile("updated.txt");

    std::cout<<"myFileOriginal "<< myFileOriginal <<std:: endl;
    std::cout<<"myFileUpdated "<< myFileUpdated <<std:: endl;

    findString(myFileOriginal, myFileUpdated);

    return 0;

    
}


// We have original document with strings in it
// We need to reupload new updated document
