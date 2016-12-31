#include <iostream>
#include <fstream>
#include <bitset>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
string bit_addition(string,string);
string ones_complement(string);
string to_string(int);


class Packet{
public:
	string destination;
	string source;
	string sequence;
	string checksum;
	string data_length;
	string data;	
public:
	Packet(){
		destination = source = sequence = checksum = data = data_length = "";
	}
	Packet(string,string,string,string,string,string);
};

bool check_checksum(Packet);
string printSourceDestination(Packet);
void file_written_word_poetry(list< list<Packet> >);
int get_total_packet_number(list<Packet>);
string look_for_packet(list<Packet>, int);
void removeDuplicates(list< list<Packet> >);

Packet::Packet(string destination, string source, string sequence, string checksum, string data_length, string data){
	this->destination = destination;
	this->source = source;
	this->sequence = sequence;
	this->checksum = checksum;
	this->data_length = data_length;
	this->data = data;
}

int main() {
	list< list<Packet> > l1, final_list;		
	int i;
	ifstream file("cases_in_order.in");	
	
	if(file.is_open()){
		string line, destination, source, sequence, checksum, data_length, data, data2;
		
		while(getline(file,line)){
			bool found_it = false;
			source = line.substr(0,32);
		 	destination = line.substr(32,32);
		 	sequence = line.substr(64,16);
		 	checksum = line.substr(80,16);
		 	data_length = line.substr(96,16);						
			
			int i = 112;
			data = "";
		 	while(i < line.length()){
		 		bitset<8> aChar(string(line.substr(i,8)));
		 		data2 += (char)(aChar.to_ulong());
		 		data += string(line.substr(i,8));
		 		i += 8;
		 	}

		 	Packet *packet = new Packet(source,destination,sequence,checksum,data_length,data);
			
			if(!l1.empty()){								
				for(list< list<Packet> >::iterator it = l1.begin(); it != l1.end(); it++){					
					for(list<Packet>::iterator it2 = it->begin(); it2 != it->end(); it2++){																							
						if(it2->source == packet->source && it2->destination == packet->destination){
							it->push_back(*packet);
							found_it = true;								
							break;
						}
					}
				}
				if(!found_it){					
					list<Packet> l2;
					l2.push_back(*packet);
					l1.push_back(l2);
				}
		 	} 
		 	else{		 		
		 		list<Packet> l2;
		 		l2.push_back(*packet);
		 		l1.push_back(l2);
		 		cout<<endl;
		 	}		 
 		} 		
	}

	i = 0;
	
	file_written_word_poetry(l1);
	file.close(); 	 	 	 	
	return 0;
}

string look_for_packet(list<Packet> l, int i){
	for(list<Packet>::iterator it = l.begin(); it != l.end(); it++){
		bitset<16> sequence(string(it->sequence));		
		if((short)(sequence.to_ulong()) == i){
			string res = "";
			if(!check_checksum(*it)) {				
				if(i != 0)
					res = "[line corrupted]";				
				else
					res = "[title corrupted]";
			} 
			else {				
				int j = 0;
				while(j < it->data.length()){
					bitset<8> aChar(string(it->data.substr(j,8)));
					res += (char)(aChar.to_ulong());					
					j+=8;
				}	
			}						
			if(i == 0){
				res += "\n" + printSourceDestination(*it);
			}

			return res;			
		}
	}	
	if(i == 0)
		return "[missing title]\n";
	return "[missing line]\n";
}

void file_written_word_poetry(list< list<Packet> > l) {
	ofstream file2("poems.in");
	
	for(list< list<Packet> >::iterator it = l.begin(); it != l.end(); it++) {
		int total_packets = get_total_packet_number(*it);		
		for(int i = 0; i < total_packets; i++){			
			cout<<look_for_packet(*it,i)<<endl;			
			file2<<look_for_packet(*it,i)<<endl;
		}

		cout<<endl;
		list< list<Packet> >::iterator it2 = it;

		if(++it2 != l.end()){
			for(int j = 0; j<80; j++){
				cout<<"-";
				file2<<"-";
			}
			cout<<endl<<endl;					
			file2<<endl<<endl;
		}
	}
	
	file2.close();
}

bool check_checksum(Packet p) {
	string checksum = p.checksum;
	p.checksum =  "0000000000000000";

	string bit_stream = p.source + p.destination + p.sequence + p.checksum;	

	if(&p.data != NULL) 
		bit_stream += p.data + p.data_length;

	string cumulative = bit_stream.substr(0,16);
	
	int i = 16;
	while(i < bit_stream.length()) {				
		string second_bts = bit_stream.substr(i,16);
		cumulative = bit_addition(cumulative,second_bts);				
		i+=16;
	}

	if(ones_complement(cumulative) == checksum)
		return true;

	return false;
}

string bit_addition(string first, string second){
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
 		temp = bit_addition(temp,"0000000000000001");

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

int get_total_packet_number(list<Packet> l) {	
	for(list<Packet>::iterator it = l.begin(); it != l.end(); it++) {
		bitset<16> seq_num(string(it->sequence));		
		if((short)(seq_num.to_ulong()) < 0){
			return -(short)(seq_num.to_ulong());
		}
	}
	return -1;
}

string printSourceDestination(Packet p){	
	int i = 0;	
	string res = "";
	while(i <p.destination.length()){
		bitset<8> first(string(p.destination.substr(i,8)));		
		res += to_string((int)(first.to_ulong()));
		
		i+=8;
		if(i != 32){
			res+=".";			
		}		
		else{
			res+="/";			
		}
	}	
	i = 0;
	while(i < p.source.length()){
		bitset<8> first(string(p.source.substr(i,8)));		
		res += to_string((int)(first.to_ulong()));

		i+=8;
		if(i != 32){
			res+=".";			
		}
	}	
	return res;
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