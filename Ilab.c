#include <stdio.h>
#include <limits.h>
#include <math.h>

#define M1 10
#define M2 20



int main()
{
    FILE* f1  = fopen("Data/DEDINSKIY.txt", "r");
    FILE* f2  = fopen("Data/Check.txt", "w");

    if (f1 == NULL || f2 == NULL)
    {
        printf("File can not be opened.\n");
        return 112;
    }
    int R = 0;
    unsigned long int sum = 0;
    double med = 0;
    int counter = 0;
    int min = INT_MAX;
    int max = 0;
    double SquareSum = 0;
    double rand = 0;

    while (fscanf(f1, "%d", &R) == 1)
    {
        /*Данные для подсчёта среднего сопротивления.*/
        sum += R;
        counter ++;


        /*Нахождение максимального и минимального значения.*/
        if(R > max)
        {
            max = R;
        }
        if(R < min)
        {
            min = R;
        }

    }

    med = ((double)sum)/((double)counter);


    /*Подсчёт разброса случайной величины.*/
    fseek(f1,0,SEEK_SET);
    while (fscanf(f1, "%d", &R) == 1)
    {
        SquareSum += pow((double)R - med, 2);
    }
    rand = pow(SquareSum/counter, 0.5);


    /*Нахождение количество попаданий на каждом участке 1.*/
    int i;
    int step1 = (max - min)/M1;
    unsigned int hits1[M1];
    for( int j = 0; j < M1; j++ )
    {
        hits1[j] = 0;
    }

    fseek(f1,0,SEEK_SET);
    while (fscanf(f1, "%d", &R) == 1)
    {
        for(i = 0; i < M1 - 1; i++)
        {
            if (R < min + (i + 1) * step1)
                break;
        }
        hits1[i]++;
    }


    /*Нахождение количество попаданий на каждом участке 2.*/
    int a;
    int step2 = (max - min)/M2;
    unsigned int hits2[M2];
    for( int j = 0; j < M2; j++ )
        hits2[ j ] = 0;

    fseek(f1,0,SEEK_SET);
    while (fscanf(f1, "%d", &R) == 1)
    {
        for(a = 0; a < M2 - 1; a++)
        {
            if (R < min + (a + 1) * step2)
                break;
        }
        hits2[a]++;
    }

    fprintf(f2, "\nhits1:\n");
    for(int b; b < M1; b++)
    {
        fprintf(f2, "%u\n", hits1[b]);
    }

    fprintf(f2, "\nhits2:\n");

    for(int s; s < M2; s++)
    {
        fprintf(f2, "%u\n", hits2[s]);
    }

    fprintf(f2, "\n min: %d max: %d med: %lf interval1: %f interval2: %f rand: %lf", min, max, med, ((double)max - (double)min)/M1, ((double)max - (double)min)/M2, rand);


    fclose(f1);
    fclose(f2);

    return 0;
}