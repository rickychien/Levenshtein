#include <iostream>
#include <fstream>
#include <string>
#include <queue>


using namespace std;

vector<string> loadfile(string filename);
void levenshtein_algo(vector<string> file1_content,vector<string> file2_content);
int minimum(int first,int second,int third);
int maxmum(int first,int second);
double similarity(int max_length,int min);

int main()
{
	vector<string> file1_content,file2_content;
	int i;
	file1_content = loadfile("test1.txt");
	file2_content = loadfile("test2.txt");
	levenshtein_algo(file1_content,file2_content);
	//test
	/*for(i = 0;i < file1_content.size();i++)
		cout<<file1_content[i];
	cout<<endl;
	for(i = 0;i < file2_content.size();i++)
		cout<<file2_content[i];*/
	system("pause");
	return 0;
}

vector<string> loadfile(string filename)
{
    vector<string> file_content;
	ifstream file(filename);
	string line;
	while(!file.eof())
	{
		getline(file,line);
		if (line.compare("") != 0)
		{
			file_content.push_back(line);
		}
	}
	file.close();
	return file_content;
}


void levenshtein_algo(vector<string> file1_content,vector<string> file2_content)
{
	int i,n,cost,length1,length2;
	//new matrix
	length1=file1_content.size();
	int **matrix = new int*[length1+1];
	length2=file2_content.size();
	for(i=0;i<(length1+1);i++)
	{
		int *temp = new int[length2+1];
		matrix[i]=temp;
	}
	//initial part value of matrix
	for(i=0;i<(length1+1);i++)
		matrix[i][0]=i;
	for(i=0;i<(length2+1);i++)
		matrix[0][i]=i;
	// set the rest part value of matrix
	for(i=1;i<(length1+1);i++)
	{
		for(n=1;n<(length2+1);n++)
		{
			cost=1;
			if(!file1_content[i-1].compare(file2_content[n-1]))
				cost=0;
			matrix[i][n] = minimum(matrix[i-1][n]+1,matrix[i][n-1]+1,matrix[i-1][n-1]+cost);
		}
	}
	cout<<"the levenshtein_distance : " <<  matrix[length1][length2] << endl;
	cout<<"the dismilarity: " << 1 - similarity(maxmum(length1,length2), matrix[length1][length2]) << endl;
	//show matrix
	/*for(i=0;i<(length1+1);i++)
	{
		for(n=0;n<(length2+1);n++)
		{
			cout<<matrix[i][n]<<" ";
		}
		cout<<endl;
	}*/
}


int minimum(int first,int second,int third)
{
	if(first < second)
	{
		if(first < third)
			return first;
		else
			return third;
	}
	else
	{
		if(second < third)
			return second;
		else
			return third;
	}
}

int maxmum(int first,int second)
{
	if(first>second)
		return first;
	else
		return second;
}

double similarity(int max_length,int min)
{
	return 1-(double)min/max_length;
}