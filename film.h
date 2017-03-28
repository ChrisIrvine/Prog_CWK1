/* 
 * File         : film.h
 * 
 * Date         : Thursday 27th October 2016
 * 
 * Author       : Christopher Irvine, ruw12gbu, 100036248
 * 
 * Description  : Header file that defines an ADT consisting of a struct
 *                and a set of interface functions that describes a single film.
 *                The struct should not be accessed outside of this file and 
 *                film.c
 * 
 * History      : 27/10/2016 v1.00
 *                10/11/2016 v1.10 - Functionality added
 *                16/11/2016 v1.20 - Comments added, code cleaned up.
 */

#ifndef FILM_H
#define FILM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>     
#include <string.h>
    

        
typedef struct FilmStruct
{
    char* title;
    int year;
    char rating[20];
    char genre[100];
    int length;
    float reviewRating;
}Film;


/*
 * Function to free the current film node
 */
static inline void film_free(Film *film)
{
    free(film);
    film = NULL;
}

/*
 * Set methods to alter the state of the Film Structs
 */
static inline void film_setTitle(Film *film, char* title)
{
    strcpy(film->title, title);
}

static inline void film_setYear(Film *film, int year)
{
    film->year = year;
}

static inline void film_setRating(Film *film, char* rating)
{
    strcpy(film->rating, rating);
}

static inline void film_setGenre(Film *film, char* genre)
{
    strcpy(film->genre, genre);
}

static inline void film_setLength(Film *film, int length)
{
    film->length = length;
}

static inline void film_setReviewRating(Film *film, float reviewRating)
{
    film->reviewRating = reviewRating;
}

/*
 * Get methods to return the current value of a variable within an individual
 * film struct.
 */
static inline const char* const film_getTitle(const Film *film)
{
    return film->title;
}
static inline int film_getYear(const Film *film)
{
    return film->year;
}

static inline const char* const film_getRating(const Film *film)
{
    return film->rating;
}

static inline const char* const film_getGenre(const Film *film)
{
    return film->genre;
}

static inline int film_getLength(const Film *film)
{
    return film->length;
}

static inline float film_getReviewRating(const Film *film)
{
    return film->reviewRating;
}

/*******************************************************************************

Procedure   : film_new

Parameters  : char * title - String of Characters taken from the films.txt file
              int year - Number taken from the films.txt file
              char * rating - String of Characters taken from the films.txt file
              char * genre - String of Characters taken from the films.txt file
              int year - Number taken from the films.txt file
              float reviewRating - Decimal point number taken from the film.txt
                                   file
 
Returns     : Film* - pointer to newly created film struct
 
Description : Allocate memory for a new Film Struct element and returns the film
              struct object, ready for use in a linked list.

 ******************************************************************************/
Film *film_new(char* title, int year, char* rating, char* genre, 
        int length, float reviewRating);

/*******************************************************************************

Procedure   : film_print

Parameters  : film - a Film struct node that contains the all the information 
                     defined in the film_new function.
 
Returns     : void
 
Description : Prints out a single Film Struct node, in a formatted fashion.

 ******************************************************************************/
void film_print(Film* film);
#ifdef __cplusplus
}
#endif

#endif /* FILM_H */

