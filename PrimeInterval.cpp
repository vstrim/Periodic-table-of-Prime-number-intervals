//	" Viktor Strohm, Periodic table of Prime number intervals, vfstrohm@yahoo.de\n";

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>          

using namespace std;

struct tprime 
{
	int p; //prime
	int x; // 1 interval(x)
	int y; // 2 interval(y)
	int z; // 3 count(z), ordinal number with coordinates (x,y)
};// end tprime

void vsieve(std::vector<int> &sieve, int sievesize, int &maxrc)
{
	// create an array of primes
	std::vector<int> tmp;
    //
    // Now search for 1 bt positions.
    //
	int k = 1;
	maxrc = 0;
    for (int i = 0; i < sievesize; i++)
      tmp.push_back(14); //egal, nur keine 0.
    for (int i = 2; i * i < sievesize; i++)
        if (tmp[i])
            for (int j = i + i; j < sievesize; j += i)
                tmp[j] = 0;
    for (int n = 2; n < sievesize; n++)
      if (tmp[n]){ 
		  sieve.push_back(n);
		  if(sieve.size() > 2){
			maxrc = max((sieve[k] - sieve[k-1]), maxrc);
			k++;
		  }
	  }
};

int main(int argc, char** argv)
{
	std::vector<int> sieve;
	vector<tprime> primes;  
	int maxrc;	
	tprime tmp;
	FILE *fout; 
	int sievesize;
	int variant;

	system("mode 650"); //pens the console to full screen
	cout << " enter integer:";
	cin >> sievesize;     
    vsieve(sieve, sievesize, maxrc);
 	maxrc = maxrc/2;
    *sieve.begin() = 1;   //replace 2 with 1
      sieve.erase(sieve.begin()+1);  //remove 3, that did not spoil the picture:)
	vector<vector<int> > tmp2(maxrc+1, vector<int>(maxrc+1, 0)); // создаём массив tmp2[maxrc+1][maxrc+1], заполненый 0.
	cout << " Interval - a difference between next prime numbers\n";
	cout << " Variant 1 - left and right intervals from a prime number are selected\n";
	cout << " Variant 2 - select successively pairs of intervals between prime numbers\n";
	cout << " variant 1 or 2 ( default 1):";
	cin >> variant;     
	cout << "\n";
    switch (variant) 
    { 
	  if(variant != 1 || variant != 2) variant = 1;
	  default: case 1: 
      //option 1 - select the left and right interval from prime
      for(int i = 1; i < sieve.size()-1; i++){
		  tmp.p = sieve[i];
		  tmp.x = (sieve[i] - sieve[i-1])/2; //left interval from prime
		  tmp.y = (sieve[i+1] - sieve[i])/2; //right intervals from prime
		  primes.push_back(tmp);
	  }
	  for(int i = 0; i < primes.size(); i++){
		tmp2[primes[i].x][primes[i].y]++;
		primes[i].z = tmp2[primes[i].x][primes[i].y];
	  }
	  //output to file
	  fout = fopen("primesInterval3.txt", "w");
	  for (int i = 0; i < primes.size(); i++) 
        fprintf(fout, "%d\t%d\t%d\t%d\n", primes[i].p, primes[i].x, primes[i].y, primes[i].z);
	  fclose(fout);
	  fout = fopen("tabInterval1.txt", "w");
	  for (int i = 1; i < maxrc; i++) 
		tmp2[0][i] = i;// i- номер столбца
	  for (int j = 1; j < maxrc; j++) 
		tmp2[j][0] = j;//j - номера строки
	
	  for (int i = 0; i < maxrc; i++){ 
		for (int j = 0; j < maxrc; j++)
			fprintf(fout, "%d%\t", tmp2[i][j],"  ");
		fprintf(fout, "\n");
	  }
	  fclose(fout);
	  //output to the screen
	  for (int i = 0; i < maxrc; i++){ 
		for (int j = 0; j < maxrc; j++) 
			printf("%d%\t", tmp2[i][j],"  ");
		printf( "\n");
	  }
      break;
	case 2: 
	  // option 2-consecutive pairs of intervals are selected
	  primes.clear();
      for(int i = 1; i < sieve.size()-2; i+=2){// pairs of intervals are selected sequentially
		tmp.p = sieve[i];//Prime number after one
		tmp.x = (sieve[i+1] - sieve[i])/2; //first interval
		tmp.y = (sieve[i+2] - sieve[i+1])/2; //second interval
		primes.push_back(tmp);
	  }
      for(int i = 0; i < primes.size(); i++){
		tmp2[primes[i].x][primes[i].y]++;
		primes[i].z = tmp2[primes[i].x][primes[i].y];
	  }
	  fout = fopen("tabInterval2.txt", "w");
	  for (int i = 1; i < maxrc; i++) 
		tmp2[0][i] = i;//column number
	  for (int j = 1; j < maxrc; j++) 
		tmp2[j][0] = j;//number of rows
	
	  for (int i = 0; i < maxrc; i++){ 
		for (int j = 0; j < maxrc; j++)
			fprintf(fout, "%d%\t", tmp2[i][j],"  ");
		fprintf(fout, "\n");
	  }
	  fclose(fout);
	  //output to the screen
	  for (int i = 0; i < maxrc; i++){ 
		for (int j = 0; j < maxrc; j++) 
			printf("%d%\t", tmp2[i][j],"  ");
		printf( "\n");
	  }
	  break;
  }
	printf("%s", "Enter:");
	getchar();
	getchar();
	return 0;
}