#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

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

void printChunks(string dir, string fileName) {
	std::queue<string> chunks;
	string word;
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
		for(int i = 0; i < line.size(); i++) {
			cout << line[i] << " ";
		}
		while(chunks.size() > 0) {
			line.erase(line.begin());
			line.push_back(chunks.front());
			chunks.pop();
			for(int i = 0; i < line.size(); i++) {
				cout << line[i] << " ";
			}
			cout << endl;
		}		
	}
}	

int main()
{
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);
	files.erase(files.begin());
	files.erase(files.begin());	

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }
	
//	readFile(dir, files[0]);    
//	readWords(dir, files[0]);
	printChunks(dir, files[1]);	
	
	return 0;
}
