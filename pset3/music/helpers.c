// Helper functions for music

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define A4REF 48

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
  int num = atoi(strtok(note, "/"));
  int denom = atoi(strtok(NULL, "/"));

  return (8 * num) / denom;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter = toupper(note[0]);
    char modifier = 'x';
    int octave;

    // Get the octave and modifier (if it has one)
    if (strlen(note) == 2)
    {
        octave = note[1] - '0';
    }
    else
    {
        modifier = note[1];
        octave = note[2] - '0';
    }

    // Get the integer version of the note, `ni`
    // i.e., the number of semitones from A4
    int ni = 12 * octave - A4REF;
    switch (letter)
    {
        case 'C': break;
        case 'D': ni += 2;
                  break;
        case 'E': ni += 4;
                  break;
        case 'F': ni += 5;
                  break;
        case 'G': ni += 7;
                  break;
        case 'A': ni += 9;
                  break;
        case 'B': ni += 11;
                  break;
    }

    if (modifier == '#')
    {
        ni += 1;
    }
    else if (modifier == 'b')
    {
        ni -= 1;
    }

    // Calculate the frequency via the given formula
    return (int) round(pow(2, (double) ni / (double) 12) * 440);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // If the string is empty, return 1
    if (strlen(s) == 0)
    {
        return 1
    }
    // Otherwise, return 0
    else
    {
        return 0
    }
}
