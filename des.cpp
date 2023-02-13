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
    if ( count != 8 ) {
        while( count != 8 ) {
            binaryString += bitset<8>('\0').to_string()  ;  
            count += 1 ;
        }
        block.push_back( binaryString ) ;
    }
    return block ;
} // 把明碼拆成許多區段

string BinaryInitial(string str){
    char changeChar[64] ;
    for( int i = 0 ; i < 64 ; i ++ ) {
        changeChar[g_iptable[i]-1] = str[i] ;
    }
    return string(changeChar) ;
}


int main() {
    string inputData ="" ;
    cin >> inputData ;
    vector<string> binaryString = StringToBinary( inputData ) ; // 得到所有區段 接下來就可以做事了
    for ( auto str : binaryString ) {
        cout << str << endl  ;
    }

}