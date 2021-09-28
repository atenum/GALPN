#include "GALPN.h"

//get s_1, z_1 and output
void UsedDataOut(void)
{
	int i, j, k;
	int temp;

	

	//Output s,G,e and z
	if (!qflag)
	{
		fpout = fopen("resultout.txt", "w");
		qflag = 1;
	}
	else
	{
		fpout = fopen("resultout.txt", "a");
	}
	printf("s\n");
	fprintf(fpout, "bool s[LENGTH]={");
	for (i = 0; i<LENGTH; i++)
	{
		printf("%d ", s[i]);
		if (i != LENGTH - 1)
		{
			fprintf(fpout, "%d,", s[i]);
		}
		else
		{
			fprintf(fpout, "%d};", s[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");

	printf("G\n");
	fprintf(fpout, "bool G[LENGTH][SAMPLESIZE]={");
	for (i = 0; i<LENGTH; i++)
	{
		fprintf(fpout, "{");
		for (j = 0; j<SAMPLESIZE; j++)
		{
			printf("%d ", G[i][j]);
			if (j != SAMPLESIZE - 1)
			{
				fprintf(fpout, "%d,", G[i][j]);
			}
			else
			{
				if (i != LENGTH - 1)
				{
					fprintf(fpout, "%d},", G[i][j]);
				}
				else
				{
					fprintf(fpout, "%d}};", G[i][j]);
				}

			}

		}
		printf("\n");

	}
	fprintf(fpout, "\n");

	printf("e\n");
	fprintf(fpout, "bool e[SAMPLESIZE]={");
	for (i = 0; i<SAMPLESIZE; i++)
	{
		printf("%d ", e[i]);
		if (i != SAMPLESIZE - 1)
		{
			fprintf(fpout, "%d,", e[i]);
		}
		else
		{
			fprintf(fpout, "%d};", e[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");

	printf("z\n");
	fprintf(fpout, "bool z[SAMPLESIZE]={");
	for (i = 0; i<SAMPLESIZE; i++)
	{
		printf("%d ", z[i]);
		if (i != SAMPLESIZE - 1)
		{
			fprintf(fpout, "%d,", z[i]);
		}
		else
		{
			fprintf(fpout, "%d};", z[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");


	for (i = 0; i<LENGTH; i++)//Calculate s_1
	{
		temp = 0;
		for (k = 0; k<LENGTH; k++)
		{
			temp = temp^s[k] & G[k][i];
		}
		s_1[i] = z[i] ^ temp;
	}

	printf("s_1\n");
	fprintf(fpout, "bool s_1[LENGTH]={");
	for (i = 0; i<LENGTH; i++)
	{
		printf("%d ", s_1[i]);
		if (i != LENGTH - 1)
		{
			fprintf(fpout, "%d,", s_1[i]);
		}
		else
		{
			fprintf(fpout, "%d};", s_1[i]);
		}
	}
	printf("\n");
	fprintf(fpout, "\n");

	printf("G_1\n");
	fprintf(fpout, "bool G_1[LENGTH][SAMPLESIZE]={");
	for (i = 0; i<LENGTH; i++)
	{
		fprintf(fpout, "{");
		for (j = 0; j<SAMPLESIZE; j++)
		{
			printf("%d ", G_1[i][j]);
			if (j != SAMPLESIZE - 1)
			{
				fprintf(fpout, "%d,", G_1[i][j]);
			}
			else
			{
				if (i != LENGTH - 1)
				{
					fprintf(fpout, "%d},", G_1[i][j]);
				}
				else
				{
					fprintf(fpout, "%d}};", G_1[i][j]);
				}
			}

		}
		printf("\n");

	}
	fprintf(fpout, "\n");

	for (i = 0; i<SAMPLESIZE; i++)// Calculate z_1
	{
		temp = 0;
		for (k = 0; k<LENGTH; k++)
		{
			temp = temp^z[k] & G_1[k][i];
		}
		z_1[i] = z[i] ^ temp;
	}

	printf("z_1\n");
	fprintf(fpout, "bool z_1[SAMPLESIZE]={");
	for (i = 0; i<SAMPLESIZE; i++)
	{
		printf("%d ", z_1[i]);
		if (i != SAMPLESIZE - 1)
		{
			fprintf(fpout, "%d,", z_1[i]);
		}
		else
		{
			fprintf(fpout, "%d};", z_1[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");

	temp = 0;
	fprintf(fpout, "1 place: ");// For reference only
	for (i = 0; i < LENGTH; i++)
	{
		if (s_1[i] == 1)
		{
			temp++;
			fprintf(fpout, "%d  ", i);
		}
	}
	//onenumber = temp;
	fprintf(fpout, "\n1 number: %d ", temp);

	
	fclose(fpout);
}

//give s,G,e and z;
void UsedData(void)
{
	int i, j;

	for (i = 0; i<LENGTH; i++)
	{
		s[i] = ((rand() % 10) < 5) ? 0 : 1;//Randomly generate key s
	}

	for (i = 0; i<LENGTH; i++)
	{
		for (j = 0; j<SAMPLESIZE; j++)
		{
			G[i][j] = ((rand() % 10) < 5) ? 0 : 1;//Randomly generate matrix G
		}
	}

	for (i = 0; i<SAMPLESIZE; i++)
	{
		e[i] = ((rand() / (double)(RAND_MAX)) < PROBABILITY) ? 1 : 0;//Randomly generated confusion vector e
	}

	int temp;
	for (i = 0; i<SAMPLESIZE; i++)
	{
		temp = 0;
		for (j = 0; j<LENGTH; j++)
		{
			temp = temp ^ s[j] & G[j][i];//Calculation vector z
		}
		z[i] = temp ^ e[i];
	}



}


//Finding the inverse of Boolean matrix
int MatrixInverse(void)
{

	int x, y;

	int i, j, k, m, n;
	int temp, result;

	int GC[LENGTH][LENGTH * 2];

	for (i = 0; i<LENGTH; i++)
	{
		for (j = 0; j<LENGTH; j++)
		{
			D[i][j] = 0;//Initialize D, and the initial value is 0
		}
	}

	for (i = 0; i<LENGTH; i++)
	{
		for (j = 0; j<LENGTH * 2; j++)
		{
			GC[i][j] = 0;//The value in the initialized GC is 0
		}
	}

	//***************************************************************************

	for (i = 0; i<LENGTH; i++)
	{

		for (j = 0; j<LENGTH; j++)//
		{
			if (G[i][j] == 1)
			{
				GC[i][j] = 1;
			}
		}
		GC[i][LENGTH + i] = 1;
	}
	

	printf("GC after initialization \n");
	for (x = 0; x<LENGTH; x++)
	{
		for (y = 0; y<LENGTH * 2; y++)//
		{
			printf("%d ", GC[x][y]);
		}
		printf("\n");
	}
	printf("\n");


	//Ladder matrix
	for (i = 0, j = 0; i<LENGTH&&j<LENGTH;)
	{
		if (GC[i][j] == 1)
		{
			for (m = i + 1; m<LENGTH; m++)
			{
				if (GC[m][j] == 1)
				{
					for (n = j; n<LENGTH * 2; n++)
					{
						GC[m][n] = GC[m][n] ^ GC[i][n];
					}
				}
			}
			i++;
			j++;
		}
		else
		{
			for (m = i + 1; m<LENGTH; m++)
			{
				if (GC[m][j] == 1)
				{
					for (n = j; n<LENGTH * 2; n++)
					{
						temp = GC[i][n];
						GC[i][n] = GC[m][n];
						GC[m][n] = temp;
					}
					break;
				}
			}
			if (m == LENGTH)
			{
				j++;
			}
		}
	}

	printf("GC transformed into a ladder matrix \n");
	for (x = 0; x<LENGTH; x++)
	{
		for (y = 0; y<LENGTH * 2; y++)//
		{
			printf("%d ", GC[x][y]);
		}
		printf("\n");
	}
	printf("\n");

	//Matrix with diagonal 1
	for (i = 0; i<LENGTH; i++)
	{
		if (GC[i][i] != 1)
		{
			for (j = i + 1; j<LENGTH; j++)
			{
				if (GC[i][j] == 1)
				{
					for (m = j; m<LENGTH * 2; m++)
					{
						temp = GC[i][m];
						GC[i][m] = GC[j][m];
						GC[j][m] = temp;
					}
				}
			}
			for (m = LENGTH; m<LENGTH * 2; m++)
			{
				if (GC[i][m] == 1)
				{
					printf("The inverse of the matrix does not exist and needs to be rearranged G");
					for (n = 0; n<LENGTH; n++)
					{
						temp = G[n][i];
						G[n][i] = G[n][LENGTH + failnum];
						GC[n][LENGTH + failnum] = temp;
					}
					failnum++;
					return failnum;
				}
			}
		}
	}

	printf("Matrix GC with diagonal 1\n");
	for (x = 0; x<LENGTH; x++)
	{
		for (y = 0; y<LENGTH * 2; y++)//
		{
			printf("%d ", GC[x][y]);
		}
		printf("\n");
	}
	printf("\n");

	//Diagonal matrix
	for (i = LENGTH - 1; i >= 0; i--)
	{
		if (GC[i][i] == 1)
		{
			for (j = i - 1; j >= 0; j--)
			{
				if (GC[j][i] == 1)
				{
					for (m = i; m<LENGTH * 2; m++)
					{
						GC[j][m] = GC[j][m] ^ GC[i][m];
					}
				}
			}
		}
		else
		{
			for (j = i - 1; j >= 0; j--)
			{
				GC[j][i] = 0;
			}
		}
	}

	printf("Diagonal matrix GC\n");
	for (x = 0; x<LENGTH; x++)
	{
		for (y = 0; y<LENGTH * 2; y++)
		{
			printf("%d ", GC[x][y]);
		}
		printf("\n");
	}
	printf("\n");

	//output
	printf("Inverse matrix obtained \n");
	for (i = 0; i<LENGTH; i++)
	{
		for (j = LENGTH; j<LENGTH * 2; j++)
		{
			if (GC[i][j] == 1)
			{
				D[i][j - LENGTH] = 1;
			}
			printf("%d ", GC[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i<LENGTH; i++)
	{
		for (j = 0; j<LENGTH; j++)
		{
			result = 0;
			for (k = 0; k<LENGTH; k++)
			{
				result = result ^ (G[i][k] & D[k][j]);
			}
			if (i == j&&result == 0)
			{
				printf("error");
				exit(0);
			}
			else if (i != j&&result == 1)
			{
				printf("error");
				exit(0);
			}
		}

	}

	return 0;
}

//get G_1 and output
void NewData(void)
{
	int i, j, k;
	int temp;

	for (i = 0; i<LENGTH; i++)//Initialize G_1
	{
		for (j = 0; j<SAMPLESIZE; j++)//
		{
			G_1[i][j] = 0;
		}
	}

	for (i = 0; i<LENGTH; i++)//Calculate G_1
	{
		for (j = 0; j<SAMPLESIZE; j++)
		{
			for (k = 0; k<LENGTH; k++)
			{
				G_1[i][j] = G_1[i][j] ^ D[i][k] & G[k][j];
			}
		}
	}

	
	if (!qflag)
	{
		fpout = fopen("resultout.txt", "w");
		qflag = 1;
	}
	else
	{
		fpout = fopen("resultout.txt", "a");
	}
	printf("s\n");
	fprintf(fpout, "bool s[LENGTH]={");
	for (i = 0; i<LENGTH; i++)
	{
		printf("%d ", s[i]);
		if (i != LENGTH - 1)
		{
			fprintf(fpout, "%d,", s[i]);
		}
		else
		{
			fprintf(fpout, "%d};", s[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");

	printf("G\n");
	fprintf(fpout, "bool G[LENGTH][SAMPLESIZE]={");
	for (i = 0; i<LENGTH; i++)
	{
		fprintf(fpout, "{");
		for (j = 0; j<SAMPLESIZE; j++)
		{
			printf("%d ", G[i][j]);
			if (j != SAMPLESIZE - 1)
			{
				fprintf(fpout, "%d,", G[i][j]);
			}
			else
			{
				if (i != LENGTH - 1)
				{
					fprintf(fpout, "%d},", G[i][j]);
				}
				else
				{
					fprintf(fpout, "%d}};", G[i][j]);
				}

			}

		}
		printf("\n");

	}
	fprintf(fpout, "\n");

	printf("e\n");
	fprintf(fpout, "bool e[SAMPLESIZE]={");
	for (i = 0; i<SAMPLESIZE; i++)
	{
		printf("%d ", e[i]);
		if (i != SAMPLESIZE - 1)
		{
			fprintf(fpout, "%d,", e[i]);
		}
		else
		{
			fprintf(fpout, "%d};", e[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");

	printf("z\n");
	fprintf(fpout, "bool z[SAMPLESIZE]={");
	for (i = 0; i<SAMPLESIZE; i++)
	{
		printf("%d ", z[i]);
		if (i != SAMPLESIZE - 1)
		{
			fprintf(fpout, "%d,", z[i]);
		}
		else
		{
			fprintf(fpout, "%d};", z[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");


	for (i = 0; i<LENGTH; i++)//Calculate s_1
	{
		temp = 0;
		for (k = 0; k<LENGTH; k++)
		{
			temp = temp^s[k] & G[k][i];
		}
		s_1[i] = z[i] ^ temp;
	}

	printf("s_1\n");
	fprintf(fpout, "bool s_1[LENGTH]={");
	for (i = 0; i<LENGTH; i++)
	{
		printf("%d ", s_1[i]);
		if (i != LENGTH - 1)
		{
			fprintf(fpout, "%d,", s_1[i]);
		}
		else
		{
			fprintf(fpout, "%d};", s_1[i]);
		}
	}
	printf("\n");
	fprintf(fpout, "\n");

	printf("G_1\n");
	fprintf(fpout, "bool G_1[LENGTH][SAMPLESIZE]={");
	for (i = 0; i<LENGTH; i++)
	{
		fprintf(fpout, "{");
		for (j = 0; j<SAMPLESIZE; j++)
		{
			printf("%d ", G_1[i][j]);
			if (j != SAMPLESIZE - 1)
			{
				fprintf(fpout, "%d,", G_1[i][j]);
			}
			else
			{
				if (i != LENGTH - 1)
				{
					fprintf(fpout, "%d},", G_1[i][j]);
				}
				else
				{
					fprintf(fpout, "%d}};", G_1[i][j]);
				}
			}

		}
		printf("\n");

	}
	fprintf(fpout, "\n");

	for (i = 0; i<SAMPLESIZE; i++)//Calculate z_1
	{
		temp = 0;
		for (k = 0; k<LENGTH; k++)
		{
			temp = temp^z[k] & G_1[k][i];
		}
		z_1[i] = z[i] ^ temp;
	}

	printf("z_1\n");
	fprintf(fpout, "bool z_1[SAMPLESIZE]={");
	for (i = 0; i<SAMPLESIZE; i++)
	{
		printf("%d ", z_1[i]);
		if (i != SAMPLESIZE - 1)
		{
			fprintf(fpout, "%d,", z_1[i]);
		}
		else
		{
			fprintf(fpout, "%d};", z_1[i]);
		}

	}
	printf("\n");
	fprintf(fpout, "\n");

	temp = 0;
	fprintf(fpout, "1 place: ");
	for (i = 0; i < LENGTH; i++)
	{
		if (s_1[i] == 1)
		{
			temp++;
			fprintf(fpout, "%d  ", i);
		}
	}
	//onenumber = temp;
	fprintf(fpout, "\n1 number: %d ", temp);

	
	fclose(fpout);
}

//Generate an initialized population;
void GenerateInitPopulation(void)
{
	int i, j, k;
	int temp;
	int s_temp[LENGTH];

	for (i = 0; i<POPSIZE; i++)
	{
		for (j = 0; j<LENGTH; j++)
		{
			population[i].chorm[j] = ((rand() % 10) < 5) ? 0 : 1;//Individuals are randomly generated
		}
	}

	for (i = 0; i<POPSIZE; i++)//Gaussian elimination
	{
		for (j = 0; j<LENGTH; j++)
		{
			temp = 0;
			for (k = 0; k<LENGTH; k++)
			{
				temp = temp^population[i].chorm[k] & G[k][j];
			}
			s_temp[j] = z[j] ^ temp;
		}

		for (k = 0; k<LENGTH; k++)
		{
			if (last0[k] == 1)
			{
				s_temp[k] = 0;
			}
			population[i].chorm[k] = s_temp[k];
		}
	}

}

//Gene Elimination Function
void Elimination(void)
{
	int i, j, k;
	int weight = 0;
	int sum, temp;


	for (i = 0; i<POPSIZE; i++)
	{
		weight = 0;
		for (k = 0; k<LENGTH; k++)
		{
			if (population[i].chorm[k] == 1)
			{
				weight++;
			}
		}

		if (weight>=H)
		{
			for (j = 0; j<LENGTH; j++)
			{
				if (population[i].chorm[j] == 1)
				{
					population[i].chorm[j] = ((rand() / (double)(RAND_MAX)) < (LENGTH*PROBABILITY)/ weight) ? 1 : 0;
				}
			}

			sum = 0;
			for (k = 0; k<SAMPLESIZE; k++)
			{
				temp = 0;
				for (j = 0; j<LENGTH; j++)
				{
					temp = temp ^ (population[i].chorm[j] & G_1[j][k]);
				}
				sum = sum + (temp ^ z_1[k]^1);
			}
			population[i].fitness = sum;

		}

	}

	sumfitness = 0.0;
	for (i = 0; i<POPSIZE; i++)
	{
		sumfitness = sumfitness + population[i].fitness;
	}

}

//Fitness Function;
void CalculateFitnessValue(void)
{
	int i, j, k;
	int sum, temp;

	for (i = 0; i<POPSIZE; i++)
	{
		sum = 0;
		for (k = 0; k<SAMPLESIZE; k++)
		{
			temp = 0;
			for (j = 0; j<LENGTH; j++)
			{
				temp = temp ^ (population[i].chorm[j] & G_1[j][k]);
			}
			sum = sum + (temp ^ z_1[k]^1);
		}
		population[i].fitness = sum;
	}

	

	sumfitness = 0.0;
	for (i = 0; i<POPSIZE; i++)
	{
		sumfitness = sumfitness + population[i].fitness;
	}

}

//Gene Position Summation
void FindBestIndividual(void)
{
	int i, j, k, best = 0;
	int t;


	for (i = 0; i<POPSIZE; i++)
	{

		if (610<= population[i].fitness <=690)
		{
			for (k = 0; k < LENGTH; k++)
			{
				if (mianyid[k] != -1 && population[i].chorm[k] == 1)
				{
					mianyid[k]++;
					
				}
				if (deleteplace[k] != 1 && mianyid0[k] != -1  && population[i].chorm[k] == 0 && last0[k]!=1)
				{
					mianyid0[k]++;
					
				}

			}
		}

	}

}

//Selection Operator
void SelectionOperation(void)
{

	static double pfitness[POPSIZE];
	int i, j, index;
	double p;



	for (i = 0; i<POPSIZE; i++)
	{
		pfitness[i] = population[i].fitness/ sumfitness;
	}



	for (i = 1; i<POPSIZE; i++)
	{
		pfitness[i] = pfitness[i - 1] + pfitness[i];
	}



	for (i = 0; i<POPSIZE; i++)
	{

		p = rand() / (double)(RAND_MAX);

		index = 0;

		if (p>pfitness[POPSIZE - 1])
		{
			index = POPSIZE - 1;

		}
		else
		{
			while (p>pfitness[index])
			{
				index++;
			}
		}	

		newpopulation[i] = population[index];

	}



	for (i = 0; i<POPSIZE; i++)
	{
		population[i] = newpopulation[i];
	}

	
}

//Crossover Operator;
void CrossoverOperation(void)
{
	int i, j, k, parent, point[2], temp;
	static  int index[POPSIZE];
	double p;
	bool change;

	for (i = 0; i<POPSIZE; i++)
	{
		index[i] = i;
	}

	for (i = 0; i<POPSIZE; i++)
	{
		parent = rand() % (POPSIZE - i);
		temp = index[i];
		index[i] = index[i + parent];
		index[i + parent] = temp;
	}

	for (i = 0; i<(POPSIZE - 1); i += 2)
	{
		p = rand() / (double)(RAND_MAX);

		if (p<Pc)
		{
			point[0] = rand() % LENGTH;
			point[1] = rand() % LENGTH;
									  

			if (point[0]>point[1])
			{
				temp = point[0];
				point[0] = point[1];
				point[1] = temp;
			}

			for (j = point[0]; j<point[1]; j++)
			{
				temp = population[index[i]].chorm[j];
				population[index[i]].chorm[j] = population[index[i + 1]].chorm[j];
				population[index[i + 1]].chorm[j] = temp;
			}

		}

	}

}

//Mutation Operator;
void MutationOperation(void)
{
	int i,j;
	double p;

	for (i = 0; i<POPSIZE; i++)
	{
		p = rand() / (double)(RAND_MAX);
			
		if (p<Pm)
		{
			j = rand() % LENGTH;
			if (deleteplace[j] != 1 && last0[j]!=1)
			{
				population[i].chorm[j] = (population[i].chorm[j] == 0) ? 1 : 0;
			}
		}
		
	}

}

//Vaccine Extraction and Vaccination
void ImmuneOperation(void)
{
	int index = 0;
	int index0 = 0;
	int temp = 0;
	int sum;
	int i, j, k;
	double p, pp;
	int number, flag;


	temp = mianyid[0];
	for (i = 0; i<LENGTH; i++)//Find the position of 1 with the largest accumulated value
	{
		if (mianyid[i]>temp)
		{
			temp = mianyid[i];
			index = i;
		}

		if (mianyid[i] != -1)
		{
			mianyid[i] = 0;
		}
	}
	mianyid[index] = -1;
	mutationnum++;

	temp = mianyid0[0];
	for (i = 0; i<LENGTH; i++)//Find the position of 0 with the largest accumulated value
	{
		if (mianyid0[i]>temp)
		{
			temp = mianyid0[i];
			index0 = i;
		}

		if (mianyid0[i] != -1)
		{
			mianyid0[i] = 0;
		}
	}

	
	mianyid0[index0] = -1;

	if (mutationnum <= CANDIDATE)
	{
		w[mutationnum - 1] = index0;

		for (i = 0; i<POPSIZE; i++)
		{
			if (population[i].chorm[index] == 0)
			{
				if ((rand() / (double)(RAND_MAX)) <= MP)
				{
					population[i].chorm[index] = 1;

					sum = 0;
					for (k = 0; k<SAMPLESIZE; k++)
					{
						temp = 0;
						for (j = 0; j<LENGTH; j++)
						{
							temp = temp ^ (population[i].chorm[j] & G_1[j][k]);
						}
						sum = sum + (temp ^ z_1[k]^1);
					}
					population[i].fitness = sum;
				}
			}
		}

	}

	sumfitness = 0.0;
	for (i = 0; i<POPSIZE; i++)
	{
		sumfitness = sumfitness + population[i].fitness;
	}

	if (mutationnum % CANDIDATE == 0)
		//a round of screening ends
	{
		mutationnum = 0;
		for (i = 0; i<LENGTH; i++)
		{
			mianyid[i] = 0;
			mianyid0[i] = 0;
		}

			for (i = 0; i < CANDIDATE; i++)
			{
				placenum[w[i]]++;
			}		
		
	}

	
}

//Regenerate Population
void ReGeneratePopulation(void)
{
	int i, j;
	int temp;

	
	for (i = 0; i < LENGTH; i++)
	{
		if (deleteplace[i] != 1)
		{
			temp = placenum[i];
			break;
		}

	}

	for (i = 0; i < LENGTH; i++)
	{
		if (placenum[i] > temp && deleteplace[i] != 1)
			temp = placenum[i];
	}

	for (i = 0; i < LENGTH; i++)
	{
		if (placenum[i] == temp || deleteplace[i] == 1)
		{

			if (deleteplace[i] == 0)
			{
				
				deleteplace[i] = 1;
				deleteplacenum++;
			}
			
		}

		for (j = 0; j < POPSIZE; j++)
		{
			population[j].chorm[i] = 0;
		}
		
	}



	for (i = 0; i < POPSIZE; i++)
	{
		for (j = 0; (j < LENGTH) && (deleteplace[j] != 1) && (last0[j]!=1); j++)
		{
			population[i].chorm[j] = ((rand() / (double)(RAND_MAX)) < ((PROBABILITY*LENGTH) / (LENGTH - deleteplacenum-lasttotal))) ? 1 : 0;
		}
	}

	for (i = 0; i < LENGTH; i++)
	{
		placenum[i] = 0;
	}
	
}

//Regenerate Population
void ReGeneratePopulationlast(void)
{
	int i, j;
	int temp;



	for (i = 0; i < LENGTH; i++)
	{
		if (deleteplace[i] != 1)
		{
			temp = placenum[i];
			break;
		}

	}

	for (i = 0; i < LENGTH; i++)
	{
		if (placenum[i] > temp && deleteplace[i] != 1)
			temp = placenum[i];
	}

	for (i = 0; i < LENGTH; i++)
	{
		if (placenum[i] == temp || deleteplace[i] == 1)
		{
			
			lastnum[i]++;


			if (deleteplace[i] == 0)
			{
				deleteplace[i] = 1;
				deleteplacenum++;
			}

		}

		for (j = 0; j < POPSIZE; j++)
		{
			population[j].chorm[i] = 0;
		}

	}
	

	for (i = 0; i < POPSIZE; i++)
	{
		for (j = 0; (j < LENGTH) && (deleteplace[j] != 1) && (last0[j]!=1); j++)
		{
			population[i].chorm[j] = ((rand() / (double)(RAND_MAX)) < ((PROBABILITY*LENGTH) / (LENGTH - deleteplacenum-lasttotal))) ? 1 : 0;
		}
	}

	for (i = 0; i < LENGTH; i++)
	{
		placenum[i] = 0;
	}
	
}

//Output result
int resultoutput(void)
{
	int i, num0;
	int temp;
	int fail;
	temp = 0;
	num0 = 0;
	fail = 0;
	if (!qflag)
	{
		fpout = fopen("resultout.txt", "w");
		qflag = 1;
	}
	else
	{
		fpout = fopen("resultout.txt", "a");
	}

	fprintf(fpout, "Determined elimination position last0: ");
	printf( "Determined elimination position last0: ");
	for (i = 0; i<LENGTH; i++)
	{
		if (lastnum[i] >= 3)
		{
			fprintf(fpout, "The index %d-%d, ", i, lastnum[i]);
			printf( "The index %d-%d£¬ ", i, lastnum[i]);
			if (s_1[i] == 1)
			{
				fprintf(fpout, "Error index %d-%d,this search failed ", i, lastnum[i]);
				printf( "Error index %d-%d,this search failed ", i, lastnum[i]);
				fail = 1;
			}
			if (last0[i] == 0)
			{
				temp = 1;
				num0++;
				fprintf(fpout, "The new index %d-%d, ", i, lastnum[i]);
				printf( "The new index %d-%d, ", i, lastnum[i]);
				last0[i] = 1;
			}
		}
		
	}
	fprintf(fpout, "\n");
	printf( "\n");

	lasttotal = lasttotal + num0;
	fprintf(fpout, "Total number of locations found is %d, ",lasttotal);
	printf( "Total number of locations found is %d, ", lasttotal);

	if (temp == 0)
	{
		fprintf(fpout, "No new positions for this time ");
		printf( "No new positions for this time ");
	}
	else
	{
		fprintf(fpout, "Number of new positions this time is %d ", num0);
		printf( "Number of new positions this time is %d ", num0);
	}
	if (fail == 1)
	{
		fprintf(fpout, "This search failed ");
		printf( "This search failed ");
	}
	fprintf(fpout, "\n");
	printf( "\n");

	fclose(fpout);

	if (fail == 1)
	{
		return 0;
	}
	else
	{
		return 2;
	}

}