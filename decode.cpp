#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//functions used in program
void insertionSort(string&);
bool ifUsed(int*, int, int);
void merge(string&, int, int, int);
void mergeSort(string&, int, int);

int main(int argc, char** argv)
{
  string sortAlg = argv[1];
  int count = 0;
  int index = 0;
  int charCount = 0;
  int x = 0;
  string input = "";
  string last = "";
  string temp = "";
  string sorted = "";
  string decoded = "";
  vector<string> encodedLine;

  while(getline(cin, input))
    {
      //blank line
      if(input.size() == 0)
	{
	  count++;
	}

      //index line
      else if(count % 2 == 0)
	{
	  stringstream ss(input);
	  ss >> index;
	  count++;
	}

      //encoded line
      else
	{
	  istringstream iss(input);
	  while(iss)
	    {
	      string character;
	      iss >> character;
	      encodedLine.push_back(character);
	    }

	  for(int i = 0; i < encodedLine.size(); i++)
	    {
	      //char count
	      if(i % 2 == 0)
		{
		  stringstream ss(encodedLine[i]);
		  ss >> charCount;
		}

	      //char to be printed
	      else
		{
		  for(int j = 0; j < charCount; j++)
		    last = last + encodedLine[i];
		}
	    }
	  //cout << last << endl;
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
	}
    }
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
