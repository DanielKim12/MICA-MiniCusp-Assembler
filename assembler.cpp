#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <utility>
#include <algorithm>
#include <iomanip>
using namespace std;

// base 10 to base 16 converter   --> (confiremed)
string baseconvert(int k) {
    string b = "0123456789ABCDEF";
    string ans = "";
    while (k != 0) {
        ans = b[k % 16] + ans;
        k = k / 16;
    }
    if (ans.length() != 3) {
        ans.insert(0, 3 - ans.length(), '0');
    }
    return ans;
}

int main(int argc, char* argv[]) {
    string myText;
    ifstream myReadtxt(argv[1]);
    unordered_map<string,string> label;
    int i = 0;
    string x = "";
    string re = "";
    // this will read the input file line by line and make symbol tables on pass 1
    // the symbol table will be used to generate address for the labels
    while (getline(myReadtxt, myText)) {
        x = baseconvert(i);   // x will be in form of 000 or 001 or 010 etc
        re = myText;
        myText.erase(remove(myText.begin(), myText.end(), ' '), myText.end());
        re.pop_back();
        if (label.find(re) != label.end()) {   //it already exists in the code
             cerr << "ASSEMBLER ERROR: label defined multiple times." << endl;
            return -1;
         }
        // operand (LSA) or .word
        if(isupper(myText[0]) || (myText[0] == '.')) {
            i++;
        } else if (islower(myText[0])) {
            pair<string, string> result;
            result = make_pair (re,x);  // stores the current
            label.insert(result);
        }
}
    //store all the possible operand
unordered_map<string, string> op;
    op["LDA"] = "00";
    op["LDX"] = "01";
    op["LDS"] = "02";
    op["LDF"] = "03";
    op["STA"] = "04";
    op["STX"] = "05";
    op["STS"] = "06";
    op["STF"] = "07";
    op["PSH"] = "08";
    op["POP"] = "09";
    op["CLR"] = "0A";
    op["SET"] = "0B";
    op["ADA"] = "10";
    op["ADX"] = "11";
    op["ADS"] = "12";
    op["ADF"] = "13";
    op["SBA"] = "14";
    op["SBX"] = "15";
    op["SBS"] = "16";
    op["SBF"] = "17";
    op["MUL"] = "18";
    op["DIV"] = "19";
    op["MOD"] = "1A";
    op["CMA"] = "20";
    op["CMX"] = "21";
    op["CMS"] = "22";
    op["CMF"] = "23";
    op["JSR"] = "41";
    op["JEQ"] = "48";
    op["JLT"] = "4A";
    op["JGE"] = "4B";
    op["PSHA"] = "FFF010";
    op["PSHX"] = "FFF011";
    op["PSHF"] = "FFF012";
    op["POPA"] = "FFF013";
    op["POPX"] = "FFF014";
    op["POPF"] = "FFF015";
    op["SHRA"] = "FFF022";
    op["SHLA"] = "FFF023";
    op["RTN"] = "FFF040";
    op["NOP"] = "FFF038";
    op["HLT"] = "FFFFFF";
   
unordered_map<string, string> map;
    map["#"] = "0";
    map[""] = "2";
    map["+"] = "4";
    map["*"] = "6";
    map["&"] = "8";
    map["#!"] = "1";
    map["!"] = "3";
    map["+!"] = "5";
    map["*!"] = "7";
    map["&!"] = "9";

    // This is when the program finds the .word in the input file  --> condition for the .word
    // pass 2
    ofstream output(argv[2]);
    ifstream mRead(argv[1]);
    while (getline(mRead, myText)) {
        myText.erase(remove(myText.begin(), myText.end(), ' '), myText.end());
        char c = myText[0];
        if(c == '.') {  //<should work if it reads the file>
            //skips the .word and find the operand/value that comes after
            stringstream ss;
            string res = "";
            for(unsigned int j = 5; j < myText.length(); j++) {
                ss << myText[j];
            }
            ss >> res;                  //convert each character into strings (confirmed)
            if(res.length() != 6) {
                output << setfill('0') << setw(6) << res << endl;   // add the leading 0's (confirmed)
            } else {
                output << res << endl;  //580000
            }
        }
        
    // when the program finds the cap char, it will determine the operand, where it could be
    // in a size of 3 or 4, if 4 it will print the value as it is (exceptional case) --=> condition for operand
        char b = myText[3];
        char f = myText[4];
        stringstream os;
        stringstream ap;
        stringstream ip;
        string val = "";
        string ji = "";
        string po = "";
        // this is the condition for exceptional cases
        // this condition is to find RTN || NOP || HLT operand -> executes right away    (confirmed)
        if((c == 'R') || (c == 'N') || (c == 'H')) {
            for (int i = 0; i < 3; i++) {
                os << myText[i];
            }
            os >> val;
            output << op.at(val) << endl;
        }
            // this is condition for the 4 char operands -> executes right away
            // check this by very first and very last char to see if they are cap
        if (isupper(b) && isupper(c)) {
            stringstream lt;
            string z = "";
            for (int i = 0; i < 4; i++) {
                lt << myText[i];
            }
            lt >> z;
            output << op.at(z) << endl;
        }
        if (isupper(myText[0])) {
            stringstream ps;
            string m = "";
            for (int p = 0; p < 3; p++) {
                ps << myText[p];
            }
            ps >> m;  // find LDA
            stringstream as;
            string s = "";
            //int num = 0;
            if (b == '$') {   // 3rd char $
                string g = "";
                for(unsigned int i = 4; i < myText.length(); i++){
                    as << myText[i];
                }
                as >> s;  //s will be the string
                s.insert(0, 3 - s.length(), '0');
                output << op.at(m) << map.at(g) << s << endl;
            } else if (islower(b)) {   //LDA label1
                string list ="";
                string g ="";
                stringstream nk;
                for(unsigned int i = 3; i< myText.length(); i++){
                    nk << myText[i];
                }
                nk >> list;
                if(label.find(list) == label.end()) {
                    cerr << "ASSEMBLER ERROR: undefined label." << endl;
                    return -1;
                }
                output << op.at(m) << map.at(g) << label.at(list) << endl;
            }
            
            else if ((b == '0') ||(b == '1') || (b == '2') || (b == '3') || (b == '4') || (b == '5') || (b == '6') || (b == '7') || (b == '8') || (b == '9')) {  //when [3] is value
                string g = "";
                stringstream gq;
                string r = "";
                for(unsigned int i = 3; i < myText.length(); i++){
                    gq << myText[i];
                }
                gq >> r;
                stringstream lp(r);
                int hq = 0;
                lp >> hq;
                output << op.at(m) << map.at(g) << baseconvert(hq) << endl;
            } else if ((b == '#') || (b == '+') || (b == '!') || (b == '*') || (b == '&')) {
                string check1;
                check1 += b;
                if (check1== "#") {
                if((m == "STA")|| (m == "STS")||(m == "POP")||(m == "CLR")||(m == "SET")||(m == "JSR")||(m == "JEQ")||(m == "JLT")||(m == "JGE") || (m == "STX")||(m == "STF")){
                   cerr << "ASSEMBLER ERROR: instruction using unsupported addressing mode." << endl;
                   return -1;
                    }
                }
                ip << b;
                if (f == '!') {  //4th char '!'
                    ip << f;
                    string check;
                    check += f;
                    if (check == "#!") {
                    if((m == "STA")|| (m == "STS")||(m == "POP")||(m == "CLR")||(m == "SET")||(m == "JSR")||(m == "JEQ")||(m == "JLT")||(m == "JGE") || (m == "STX")||(m == "STF")){
                    cerr << "ASSEMBLER ERROR: instruction using unsupported addressing mode." << endl;
                    return -1;
                        }
                    }
                    if (islower(myText[5])) {  // LDA#!label1
                        stringstream qi;
                        string u = "";
                        for (unsigned int i = 5; i < myText.length(); i++){
                            qi << myText[i];
                        }
                        qi >> u;
                        // to check if it was declared
                        if(label.find(u) == label.end()) {
                            cerr << "ASSEMBLER ERROR: undefined label." << endl;
                            return -1;
                        }
                        ip >> po;
                        output << op.at(m) << map.at(po) << label.at(u) << endl;
                    } else if (myText[5] == '$') { //5th $
                        stringstream qi;
                        string lam = "";
                        for (unsigned int i = 6; i < myText.length(); i++) {
                            qi << myText[i];
                        }
                        qi >> lam;
                        ip >> po;
                        lam.insert(0, 3 - lam.length(), '0');
                        output << op.at(m) << map.at(po) << lam << endl;
                    } else if((myText[5] == '0') ||(myText[5] == '1') || (myText[5]  == '2') || (myText[5] == '3') || (myText[5] == '4') || (myText[5] == '5') || (myText[5] == '6') || (myText[5] == '7') || (myText[5] == '8') || (myText[5] == '9')) { //5th number
                        for (unsigned int i = 5; i < myText.length(); i++) {
                            ap << myText[i];
                        }
                        ap >> ji;   //ji the value
                        stringstream bi(ji);
                        int e = 0;
                        bi >> e; //bi the int of the string
                        ip >> po;
                        output << op.at(m) << map.at(po) << baseconvert(e) << endl;
                    }
                } else if (islower(f)) {  //4th label
                    stringstream up;
                    string gk;
                    for (unsigned int i = 4; i < myText.length(); i++){
                        up << myText[i];
                    }
                    up >> gk;
                    if(label.find(gk) == label.end()) {
                        cerr << "ASSEMBLER ERROR: undefined label." << endl;
                        return -1;
                    }
                    ip >> po;
                    output << op.at(m) << map.at(po) << label.at(gk) << endl;
                } else if (f == '$') {   //4th char being an '$'  --> LDA#$58
                    stringstream pp;
                    string ah = "";
                    for(unsigned int k = 5; k < myText.length(); k++) {
                        pp << myText[k];
                    }
                    pp >> ah;
                    ip >> po;
                    ah.insert(0, 3 - ah.length(), '0');
                    output << op.at(m) << map.at(po) << ah << endl;  //operand + addy + val
                } else {    //4th number
                    stringstream zz;
                    string ls = "";
                    for(unsigned int j = 4; j < myText.length(); j++){
                        zz << myText[j];
                    }
                    zz >> ls;
                    stringstream jp(ls);
                    int kp = 0;
                    jp >> kp;
                    ip >> po;
                    output << op.at(m) << map.at(po) << baseconvert(kp) << endl;   //operand + "addressing mode" + converted hex
                    }
            }
    }
}


    
}
