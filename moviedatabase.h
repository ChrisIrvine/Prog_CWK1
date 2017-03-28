/*
 * File         : moviedatabase.h
 * 
 * Date         : Thursday 27th October 2016
 * 
 * Author       : Christopher Irvine, ruw12gbu, 100036248
 * 
 * Description  : Header file that defines an ADT representing the database 
 *                (collection) of Film structures. This should be implemented as
 *                a linked list (or other suitable data structure) as the
 *                number of films in the database is not known in advance.
 *                This should include an interface routing for loading the
 *                database from the file. 
 * 
 * History      : 27/10/2016 v1.00
 *                10/11/2016 v1.10 - Functionality added
 *                16/11/2016 v1.20 - Comments added, code cleaned up.
 */

#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
    
#include "film.h"
    
typedef struct _Mvdb
{
    Film* value;
    struct _Mvdb* next;
}Mvdb;

typedef struct _List
{
    Mvdb* first;
    Mvdb* last;
}List;

typedef Mvdb* Iterator;


/*
 * Inline methods to help navigate the linked list.
 */
static inline Iterator list_begin(const List *list)
{
    return list->first; 
}

static inline Iterator list_end(const List *list)
{
    return NULL;
}

static inline Iterator iterator_next(const Iterator i)
{
    return i->next;
}

static inline Film* iterator_value(const Iterator i)
{
    return i->value;
}

static inline Iterator iterator_set(Iterator i, Film* value)
{
    i-> value = value;
}

List * list;

/*******************************************************************************

Procedure   : list_populate

Parameters  : FILE* input - a function that opens up, in read mode, an external 
                            .txt file. Allowing the data to be scraped.
 
Returns     : List* - a pointer to a linked list of film structs
 
Description : Scrape an open file; uses the film_new() method to add its data,
              line by line, to a struct and then adds the newly made struct into
              a linked list.

 ******************************************************************************/
List* list_populate(FILE* input);

/*******************************************************************************

Procedure   : list_new

Parameters  : No parameters
 
Returns     : List* - an empty linked list
 
Description : Creates an empty linked list (List* list) that is ready for use.

 ******************************************************************************/
List* list_new();

/*******************************************************************************

Procedure   : list_add

Parameters  : List* list - a filled linked list of Film structs
              Film* value - a filled Film Struct
 
Returns     : void
 
Description : Takes the currently selected Film Struct and appends it into the 
              linked list, list. 

 ******************************************************************************/
void list_add(List* list, Film* value);

/*******************************************************************************

Procedure   : list_insert

Parameters  : List* list - a filled linked list of Film structs
              Film* value - a filled Film Struct
 
Returns     : void
 
Description : Takes the currently selected Film Struct and inserts it to the 
              front of the linked list. 

 ******************************************************************************/
void list_insert(List* list, Film* value);

/*******************************************************************************

Procedure   : list_length

Parameters  : List* list - a filled linked list of Film structs
 
Returns     : int - a single number representing the length of the linked list
 
Description : Iterates over the entire linked list, list, when it comes across 
              a used node it adds 1 to a counter. When it reaches the end of 
              the linked list it returns the value of the counter variable.

 ******************************************************************************/
int list_length(List* list);

/*******************************************************************************

Procedure   : list_head

Parameters  : List* list - a filled linked list of Film structs
 
Returns     : Film* - pointer to a Film Struct
 
Description : Selects the first element in the linked list, list, and returns 
              all data attached to it.

 ******************************************************************************/
Film* list_head(List* list);

/*******************************************************************************

Procedure   : list_tail

Parameters  : List* list - a filled linked list of Film structs
 
Returns     : Film* - pointer of a Film Struct
 
Description : Selects all elements after the first in the linked list, list, and
              returns all data attached to them.

 ******************************************************************************/
Film* list_tail(List* list);

/*******************************************************************************

Procedure   : list_sortBy

Parameters  : List* list - a filled linked list of Film structs
              int* function(Mvdb*) - a function pointer to one a function that 
                                     instructs the function by what element it 
                                     sorting by.
 
Returns     : void
 
Description : Sorts the linked list, list, by a given element, as defined when
              the function is called. Occurs by iterating over list and if the
              next Film Struct's given element is higher that of the currently
              selected Film Struct's the next element is moved above to the top 
              of list.

 ******************************************************************************/
void list_sortBy(List* list, int function(Mvdb*));

/*******************************************************************************

Procedure   : list_searchFilmNoir

Parameters  : List* list - a filled linked list of Film structs
               
Returns     : TempList* - pointer to a filled temporary holding linked list
 
Description : Searched over the linked list, list, for all Film Struct's whose 
              Genre element contains "Film-Noir". When one is found it is added
              to a temporary holding linked list. That linked list is then 
              returned and is ready for use.

 ******************************************************************************/
List* list_searchFilmNoir(List* list);

/*******************************************************************************

Procedure   : list_searchSciFi

Parameters  : List* list - a filled linked list of Film structs
               
Returns     : TempList* - pointer to a filled temporary holding linked list
 
Description : Searched over the linked list, list, for all Film Struct's whose 
              Genre element contains "Sci-Fi". When one is found it is added
              to a temporary holding linked list. That linked list is then 
              returned and is ready for use.

 ******************************************************************************/
List* list_searchSciFi(List* list);

/*******************************************************************************

Procedure   : list_sortTitle

Parameters  : List* list - a filled linked list of Film structs
 
Returns     : Returns an organised linked list.
 
Description : Sorts the linked list, list, looking for the shortest title.

 ******************************************************************************/
Film* list_sortTitle(List* list);

/*******************************************************************************

Procedure   : list_deleteRFilms

Parameters  : List* list - a filled linked list of Film structs
               
Returns     : void
 
Description : Iterates over the linked list, list, and frees any film with the 
              Rating "R".

 ******************************************************************************/
void list_deleteRFilms(List* list);

/*******************************************************************************

Procedure   : list_clear

Parameters  : List* list - a filled linked list of Film structs
 
Returns     : void
 
Description : Frees all the nodes in the linked list, list.

 ******************************************************************************/
void list_clear(List* list);

/*******************************************************************************

Procedure   : list_printAll

Parameters  : List* list - a filled linked list of Film structs
 
Returns     : void
 
Description : Iterates over the linked list, list, and prints out each Film 
              Struct one by one by using the film_print() function. Also 
              includes some general formatting for ease of use.

 ******************************************************************************/
void list_printAll(List* list);

/*******************************************************************************

Procedure   : list_printSelect

Parameters  : List* list - a filled linked list of Film structs
              int index - Number of the element that should be printed
 
Returns     : void
 
Description : Iterates over the linked list - a set number of times, list, and 
              prints a selected Film Struct one by one by using the film_print()
              function. Also includes some general formatting for ease of use.

 ******************************************************************************/
void list_printSelect(List* list, int index);

/*******************************************************************************

Procedure   : list_title

Parameters  : Mvdb* node - pointer to a Film Struct object
 
Returns     : int - returns a 1 or a 0 depending on the Film Structs data
 
Description : Tests the selected Film Struct's title against the next Film
              Struct's title in the linked list, list, currently organises in 
              alphabetical order.

 ******************************************************************************/
int list_title(Mvdb* node);

/*******************************************************************************

Procedure   : list_year

Parameters  : Mvdb* node - pointer to a Film Struct object
 
Returns     : int - returns a 1 or a 0 depending on the Film Structs data
 
Description : Compares the current Film Struct's year against the next Film 
              Struct in the linked list. Returns a 1 if it is greater and a 0
              if it is less. Uses an if statement.

 ******************************************************************************/
int list_year(Mvdb* node);

/*******************************************************************************

Procedure   : list_rating

Parameters  : Mvdb* node - pointer to a Film Struct object
 
Returns     : int - returns a 1 or a 0 depending on the Film Structs data
 
Description : Tests the selected Film Struct's rating against the next Film
              Struct's rating in the linked list, list, currently organises in 
              alphabetical order.

 ******************************************************************************/
int list_rating(Mvdb* node);

/*******************************************************************************

Procedure   : list_rating

Parameters  : Mvdb* node - pointer to a Film Struct object
 
Returns     : int - returns a 1 or a 0 depending on the Film Structs data
 
Description : Tests the selected Film Struct's genre against the next Film
              Struct's genre in the linked list, list, currently organises in 
              alphabetical order.

 ******************************************************************************/
int list_genre(Mvdb* node);

/*******************************************************************************

Procedure   : list_lengthS

Parameters  : Mvdb* node - pointer to a Film Struct object
 
Returns     : int - returns a 1 or a 0 depending on the Film Structs data
 
Description : Compares the current Film Struct's length against the next Film 
              Struct in the linked list. Returns a 1 if it is longer and a 0
              if it is shorter. Uses an if statement.

 ******************************************************************************/
int list_lengthS(Mvdb* node);

/*******************************************************************************

Procedure   : list_reviewRating

Parameters  : Mvdb* node - pointer to a Film Struct object
 
Returns     : int - returns a 1 or a 0 depending on the Film Structs data
 
Description : Compares the current Film Struct's reviewRating against the next 
              Film Struct's reviewRating in the linked list. Returns a 1 if it 
              is longer and a 0 if it is shorter. Uses an if statement.

 ******************************************************************************/
int list_reviewRating(Mvdb* node);

#ifdef __cplusplus
}
#endif

#endif /* MOVIEDATABASE_H */

