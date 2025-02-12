/*
 * EclipseR.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: Justin
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "EclipseR.h"

#include "../test/UnitTests.h"

using namespace std;


int main()
{
	//UNCOMMENT BELOW TO RUN UNIT TESTS HERE
	//UnitTests unitTest;

	//Create the linked list of Eclipse objects
	AVLTree<Eclipse> eclipseTree;

	//Create a FileInput object that will take care of all data input
	FileInput fileInput;

	//Load the data that the user wants
	dataInputLoop(eclipseTree, fileInput);

	//If the user actually gave us files with data, then continue, else exit.
	if(eclipseTree.getSize() > 0)
	{
		//Manipulate the data however the user wants until the program ends.
		dataManipLoop(eclipseTree, fileInput);
	}

	cout << "Thanks for using EclipseR!\n";

	return 0;
}

void dataInputLoop(AVLTree<Eclipse>& eclipseTree, FileInput& fileInput)
{
	//File name to load
	string filename = " ";

	//Is the file load a success?
	bool result = false;

	//While the user is entering real filenames
	while(!result)
	{
		cout << "Enter a data file name: ";
		getline(cin, filename);

		//If the file name is legitimate, load the file
		if(filename != "")
		{
			result = fileInput.loadFile(eclipseTree, filename);
		}
		else
		{
			break;
		}
	}
}

void dataManipLoop(AVLTree<Eclipse>& eclipseTree, FileInput& fileInput)
{
	//Create a data operations object for searching and sorting
	EclipseOperations dataOps;

	//Create a string to contain user input
	string userInput = "";
	string filename = "";

	//Did the file load successfully
	bool fileLoadResult = false;

	//Create the array for searching and sorting purposes
	ResizableArray<Eclipse> eclipseArray;

	//Load Linked List data into array
	eclipseArray = eclipseTree.buildArray();

	//Create a linked Hash table for fast lookup of eclipses by catalog number
	//Aim for a load factor of 0.7
	LinkedHashTable<Eclipse> eclipseHashTable(10*eclipseTree.getSize()/7);

	//Load the data into the hash table
	for(int ii = 0; ii < eclipseArray.getNumElements(); ++ii)
	{
		eclipseHashTable.insert(eclipseArray.get(ii).getCell(0).getIntValue(), eclipseArray.get(ii));
	}

	//Stay in the loop until the user presses quit
	while(userInput != "Q")
	{
		//Ask for user input
		cout << "(O)utput, (S)ort, (F)ind, (M)erge, (P)urge, (C)atalog Order, (L)inked, (H)ash, P(R)e Order, Pos(T) Order, or (Q)uit?\n";
		getline(cin, userInput);

		//If the user wants to output the list:
		if(userInput == "O")
		{
			ofstream outputFile;
			string outputUserInput = "";
			bool usingStdout = false;

			//Until the user enters an available file, or no file, ask for more input
			while(true)
			{
				cout << "Enter the name of an output file: ";
				getline(cin, outputUserInput);

				//They entered nothing: use stdout
				if(outputUserInput == "")
				{
					usingStdout = true;
					break;
				}
				else
				{
					outputFile.open(outputUserInput.c_str());
				}

				if(outputFile.good())
				{
					break;
				}
				else
				{
					cerr << "File is not available.\n";
				}
			}

			//Output to stdout if it was selected
			if(usingStdout)
			{
				cout << fileInput.getHeader() << endl;
				cout << eclipseArray;
				cout << endl;
				cout << "Data lines read: " << fileInput.getTotal();
				cout << "; Valid eclipses read: " << fileInput.getNumValid();
				cout << "; Eclipses in memory: " << eclipseArray.getNumElements();
				cout << endl;
			}
			else //Output to file instead
			{
				outputFile << fileInput.getHeader();
				outputFile << endl;
				outputFile << eclipseArray;
				outputFile << endl;
				outputFile << "Data lines read: " << fileInput.getTotal();
				outputFile << "; Valid eclipses read: " << fileInput.getNumValid();
				outputFile << "; Eclipses in memory: " << eclipseArray.getNumElements();
				outputFile << endl;
			}
		}
		else if(userInput == "S") //If the user selected sort:
		{
			int col;
			string c;

			//Request the column to sort
			cout << "Data field (2-18)?\n";
			getline(cin, c);

			//If the user did not just press enter, attempt to convert the input
			if(c != "")
			{
				try{
					col = fileInput.convertStrToInt(c);

					//Only operate on valid column numbers
					if(col >= 2 && col <= 18)
					{
						//Change to 0 indexing
						col = col - 1;

						//Sort on that column number
						dataOps.sort(col, eclipseArray);
					}
				}
				catch(...)
				{
					//The user entered an invalid value, reset to manip loop
				}
			}
		}
		else if(userInput == "F") //If the user wanted to find a certain value
		{
			int col;
			string value, c;

			//Request the column to sort
			cout << "Data field (1-18)?\n";
			getline(cin, c);

			//If the user entered something
			if(c != "")
			{
				try{
					//Convert the value...
					col = fileInput.convertStrToInt(c);

					//Only operate on valid column numbers
					if(col >= 1 && col <= 18)
					{
						col = col - 1;

						//If this is supposed to be a int, convert it and find
						if(col == 0 || col == 1 || col == 2 || col == 4 || col == 6 || col == 7 || col == 8 || col == 14 || col == 15 || col == 16)
						{
							cout << "Number to find?\n";
							getline(cin, value);

							try{
								int num = fileInput.convertStrToInt(value);
								Cell c(num);
								dataOps.find(col, c, eclipseArray, eclipseHashTable, fileInput);
							}
							catch(...)
							{
								//This is not a valid value to look for; give up
							}
						}
						else if(col == 10 || col == 11)
						{
							cout << "Number to find?\n";
							getline(cin, value);

							try{
								double fPoint = fileInput.convertStrToDouble(value);
								Cell c(fPoint);
								dataOps.find(col, c, eclipseArray, eclipseHashTable, fileInput);
							}
							catch(...)
							{
								//This is not a valid value to look for; give up
							}
						}
						else if(col == 3)
						{
							cout << "Month abbreviation to find?\n";
							getline(cin, value);

							bool valid = false;
							string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

							int i = 0;
							for(; i < 12; ++i)
							{
								if(value == months[i])
								{
									valid = true;
									break;
								}
							}

							//It is relatively unclear, but I will sort based on the abbreviation representation
							if(valid)
							{
								Cell c(i);
								dataOps.find(col, c, eclipseArray, eclipseHashTable, fileInput);
							}
						}
						else
						{
							cout << "Value to find?\n";
							getline(cin, value);

							if(col == 16 && value == "")
							{
								Cell c(0, true);
								dataOps.find(col, c, eclipseArray, eclipseHashTable, fileInput);
							}
							else
							{
								Cell c(value);
								dataOps.find(col, c, eclipseArray, eclipseHashTable, fileInput);
							}
						}
					}
				}
				catch(...)
				{
					//The user entered an invalid number, go back to manip loop
				}
			}
		}
		//The user wants to add more files to the list
		else if(userInput == "M")
		{
			try{
				cout << "Enter a data file name: ";
				getline(cin, filename);

				//If the file name is legitimate, load the file
				if(filename != "")
				{
					fileLoadResult = fileInput.loadFile(eclipseTree, filename);
				}

				//Only update the array if needed (if the file is not available, no need to reload)
				if(fileLoadResult)
				{
					//Rebuild the array
					eclipseArray = eclipseTree.buildArray();

					//Create a temporary hash table to restart
					LinkedHashTable<Eclipse> temp(10*eclipseTree.getSize()/7);

					//Set the master hash table to the blank slate
					eclipseHashTable = temp;

					//Load the data into the hash table
					for(int ii = 0; ii < eclipseArray.getNumElements(); ++ii)
					{
						eclipseHashTable.insert(eclipseArray.get(ii).getCell(0).getIntValue(), eclipseArray.get(ii));
					}
				}
			}
			catch(const char* msg)
			{
				cout << msg << endl;
			}
		}
		//The user has a file of eclipses they want to remove
		else if(userInput == "P")
		{
			cout << "Enter a data file name: ";
			getline(cin, filename);

			//If the file name is legitimate, load the file
			if(filename != "")
			{
				fileLoadResult = fileInput.loadFile(eclipseTree, filename, 1);
			}

			//Only update the array if needed (if the file is not available, no need to reload)
			if(fileLoadResult)
			{
				eclipseArray = eclipseTree.buildArray();

				//Create a temporary hash table to restart
				LinkedHashTable<Eclipse> temp(10*eclipseTree.getSize()/7);

				//Set the master hash table to the blank slate
				eclipseHashTable = temp;

				//Load the data into the hash table
				for(int ii = 0; ii < eclipseArray.getNumElements(); ++ii)
				{
					eclipseHashTable.insert(eclipseArray.get(ii).getCell(0).getIntValue(), eclipseArray.get(ii));
				}
			}
		}
		//Output by catalog number (i.e. output the linked list)
		else if(userInput == "C")
		{
			ofstream outputFile;
			string outputUserInput = "";
			bool usingStdout = false;

			//Until the user enters an available file, or no file, ask for more input
			while(true)
			{
				cout << "Enter the name of an output file: ";
				getline(cin, outputUserInput);

				//They entered nothing: use stdout
				if(outputUserInput == "")
				{
					usingStdout = true;
					break;
				}
				else
				{
					outputFile.open(outputUserInput.c_str());
				}

				if(outputFile.good())
				{
					break;
				}
				else
				{
					cerr << "File is not available.\n";
				}
			}

			//Output to stdout if it was selected
			if(usingStdout)
			{
				cout << fileInput.getHeader() << endl;
				cout << eclipseTree;
				cout << endl;
				cout << "Data lines read: " << fileInput.getTotal();
				cout << "; Valid eclipses read: " << fileInput.getNumValid();
				cout << "; Eclipses in memory: " << eclipseTree.getSize();
				cout << endl;
			}
			else //Output to file instead
			{
				outputFile << fileInput.getHeader();
				outputFile << endl;
				outputFile << eclipseTree;
				outputFile << endl;
				outputFile << "Data lines read: " << fileInput.getTotal();
				outputFile << "; Valid eclipses read: " << fileInput.getNumValid();
				outputFile << "; Eclipses in memory: " << eclipseTree.getSize();
				outputFile << endl;
			}
		}
		//Linked display
		else if(userInput == "L")
		{
			//Output insertion order to standard output
			cout << eclipseHashTable.getInsertionOrder() << endl;
		}
		//Hash display
		else if(userInput == "H")
		{
			//Output the hash table to standard output
			cout << eclipseHashTable;
			cout << endl;
		}
		else if(userInput == "R")
		{
			eclipseTree.printPreOrder();
			cout << endl;
		}
		else if(userInput == "T")
		{
			eclipseTree.printPostOrder();
			cout << endl;
		}
		//If the user wants out, leave the loop and exit the program
		else if(userInput == "Q")
		{
			break;
		}
		else
		{
			//The user entered bad information, so just ask again?
		}
	}
}
