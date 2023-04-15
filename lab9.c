#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RecordType
{
    int id;
    char name;
    int order;
};

struct HashType
{
    int key;
    int count;
    struct RecordType *records;
};

int hash(int x)
{
    int hashValue = x % 11;
    return hashValue;
}

int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);

        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }

        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name, &pRecord->order);
        }

        fclose(inFile);
    }

    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i, j;

    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);

        if (pHashArray[i].count > 0)
        {
            for (j = 0; j < pHashArray[i].count; ++j)
            {
                printf("%d, %c, %d -> ", pHashArray[i].records[j].id, pHashArray[i].records[j].name, pHashArray[i].records[j].order);
            }
            printf("NULL\n");
        } else {
            printf("NULL\n");
        }
    }
}


int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    const int hashSz = 10;
    struct HashType hashArray[hashSz];
    memset(hashArray, 0, sizeof(hashArray)); // set all the keys to 0

    // Insert records into hash table
    for (int i = 0; i < recordSz; i++)
    {
        int hashValue = hash(pRecords[i].id);
        struct HashType *pHash = &hashArray[hashValue];

        if (pHash->records == NULL)
        {
            pHash->key = hashValue;
            pHash->count = 0;
            pHash->records = malloc(sizeof(struct RecordType) * recordSz);
        }

        pHash->records[pHash->count] = pRecords[i];
        pHash->count++;
    }

    // Display hash table
    displayRecordsInHash(hashArray, hashSz);

    free(pRecords);
    return 0;
}
