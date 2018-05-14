#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char** findAtomList(char** atomList, char* str);
char** tidyList(char **atomList, int j);
int* matrixSolution(int** matrix, int column, int row);
int **coefMatrix(char *string, char **tidy);
int atomCount(char** atom, int m, int begin, int end, char* string);
int gcd(int a, int b);
int count;
int main() {
	char *string = NULL;
	string = (char*)malloc(sizeof(char) * 1);
	char ch = 's';
	int **tobeSolved = NULL;
	int i = 0;
	char **atomList = NULL;

	atomList = (char**)malloc(sizeof(char*) * 1);

	while (ch != '\n') {
		ch = getchar();
		string = (char*)realloc(string, sizeof(char)*(i + 1));
		string[i] = ch;
		i++;
	}

	atomList = findAtomList(atomList, string);


	tobeSolved = coefMatrix(string, atomList);
	return 0;


}

char** findAtomList(char** atomList, char* str) {
	int i = 0, j = 0;
	int len = strlen(str);
	while (i <len) {
		if ((str[i] >= 'A') && (str[i] <= 'Z')) {
			if ((str[i + 1] >= 'a') && (str[i + 1] <= 'z')) {

				atomList = (char**)realloc(atomList, sizeof(char*) * (j + 1));

				atomList[j] = (char*)calloc(2, sizeof(char));
				atomList[j][0] = str[i];
				atomList[j][1] = str[++i];
				

				j++;


			}

			else {

				atomList = (char**)realloc(atomList, sizeof(char*) * (j + 1));

				atomList[j] = (char*)calloc(2, sizeof(char));
				atomList[j][0] = str[i];
				

				j++;



			}

		}
		i++;
	}
	atomList = tidyList(atomList, j);
	return  atomList;
}
char** tidyList(char **atomList, int j) {
	char** tidy;
	tidy = NULL;
	tidy = (char**)malloc(1 * sizeof(char*));
	int i = 0, k, m, exist = 0;
	tidy[0] = (char*)malloc(2 * sizeof(char));
	for (k = 0; k < j; k++) {


		for (m = 0; m < i; m++) {
			if ((tidy[m][0] == atomList[k][0]) && (tidy[m][1] == atomList[k][1])) {
				exist = 1;
			}
		}
		if (exist == 0) {
			tidy = (char**)realloc(tidy, (i + 1) * sizeof(char*));
			tidy[i] = (char*)malloc(2 * sizeof(char));
			tidy[i][0] = atomList[k][0];
			tidy[i][1] = atomList[k][1];


			i++;
		}
		else {
			exist = 0;

		}

		count = i;



	}
	return tidy;
}


int **coefMatrix(char *string, char **tidy) {
	int i = 0;
	int begin, end, m = 0, n, k = 0;
	int **matrix = NULL;
	int middle = 400;
	matrix = (int**)malloc(sizeof(int*) * 1);

	while (m<count) {
		i = 0;
		begin = 0;
		n = 0;
		end = 0;
		matrix = (int**)realloc(matrix, sizeof(int*) * (m + 1));
		matrix[m] = (int*)malloc(sizeof(int) * 1);

		while (i<strlen(string)) {
			if (string[i] == '+') {
				end = i;
				matrix[m] = (int*)realloc(matrix[m], sizeof(int) * (n + 1));
				if (i < middle) {
					matrix[m][n] = atomCount(tidy, m, begin, end, string);

				}
				else {
					matrix[m][n] = -atomCount(tidy, m, begin, end, string);

				}
				n++;
				begin = i + 1;
			}
			else if (string[i] == '>') {
				middle = i;
				matrix[m] = (int*)realloc(matrix[m], sizeof(int) * (n + 1));

				matrix[m][n] = atomCount(tidy, m, begin, middle - 1, string);
				n++;
				begin = i + 1;
			}
			else if (i == strlen(string) - 1) {
				end = i;
				matrix[m] = (int*)realloc(matrix[m], sizeof(int) * (n + 1));

				matrix[m][n] = -atomCount(tidy, m, begin, end, string);


			}
			i++;
		}
		m++;
	}

	matrixSolution(matrix, n + 1, m);
	return matrix;

}

int atomCount(char **atom, int m, int begin, int end, char *string) {
	int count = 0;
	int i = begin;
	int e, j;
	int n1, n2;
	e = 0;
	j = 0;



	if (atom[m][1] != NULL) {
		while (i < end) {
			if (string[i] == atom[m][0]) {

				if (string[i + 1] == atom[m][1]) {
					if ((string[i + 2] >= '1') && (string[i + 2] <= '9')) {
						n1 = string[i + 2] - '0';
						if ((string[i + 3] >= '0') && (string[i + 3] <= '9')) {
							n2 = string[i + 3] - '0';
							count += 10 * n1 + n2;
						}
						else {
							count += n1;
						}
					}
					else if ((string[i + 2] >= 'A') && (string[i + 2] <= 'Z')) {
						count++;
					}
				}
				else {

				}

			}
			else if (string[i] == '(') {
				j = i + 1;
				while (j < end) {
					if (string[j] == ')') {
						e = j;
						break;
					}
					j++;
				}
				if ((string[e + 1] >= '1') && (string[e + 1] <= '9')) {
					n1 = string[e + 1] - '0';
					if ((string[e + 2] >= '0') && (string[e + 2] <= '9')) {
						n2 = string[e + 2] - '0';
						count += ((10 * n1 + n2 - 1)*atomCount(atom, m, i, e, string));
					}
					else {
						count += (n1 - 1)*atomCount(atom, m, i, e, string);
					}
				}
				else {
					count += atomCount(atom, m, i, e, string);

				}

			}
			else {
			}
			i++;
		}
	}
	else {

		while (i < end) {
			if (string[i] == atom[m][0]) {

				if ((string[i + 1] >= 'A') && (string[i + 1] <= 'Z')) {
					count++;
				}
				else if ((string[i + 1] >= '1') && (string[i + 1] <= '9')) {
					n1 = string[i + 1] - '0';
					if ((string[i + 2] >= '0') && (string[i + 2] <= '9')) {
						n2 = string[i + 2] - '0';
						count += 10 * n1 + n2;
					}
					else {
						count += n1;
					}
				}
				else {

				}
				i++;
			}



			else if (string[i] == '(') {
				j = i + 1;
				while (j < end) {
					if (string[j] == ')') {
						e = j;
						break;
					}
					j++;
				}
				if ((string[e + 1] >= '1') && (string[e + 1] <= '9')) {
					n1 = string[e + 1] - '0';
					if ((string[e + 2] >= '0') && (string[e + 2] <= '9')) {
						n2 = string[e + 2] - '0';
						count += (10 * n1 + n2 - 1)*atomCount(atom, m, i, e, string);
					}
					else {
						count += (n1 - 1)*atomCount(atom, m, i, e, string);
					}
				}
				else {
					count += atomCount(atom, m, i, e, string);

				}

			}
			else {
			}
			i++;
		}
	}
	return count;

}

int* matrixSolution(int** matrix, int column, int row) {
	int m = 0, j = 0;
	int p, i, Gcd;
	int c1, c2;
	int* solution = NULL;
	solution = (int*)malloc(sizeof(int)*column);
	while (m <row-1) {
		for (p = m + 1;p < row;p++) {
			
			c1 = matrix[m][m];
			c2 = matrix[p][m];
			Gcd = gcd(c1, c2);
			if (c1 == 0) {
				break;
			}
			else if (c2 == 0) {
				continue;
			}
			else {
				for (i = 0; i < column;i++) {
					matrix[m][i] *= c2 / Gcd;
				}
				for (i = 0; i < column;i++) {
					matrix[p][i] *= c1 / Gcd;
				}
				for (i = 0; i < column;i++) {
					matrix[p][i] -= matrix[m][i];
				}
			}

			
		}
		m++;

	}
	

	for (m = row - 1; m >= 0;m--) {
		
		solution[m] = matrix[m][column-1];
		for (i = column-1;i > m - 1;i--) {
			solution[m] -= matrix[m][i] * solution[i];

		}
		if (solution[m] % matrix[m][m] == 0) {
			solution[m] /= matrix[m][m];
		}
	}
	
	Gcd = solution[0];
	for (i = 1;i < column;i++) {
		Gcd= gcd(solution[i], Gcd);

	}
	for (i = 0;i < column;i++) {
		solution[i] = solution[i]/Gcd;
	}
	
	return solution;

}
int gcd(int a, int b) {
	int  remainder, temp;
	if (a == b) {
		return a;
	}
	if (a == 0) {
		if (b == 0) {
			return 1;
		}
		else {
			return b;
		}
		 
	}
	if(b == 0) {
		return a;
	}
	if (a < b) {
		temp = b;
		b = a;
		a = temp;
	}
	while (1) {
		if (b == 0) {
			return a;
		}

		remainder = a % b;



		a = b;
		b = remainder;
	}
	
}
















