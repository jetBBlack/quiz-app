#include <iostream>
#include <fstream>
#include <string>
#include "file_handle.cpp"


void readQuestion(int position, string filename, string question[]);
void readAnswer(string filename, string answer[]);
void saveScore(string player_name, int score);
void shuffle_array(Question arr[], int n);
