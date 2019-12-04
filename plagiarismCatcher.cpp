#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct Node {
	int index;
	struct Node* next;
} Node;


/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void readFile(string dir, string fileName) {
	string line;
	ifstream myfiles((dir + "/" + fileName).c_str());
	if(myfiles.is_open()) {
		while(getline(myfiles, line)) {
			cout << line << endl;
		}
	}
}

void readWords(string dir, string fileName) {
	string word;
	ifstream myfiles((dir + "/" + fileName).c_str());
	if(myfiles.is_open()) {
		while(myfiles >> word) {
			cout << word << endl;
		}
	}
}

unsigned long hashChunk(vector<string> chunk){
	string megaChunk = "";
	unsigned long power = 1;
	unsigned long sum = 0;
	for(int i = 0; i < chunk.size(); i++){
		megaChunk = megaChunk + chunk[i];
	}
	for(int i = 0; i < megaChunk.length(); i++){
		sum += (unsigned long)(megaChunk[i]*power);
		power = power * 7;
	}
	sum = sum % 1500007;
	return sum;
}

void addNode(Node* hashTable[], int index, int fileNum) {
	Node* entry = new Node;
	entry->index = fileNum;
	entry->next = NULL;
	if(hashTable[index] == NULL){
		hashTable[index] = entry;
	} 
	else {
		entry->next = hashTable[index];
		hashTable[index] = entry;
	}
}	
	

void printChunks(string dir, string fileName, Node* hashTable[], int fileNum) {
	std::queue<string> chunks;
	string word;
	int index = 0;
	ifstream myfiles((dir + "/" + fileName).c_str());
	if(myfiles.is_open()) {
		while(myfiles >> word) {
			transform(word.begin(), word.end(), word.begin(), ::toupper);	
			for(int i = 0; i < word.length(); i++) {
				if(!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9'))) {
					word.erase(word.begin() + i);
					i--;
				}
			}
			chunks.push(word);
		}
		vector<string> line = vector<string>();
		for(int i = 0; i < 6; i++) {
			line.push_back(chunks.front());
			chunks.pop();
		}

		index = hashChunk(line);
		addNode(hashTable, index, fileNum);

		/*
		for(int i = 0; i < line.size(); i++) {
			cout << line[i] << " ";
		}
		*/		

		while(chunks.size() > 0) {
			line.erase(line.begin());
			line.push_back(chunks.front());
			chunks.pop();
			index = hashChunk(line);
			addNode(hashTable, index, fileNum);
			/*
			for(int i = 0; i < line.size(); i++) {
				cout << line[i] << " ";
			}
			cout << endl;
			*/
		}		
		
	}
}	


int main()
{   
	Node* hashTable[1500007];
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);
	files.erase(files.begin());
	files.erase(files.begin());	
/*
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }
*/	
	for(int i = 0; i<1500007; i++){
		hashTable[i] = NULL;
	}
		
	
//	readFile(dir, files[0]);    
//	readWords(dir, files[0]);
	int fileNum = 1;
	printChunks(dir, files[1], hashTable, fileNum);	
	int x = 0;	
	return 0;
}
