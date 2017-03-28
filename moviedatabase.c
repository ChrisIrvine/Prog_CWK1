/*
 * File         : moviedatabase.c
 * 
 * Date         : Thursday 27th October 2016
 * 
 * Author       : Christopher Irvine, ruw12gbu, 100036248
 * 
 * Description  : Source file that defines an ADT representing the database 
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "moviedatabase.h"

List* list_populate(FILE* input)
{
    char line[255];
    char title[100];
    int year;
    char rating[50];
    char genre[100];
    int length;
    float reviewRating;
    list = list_new();
    
    while(fgets(line, 255, input) != NULL)
    {
        sscanf(line, "\"%[^\",]\",%d,\"%[^\",]\",\"%[^\",]\",%d,%f\n", title, 
            &year, rating, genre, &length, &reviewRating);
        
        Film * f = film_new(title, year, rating , genre, length, reviewRating);
        
        list_add(list, f);  
    }
    printf("Films successfully read into MVDB: %i", list_length(list));
    return list;
    
}

List* list_new()
{
    List* list = (List*)malloc(sizeof(List));
    
    if (list == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory in list_new()\n");
        
        exit(EXIT_FAILURE);
    }
    
    list->first = NULL;
    list->last = NULL;
    
    return list;
}

void list_add(List* list, Film* value)
{
    Mvdb* node = (Mvdb*)malloc(sizeof(Mvdb));
    
    if (node == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory in list_add()\n");
        
        exit(EXIT_FAILURE);
    }
    
    node->value = value;
    node->next = NULL;
    
    if (list->last == NULL)
    {
        list->first = list->last = node;
    }
    else
    {
        list->last = list->last->next = node;
    }
}

void list_insert(List* list, Film* value)
{
    Mvdb* node = (Mvdb*)malloc(sizeof(Mvdb));
    
    if (node == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory in list_insert()\n");
        
        exit(EXIT_FAILURE);
    }
    
    node->value = value;
    node->next = list->first;
    
    if (list->first == NULL)
    {
        list->first = list->last = node;
    }
    else
    {
        list->first = node;
    }
}

int list_length(List* list)
{
    int length = 0;
    
    for (Mvdb* node = list->first; node != NULL; node = node->next)
    {
        length++;
    }
    
    return length;
}

Film* list_head(List* list)
{
    if (list->first == NULL)
    {
        fprintf(stderr, "Error: attempt to return the head of an empty list.");
        
        exit(EXIT_FAILURE);
    }
    
    Film* value = list->first->value;
    
    Mvdb *node = list->first;
    
    if (list->first == list->last)
    {
        list->first = list->last = NULL;
    }
    else
    {
        list->first = list->first->next;
    }
    
    free(node);
    
    return value;
}

Film* list_tail(List* list)
{
    if (list->first == NULL)
    {
        fprintf(stderr, "Error: attempt to return the tail of an empty list.");
        
        exit(EXIT_FAILURE);
    }
    
    Film* value = list->last->value;
    
    Mvdb* tail = list->last;
    
    if (list->first == list->last)
    {
        list->first = list->last = NULL;
    }
    else
    {
        Mvdb* node;
        
        for (node = list->first; node->next != tail; node = node-> next);
        
        list->last          = node;
        list->last->next    = NULL;
    }
    
    free(tail);
    
    return value;
}

void list_sortBy(List* list, int (function)(Mvdb*))
{
    if (list->first != list->last) //list contains two or more items
    {
        int sorted;
        
        do
        {
            sorted = 1;
            
            for (Mvdb* node=list->first; node->next!=NULL; node=node->next)
            {
                if (function(node))
                {
                    Film* temp = node->value;
                    node->value = node->next->value;
                    node->next->value = temp;
                    sorted = 0;
                }
            }
        }
        while(!sorted);
    }
}

List* list_searchFilmNoir(List* list)
{
    List* tempList = list_new();
    Mvdb* node = list->first;
    while(node!=NULL)
    {
        if(strstr(node->value->genre, "Film-Noir"))
        {
            list_add(tempList, node->value);
        }
        node = node->next;
    }
    return tempList;
}

List* list_searchSciFi(List* list)
{
    List* tempList = list_new();
    Mvdb* node = list->first;
    while(node!=NULL)
    {
        if(strstr(node->value->genre, "Sci-Fi"))
        {
            list_add(tempList, node->value);
        }
        node = node->next;
    }
    return tempList;
}

Film* list_sortTitle(List* list)
{
    Mvdb* node = list->first;
    Film* shortTitle = node->value;
    printf("\n");
    while(node != NULL)
    {
        if(strlen(node->value->title) < strlen(shortTitle->title))
        {
            shortTitle = node->value;
        }
        node = node->next;
    }
    
    return shortTitle;
}

void list_deleteRFilms(List* list)
{
    Mvdb* node = list->first;
    
    while(node!=NULL)
    {
        if(strstr(node->value->rating, "R"))
        {
            film_free(node);
        }
        node = node->next;
    }
}

void list_clear(List *list)
{
    while (list->first != NULL)
    {
        Mvdb* node = list->first; 
        
        list->first = node->next;
        
        free(node);
    }
    
    list->last = NULL;
}

void list_printAll(List* list)
{
    printf("\n");
    
    printf("*********************************************************\n");
    Mvdb* node = list->first;
    while(node!=NULL)
    {        
        printf("----------------------------------------------------------\n");
        film_print(node->value);
        node = node->next;
    }
    printf("*********************************************************\n");
}

void list_printSelect(List* list, int index)
{
    printf("\n");
    
    printf("*********************************************************\n");
    Mvdb* node = list->first;
    int i = 0;
    for(int i = 1; i < index; i++)
    {
        node = node->next;
    }
   
    film_print(node->value);

    printf("*********************************************************\n");
}

int list_title(Mvdb* node)
{
    if (strlen(node->value->title) > strlen(node->value->title))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int list_year(Mvdb* node)
{
    if ((node->value->year > node->next->value->year) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int list_rating(Mvdb* node)
{
    if (strcmp(node->value->rating, node->next->value->rating) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int list_genre(Mvdb* node)
{
    if (strcmp(node->value->genre, node->next->value->genre) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int list_lengthS(Mvdb* node)
{
    if ((node->value->length < node->next->value->length) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int list_reviewRating(Mvdb* node)
{
    if ((node->value->reviewRating < node->next->value->reviewRating) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}