#include <iostream> 
#include <string> 
#include <fstream> 

// Project 3 - Group of Ruby Boyle & Pernille Dahl 

using namespace std; 

class Cryptography{
    
    private:
    
        int  shift = 0; // if we are doing linear encryption, this is how many characters we move forward or backward
        bool isLinear = true; // we have two types of encryption in this class
        
        /**
         *  encrypts source non-linearly and saves the encrypted source in result
         */
        int encryptNonLinear(string &source, string &result){
            if(source.length()==0){
                return -1;
            }
            result = source;
            for(int i = 0; i < result.length(); i++){
                unsigned char temp = result[i];
                unsigned char a = temp>>4;
                unsigned char b = temp<<4;
                result[i] = a | b;
            }
            // debug:: cout<<result<<endl;
            return result.length();
        }
    
        /**
         *  decrypts source non-linearly and saves the decrypted source in result
         */
        int decryptNonLinear(string &source, string &result){
            if(source.length()==0){
                return -1;
            }
            result = source;
            for(int i=0; i < result.length(); i++){
                unsigned char temp = result[i];
                unsigned char a = temp << 4;
                unsigned char b = temp >> 4;
                result[i] = a | b;
            }
            // debug:: cout<<result<<endl;
            return result.length();
        }
    
    
        /**
         *  encrypts source linearly and saves the encrypted source in result
         */
        int encryptLinear(string &source, string &result){
            if(source.length()==0){
                return -1;
            }
            result = source;
            for(int i = 0; i < result.length(); i++){
                result[i] = result[i]+shift;
            }
            // debug:: cout<<result<<endl;
            return result.length();
        }
    
        /**
         *  decrypts source linearly and saves the decrypted source in result
         */
        int decryptLinear(string &source, string &result){
            if(source.length()==0){
                return -1;
            }
            result = source;
            for(int i=0; i < result.length(); i++){
                result[i] = result[i]-shift;
            }
            // debug:: cout<<result<<endl;
            return result.length();
        }
        
    public:
        /**
         * public facing encryption function
         */
        int encrypt(string &source, string &result){
            if(isLinear){
                return encryptLinear(source, result);
            }else{
                return encryptNonLinear(source, result);
            }
        }
        
        /**
         * public facing decryption function
         */
        int decrypt(string &source, string &result){
            if(isLinear){
                return decryptLinear(source, result);
            }else{
                return decryptNonLinear(source, result);
            }
        }
        /**
         * linear: if true encypts linearly, if false non-linearly
         * shif: if linear encryption, shif will be number of chars to move
         */
        Cryptography(bool linear,int shiftNum)
        {
            shift = shiftNum;
            isLinear = linear;
        }
};


int main(){
    
    ifstream string_input;
    ofstream string_output; 
  
    string_input.open("file_a.txt"); 
      
    string source;
      
    while(string_input.eof() == 0){
        getline(string_input, source);
    }
      
    string encrypted; 
    string decrypted; 
      
    Cryptography myCrypto(false,0); //when false the second argument doesn't matter
    myCrypto.encrypt(source, encrypted); 
  
    string_input.close(); 
    // we have to safe to file B
    string_output.open("file_b.txt");
    
    for(int i = 0; i < source.length(); i++){
        string_output << encrypted[i]; 
    }
    
    //cout << encrypted << endl;
    myCrypto.decrypt(encrypted, decrypted);
    cout << decrypted << endl; 
    
    return 0;
}