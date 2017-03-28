/* 
 * File         : main.c
 * 
 * Date         : Thursday 27th October 2016
 * 
 * Author       : Christopher Irvine, ruw12gbu, 100036248
 * 
 * Description  : Source file that utilises the ADTs defined in film.h, film.c,
 *                moviedatabase.h and moviedatabase.c to perform a series of 
 *                tasks on a movie collection.
 * 
 * History      : 27/10/2016 v1.00
 *                10/11/2016 v1.10 - added Scrape method, functionality added
 *                16/11/2016 v1.20 - added comments, cleaned up code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moviedatabase.h"
#include "film.h"

Film chronologicalOrder(List* list);

Film filmNoirSearch(List* list);

Film sciFiSearch(List* list);

Film highestRated(List* list);

Film shortestTitle(List* list);

void deleteR(List* list);

int main(int argc, char** argv) 
{
    FILE*input = fopen("films.txt", "r");
    
    if(input == NULL)
    {
        printf("Error: unable to open 'film.txt' in mode 'r'\n");
        
        exit(EXIT_FAILURE);
    }
    
    List* list = list_populate(input);
    
    chronologicalOrder(list);
    
    filmNoirSearch(list);
    
    sciFiSearch(list);
    
    highestRated(list);
    
    shortestTitle(list);
    
    deleteR(list);
    
    return (EXIT_SUCCESS);
}

Film chronologicalOrder(List* list)
{
    printf("\nOffline MVDB in Chronological Order (oldest to newest):");
    list_sortBy(list, list_year);
    list_printAll(list);
}
    
    //method to display the 3rd longest film in y genre
Film filmNoirSearch(List* list)
{
    int index = 3;
    printf("\nThe Third Longest Film-Noir film is: ");
    list_sortBy(list, list_lengthS);
    list_printSelect(list_searchFilmNoir(list), index);
}

Film sciFiSearch(List* list)
{
    int index = 10;
    printf("\nThe Tenth Highest Rated Sci-Fi Film is: ");
    list_sortBy(list, list_reviewRating);
    list_printSelect(list_searchSciFi(list), index);
}

Film highestRated(List* list)
{
    int index = 1;
    printf("\nThe Highest Rated Film is: ");
    list_sortBy(list, list_reviewRating);
    list_printSelect(list, index);
}

Film shortestTitle(List* list)
{
    int index = 1;
    printf("\nThe Film with the Shortest Title is:");
    film_print(list_sortTitle(list));
}
    
void deleteR(List* list)
{
    list_deleteRFilms(list);
    list_printAll(list);
}