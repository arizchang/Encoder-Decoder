#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

//functions used in program
void insertionSort(string&);
bool ifUsed(int*, int, int);
void merge(string&, int, int, int);
void mergeSort(string&, int, int);
bool isNumber(string);
void compressionExperiment(const vector<double>&);

int main(int argc, char** argv)
{
  auto start = high_resolution_clock::now();
  string sortAlg = argv[1];
  int count = 0;
  string input = "";
  int index = 0;
  vector<double> compressionRatios;

  while(getline(cin, input))
    {
   
      int charCount = 0;
      int x = 0;
      string last = "";
      string temp = "";
      string sorted = "";
      string decoded = "";
      vector<string> encodedLine;

      //blank line
      if(input.size() == 0)
	{
	  count++;
	  cout << endl;
	}

      //index line
      else if(count % 2 == 0)
	{
	  index = stoi(input);
	  count++;
	}
      //encoded line
      else
	{
	  int i = 0;

	  while(i < input.length())
	    {
	      string character;
	      int startIndex = i;
	      int moveBy = 0;
	      while(input[i] != ' ' && i < input.length())
		{
		  i++;
		  moveBy++;
		}
	      character = input.substr(startIndex, moveBy);
	      while(input[i] == ' ' && i < input.length())
		i++;
	      //iss >> character;
	      encodedLine.push_back(character);
	    }
	    
	  //accounts for missed spaces
	  for(int i = 0; i < encodedLine.size(); i++)
	    {
	      if(i > 0 && isNumber(encodedLine[i]) && isNumber(encodedLine[i-1]))
		{
		  encodedLine.insert(encodedLine.begin() + i, " ");
		}
	    }
	  if(isNumber(encodedLine[encodedLine.size()-1]))
	    encodedLine.push_back(" ");

	  //creating last
	  for(int i = 0; i < encodedLine.size(); i++)
	    {
	      //char count
	      if(i % 2 == 0)
		{
		  charCount = stoi(encodedLine[i]);
		}

	      //char to be printed
	      else
		{
		  for(int j = 0; j < charCount; j++)
		    last = last + encodedLine[i];
		}
	    }

	  //making list of compression ratios
	  int numClusters = 0;
	  double ratio = 0;
	  for(int i = 0; i < encodedLine.size(); i++)
	    {
	      if(i % 2 == 0)
		{
		  numClusters++;
		}
	    }
	  ratio = ((double)(last.length() - numClusters)/last.length())*100;
	  //cout << "Input length: " << last.length() << endl;
	  //cout << "Num clusters: " << numClusters << endl;
	  //cout << "Ratio: " << ratio << endl;
	  compressionRatios.push_back(ratio);

	  //determines which sorting to use
	  temp = last;
	  if(sortAlg == "insertion")
	    insertionSort(temp);
	  else if(sortAlg == "merge")
	    mergeSort(temp, 0, temp.length()-1);
	  else
	    cout << "Invalid input" << endl;

	  sorted = temp;

	  int* next = new int[sorted.length()];
	  //fill with -1
	  for(int i = 0; i < sorted.length(); i++)
	    next[i] = -1;

	  for(int i = 0; i < sorted.length(); i++)
	    {
	      for(int j = 0; j < sorted.length(); j++)
		{
		  if(sorted[i] == last[j] && !ifUsed(next, sorted.length(), j))
		    {
		      next[i] = j;
		      j = sorted.length();
		    }
		}
	    }

	  x = next[index];
	  for(int i = 0; i < sorted.length(); i++)
	    {
	      decoded = decoded + last[x];
	      x = next[x];
	    }
	  cout << decoded << endl;
	  count++;
	  input = "";
	}
    }
  
  //experiments
  compressionExperiment(compressionRatios);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  //cout << "Execution time: " << duration.count() << " microseconds" << endl;
}

//insertion sort
void insertionSort(string &last)
{
  char key;
  int j = 0;

  for(int i = 0; i < last.length(); i++)
    {
      key = last[i];
      j = i-1;
      while(j >= 0 && last[j] > key) //shifting
	{
	  last[j+1] = last[j];
	  j--;
	}
      last[j+1] = key;
    }
}

//checks if number is already in the array
bool ifUsed(int* array, int size, int num)
{
  for(int i = 0; i < size; i++)
    {
      if(array[i] == num)
	return true;
    }
  return false;
}

//merges two halves for sorting
void merge(string &array, int start, int mid, int end)
{
  string temp = "";
  int a = start;
  int b = mid + 1;
  int c = 0;

  //places values into a temporary array
  while (a <= mid && b <= end)
    {
      if(array[a] <= array[b])
	{
	  temp[c] = array[a];
	  c++;
	  a++;
	}
      else
	{
	  temp[c] = array[b];
	  c++;
	  b++;
	}
    }

  //copies leftover elements
  while(a <= mid)
    {
      temp[c] = array[a];
      c++;
      a++;
    }

  //copies leftover elements
  while(b <= end)
    {
      temp[c] = array[b];
      c++;
      b++;
    }

  //places the temporary data back into the array
  for(a = start; a <= end; a++)
    {
      array[a] = temp[a - start];
    }
}

//recursive function for completing merge sort
void mergeSort(string &array, int start, int end)
{
  if(start < end)
    {
      //sorts first half, second half, then merges them together
      int mid = (start + end)/2;
      mergeSort(array, start, mid);
      mergeSort(array, mid + 1, end);
      merge(array, start, mid, end);
    }
}

bool isNumber(string word)
{
  for(int i = 0; i < word.length(); i++)
    {
      if(!isdigit(word[i]))
	return false;
    }
  return true;
}

void compressionExperiment(const vector<double> &ratios)
{
  double min = 100;
  double max = 0;
  double sum = 0;
  double average = 0;
  double stdAverage = 0;
  double stdSum = 0;
  double stdDeviation = 0;

  double* stdArray = new double[ratios.size()];

  for(int i = 0; i < ratios.size(); i++)
    {
      if(ratios[i] < min)
	min = ratios[i];

      if(ratios[i] > max)
	max = ratios[i];

      sum += ratios[i];
    }

  average = (double)sum/ratios.size();

  for(int i = 0; i < ratios.size(); i++)
    {    
      stdArray[i] = ((double)ratios[i] - average)*((double)ratios[i] - average);
      stdSum += stdArray[i];
    }

  stdAverage = stdSum/ratios.size();
  stdDeviation = sqrt(stdAverage);

  cout << "Min: " << min << "%" << endl;
  cout << "Max: " << max << "%" << endl;
  cout << "Average: " << average << "%" << endl;
  cout << "Standard Deviation: " << stdDeviation << "%" << endl;
}
