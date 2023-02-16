#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>

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

int s_box[8][4][16] = 
            {{{14,04,13,01,02,15,11,8,03,10,06,12,05,9,00,07},
             {00,15,07,04,14,02,13,01,10,06,12,11,9,05,03,8},
             {04,01,14,8,13,06,02,11,15,12,9,07,03,10,05,00},
             {15,12,8,02,04,9,01,07,05,11,03,14,10,00,06,13}},

             {{15,01,8,14,06,11,03,04,9,07,02,13,12,00,05,10},
             {03,13,04,07,15,02,8,14,12,00,01,10,06,9,11,05},
             {00,14,07,11,10,04,13,01,05,8,12,06,9,03,02,15},
             {13,8,10,01,03,15,04,02,11,06,07,12,00,05,14,9}},

             {{10,00,9,14,06,03,15,05,01,13,12,07,11,04,02,8},
             {13,07,00,9,03,04,06,10,02,8,05,14,12,11,15,01},
             {13,06,04,9,8,15,03,00,11,01,02,12,05,10,14,07},
             {01,10,13,00,06,9,8,07,04,15,14,03,11,05,02,12}} ,

             {{07,13,14,03,00,06,9,10,01,02,8,05,11,12,04,15},
             {13,8,11,05,06,15,00,03,04,07,02,12,01,10,14,9},
             {10,06,9,00,12,11,07,13,15,01,03,14,05,02,8,04},
             {03,15,00,06,10,01,13,8,9,04,05,11,12,07,02,14}} ,

             {{02,12,04,01,07,10,11,06,8,05,03,15,13,00,14,9},
             {14,11,02,12,04,07,13,01,05,00,15,10,03,9,8,06},
             {04,02,01,11,10,13,07,8,15,9,12,05,06,03,00,14},
             {11,8,12,07,01,14,02,13,06,15,00,9,10,04,05,03}} ,

             {{12,01,10,15,9,02,06,8,00,13,03,04,14,07,05,11},
             {10,15,04,02,07,12,9,05,06,01,13,14,00,11,03,8},
             {9,14,15,05,02,8,12,03,07,00,04,10,01,13,11,06},
             {04,03,02,12,9,05,15,10,11,14,01,07,06,00,8,13}} ,

             {{04,11,02,14,15,00,8,13,03,12,9,07,05,10,06,01},
             {13,00,11,07,04,9,01,10,14,03,05,12,02,15,8,06},
             {01,04,11,13,12,03,07,14,10,15,06,8,00,05,9,02},
             {06,11,13,8,01,04,10,07,9,05,00,15,14,02,03,12}} ,

             {{13,02,8,04,06,15,11,01,10,9,03,14,05,00,12,07},
             {01,15,13,8,10,03,07,04,12,05,06,11,00,14,9,02},
             {07,11,04,01,9,12,14,02,00,06,10,13,15,03,05,8},
             {02,01,14,07,04,10,8,13,15,12,9,00,03,05,06,11}} } ;

int P2[32] = {16,07,20,21,29,12,28,17,01,15,23,26,05,18,31,10,
              02,8,24,14,32,27,03,9,19,13,30,06,22,11,04,25} ;

int inver_P1[64] = {40,8,48,16,56,24,64,32,
                    39,7,47,15,55,23,63,31,
                    38,6,46,14,54,22,62,30,
                    37,5,45,13,53,21,61,29,
                    36,4,44,12,52,20,60,28,
                    35,3,43,11,51,19,59,27,
                    34,2,42,10,50,18,58,26,
                    33,1,41,9,49,17,57,25} ;

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

string XOR(string s1, string s2) {
    string result = "" ;
    int size = s1.size() ;
    if ( s1.size() == s2.size() ) {
        for (int i = 0 ; i < size ; i ++ ) {
            if ( s1[i] == s2[i] ) {
                result += "0" ;
            }
            else {
                result += "1" ;
            }
        }
    }
    return result ;
}

int StringBitToInt(string str) {
    int result = 0;
    for(int i = 0 ; str != "" ; i ++ ) {
        if ( str.back() == '1' ) {
            result += pow(2,i) ;
        }
        str.pop_back() ;
    }
    return result ;
}

string IntToStringBit( int num ) {
    string result = "" ;
    while( num > 0 ) {
        result.insert(0,to_string(num%2)) ;
        num /= 2 ;
    }
    for ( ;result.size() < 4; ) {
        result.insert(0,"0") ;
    }
    return result ;
}

char StrToChar(string str) {
    char parsed = 0;
    for (int i = 0; i < 8; i++) {
        if (str[i] == '1') {
            parsed |= 1 << (7 - i);
        }
    }
    return parsed;
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
        }
        

    }

    public : string GetKeyByIndex(int i) {
        return subKey[i] ;
    }

} des_key;

class Decoder{
    public : Key key ;
    public : Key key_2 ;
    public : Key key_3 ;
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

        void LoadLeftBit( string total_bit ) {
            string str = "" ;
            int size = total_bit.size() ;
            for ( int i = 0  ; i < size/2 ; i ++ ) {
                str += total_bit[i] ;
            }
            this->leftBit = str ;
        }


        void LoadRightBit( string total_bit ) {
            string str = "" ;
            int size = total_bit.size() ;
            for ( int i = size/2  ; i < size ; i ++ ) {
                str += total_bit[i] ;
            }
            this->rightBit = str ;
        }

        string GetLeftBit() {
            return this->leftBit ;
        }


        string GetRightBit() {
            return this->rightBit ;
        }

        public: void LoadMessageAndKey( string message, string key ) {
            this->key.InputKey(key) ;
        }

        string E_Extention( string str ) {
            string changeChar = "" ;
            for ( int index : E_table ) {
                changeChar += str[index-1] ;
            }
            return changeChar ;
        }

        string S_Replace(string str, int index ) {
            string rowBit = "" ;
            rowBit += str[0] ;
            rowBit += str[5] ;
            int row = StringBitToInt(rowBit) ;
            int col = StringBitToInt( str.substr(1,4) ) ;
            return IntToStringBit( s_box[index][row][col] ) ;
        }

        string P2_Repalce(string str) {
            string result = "" ;
            for ( int index : P2 ) {
                result += str[index-1] ;
            }
            return result ;
        }

        string F_function( string message, string key ) {
            string temp = XOR(E_Extention(message),key) ;
            string result = "" ;
            for( int i = 0 ; i < 48 ; i += 6 ) {
                result += S_Replace(temp.substr(i,6),i/6) ;
            }
            result = P2_Repalce(result) ;
            return result ;
        }

        string Inverse_Replace(string str) {
            string result ;

            for ( int index : inver_P1 ) {
                result += str[index-1] ;

            }
            return result ;
        }

        string Des_Decode(string str, Key key) {
            str = BinaryInitial(str) ;
            LoadLeftBit(str) ;
            LoadRightBit(str) ;
            for ( int i = 0 ; i < 16 ; i ++ ) {
                string tempBit = this->rightBit ;
                this->rightBit = XOR(this->leftBit,F_function(this->rightBit,key.GetKeyByIndex(i)) );
                this->leftBit = tempBit ; // 這要放在最後
            }
            string decode = "" ;

            decode += this->rightBit ;
            decode += this->leftBit ;
            
            decode = Inverse_Replace(decode) ;
            return decode ;
            string result = "";
            for ( int i = 0 ; i < 64 ; i = i + 8 ) {
                result += StringBitToInt(decode.substr(i,8)) ;
            }
            return result ;
        }

        string Des_Encode(string str, Key key) {
            str = BinaryInitial(str) ;
            LoadLeftBit(str) ;
            LoadRightBit(str) ;
            for ( int i = 15 ; i >= 0 ; i -= 1 ) {
                string tempBit = this->rightBit ;
                this->rightBit = XOR(this->leftBit,F_function(this->rightBit,key.GetKeyByIndex(i)) );
                this->leftBit = tempBit ; // 這要放在最後
            }
            string encode = "" ;

            encode += this->rightBit ;
            encode +=  this->leftBit;
            
            encode = Inverse_Replace(encode) ;
            return encode ;
            /*
            string result = "";
            for ( int i = 0 ; i < 64 ; i = i + 8 ) {
                result += StringBitToInt(decode.substr(i,8)) ;
            }
            return result ;    
            */        
        }
    
        public :string Triple_Des_Decode(string message) {
            message = Des_Decode(message,key) ;
            message = Des_Encode(message,key_2) ;
            message = Des_Decode(message,key_3) ;
            return message ;
        }

        public :string Triple_Des_Encode(string message) {
            message = Des_Encode(message,key_3) ;
            message = Des_Decode(message,key_2) ;
            message = Des_Encode(message,key) ;
            return message ;
        }

} des_decoder ;


int main() {
    string inputData ="computer etsetset sdfsdfsfgsadrf fd esaedafgfgfds sadfedsfas e" ;
    // cin >> inputData ;
    
    des_decoder.key.InputKey("testtest") ;
    des_decoder.key_2.InputKey("abcdefgf") ;
    des_decoder.key_3.InputKey("qqqqwwww") ;
    vector<string> binaryString = des_decoder.StringToBinary( inputData ) ; // 得到所有區段 接下來就可以做事了
    for ( auto str : binaryString ) {
        cout << str << endl ;
        string decode = des_decoder.Triple_Des_Decode(str) ;
        cout << decode << endl ;
        string encode = des_decoder.Triple_Des_Encode(decode) ;
        cout << encode << endl ;
        cout << "------------------------------分隔線---------------------------------" << endl ;
    }
        
    
}
