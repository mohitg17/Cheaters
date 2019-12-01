#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

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
	
	readFile(dir, files[0]);    

	return 0;
}
