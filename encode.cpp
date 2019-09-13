#include <iostream>
#include <string>

using namespace std;

//functions used in program
void insertionSort(string*, int);
int stringMatch(string, string*, int);
void output2(string, int);
void merge(string*, int, int, int);
void mergeSort(string*, int, int);

int main(int argc, char** argv)
{
  //defining strings used
  string sortAlg = argv[1];
  string input = "";

  //loops while there is still string input
  while(getline(cin, input))
    { 
      //declaring new string arrays
      string* originalList = new string[input.size()];
      string* tempList = new string[input.size()];
      string* sortedList = new string[input.size()];
      string temp = input;
      string lastColumn = "";
      int output1 = 0;

      //stores the word into arrays
      originalList[0] = temp;
      tempList[0] = temp;

      //performs shifting and fills originalList
      for(int i = 1; i < input.size(); i++)
	{
	  originalList[i] = temp.substr(1, 10) + temp.substr(0, 1);
	  tempList[i] = originalList[i];
	  temp = originalList[i];
	}

      if(sortAlg == "insertion")
	insertionSort(tempList, input.size());
      else if(sortAlg == "merge")
	mergeSort(tempList, 0, input.size()-1);
      else
	cout << "Invalid input" << endl;
	  
      //places sorted strings into sortedList
      for(int i = 0; i < input.size(); i++)
	{
	  sortedList[i] = tempList[i];
	  lastColumn = lastColumn + sortedList[i].substr(input.size()-1, 1);
	}

      //output
      cout << stringMatch(input, sortedList, input.size()) << endl;
      output2(lastColumn, lastColumn.size());
    }

  return 0;
}

void insertionSort(string* array, int size)
{
  string key = "";
  int j = 0;

  for(int i = 0; i < size; i++)
    {
      key = array[i];
      j = i - 1;
      while(j >= 0 && array[j] > key)
	{
	  array[j+1] = array[j];
	  j--;
	}
      array[j+1] = key;
    }
}

int stringMatch(string word, string* array, int size)
{
  for(int i = 0; i < size; i++)
    {
      if(word == array[i])
	return i;
    }
}

void output2(string word, int size)
{
  int count;
  char letter;
  int index;

  for(int i = 0; i < size; i += count)
    {
      count = 1;
      index = i;
      letter = word[i];
      while(word[index] == word[index+1])
	{
	  count++;
	  index++;
	}
      cout << count;
      cout << letter;
    }
  cout << endl;
}

void merge(string* array, int start, int mid, int end)
{
  string* temp = new string[end-start+1];
  int a = start;
  int b = mid + 1;
  int c =0;

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
void mergeSort(string* array, int start, int end)
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
