/* checksum algorithm
 * by jace roldan 11/2/16
 */

#include <iostream>
#include <bitset>
#include <string>
#include <stdlib.h>

using namespace std;
string bitAddition(string,string);
string ones_complement(string);
string to_string(int);
int main(){
	string a = to_string(16632);
	cout<<a<<endl;
	/*string sample_bit = "101011000110100101011001000101111011100101001011110100001001011100000000000000101110001001110110000000010011100001000011011011000110111101110011011001010010000001100010011011110111001101101111011011010010110101100110011100100110100101100101011011100110010000100000011011110110011000100000011101000110100001100101001000000110110101100001011101000111010101110010011010010110111001100111001000000111001101110101011011100011101100000000";
	string cumulative = sample_bit.substr(0,16);
	sample_bit.replace(80,16,"0000000000000000");
	
	int i = 16;
	while(i < sample_bit.length()) {				
		string second_bts = sample_bit.substr(i,16);
		cout<<cumulative<< " plus " << second_bts<<" equals ";
		cumulative = bitAddition(cumulative,second_bts);		
		cout<<cumulative<<endl;		
		i+=16;
	}


	cout<<ones_complement(cumulative)<<endl;
	return 0;*/
}
string to_string(int a){
	string res = "";
	char aBit;
	while(a>0){
		aBit = (a%10)+48;
		res = aBit+res;
		a /= 10;
	}
	return res;
}

string bitAddition(string first, string second){
 	int bit1, bit2, carry = 0; 	
 	string temp = "";
 	string ans;

 	for(int j = 15; j>=0; j--){
 		bit1 = (int)(first[j] - 48);
 		bit2 = (int)(second[j] - 48);

 		ans = (char)(((bit1 ^ bit2) ^ carry) + 48);
 		temp = ans + temp;

 		if((bit1 == 1 && bit2 == 1) || ((bit1 == 1 || bit2 == 1) && carry))
 			carry = 1; 
 		else
 			carry = 0; 		
 	}
 	if(carry == 1)
 		temp = bitAddition(temp,"0000000000000001");

 	return temp;
}

string ones_complement(string arg){
	for(int i = 0; i<arg.length(); i++){
		if(arg[i] == '1')
			arg[i] = '0';
		else if(arg[i] == '0')
			arg[i] = '1';
	}
	return arg;
}