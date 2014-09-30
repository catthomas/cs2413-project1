#include <iostream>
#include <cstring>
#include <fstream>
#include "BibEntry.h"
#include "String.h"
#include "Vector.h"
#include "TextField.h"
#include "Author.h"


//-------------------------------------------------------------------Main method functions
/*
This method implements a recursive binary search through
a Vector of bibliographic entries by looking at the title
of the bibliographic entry.
vec: The vector to be searched
title: Title of the desired bib entry
first: Search start position
Last: Search end position

Returns index of where it is/should be located.
*/
int recursiveBinarySearch(Vector<BibEntry>& vec, String& title, int first, int last)
{
	int mid;
	String midtitle; //stores title of bibentry in middle of vector
	int result; //stores result of binary search

	if (first < last)
	{
		mid = (first + last) / 2;
		midtitle = vec[mid].name();
		if (title == midtitle) return mid + 1;
		else if (midtitle < title)
			return recursiveBinarySearch(vec, title, mid + 1, last);
		else return recursiveBinarySearch(vec, title, first, mid);
	}
	else
	{
		if ((first == last) && (vec[first].name() < title))
			result = first + 1;
		else
			result = first;
	}
	return result;
}//end binarySearch

/*
This method inserts a bibliographic entry into it's
correct alphabetical position. It runs a recursive binary
search to locate the correct position.

vec: The vector in which the new entry should be added
bibentry: The bibentry to be added
*/
void insertInto(Vector<BibEntry>& vec, BibEntry bibentry)
{
	int position;
	position = recursiveBinarySearch(vec, bibentry.name(), 0, vec.size() - 1);
	vec.insert(bibentry, position);
} //end insertInto


//-------------------------------------------------------------Main method
/*
NAME: Catherine Thomas
DATE: 09/16/2014

Main method for 'PublicScholar'. It reads in a text file of bibliographic entries through
as instructed by the user, stores the data alphabetically based on the name of the entry,
then allows the user to search for a specific entry or to re-print the data to a file. 
*/
void main(){
	const int START_NUMBER_OF_ENTRIES = 100; //Size of initial vector that will hold bibliographic entries
	const int MAX_FILE_NAME_SIZE = 100; //Maximum file name size
	const int MAX_FILE_LINE_SIZE = 5000; //Maximum length of a single line
	const int MAX_FIELD_DESIGNATOR_SIZE = 20; //Maximum field designator size
	const int MAX_NUMBER_AUTHORS = 50; //Maximum number of authors
	const int MAX_AUTHOR_NAME_LENGTH = 150; //Maximum name of author length
	const int MAX_FIELD_VALUE_SIZE = 2000;
	Vector<BibEntry> allBibEntries(START_NUMBER_OF_ENTRIES); //Vector to contain all bib entries


	//--------------------------------------------Retrieve user input for name of text file
	cout << "Please enter the name of a text file with bibliographic data: " << endl;
	char filename[MAX_FILE_NAME_SIZE];
	cin.getline(filename, MAX_FILE_NAME_SIZE - 1);
	
	//---------------------------------------------Parse data from text file to all BibEntries
	ifstream myfile(filename);
	char data[MAX_FILE_LINE_SIZE]; //contains one line of file at a time
	BibEntry bibentry; //Hold one bibentry at a time
	if (myfile.is_open())
	{
		while (myfile.getline(data, MAX_FILE_LINE_SIZE-1))
		{
			//------------------------------ start parse data from file -----------//
			//Identified new entry with '@', build the bib entry TYPE and NAME
			if (data[0] == '@'){
				//---------- Entry type = char array between @ and next {
				int t = 0;
				char* bibType = new char[MAX_FIELD_DESIGNATOR_SIZE];
				int i = 1;
				while (data[i] != '{' && t < MAX_FIELD_DESIGNATOR_SIZE){
					bibType[t++] = data[i++];
				} //end while type loop
				bibType[t] = '\0';

				//---------- Entry name = char array between { and ,
				int n = 0;
				char* bibName = new char[MAX_FIELD_DESIGNATOR_SIZE];
				++i;
				while (data[i] != ',' && n < MAX_FIELD_DESIGNATOR_SIZE){
					bibName[n++] = data[i++];
				} //end while name loop
				bibName[n] = '\0';

				//------------Set type and name to bibentry-------------------------
				bibentry.setType(bibType);
				bibentry.setName(bibName);
			} //end @ if 
			else if (data[0] == '	'){ //Line starts with tab, take in a field designator and value
				//---------- fieldDesignator = char array after , and before = 
				//assumed to be no longer than 20 characters
				char* fieldDesignator = new char[MAX_FIELD_DESIGNATOR_SIZE];
				int fd = 0;
				int i = 1; //iterate up one
				while (data[i] != ' ' && data[i] != '=' && fd < MAX_FIELD_DESIGNATOR_SIZE){
					fieldDesignator[fd++] = data[i++];
				} //end while type loop
				fieldDesignator[fd] = '\0';


				//-------------------------- fieldValue = value between next *matching* {}
				//iterate line up to the next '{'
				while (data[i] != '{' && i < MAX_FILE_LINE_SIZE) {
					++i;
				}

				int authorCounter = i;
				//IF designator is 'author', make array of authors
				if (String(fieldDesignator) == "author"){
					Author* authors = new Author[MAX_NUMBER_AUTHORS];

					int unmatchedBracketCount = 1; //start with  one unmatched open bracket
					int authorCount = 0; //count number of authors created
					++i; //increment past first bracket
					int authorFieldSize = i;
					while (unmatchedBracketCount > 0 && i < MAX_FILE_LINE_SIZE - 4){
						//Build char arrays for individual author names
						char* authorName = new char[MAX_AUTHOR_NAME_LENGTH];
						int an = 0;
						while (unmatchedBracketCount > 0 &&
							!(data[i] == ' ' && data[i + 1] == 'a' && data[i + 2] == 'n' && data[i + 3] == 'd')){
							//Count brackets
							if (data[i] == '{')
								++unmatchedBracketCount;
							else if (data[i + 1] == '}')
								--unmatchedBracketCount;

							//Build author name
							authorName[an++] = data[i++];
						} //end while
						authorName[an] = '\0';

						//Add author name to array of authors
						authors[authorCount++].setName(authorName);

						//iterate past next and
						i = i + 4;
					} //end while

					//Tell bib entry the number of authors
					bibentry.setNumberOfAuthors(authorCount);
					//Add field to bibentry
				} //  end if author

				char* fieldValue = new char[MAX_FIELD_VALUE_SIZE];
				int unmatchedBracketCount = 1; //start with one unmatched open {
				int fv = 0;
				i = ++authorCounter; //iterate up one
				while (unmatchedBracketCount > 0 && fv < MAX_FIELD_VALUE_SIZE){
					if (data[i] == '{')
						++unmatchedBracketCount;
					else if (data[i + 1] == '}')
						--unmatchedBracketCount;

					fieldValue[fv++] = data[i++];
				} //end while value loop
				fieldValue[fv] = '\0';

				//Add field to bibentry
				bibentry.addField(TextField(fieldDesignator, fieldValue));
			} // end tab if	
			else if (data[0] == '}'){ //Line starts with a }, the bib entry is completed
				//Search for index of appropriate place to be added
				
				//Add Bibentry to appropriate place
				insertInto(allBibEntries, bibentry);

				//Reset bibentry to empty
				bibentry = BibEntry();

			} //end } else if
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	//Enter loop - ask user for appropriate action
	char userChoice = 'o';
	while (userChoice != 'E' && userChoice != 'e')
	{
		cout << "Enter S for search, D for delete, P for print, and E for exit." << endl;
		cin >> userChoice;
		cin.get(); //eats enter
		if (userChoice == 'S' || userChoice == 's'){ //'S' = search
			cout << "Enter the name of the bibliographic entry you would like to search for: " << endl;
			char entryname[MAX_FIELD_VALUE_SIZE];
			cin.getline(entryname, MAX_FIELD_VALUE_SIZE -1);
			String entrynameAsString = entryname;

			//Search for the entry
			int entryIndex = recursiveBinarySearch(allBibEntries, entrynameAsString, 0, allBibEntries.size()-1);

			if (entryIndex < allBibEntries.size() && allBibEntries[entryIndex].name() == entrynameAsString){ //check if position has matching name
				cout << allBibEntries[entryIndex] << endl;
			}
			else{
				cout << "There is no bibliographic entry with that name." << endl;
			}
		} //end search if statement
		else if (userChoice == 'D' || userChoice == 'd'){ //'D' = delete
			cout << "Enter the name of the bibliographic entry you would like to delete: " << endl;
			char entryname[MAX_FIELD_VALUE_SIZE];
			cin.getline(entryname, MAX_FIELD_VALUE_SIZE - 1);
			String entrynameAsString = entryname;

			//Search for the entry
			int entryIndex = recursiveBinarySearch(allBibEntries, entrynameAsString, 0, allBibEntries.size() - 1);

			if (allBibEntries[entryIndex].name() == entrynameAsString){ //check if position has matching name
				//Print bib entry
				cout << allBibEntries[entryIndex] << endl;

				//Ask user to confirm delete
				cout << "Are you sure you would like to delete this entry? Y/N" << endl;
				char response;
				cin >> response;
				cin.get(); //eats enter

				if (response == 'Y'){
					//Remove entry at index
					allBibEntries.remove(entryIndex);
					cout << "Success! The bibliographic entry was removed." << endl;
				}
				else if (response == 'N'){
					cout << "The entry was not deleted." << endl;
				}
				else{
					cout << "Invalid input." << endl;
				}
			}
			else{
				cout << "There is no bibliographic entry with that name." << endl;
			}
		} //end delete if statement
		else if (userChoice == 'P' || userChoice == 'p'){ //'P' = print
			cout << "Enter the name of the file you would like to print to or nothing to print to the console:" << endl;
			char filename[MAX_FILE_NAME_SIZE];
			cin.getline(filename, MAX_FILE_NAME_SIZE - 1);
			
			if (filename[0] == '\0'){ //user entered nothing, print to console
				cout << allBibEntries << endl;
			}
			else{ //write to file
				ofstream myfile;
				myfile.open(filename);
				for (int i = 0; i < allBibEntries.size(); ++i){
					myfile << allBibEntries[i] << endl;
				}
				myfile.close();
			}
		} //end print if statement
		else if (userChoice != 'E' && userChoice != 'e')
		{
			cout << "That was not a valid choice!" << endl;
		} //end else
	};

} //end main method

