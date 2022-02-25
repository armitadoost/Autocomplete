#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"


long int compare1(const void * terms1, const void * terms2){
    return strcmp(((struct term *)terms1)->term, ((struct term *)terms2)->term);
}
void read_in_terms(struct term **terms, int *pnterms, char *filename){
    char line[200];
    FILE *fp = fopen(filename, "r");
    *pnterms = atoi(fgets(line, sizeof(line), fp));
    
    *terms = (struct term*)malloc(sizeof(struct term)*(*pnterms));

    int countt;
    int countn;
    double dig_int;
    int start_num;
    int end_num;
    int space;

    for (int i = 0; i < (*pnterms); i++)
    {
        fgets(line, sizeof(line), fp);
        countt = 0;
        countn = 0;
        dig_int = 0;
        start_num = 0;
        end_num = 0;
        char dig[100];
        memset(dig, '\0', sizeof(dig));
        

        for (int j = 0; j < strlen(line); j++){

            if (isdigit(line[j]) && end_num == 0){
                if (start_num == 0){
                    start_num = 1;
                }
                if (!isdigit(line[j + 1]) && start_num == 1){
                    end_num = 1;
                    space = j + 1;
                }
                dig[countn] = line[j];
                countn++;
            }
            if (space == j){
                continue;
            }

            if (end_num == 1 && line[j] != '\0' && line[j] != '\n' && j != (space-1)){
                (*terms)[i].term[countt] = line[j];
                countt++;
            }

            dig_int = atof(dig);
        }
        (*terms)[i].weight = dig_int;
    }
    qsort((*terms), (*pnterms), sizeof(struct term), compare1);
}

int lowest_match(struct term *terms, int nterms, char *substr){

    int first;
    int last;
    int index;
    int count;
    int mid;
    int len;
    char temp[200];

    first = 0;
    last = nterms - 1;
    index = -1;
    count = -1;
    len = strlen(substr);
    

    while (first <= last && count != 0){
        mid = (first+last)/2;
        memset(temp, '\0', sizeof(temp));
        strncpy(temp, (terms[mid].term), len);

        if(strcmp(temp, substr) == 0){
            index = mid;
            count = count + 2;
            last--;
        }

        else{
            if (count != -1){
                count = 0;
            }
            if (strcmp(temp, substr) > 0){
                last = mid-1;
            }
            else{
                first = mid + 1;
            }
        }
    }
    return index;
}

int highest_match(struct term * terms, int nterms, char *substr){

    int first;
    int last;
    int index;
    int count;
    int mid;
    int len;
    char temp[200];

    first = 0;
    last = nterms - 1;
    index = -1;
    count = -1;
    len = strlen(substr);

    while (first <= last && count != 0){
        mid = (first+last)/2;
        memset(temp, '\0', sizeof(temp));
        strncpy(temp, (terms[mid].term), len);

        if(strcmp(temp, substr) == 0){
            index = mid;
            count = count + 2;
            first++;
        }

        else{
            if (count != -1){
                count = 0;
            }
            if (strcmp(temp, substr) > 0){
                last = mid-1;
            }
            else{
                first = mid + 1;
            }
        }
    }
    return index;
}

long int compare2(const void * terms1, const void * terms2){
    float value_compare;
    value_compare = ((((struct term *)terms2)->weight) - (((struct term *)terms1)->weight));

    if (value_compare == 0){
        return 0;
    }
    if (value_compare > 0){
        return 1;
    }
    if (value_compare < 0){
        return -1;
    }
}

void autocomplete(struct term * *answer, int *n_answer, struct term *terms, int nterms, char *substr){

    int low;
    int high;
    int countt;

    low = lowest_match(terms, nterms, substr);
    high = highest_match(terms, nterms, substr);
    countt = 0;

    (*n_answer) = (high-low) + 1;
    *answer = (struct term*)malloc(sizeof(struct term)*(*n_answer));

    if(low == -1 && high == -1){
        (*n_answer) = 0;
        *answer = NULL;
    }

    if((*n_answer) != 0){
        for(int i = low; i <= high; i++){
            strcpy((*answer)[countt].term, terms[i].term);
            (*answer)[countt].weight = terms[i].weight; 
            countt++;
        }
        qsort((*answer), (*n_answer), sizeof(struct term), compare2);
    }
}