#include "autocomplete.h"

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");

    printf("%d\n" , lowest_match(terms, nterms, "123"));

    
    printf("%d", highest_match(terms, nterms, "13"));
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "13");
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
}