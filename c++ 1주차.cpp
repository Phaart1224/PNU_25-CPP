#define _CRT_SECURE_NO_WARNINGS
# include <cstdlib>
# include <cstdio>



const int NUMBER_STUDENTS = 2;
const int NUMBER_QUIZZES = 3;
void readScores(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES]) {
	for (int row = 0; row < NUMBER_STUDENTS; row++) {
		for (int column = 0; column < NUMBER_QUIZZES; column++)
			scanf("%d", &score[row][column]);
	}
}
void display(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES]) {
	for (int row = 0; row < NUMBER_STUDENTS; row++) {
		for (int column = 0; column < NUMBER_QUIZZES; column++){
			printf("%5d", score[row][column]);
		}
		printf("\n");
	}
	printf("\n");
}
void display(const float* average, const int number) {
	for (int row = 0; row < number; row++)
		printf("%lf   ", average[row]);
	printf("\n");
}
void computeStudentAverage(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES], float* average) {
	float sum = 0;
	for (int row = 0; row < NUMBER_STUDENTS; row++) {
		for (int column = 0; column < NUMBER_QUIZZES; column++) {
			sum += score[row][column];
		}
		average[row] = sum;
	}
}
void computeQuizAverage(const int score[NUMBER_STUDENTS][NUMBER_QUIZZES], float* average){
	float sum = 0;
	for (int column = 0; column < NUMBER_QUIZZES; column++) {
		for (int row = 0; row < NUMBER_STUDENTS; row++) {
			sum += score[row][column];
		}
		average[column] = sum;
	}
}

int main() {
	int scores[NUMBER_STUDENTS][NUMBER_QUIZZES];
	float studentAverage[NUMBER_STUDENTS];
	float quizAverage[NUMBER_QUIZZES];

	readScores(scores);

	printf("Student/Quiz Scores:\n");
	display(scores);

	computeStudentAverage(scores, studentAverage);
	printf("Student Average:\n");
	display(studentAverage, NUMBER_STUDENTS);

	computeQuizAverage(scores, quizAverage);
	printf("Quiz Average:\n");
	display(quizAverage, NUMBER_QUIZZES);
}
