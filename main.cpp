//============================================================================
//	Hassan Shahzad
//	18i-0441
//	FAST-NUCES
//	Apriori Algorithm
//	Contact at : chhxnshah@gmail.com
//============================================================================


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

template <class T>

class Grocery {

    T** arr;
    char threshold[5];
    char transactions[3];
    int trans = 0;
    double thresh = 0;
    double freq[50];
    int size = 0;
    double st[50];
    double sthresh = 0;

    T** itemList;
    int items = 0;
    int size1 = 0;
public:

    void ReadFile()
    {
        fstream in("GroceryStore.txt", ios::in);
        arr = new T * [100]; // can have 100 words
        for (int i = 0; i < 100; i++)
            arr[i] = new T[50]; // each word can have 50 letters

        T* temp = new T[100];
        T* temp2 = new T[50];


        if (in.is_open())
        {
            in >> threshold;
            in >> transactions;

            thresh = atof(threshold); // convert to float
            trans = atoi(transactions); // convert to int

            int i = 0;
            bool flag = true;
            while (!in.eof()) // keep reading till file ends
            {

                // temp is a char*. getline reads into it till it finds a '\n' 
                in.getline(temp, 100, '\n'); //reads one line
                checkArray(temp); //removes '\n' from start from temp

                //moves individual words from temp into arr
                int k = 0;
                for (int j = 0; temp[j - 1] != '\0'; j++)
                {

                    if (temp[j] == ',' || temp[j] == '\n' || temp[j] == '\0')
                    {
                        copyWord(arr[i], temp2);

                        i++;

                        if (flag && i == 1)
                        {
                            flag = false;
                            i--;
                        }

                        k = 0;
                        for (int l = 0; l < 50; l++)
                            temp2[l] = '\0';
                    }

                    else
                    {
                        temp2[k] = temp[j];
                        k++;
                    }
                }
            }



            size = i;

            sthresh = thresh * trans;
        }
        in.close();

    }

    void RFile1()
    {
        fstream in("GroceryStore.txt", ios::in);

        char tmp[1000];


        if (in.is_open())
        {
            in >> threshold;
            in >> transactions;

            thresh = atof(threshold); // convert to float
            trans = atoi(transactions); // convert to int

            int i = 0;
            while (!in.eof())
            {
                in.get(tmp[i]);
                i++;
            }

            size1 = i;

        }

        in.close();

        fstream out("Lines.txt", ios::out);

        for (int i = 1; i < size1; i++)
        {
            out << tmp[i];
        }
        out.close();
    }



    //creates list of unique, individual items
    void findUniqueWords()
    {
        itemList = new T * [100]; // can have 100 words
        for (int i = 0; i < 100; i++)
            itemList[i] = new T[50]; // each word can have 50 letters

        copyWord(itemList[0], arr[0]);
        items++;

        for (int i = 1; i < size; i++)
        {

            bool flag = true;

            for (int j = 0; j < items; j++)
            {
                if (compareWords(arr[i], itemList[j]) == true) //if itemList already has the word from arr[i] 
                {
                    flag = false;
                }
            }

            if (flag == true) {
                copyWord(itemList[items], arr[i]); // copy the word to itemList
                items++;
            }
        }
    }

    void Frequency()    //Finding Frequency of single items
    {
        cout << "--------------------------------------------------------------" << endl;
        cout << endl << "The Frequencies are = " << sthresh << endl;

        for (int i = 0; i < items; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (compareWords(itemList[i], arr[j]) == true)
                {
                    freq[i]++;
                }
            }
        }
    }

    void SThresh()
    {
        ofstream out("1-ItemSet.txt");

        out << "Items" << "\t\t" << "Frequency" << endl;

        for (int i = 0; i < items; i++)
        {
            if (freq[i] >= sthresh)
            {
                out << itemList[i] << "\t\t" << freq[i] << endl;
            }
        }
    }


    void checkArray(char* word) //removes newline from start of every word
    {
        if (word[0] == '\n' || word[0] == ' ')
        {
            for (int i = 0; word[i] != '\0'; i++)
                word[i] = word[i + 1];
        }
    }

    void copyWord(char* arr1, char* arr2) //copies arr2 to arr1
    {
        int i = 0;

        while (arr2[i] != '\0' || arr2[i] == ',')
        {
            arr1[i] = arr2[i];
            i++;
        }

        arr1[i] = '\0';
    }

    bool compareWords(char* word1, char* word2) //tells if two words are the same
    {
        int i = 0;

        while (word1[i] != '\0')
        {

            if (word1[i] != word2[i])
                return false;

            i++;
        }

        return true;
    }

    void sortArray() //sorts list of items according to their frequency
    {

        for (int i = 0; i < items; i++)
        {
            for (int j = 0; j < items; j++)
            {

                if (freq[i] > freq[j])
                {
                    double temp = freq[i];
                    freq[i] = freq[j];
                    freq[j] = temp;

                    T* temp2 = new T[50];
                    copyWord(temp2, itemList[i]);
                    copyWord(itemList[i], itemList[j]);
                    copyWord(itemList[j], temp2);
                }
            }
        }

        cout << "Item\t\tFrequency" << endl;

        for (int i = 0; i < items; i++)
            cout << itemList[i] << "\t\t" << freq[i] << endl;
    }
};

int main()
{
    Grocery <char> obj;

    obj.ReadFile();
    obj.findUniqueWords();
    obj.Frequency();
    obj.sortArray();
    obj.SThresh();
    obj.RFile1();

}