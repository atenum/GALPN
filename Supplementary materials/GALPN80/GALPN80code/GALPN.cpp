#include "GALPN.h"

int generation = 0;//Iterations
double sumfitness = 0.0;// The sum of fitness values of all individuals in the population

struct individual population[POPSIZE];//Population
struct individual newpopulation[POPSIZE];//Newpopulation


bool D[LENGTH][LENGTH];//Inverse of matrix G
bool s[LENGTH];
bool G[LENGTH][SAMPLESIZE];
bool e[SAMPLESIZE];
bool z[SAMPLESIZE];
bool s_1[LENGTH];
bool G_1[LENGTH][SAMPLESIZE];
bool z_1[SAMPLESIZE];


int mianyid[LENGTH];
int mianyid0[LENGTH];
int placenum[LENGTH];
int deleteplace[LENGTH];
int deleteplacenum;
int mutationnum;
int last0[LENGTH];
int lastnum[LENGTH];
int lasttotal;

FILE *fpdata = NULL;
FILE *fpout = NULL;

int qflag = 0;
int failnum = 0;

int w[CANDIDATE];
int w_b[CANDIDATE];


int main()
{
	clock_t start, finish;
	long long totaltime;
	int day=0, hour=0, minite=0, second=0;
	int i, j,x1,x2;
	char ch;
	int matrixflag;
	int flagfs=1;
	deleteplacenum = 0;
	lasttotal = 0;

	srand((int)time(0));

	while (1)
	{
		lasttotal = 0;
		for (i = 0; i < LENGTH; i++)
		{
			last0[i] = 0;
		}

		if (flagfs == 1)//If successful, regenerate the data
		{
			UsedData();

			failnum = 0;
			matrixflag = MatrixInverse();

			while (matrixflag)
			{
				if (matrixflag == (SAMPLESIZE - LENGTH))
				{
					for (i = 0; i<LENGTH; i++)
					{
						for (j = 0; j<SAMPLESIZE; j++)
						{
							G[i][j] = ((rand() % 10) < 5) ? 0 : 1;//Regenerate matrix G
						}
					}
				}
				matrixflag = MatrixInverse();
			}

			NewData();//Convert to new data and output

		}

		while (1)
		{
			for (i = 0; i <LENGTH; i++)
			{
				lastnum[i] = 0;

			}

			for (x2 = 0; x2 < 6; x2++)
			{
				mutationnum = 0;
				deleteplacenum = 0;
				for (i = 0; i <LENGTH; i++)
				{
					mianyid[i] = 0; 
					mianyid0[i] = 0; 
					placenum[i] = 0;
					deleteplace[i] = 0;

				}


				GenerateInitPopulation();//Generate initial population;

				CalculateFitnessValue();//Calculate fitness values;

				for (x1 = 0; x1 < 2; x1++)
				{
					while (generation <= MAXGENERATION)
					{
						generation++;

						SelectionOperation();

						CrossoverOperation();

						MutationOperation();

						CalculateFitnessValue();

						FindBestIndividual();//Gene Position Summation

						Elimination();//Gene Elimination Function

						if (generation % MUTATIONNUM == 0)
						{
							ImmuneOperation();//Vaccine Extraction and Vaccination
											  
						}


					}

					ReGeneratePopulation();// Regenerate Population
					CalculateFitnessValue();
					generation = 0;
					for (i = 0; i<LENGTH; i++)
					{
						mianyid[i] = 0;
						mianyid0[i] = 0;
					}
				}
				while (generation <= MAXGENERATION)
				{
					generation++;
					SelectionOperation();
					CrossoverOperation();
					MutationOperation();
					CalculateFitnessValue();
					FindBestIndividual();
					Elimination();
					if (generation % MUTATIONNUM == 0)
					{
						ImmuneOperation();
					}
				}

				ReGeneratePopulationlast();
				
				CalculateFitnessValue();
				generation = 0;
				for (i = 0; i<LENGTH; i++)
				{
					mianyid[i] = 0;
					mianyid0[i] = 0;
				}

			}

			flagfs = resultoutput();

			if (!qflag)
			{
				fpout = fopen("resultout.txt", "w");
				qflag = 1;
			}
			else
			{
				fpout = fopen("resultout.txt", "a");
			}

			if (flagfs == 0)//Search failed, restart search
			{
				fclose(fpout);
				break;
			}
			else if (flagfs == 2)//This round has not failed. Continue to search
			{
				if (lasttotal >= 4)
				{
					fprintf(fpout, "successful \n");
					flagfs = 1;
					fclose(fpout);
					printf("This search is successful ");
					break;
				}
				else
				{
					fclose(fpout);
				}

			}
		}
	}

	return 0;
}


