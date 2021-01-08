#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<random>
#include<chrono>
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

class Player{
	public:
		string name;
		int score;
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
		if(score >= 50){
			save << player_name << ": " << score <<" pass" << "\n";
		}else{
			save << player_name << ": " << score <<" un_pass" << "\n";
		}
		save.close();
	}
}
void shuffle_array(Question arr[], int n)
{

	// To obtain a time-based seed
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// Shuffling our array
	shuffle(arr, arr + n, default_random_engine(seed));
}
//saveTopTen
// void readScore(vector<Player> &player)
// {
// 	string name;
// 	int score;
// 	ifstream infile("score.txt");
// 	while (infile >> name >> score)
// 	{

// 		Player p;
// 		p.name = name;
// 		p.score = score;
// 		player.push_back(p);
// 	}
// }
// int findMinScore(vector<Player>ps){
// 	int min = 10000;
// 	for (int i = 0; i < ps.size(); i++)
// 	{
// 		if(min > ps[i].score){
// 			min = ps[i].score;
// 		}
// 	}
// 	return min;
// }
// void saveMultiScore(string player_name, int score){
// 	fstream save;
// 	save.open("score.txt");
// 	if (save.is_open())
// 	{
// 		save << player_name << ": " << score << "\n";
// 		save.close();
// 	}
// }
// void saveScore(string player_name, int score){
// 	Player new_player;
// 	new_player.name = player_name;
// 	new_player.score = score;
// 	vector<Player> players;
// 	readScore(players);
// 	if((int)players.size() < 10){
// 		saveSingleScore(player_name, score);
// 	}else{
// 		int min = findMinScore(players);
// 		for (int i = 0; i < players.size(); i++)
// 		{
// 			if(players[i].score == min){
// 				players[i] = new_player;
// 			}
// 		}
// 		for (int i = 0; i < 10; i++)
// 		{
// 			/* code */
// 			saveMultiScore(players[i].name, players[i].score);
// 		}
// 	}
// }