/*
 * File         : film.c
 * 
 * Date         : Thursday 27th October 2016
 * 
 * Author       : Christopher Irvine, ruw12gbu, 100036248
 * 
 * Description  : Source file that defines ADTs consisting of a struct and a 
 *                set of interface functions that describes a single film.
 *                Struct should not be accessed outside of this file and film.h
 * 
 * History      : 27/10/2016 v1.00
 *                10/11/2016 v1.10 - Functionality added
 *                16/11/2016 v1.20 - Comments added, code cleaned up.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "film.h"

Film *film_new(char* title, int year, char* rating, char* genre, int length,
        float reviewRating)
{
    Film *film = (Film*)malloc(sizeof(Film));
    
    film->title = strdup(title);
    film->year = year;
    strcpy(film->rating, rating);
    strcpy(film->genre, genre);
    film->length = length;
    film->reviewRating = reviewRating;
    return film;
}

void film_print(Film* film) 
{
    printf("Title: %s\n", film->title);
    printf("Year: %d\n", film->year);
    printf("Certificate: %s\n", film->rating);
    printf("Genre: %s\n", film->genre);
    printf("Run time: %d\n", film->length);
    printf("Review Rating: %f\n", film->reviewRating);
}