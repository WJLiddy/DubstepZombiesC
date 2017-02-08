//linklibraries.cpp
//takes in shell input of 
//files and what they rely on
//forms a graph that determines what libraries need linked first!

#include <iostream>
#include <cstddef> // NULL ptr
#include <vector> // vector
#include <string> // string
using namespace std; // for cin >>

class Library{
private:
    string name;
    string extension; //I.E., .cpp or .h
    vector<string> include;//Files included - necesarry for order of linkedness
public:
    //Constructors:
    Library(){}
    Library(string fName, string fExtension)
    {name = fName; extension = fExtension;}    

    //Mutators:
    void setName(string fName){name = fName;}
    void setExtension(string fExt){extension = fExt;}
    void addDeps(vector<string> deps){include = deps;}

    //Getters:
    string getName() const{return name;}
    string getExtensions() const{return extension;}
    vector<string> getDeps() const{return include;}
};


class LibraryTree{
private:
    //The Idea is that we have a graph of what all other files 
    vector<Library> libs;
    //The linked list portion of the filenod
public:
    //Default ctr not needed
    bool inLibrary(string name){ //Is the library existant?
	for (int index=0; index < libs.size(); index++){
	    if (name == libs[index].getName())
		return true;
	}
	return false;
    }


    /*Addlibrary - add a library to the tree of libraries
	name - name of library
	Deps- What other libraries does this depend on?*/

    void addLibrary(string name, vector<string> Deps)
    {
	Library newLib(name, ".cpp");
	newLib.addDeps(Deps);
	libs.push_back(newLib);
    }
    void addLibrary(string name, string extension, vector<string> Deps)
    {
	Library newLib(name, extension);
	newLib.addDeps(Deps);
	libs.push_back(newLib);
    }

    /*analyzeAndReturn - analyze the library, and return 
	TARGET_LINK_LIBRARIES(lib1 dep1-1)
	TARGET_LINK_LIBRARIES(lib1 dep1-2)
	...
	TARGET_LINK_LIBRARIES(lib2 dep2-1)
	...*/
    //TODO: What if the library does not exist?
    vector<string> analyzeAndReturn(){
	vector<string> returnVector;
	for(int index = 0; index < libs.size(); index++){
	    string name = libs[index].getName();//get current name
	    vector<string> currLibDeps = libs[index].getDeps();//Look at current lib	    
	    for(int subIndex = 0; subIndex < currLibDeps.size(); subIndex++){
		string link = "target_link_libraries(";
		//add name plus dependant
		//BUT ONLY IF IT IS A REAL LIBRARY
		if (inLibrary(currLibDeps[subIndex])){
		    link = link + name + ' ' + currLibDeps[subIndex] + ')';
		    returnVector.push_back(link); 
		}
	    }
	}
	return returnVector;
    }
};

bool inVect(vector<string> names, string name){
    for(int index = 0; index < names.size(); index++){
	if (names[index] == name)
	    return true;
    }
    return false; //end of list
}

//Remove #include "../dda/ws/FILENAME.dw"
//and retrieve FILENAME
string rmInclude(string lib){
    //Cut of " at end:
    lib = lib.substr(0, lib.size() - 2);
    std::size_t dot = lib.find_last_of('.');
    std::size_t fileStart = lib.find_last_of("/\"");
    string filename = lib.substr(fileStart + 1, dot - fileStart - 1);
    return filename;
}


int main(){
   
    string libname;//To hold a library until it is ready for adding
    vector<string> deps;//librarys that depend on libname
    LibraryTree tree;//To hold all the names of all libraries
    string input;
    while (getline(cin, input)){
	//if the line don't start with #, its a library. 
	if (input[0] != '#'){
	    if (libname.size() != 0){
//		cout << "Appending Library " << libname << endl;
		tree.addLibrary(libname, deps);
		deps.clear(); // clear the dependancies
	    }
	    libname = input; 
//	    cout << "Created Library " << libname << endl;
	}
	//If it does, then its a library that is depended on 
	if (input[0] == '#'){
	    //then get rind of the #include "
	    //                     0123456789	
	    // and the .h at the end 
	    //	There are 13 characters in #include_" and .h" 
	    //  combined. Later we can check for .cpp's by seeing
	    //	if the third to last character is a .
	    //  Also- Don't add the library to itself
	    if ((!inVect(deps, rmInclude(input))) 
		&& (rmInclude(input) != libname) ){

//		cout << "Adding " << rmInclude(input)  
//		     << " to " << libname <<  endl;
	    	deps.push_back(rmInclude(input));
	    }
	}    
    }
    //And finally, add the last library:
    if (libname.size() != 0){
//	cout << "Appending library " << libname << endl;
	tree.addLibrary(libname, deps);
	deps.clear();
    }

    //Now cout all of the target_things
    vector<string> output = tree.analyzeAndReturn();
    for (int index = 0; index < output.size(); index++){
	cout << output[index] << endl;
    }


	


	

    return 0;
}

