#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>

using namespace std;

int read_file (vector <string> &v); //read in file w ints separated by commas (everybodys_socials.txt)
void write_to_file(int *&v, int m); //write out hash table w filename hashed_socials.txt
int extract (string ssn); //extracts 4 digits from SSN that will be used for quadratic probing/hashing
int probe (int key, int answer, int m); //used to perform quad probing and return pos where to insert things into hash table
int str_conversion (string a); //convert string to an int thru a char array


int main()
{
    int M = 450000000; //max value for hashing
    int n = 65000; //number of SSNs in file
    int answer, cuatro, index, key, next_index;
    vector <string> read_ints;
    int *hash_table=new int [n];
    for(int i=0;i<n;i++)    //initialize the hash table to contain 0s
        hash_table[i]=0;
    read_file(read_ints);
    cout << endl << "Enter a number between 1 and 450,000,000 (450 million), NOT separated by commas: \n";
    cin >> answer; //ask user to give number to be later used for quad probing
    if (answer<1 || answer>M) //check answer provided, make sure it's between right numbers
    {
        cout << "ERROR, please type a valid answer: \n";
        cin >> answer;
    }
    cout << "Your number: " << answer << endl;
    for (int j=0;j<read_ints.size();j++)
    {
        cuatro = extract(read_ints[j]); //find the 4 numbers that must be extracted from each SSN
        key = str_conversion(read_ints[j]); //convert SSN to be inserted into hash table
        if (hash_table[cuatro]!=0) //COLLISION OCCURS
        {
            index = probe(key, answer, n); //index of hash table for certain value
            for (int c=0;c<n;c++)
            {
                if (hash_table[c]==0)
                    next_index = c; //find next available space, save it
            }
            if (hash_table [index]!=0) //space is already occupied
                hash_table[next_index] = key;
            else
                hash_table [index] = key;
        }
        else
            hash_table [cuatro] = key;
    }

    write_to_file(hash_table, n); //write out hash table to file
    cout << "Finished writing file, please check it! \n"; //completion message!
    return 0;
}

void write_to_file (int *&v, int m) //hash table written to file
{
    int j; //keep track of index of hash table
    ofstream out; //write out to file
    out.open("hashed_socials.txt");
    for (j=0;j<m-1;j++)
        out << v[j] << ","; //comma as delimiter
    out << v[j]; //write out last value from hash table into file (w/o added comma)
    out.clear();
    out.close();
}

int read_file (vector <string> &v)
{
    ifstream in; //input filestream to read file
    char * filename = new char [15]; //user input to type name of file with .txt extension
    cout << "Please enter the name of the file: \n";
    cin >> filename;
    in.open(filename); //read from file name as provided by user in line 20 (right above)
    if (!in.is_open()){ //when the file cannot be opened, show error msg
        cout << "Error, please try another file. \n";
        return read_file(v);
    }

    char * num = new char [100]; //char array to store the integers as they are read
    while (in.peek()!=EOF){
            in.getline(num,100,','); //int will be put in char array with the delineator
            v.push_back(num);
    }
    in.clear();
    in.close();
    return 1;
}

int extract (string ssn)
{
    int number;
    char * num_array = new char [4]; //to be used to convert char array into int
    //begin sorting and locating digits: 3, 5, 7, and 8 in the SSN (coming in as string), put them in array extract
    num_array [0]=ssn [2]; num_array [1]=ssn[4]; num_array [2]=ssn [6]; num_array [3]=ssn [7];
    number = atoi(num_array); //array is converted into int
    return number; //return int for EVERY SSN in string vector
}

int probe (int key, int answer, int m) //collision resolution
{
    //algorithm consists of: hash + i^2 MOD m
    int table_index, i, hashh; //table index will be returned at the end; i refers to algorithm above; hashh = hash algorithm
    hashh = answer%m;
    i = (answer%((m-1)/2))+1; //set i equal to val bet 1 and (m-1)/2, BUT add 1 to ensure it is always AT LEAST 1
    table_index = (hashh+(i*i))%m; //table index will now be final algorithm (hash(key)+i^2%m)
    return table_index;
}

int str_conversion (string n_str)
{
    int real_int;
    char * new_array = new char [9];
    for (int b=0;b<9;b++) //copy chars into each other
        new_array [b] = n_str [b];
    real_int = atoi(new_array); //new_array contains SSN in char form, convert to int
    return real_int;
}

