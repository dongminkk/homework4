#include <stdio.h>
#include <stdlib.h> //srand, 동적할당
#include <time.h> //time

/* Method Declaration */
int** create_matrix(int row, int col); //동적 메모리할당하여 행렬 만드는 함수
void print_matrix(int** matrix, int row, int col); // 행렬을 출력하는 함수
int free_matrix(int** matrix, int row, int col); //동적 메모리로 할당되었던 배열 해제하는 함수
int fill_data(int** matrix, int row, int col); // // 입력한 행 열에 맞게 임의값 할당하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //A와 B의 행렬을 더하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // A와 B의 행렬을 빼는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 해당 행렬의 전치행렬 T를 구현하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //A × T를 하는 함수

int main()
{
    char command; //문자형 변수 선언 매뉴선택
    printf("[----- [kim dongmin]  [2017038093] -----]\n");

	int row, col; //정수형 변수 선언
	srand(time(NULL)); //난수 생성

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); //행과 열 입력
    int** matrix_a = create_matrix(row, col); // 입력한 행과 열에 맞게 동적 메모리할당하여 행렬을 만듬 a행렬 
	int** matrix_b = create_matrix(row, col); // 입력한 행과 열에 맞게 동적 메모리할당하여 행렬을 만듬 b행렬
    int** matrix_a_t = create_matrix(col, row); // 입력한 행과 열과 반대로 동적 메모리할당하여 행렬을 만듬 t행렬

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} //행렬 a b가 없으면 리턴 -1

	do{ // 반복문 do
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n"); 
		printf(" Add Matrix          = a           Subtract Matrix     = s \n"); 
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n"); 
		printf(" Quit                = q \n"); 
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command에 값을 할당 받음

		switch(command) { // 스위치 문 커맨드에 맞는 기능 실행
		case 'z': case 'Z':  // 행렬 A, B의 성분값은 0 ∼ 19 사이의 값을 갖는 랜덤값으로 채운다.
		    printf("Matrix Initialized\n"); 
			fill_data(matrix_a, row, col); // 행렬 A에 0 ∼ 19 사이의 값을 갖는 랜덤값으로 채운다.
			fill_data(matrix_b, row, col); //행렬 B에 0 ∼ 19 사이의 값을 갖는 랜덤값으로 채운다.
			break;
        case 'p': case 'P': // A와 B 행렬을 출력한다.
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); //행렬 a 출력
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); //행렬 b 출력
			break;
        case 'a': case 'A': //A + B을 한다.
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); //a행렬 d행렬 열 행을 받아 A + B을 한다.
			break;
        case 's': case 'S': //A − B를 한다.
			printf("Subtract two matrices \n"); //A − B를 한다.
            subtraction_matrix(matrix_a, matrix_b, row, col); //a행렬 d행렬 열 행을 받아 A − B를 한다.
			break;
        case 't': case 'T': // 전치행렬을 구하고 출력한다.
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // a의 전치행렬 T를 구한다.
            print_matrix(matrix_a_t, col, row); // a의 전치행렬 T를 출력한다.
			break;
        case 'm': case 'M': //A × T를 한다.
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //a의 전치행렬 T를 구한다.
            multiply_matrix(matrix_a, matrix_a_t, row, col); //A × T를 한다.
			break;
        case 'q': case 'Q': //동적 메모리로 할당되었던 모든 배열 해제한다.
            printf("Free all matrices..\n"); 
            free_matrix(matrix_a_t, col, row); //동적 메모리로 할당되었던 배열 t를 해제한다.
            free_matrix(matrix_a, row, col); //동적 메모리로 할당되었던 배열 a를 해제한다.
            free_matrix(matrix_b, row, col); //동적 메모리로 할당되었던 배열 b를 해제한다.
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //종료(case 'q': case 'Q':)가 아니면 반복

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) //동적 메모리할당하여 행렬 만드는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); // 이중포인터 matrix를 선언하고 row만큼 만들어서 주소를 저장한다.
	//두번 접근 해야하기 때문에 이중 포인터를 사용한다.
	for (int r = 0; r < row; r++) { //row만큼 반복하여 행을 만든다.                         0은 row
		matrix[r] = (int*)malloc(sizeof(int) * col); // 열과 행만큼 동적메모리 할당한다. 예 : [0][col 1] , [0][col 2]..
	}

	/* Check post conditions */
	if (matrix == NULL) { //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix; //matrix 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // 행렬을 출력하는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		printf("Check the size of row and col!\n"); 
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col만큼 반복
			printf("%3d ", matrix[matrix_row][matrix_col]); // 행렬을 출력한다.
			printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) { //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //동적 메모리로 할당되었던 배열 해제하는함수
{
	/* Check pre conditions */ 
	if (row <= 0 || col <= 0) { //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row만큼 반복
		free(matrix[matrix_row]); // 동적메모리 해제
	}

	free(matrix); //동적 메모리로 할당되었던 배열 해제
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) // 입력한 행 열에 맞게 임의값 할당
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) //row만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col만큼 반복
			matrix[matrix_row][matrix_col] = rand() % 20; //0 ∼ 19 사이의 값 랜덤 할당
	/* Check post conditions */
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n"); //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //A와 B의 행렬을 더하는 함수
{
    int** matrix_sum = create_matrix(row, col); // 동적 메모리할당하여 행렬 matrix_sum을 만듬 같은 열 행
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //모든 함수는 전처리 및 후처리 검사를 수행하여 비정상적인 입력과 결과값에 대비 한다
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // row만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col만큼 반복
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}       // 행렬 a b의 같은 행 열 에서 값을 더해 matrix_sum 행렬에 저장
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { //후처리 검사
		printf("Memory Allocation Failed.\n"); 
		return -1;
	}

	print_matrix(matrix_sum, row, col); //a행렬과 b행렬을 더한 행렬matrix_sum을 출력한다.
	free_matrix(matrix_sum, row, col); //동적 메모리로 할당되었던 배열 matrix_sum을 해제한다.
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //A와 B의 행렬을 빼는 함수
{
    int** matrix_sub = create_matrix(row, col); //동적 메모리할당하여 행렬을 만든다.
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //전처리 검사
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // row만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col만큼 반복
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}       // 행렬 a b의 같은 행 열에서 값을 빼서 matrix_sum 행렬에 저장
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { //후처리 검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col); // a-b를 한 행렬 matrix_sub을 출력한다.
	free_matrix(matrix_sub, row, col); //동적 메모리로 할당되었던 배열 matrix_sub을 해제한다.

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // 해당 행렬의 전치행렬 T를 구현하는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //전처리 검사
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //col만큼 반복
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; // 행과 열을 바꾸어 전치행렬을 만든다.
	}         
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) { //후처리 검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) //A × 전치행렬 T를 하는 함수
{
    int** matrix_axt = create_matrix(row, row); //동적 메모리할당하여 행렬을 만든다.

	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //전처리 검사
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) { //row만큼 반복
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) { //col만큼 반복
			int temp = 0; //정수형 변수 temp선언 초기화
			for (int matrix_col = 0; matrix_col < col; matrix_col++)  // //row만큼 반복
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; // 곱한후 tem누적한다.
				matrix_axt[matrix_a_row][matrix_t_row] = temp; // temp의 값을 행렬 matrix_axt에 저장한다.
		} //두 회소행렬의 곱셈 결과는 희소 행렬이 아니다.
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { //후처리 검사
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row); // A × T를 한 배열을 출력
	free_matrix(matrix_axt, row, col); //동적 메모리로 할당되었던 배열 matrix_axt을 해제한다.
	return 1;
}