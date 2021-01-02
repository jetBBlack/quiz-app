#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Question
{
public:
	string question;
	string option1;
	string option2;
	string option3;
	string option4;
	string answer;
	void setObjProperty(int index);
};

void readQuestion(int position,string filename,string question[]){
	string line;
	string sentence[20][6];
	int indexX = 0;
	int indexY = 0;
	ifstream myFile(filename);
	
	if (myFile.is_open())
	{
		/* code */
		while(getline(myFile,line)){
			sentence[indexX][indexY++]=line;
			if(line==""){
				continue;
				indexX++;
				indexY=0;
			}
		}
		
	}
	
	for (int i = 0; i < 5; i++)
	{
		question[i] = sentence[position][i];
	}
}
void readAnswer(string filename,string answer[]){
	string line;
	ifstream myAns(filename);
	int index =0;
	if (myAns.is_open())
	{
		while(getline(myAns, line)){
			answer[index++]=line;
		}
	}
}
void Question::setObjProperty(int index)
{
	string aFilename = "answer.txt";
	string qFilename = "fun-quiz.txt";
	string que[100];
	string ans[100];
	readAnswer(aFilename, ans);
	readQuestion(index, qFilename, que);
	question = que[0];
	option1 = que[1];
	option2 = que[2];
	option3 = que[3];
	option4 = que[4];
	answer = ans[index];
}

void saveScore(string player_name, int score)
{
	
	fstream save;
	save.open("score.txt", fstream::app);
	if (save.is_open())
	{
		save << player_name << ": " << score << "\n";
		save.close();
	}
}
