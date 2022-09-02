
// Author: Cesar Garcia
// Program: Caesar Cipher Decoder
//
// The program decrypts a Caesar Cipher encrypted ciphertext
// and outputs the offset value used in the encryption, the plaintext, and
// the file name of the plaintext .txt file.
// 
// The letters are shifted 1-25 ASCII Character Set values and a word list is used to detect the 
// shifted output with the most words from the word list to give the plaintext.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

void decrypt(){
    
    //cipher .txt file name
    ifstream inFile("cipher.txt");
    string ciph;
    if (inFile){
        ostringstream ctext;
        ctext << inFile.rdbuf();
        ciph = ctext.str();
    }
    ofstream plainText;
    plainText.open("plainText.txt");
    //a word list is used to detect the shifted text with the most words
    ifstream wFile("words.txt");
    string words;
    if (wFile){
        ostringstream wtext;
        wtext << wFile.rdbuf();
        words = wtext.str();
    }

    int wordCountArr[26];
    string shiftedCiphers[26];

    string decrypted = ciph; 
    //shifts the alphabetic letters 0 to 25 values, when the end of the alphabet is
    //reached the alphabet cycle begins anew
    for(int shift = 0; shift <= 25; shift++){ 

        for(int letter = 0; letter < ciph.length(); letter++){

            if((ciph[letter]>='a' && ciph[letter]<='z') || (ciph[letter]>='A' && ciph[letter]<='Z')){
                
                if (ciph[letter] >= 'A' && ciph[letter] <= 'Z'){
                    
                    if (ciph[letter] + shift >'Z'){
                        decrypted[letter] = (ciph[letter]+ shift)-26; 
                    }
                    else decrypted[letter] = ciph[letter]+shift;
                    
                }
                
                if (ciph[letter] >= 'a' && ciph[letter] <= 'z'){
                    
                    if (ciph[letter] + shift >'z'){
                        decrypted[letter] = (ciph[letter]+ shift)-26;
                    }
                    else decrypted[letter] = ciph[letter]+shift;
                    
                }
            }
        }
        //every shift is written into plaintext.txt with every cycle being separated by
        //a new line
        plainText << decrypted << "\n";
        //at every shift cycle the output is also written into file(shift).txt
        string fileName = "file" + to_string(shift) + ".txt";
        ofstream file(fileName);
        file << decrypted;   
        
        
        istringstream iss(decrypted);
        istringstream wordFile(words);

        string dict, crypt;
        int wordCount = 0;

        while( wordFile>> dict){
            iss.clear();
            iss.seekg(0);
            while ( iss >> crypt){
                if(crypt == dict){
                    wordCount++;
                }
            }
        }
        wordCountArr[shift] = wordCount;
        shiftedCiphers[shift] = decrypted;
    }
    int s = sizeof(wordCountArr)/sizeof(wordCountArr[0]);
    int maxElement = *max_element(wordCountArr, wordCountArr + s);
    int maxElementIndex = find(wordCountArr,wordCountArr+s,maxElement)-wordCountArr;
    //The offset value, plaintext, and the file name where the plaintext is saved is given
    cout <<"The offset value is: " + to_string(maxElementIndex)+"\n";
    cout <<"The plaintext is: "+ (shiftedCiphers[maxElementIndex])+"\n";
    cout <<"The plaintext file name is: file" + to_string(maxElementIndex) + ".txt";
    
}

int main()
{
    decrypt();
}
