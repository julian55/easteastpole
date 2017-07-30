#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <cassert>

// Code Word 
typedef unsigned short int U16_t ;

using namespace std;

//initializd 128, sym+=1
U16_t sym = 1 << 7;

//dictionary
std::map<string, U16_t> _map; // map string to code word 
std::map<U16_t, string> _inverse_map; // map code word to string 

// initialize dictionary 
void init_map(void)
{
    U16_t t;
    char c;
    string s;
    s.append(1,'\0');
    for (size_t i = 0; i < 128; i++) {
        c = (char)i;
        s[0] = c ;
        _map[s] = (U16_t)i; //map string of length 1 to corresponding code word 
    }
}

void init_inverse_map()
{
    char c;
    string s0 ;
    s0.append(1,'c');
    for(U16_t t= 0; t < 128 ;t++)
    {
        c= t % 128 ;  
        s0[0] = c;
        _inverse_map[t] = s0; // map code word to string of length 1 
    }
}

// LZW compress algorithm realization 
void compress(char* inf, char* outf)
{

    std::string s0, s1;
    char c, c_temp ;
    U16_t val ;
    std::ifstream infile(inf, std::ios::in);
    std::ofstream outfile(outf, std::ios::out | std::ios::trunc);
    if (!outfile.is_open()) {
        std::cerr << "Unable to open file for writing" << '\n';
        exit(-1);
    }
    if (!infile.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(-1);
    }
    init_map();
    s0.clear(); // prepare s0 and s1 for algorithm 
    s1.clear();
    while (!infile.eof()) { // repeat until the end of file 
        c = infile.get(); // get one character
        s0.append(1,c); 
        while(1 == _map.count(s0)){ // get the longest matching string
            s1.append(1,c);
            c = infile.get();
            if(infile.eof()){
                break;
            }
            else{
                s0.append(1,c); 
            }
        }
        if(infile.eof()){ // if break for reaching end of file then simply write code word to output file 
            val = _map[s1];
            c_temp = val/128;
            outfile.write(&c_temp, 1) ;
            c_temp = val  % 128;
            outfile.write(&c_temp, 1) ;
            outfile.close();
            infile.close(); // terminate 
            return ;
        }
        else{ // map new key to codeword 
            val = _map[s1];
            _map[s0]=sym++;// sym+1, update new code word for next use
            c_temp = val/128;
            outfile.write(&c_temp, 1) ;
            c_temp = val  % 128;
            outfile.write(&c_temp, 1) ;
            s1.clear();
            s0.clear(); 
            s0.append(1,c); // for single string is already in dictionary, we append c to both s0, and s1
            s1.append(1,c);
        }
    }
    outfile.close();
}

// LZW decompress algorithm 
void decompress( char* inf, char* outf)
{
    char ch,cl,c_temp;
    U16_t  val ;
    string s0,s1,s_temp;

    std::ifstream infile(inf, std::ios::in);
    std::ofstream outfile(outf, std::ios::out | std::ios::trunc);
    if (!outfile.is_open()) {
        std::cerr << "Unable to open file for writing" << '\n';
        exit(-1);
    }
    if (!infile.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(-1);
    }
    init_inverse_map();
    s0.clear();
    s1.clear();
    ch =  (char)infile.get();
    cl =  (char)infile.get();
    while (!infile.eof()) 
    {
        val = 128 * (int)ch + (int)cl; // construct code word from 2 input byte
        if(!_inverse_map.count(val)){ // if code word not in dictionary, then it is proved to 
                                     //consist of the same charctor, and map[code] =  concate(str0.
                                     // str0.back())
            c_temp = s0.back();
            assert(s0.length()>0);
            s0.append(1,c_temp);
            assert(sym == val);
            _inverse_map[sym] = s0 ;
            sym++;
            outfile.write(s0.c_str(), s0.length()); // write new key string to output file 
        }
        else{
            if(0 == s0.length()){ // if s0 is equeal to 0(this must happen at the beginning of algorithm)
                s0 = _inverse_map[val] ;
                outfile.write(s0.c_str(), s0.length());
            }
            else{
                s_temp = _inverse_map[val]; 
                outfile.write(s_temp.c_str(), s_temp.length());
                s0.append(1,s_temp.front());
                _inverse_map[sym] = s0 ; // in order s0 should corresponse to sym 
                s0= s_temp;
                sym++;  // udpate sym for next use
            }
        }
        ch =  infile.get(); // to construct new code word
        cl =  infile.get();
    }
    infile.close();
    outfile.close();
}

int main(int argc, char* argv[])
{
    string usage("Usage: lzw [-d] [-o output_file_name] filename\n d : decompress input file     default: compress file\n");
    char *inf = NULL , *outf0 = "compressed", *outf1= "decompressed";

    if(argc == 1 ){ // only program name, print usage 
        cout << usage ;
        exit(-1);
    }
    if(argc ==  2 ) { // no -d , compress file 
        inf = argv[1];
        compress(inf,outf0);
    }
    if(argc == 3 ){
        if(argv[1][0] == '-' && argv[1][1]  =='d' ){
            inf = argv[2];// -d , decompress 
            decompress(inf, outf1);
        }
        else{
            // bad command format, print usage, quit
            cout << argv[1];
            cout << usage;
            exit(-1);
        }
    }
    if(argc == 4){
        // specify output file name
        if(0 == strcmp(argv[1], "-o")){
            outf1 = argv[2];
            inf  = argv [1];
            compress(inf, outf0);
        }
        else{
            cout << usage ;
            exit(-1);
        }
    }
    if(argc == 5){
        if(strcmp(argv[1], "-d") && strcmp(argv[1], "-o"))
        {
            outf1 = argv[2];
            inf  = argv [1];
            decompress(inf, outf1);
        }
        else{
            cout << usage ;
            exit(-1);
        }
    }

}
