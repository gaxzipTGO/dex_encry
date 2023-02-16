#include <iostream>
#include <bitset>
#include <vector>

using namespace std ;

int g_iptable[64] = { 58,50,42,34,26,18,10,2,
                      60,52,44,36,28,20,12,4,
                      62,54,46,38,30,22,14,6,
                      64,56,48,40,32,24,16,8,
                      57,49,41,33,25,17,9,1,
                      59,51,43,35,27,19,11,3,
                      61,53,45,37,29,21,13,5,
                      63,55,47,39,31,23,15,7 } ;

int PC_1[56] = { 57,49,41,33,25,17,9,
                 1,58,50,42,34,26,18,
                 10,2,59,51,43,35,27,
                 19,11,3,60,52,44,36,
                 63,55,47,39,31,23,15,
                 7,62,54,46,38,30,22,
                 14,6,61,53,45,37,29,
                 21,13,5,28,20,12,4} ;

int PC_2[48] = {14,17,11,24,1,5,
                3,28,15,6,21,10,
                23,19,12,04,26,8,
                16,07,27,20,13,02,
                41,52,31,37,47,55,
                30,40,51,45,33,48,
                44,49,39,56,34,53,
                46,42,50,36,29,32 } ;

int E_table[48] =   {32,1,2,3,4,5,
                    4,5,6,7,8,9,
                    8,9,10,11,12,13,
                    12,13,14,15,16,17,
                    16,17,18,19,20,21,
                    20,21,22,23,24,25,
                    24,25,26,27,28,29,
                    28,29,30,31,32,1} ;

int shiftTable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1} ;

string CharToString( char* ch_array, int size ) {
    string str = "" ;
    for ( int i = 0 ; i < size ; i ++ ) {
        str += ch_array[i] ;
    }
    return str ;
}
string ShiftBit( string str, int value ) {
    string changeStr = "" ;
    for ( int i = value ; i < str.size() ; i ++ ) {
        changeStr += str[i] ;
    }
    for ( int i = 0 ; i < value ; i ++ ) {
        changeStr += str[i] ;
    }
    return changeStr ;
}
class Key{

    private : string key = "" ;
    private : string cheakbit = "" ;
    private : string leftbit = "" ;
    private : string rightbit = "" ;
    private : string subKey[16] ;

    private : void LoadingKey(string str ) {
        int count = 0 ;
        for ( auto ch : str ) {
            key += bitset<8>(ch).to_string()  ;
            count += 1 ;
            if ( count == 8 ) {
                break ;
            }
        } // 每64bit 一個range
        if ( count < 8 && count != 0 ) {
            while( count < 8 ) {
                key += bitset<8>('\0').to_string()  ;  
                count += 1 ;
            }
        }        
    }

    public : void InputKey( string str ) {
        LoadingKey(str) ;
        GetLeftAndRightBit(ChangeControlKey(this->key)) ;
        CreateKey() ;
    }

    private : string ChangeControlKey( string str ) {
        string changeChar = "" ;
        int i = 0 ;
        for ( int index : PC_1 ) {
            changeChar += str[index-1] ;
            i += 1 ;
            if ( (i+1)%8 == 0 ) {
                this->cheakbit += str[i] ;
                i += 1 ;
            }
        }
        return changeChar ;
    }

    private : string ChangeControlTwoKey( string str ) {
        string changeChar = "" ;
        int i = 0 ;
        for ( int index : PC_2 ) {
            changeChar += str[index-1] ;
        }
        return changeChar ;
    }

    private : void GetLeftAndRightBit( string str ) {
        int i = 0 ;
        for ( ; i < 28 ; i ++ ) {
            this->leftbit += str[i] ;
        }
        for ( ; i < 56 ; i ++ ) {
            this->rightbit += str[i] ;
        }
    }

    private : void CreateKey() {

        
        for ( int i = 0 ; i < 16 ; i ++ ) { 
            this->leftbit = ShiftBit(this->leftbit,shiftTable[i]) ;
            this->rightbit = ShiftBit(this->rightbit,shiftTable[i]) ;
            subKey[i] = ChangeControlTwoKey(this->leftbit+this->rightbit) ;
            cout << subKey[i] << endl ;
        }
        

    }

    public : string GetKeyByIndex(int i) {
        return subKey[i] ;
    }

} des_key;

class Decoder{
    public : Key key ;
    public : string leftBit = "" ;
    public : string rightBit = "" ;
    public :
        vector<string> StringToBinary( string s ) {
            string binaryString = "" ;
            vector<string> block ;
            int count = 0 ;
            for ( auto ch : s ) {
                binaryString += bitset<8>(ch).to_string()  ;
                count += 1 ;
                if ( count == 8 ) {
                    block.push_back(binaryString) ;
                    binaryString = "" ;
                    count = 0 ;
                }
            } // 每64bit 一個range
            if ( count < 8 && count != 0 ) {
                while( count < 8 ) {
                    binaryString += bitset<8>('\0').to_string()  ;  
                    count += 1 ;
                }
                block.push_back( binaryString ) ;
            }
            return block ;
        } // 把明碼拆成許多區段

        string BinaryInitial(string str){
            string changeChar = "" ;
            for( int index : g_iptable ) {
                changeChar += str[index-1] ;
            }
            
            return changeChar ;
        }

        string LoadLeftBit( string total_bit ) {
            string str = "" ;
            int size = total_bit.size() ;
            for ( int i = 0  ; i < size/2 ; i ++ ) {
                str += total_bit[i] ;
            }
            this->leftBit = str ;
        }


        string LoadRightBit( string total_bit ) {
            string str = "" ;
            int size = total_bit.size() ;
            for ( int i = size/2  ; i < size ; i ++ ) {
                str += total_bit[i] ;
            }
            return str ;
        }

        string E_Extention( string str ) {
            string changeChar = "" ;
            for ( int index : E_table ) {
                changeChar += str[index-1] ;
            }
            return changeChar ;
        }

        string F_function( string str, int i ) {

        }

    

} des_decoder ;


int main() {
    string inputData ="kevinasdd" ;
    // cin >> inputData ;
    /*
    vector<string> binaryString = des_decoder.StringToBinary( inputData ) ; // 得到所有區段 接下來就可以做事了
    for ( auto str : binaryString ) {
        string temp = des_decoder.BinaryInitial(str) ;
        cout << des_decoder.GetLeftBit(temp) << endl  ;
        cout << des_decoder.GetRightBit(temp) << endl  ;
    }
    
    */
}
