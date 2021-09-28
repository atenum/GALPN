#ifndef _GALPN_
#define _GALPN_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POPSIZE 1000//Population size
#define LENGTH 80//Individual length
#define MAXGENERATION 250
#define SAMPLESIZE 395
#define PROBABILITY 0.125
#define CANDIDATE 10
#define BESTUPDOWN 20
#define MUTATIONNUM 5
#define H 10

#define Pc 0.9//Crossover probability
#define Pm 0.06//Mutation probability
#define MP 0.5
#define Pm1 0.5
#define Pm2 0.3
#define Pm3 0.2

extern int generation;
extern double sumfitness;

struct individual//Individual definition
{
	bool chorm[LENGTH];
	int fitness;
};


extern struct individual population[POPSIZE];
extern struct individual newpopulation[POPSIZE];

extern bool G[LENGTH][SAMPLESIZE];
extern bool G_1[LENGTH][SAMPLESIZE];
extern bool D[LENGTH][LENGTH];
extern bool e[SAMPLESIZE];
extern bool z[SAMPLESIZE];
extern bool z_1[SAMPLESIZE];
extern bool s[LENGTH];
extern bool s_1[LENGTH];


extern int mianyid[LENGTH];
extern int mianyid0[LENGTH];
extern int placenum[LENGTH];
extern int deleteplace[LENGTH];
extern int deleteplacenum;
extern int mutationnum;
extern int last0[LENGTH];
extern int lastnum[LENGTH];
extern int lasttotal;

extern FILE *fpdata;
extern FILE *fpout;

extern int qflag;
extern int failnum;

extern int w[CANDIDATE];
extern int w_b[CANDIDATE];


//give s,G,e and z;
void UsedData(void);

//get s_1, z_1 and output
void UsedDataOut(void);

//Finding the inverse of Boolean matrix
int MatrixInverse(void);

//get G_1 and output
void NewData(void);

//Generate an initialized population;
void GenerateInitPopulation(void);

//Gene Elimination Function
void Elimination(void);

//Fitness Function;
void CalculateFitnessValue(void);

//Gene Position Summation
void FindBestIndividual(void);

//Selection Operator
void SelectionOperation(void);

//Crossover Operator;
void CrossoverOperation(void);

//Mutation Operator;
void MutationOperation(void);

//Vaccine Extraction and Vaccination
void ImmuneOperation(void);

//Regenerate Population
void ReGeneratePopulation(void);

//Regenerate Population
void ReGeneratePopulationlast(void);

//Output result
int resultoutput(void);

#endif