//Christopher deWolf
//

#include <iostream>
#include <cmath>
#include <fstream>        
#include <ctime>
#define MAXSIZE 2100000   // sets maxsize of file 
using namespace std;

void bubblesort( signed long int data[], int n)      //bubblesort function declaration
{
	ofstream outfile;                              

	double begin_time = clock();       //start clock
	for( int i = 0; i < n-1; i++)           
	{
		for( int j = n-1; j > i; --j)     // loop starting from last and decrementing
		{
			if( data[j] < data[j-1])      //checking if current value is smaller than previous then sorts the two
			{
				signed long int t = data[j]; 
				data[j] = data[j-1];
				data[j-1] = t;
			}
		}
			
	}
	double end_time = clock();        //end clock
	double cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;   //finds time
	cout << cpu_time_used << endl;
	outfile.open("/home/ubuntu/ece2620/labs/lab5/src/lab5_bubbleout.txt");
	for( int i = 0; i < n; ++i)
	{
			outfile << data[i] << " ";        //puts the sorted data into the bubbleout text file
	}
	outfile.close();                          //closes the outfile
}

void merge( signed long int *data, signed long int first, signed long int last, signed long int mid, signed long int *temp)
{
	signed long int i1=0;
	signed long int i2 = first;     //establishes the subarrays
	signed long int i3 = mid+1;

	while( i2 <= mid && i3 <= last)  //checks to see if array2 and array3 contain elements
	{
		if( *(data+i2) < *(data+i3))
		{
			*(temp+i1) = *(data+i2);    //sets the temp pointer and increments
			++i1;
			++i2;
		}
		else 
			{
				*(temp+i1) = *(data+i3);    //sets temp pointer and increments
				++i1;
				++i3;
			}
	}	
	while( i2 <= mid )                 //loads array into temp
	{
		*(temp+i1) = *(data+i2);
		i1++;
		i2++;
	}
	while( i3 <= last)                 //loads array into temp
	{
		*(temp+i1) = *(data+i3);     
		i1++;
		i3++;
	}
	for( int i = 0; i < (last-first+1); ++i)    //loads temp into array
		{
			*(data+(first+i)) = *(temp+i);
		}

}

void mergesort( signed long int *data, signed long int first, signed long int last, int n, signed long int *temp) {
	signed long int mid;
	
	if( first < last)
		{
			mid = (first + last) / 2;              
			mergesort( data, first, mid, n, temp);   //calls itself
			mergesort( data, mid+1, last, n, temp);  //calls itself
		
			merge( data, first, last, mid, temp);    //calls the merge function

		}
}


int main()
{
	ifstream infile; 
	
	int count = 0;
	int v;
	int n = 0;
	
	signed long int x;
	infile.open("/home/ubuntu/ece2620/labs/lab5/src/lab5biginputfile.txt");  //checks an input file and checks if runs
			if( infile.fail())
			{
				cout<< "ERROR: Program could not open input file" << endl;
				return 1;
			}
				else
				{
					cout << "Input file open successfully" << endl;
		
				}

	while(!infile.eof())        //reads file until the end of file and increments n for every value to get n number of elements
			{ 
				infile >> x;
				n++;
			}
	infile.close();
	signed long int *data = new signed long int[n];   //creates dynamic array of data
	if( data == NULL)                                 
	{
		cout << "ERROR: Operating System could not allocate memory." << endl;
		return 1;
	}

	signed long int first = 0;                      //declares first and last variables
	signed long int last = n;
	signed long int *temp = new signed long int[n];  //creates dynamic array of temp
	if( temp == NULL)
	{
		cout << "ERROR: Operating System could not allocate memory." << endl;
		return 1;
	}
	
	ofstream outfile;
	while(1)                                            //while loop outside of switch statement and exits if 0 (case 4)
	{
	cout << "(1) Read Data from input file" << endl;
	cout << "(2) Sort Data usig Bubble Sort" << endl;
	cout << "(3) Sort Data using Merge Sort" << endl;
	cout << "(4) Exit" << endl;
    cin >> v;

		
	switch(v){          //switch statement based on what choice they input
		
		case 1: 
			infile.open("/home/ubuntu/ece2620/labs/lab5/src/lab5biginputfile.txt");   //loads in the file
			if( infile.fail())
			{
				cout<< "ERROR: Program could not open input file" << endl;
				return 1;
			}
				else
				{
					cout << "Input file open successfully" << endl;
		
				}
			for( int i = 0; i < n; ++i)         //reads in the elements of the file and puts into dynamic array data
			{
				infile >> *(data+i);
			}
			
		    break;
		case 2:
				bubblesort(data, n);       //calls bubblesort: O(n^2)
			    
			break;
		case 3:
		{
			double begin_time2 = clock();               //start clock
			mergesort(data, first, last, n, temp);     //calls mergesort: O(n*logn)
			double end_time2 = clock();        //end clock
			double cpu_time_used2 = (end_time2 - begin_time2) / CLOCKS_PER_SEC;
			cout << cpu_time_used2 << endl;
			outfile.open("/home/ubuntu/ece2620/labs/lab5/src/lab5_mergeout.txt");
			for( int i = 0; i < n; ++i)
				{
					outfile << data[i] << " ";        //copy the elements in dynamic array data into the output file
				}
			outfile.close();
			
			break;
				}
		case 4:
			return 0;
			
		default:								//prints "Invalid Input" for any invalid inputs
			cout << "Invalid input" << endl;
			break;
		} 
	
	}

	delete[] data;                                  // deletes both dynamic arrays
	delete[] temp;
	
	return 0;
}



