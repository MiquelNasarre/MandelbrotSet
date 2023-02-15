#include "Header.h"

// RECURSIVE PLOT FUNCTIONS

bool Iterate(double a, double b) {
	double a0 = a, b0 = b;
	double* at = (double*)calloc(sizeof(double), OrbitFinder + 1);
	double* bt = (double*)calloc(sizeof(double), OrbitFinder + 1);
	for (int i = 0; i < Iterations; i++) {

			//for (int j = 0; j < OrbitFinder; j++) {
			//	if (fabs(a - at[j]) < Epsilon && fabs(b - bt[j]) < Epsilon)return true;
			//}
			//memcpy(&at[1], &at[0], sizeof(double) * OrbitFinder);
			//memcpy(&bt[1], &bt[0], sizeof(double) * OrbitFinder);
		
		at[0] = a;
		bt[0] = b;
		a = at[0] * at[0] - bt[0] * bt[0] + a0;
		b = 2 * bt[0] * at[0] + b0;
		if (fabs(a) > 10 || fabs(b) > 10)return false;
		
	}
	return true;
}

void fullFILL(FILE* file, double x0, double y0, double x1, double y1, int xpoints, int ypoints) {
	double Xstep = (x1 - x0) / (double)xpoints;
	double Ystep = (y1 - y0) / (double)ypoints;
	for (int i = 0; i < xpoints; i++) {
		for (int j = 0; j < ypoints; j++) {
				fprintf(file, PlotPrecition, x0 + i * Xstep, y0 + j * Ystep);
		}
	}
}

void PixelFILL(FILE* file, double x0, double y0, double x1,double y1, int xpoints, int ypoints) {
	double Xstep = (x1 - x0) / (double)xpoints;
	double Ystep = (y1 - y0) / (double)ypoints;
	for (int i = 0; i < xpoints; i++) {
		for (int j = 0; j < ypoints; j++) {
			if (Iterate(x0 + i * Xstep, y0 + j * Ystep)) {
				fprintf(file, PlotPrecition, x0 + i * Xstep, y0 + j * Ystep);
			}
		}
	}
}

void createMandelbrotFileRecursive(int depth) {
	char FileName[100] = DataFilesDirectory;
	printf("NAME:  ");
	scanf("%s", FileName + DirectoryStringLenght);

	FILE* file = fopen(FileName, "w");
	if (!file) return;

	double ti = clock();

	RecursiveGridFiller(file, X0, Y0, X1, Y1, Xpoints, Ypoints, GridLenght, depth);
	
	fclose(file);
	printf("Computation time %.3fs", (clock() - ti) / CLOCKS_PER_SEC);
}

void RecursiveGridFiller(FILE* file, double x0, double y0, double x1, double y1, int xpoints, int ypoints, int gridLenght, int depth) {
	double GXstep = gridLenght * (x1 - x0) / (double)xpoints;
	double GYstep = gridLenght * (y1 - y0) / (double)ypoints;

	bool** Grid = (bool**)calloc(xpoints / gridLenght + 1, sizeof(void*));
	bool** MiddleGrid = (bool**)calloc(xpoints / gridLenght, sizeof(void*));

	for (int i = 0; i < xpoints / gridLenght + 1; i++) {
		Grid[i] = (bool*)calloc(ypoints / gridLenght + 1, sizeof(bool));
		for (int j = 0; j < ypoints / gridLenght + 1; j++) Grid[i][j] = Iterate(x0 + i * GXstep, y0 + j * GYstep);
	}

	for (int i = 0; i < ypoints / gridLenght; i++) {
		MiddleGrid[i] = (bool*)calloc(ypoints / gridLenght, sizeof(bool));
		for (int j = 0; j < ypoints / gridLenght; j++) MiddleGrid[i][j] = Iterate(x0 + (i + 0.5) * GXstep, y0 + (j + 0.5) * GYstep);
	}

	for (int i = 0; i < xpoints / gridLenght; i++) {
		for (int j = 0; j < ypoints / gridLenght; j++) {
			if (MiddleGrid[i][j] == Grid[i    ][j    ] &&
				MiddleGrid[i][j] == Grid[i    ][j + 1] &&
				MiddleGrid[i][j] == Grid[i + 1][j    ] &&
				MiddleGrid[i][j] == Grid[i + 1][j + 1] &&

				(!i                            || MiddleGrid[i - 1][j    ] == MiddleGrid[i][j]) &&
				(!j                            || MiddleGrid[i    ][j - 1] == MiddleGrid[i][j]) &&
				(i == xpoints / gridLenght - 1 || MiddleGrid[i + 1][j    ] == MiddleGrid[i][j]) &&
				(j == ypoints / gridLenght - 1 || MiddleGrid[i    ][j + 1] == MiddleGrid[i][j]) &&

				(!i                            || !j                            || MiddleGrid[i - 1][j - 1] == MiddleGrid[i][j]) &&
				(!i                            || j == ypoints / gridLenght - 1 || MiddleGrid[i - 1][j + 1] == MiddleGrid[i][j]) &&
				(i == xpoints / gridLenght - 1 || !j                            || MiddleGrid[i + 1][j - 1] == MiddleGrid[i][j]) &&
				(i == xpoints / gridLenght - 1 || j == ypoints / gridLenght - 1 || MiddleGrid[i + 1][j + 1] == MiddleGrid[i][j])
				
				
				)
			{
				if (Grid[i][j] == true)fullFILL(file, x0 + i * GXstep, y0 + j * GYstep, x0 + (i + 1) * GXstep, y0 + (j + 1) * GYstep, gridLenght, gridLenght);
			}
			else {
				if (!depth) PixelFILL(file, x0 + i * GXstep, y0 + j * GYstep, x0 + (i + 1) * GXstep, y0 + (j + 1) * GYstep, gridLenght * gridLenght, gridLenght * gridLenght);
				else RecursiveGridFiller(file, x0 + i * GXstep, y0 + j * GYstep, x0 + (i + 1) * GXstep, y0 + (j + 1) * GYstep, gridLenght * gridLenght, gridLenght * gridLenght, gridLenght, depth - 1);
			}
		}
	}
	for (int i = 0; i < xpoints / gridLenght + 1; i++) free(Grid[i]);
	free(Grid);
	for (int i = 0; i < ypoints / gridLenght; i++) free(MiddleGrid[i]);
	free(MiddleGrid);
}

// COLOURFUL PLOT FUNCTIONS

int ColorIterate(double a, double b) {
	double a0 = a, b0 = b;
	double* at = (double*)calloc(sizeof(double), OrbitFinder + 1);
	double* bt = (double*)calloc(sizeof(double), OrbitFinder + 1);
	for (int i = 0; i < Iterations; i++) {

		//for (int j = 0; j < OrbitFinder; j++) {
		//	if (fabs(a - at[j]) < Epsilon && fabs(b - bt[j]) < Epsilon)return true;
		//}
		//memcpy(&at[1], &at[0], sizeof(double) * OrbitFinder);
		//memcpy(&bt[1], &bt[0], sizeof(double) * OrbitFinder);

		at[0] = a;
		bt[0] = b;
		a = at[0] * at[0] - bt[0] * bt[0] + a0;
		b = 2 * bt[0] * at[0] + b0;
		if (fabs(a) > 10 || fabs(b) > 10)return i;

	}
	return 0;
}

void ColorPixelFILL(FILE** Files, int* Intervals, double x0, double y0, double x1, double y1, int xpoints, int ypoints) {
	double Xstep = (x1 - x0) / (double)xpoints;
	double Ystep = (y1 - y0) / (double)ypoints;
	for (int i = 0; i < xpoints; i++) {
		for (int j = 0; j < ypoints; j++) {
			int c = ColorIterate(x0 + i * Xstep, y0 + j * Ystep);
			for (int k = 0; k < NumberOfFiles; k++) {
				if (c <= Intervals[k]) {
					fprintf(Files[k], PlotPrecition, x0 + i * Xstep, y0 + j * Ystep);
					break;
				}
			}
		}
	}
}

void createMandelbrotFilesColor() {

	char FolderName[100] = DataFilesDirectory;
	printf("FOLDER NAME:  ");
	scanf("%s", FolderName + DirectoryStringLenght);
	_mkdir(FolderName);

	double ti = clock();

	char** FilesName = (char**)calloc(NumberOfFiles, sizeof(void*));
	for (int i = 0; i < NumberOfFiles; i++) {
		FilesName[i] = (char*)calloc(100, sizeof(char));
		int j = 0;
		while (FolderName[j]) { FilesName[i][j] = FolderName[j]; j++; }
		FilesName[i][j] = '/'; j++;
		if (i < 10) { FilesName[i][j] = 48 + i; j++; }
		else { FilesName[i][j] = 87 + i; j++; }
		FilesName[i][j] = '.'; j++;
		FilesName[i][j] = 'd'; j++;
		FilesName[i][j] = 'a'; j++;
		FilesName[i][j] = 't'; j++;
		
	}

	FILE** Files = (FILE**)calloc(NumberOfFiles, sizeof(void*));

	int Intervals[NumberOfFiles] = IntervalFiles;

	for (int i = 0; i < NumberOfFiles; i++)Files[i] = fopen(FilesName[i], "w");

	double GXstep = GridLenght * (X1 - X0) / (double)Xpoints;
	double GYstep = GridLenght * (Y1 - Y0) / (double)Ypoints;

	int** Grid = (int**)calloc(Xpoints / GridLenght + 1, sizeof(void*));
	int** MiddleGrid = (int**)calloc(Xpoints / GridLenght, sizeof(void*));

	for (int i = 0; i < Xpoints / GridLenght + 1; i++) {
		Grid[i] = (int*)calloc(Ypoints / GridLenght + 1, sizeof(int));
		for (int j = 0; j < Ypoints / GridLenght + 1; j++) Grid[i][j] = ColorIterate(X0 + i * GXstep, Y0 + j * GYstep);
	}

	for (int i = 0; i < Ypoints / GridLenght; i++) {
		MiddleGrid[i] = (int*)calloc(Ypoints / GridLenght, sizeof(int));
		for (int j = 0; j < Ypoints / GridLenght; j++) MiddleGrid[i][j] = ColorIterate(X0 + (i + 0.5) * GXstep, Y0 + (j + 0.5) * GYstep);
	}

	for (int i = 0; i < Xpoints / GridLenght; i++) {
		for (int j = 0; j < Ypoints / GridLenght; j++) {
			if (MiddleGrid[i][j] == Grid[i][j] &&
				MiddleGrid[i][j] == Grid[i][j + 1] &&
				MiddleGrid[i][j] == Grid[i + 1][j] &&
				MiddleGrid[i][j] == Grid[i + 1][j + 1] &&

				(!i || MiddleGrid[i - 1][j] == MiddleGrid[i][j]) &&
				(!j || MiddleGrid[i][j - 1] == MiddleGrid[i][j]) &&
				(i == Xpoints / GridLenght - 1 || MiddleGrid[i + 1][j] == MiddleGrid[i][j]) &&
				(j == Ypoints / GridLenght - 1 || MiddleGrid[i][j + 1] == MiddleGrid[i][j]) &&

				(!i || !j || MiddleGrid[i - 1][j - 1] == MiddleGrid[i][j]) &&
				(!i || j == Ypoints / GridLenght - 1 || MiddleGrid[i - 1][j + 1] == MiddleGrid[i][j]) &&
				(i == Xpoints / GridLenght - 1 || !j || MiddleGrid[i + 1][j - 1] == MiddleGrid[i][j]) &&
				(i == Xpoints / GridLenght - 1 || j == Ypoints / GridLenght - 1 || MiddleGrid[i + 1][j + 1] == MiddleGrid[i][j])
				) 
			{
				for (int k = 0; k < NumberOfFiles; k++) {
					if (Grid[i][j] <= Intervals[k]) {
						fullFILL(Files[k], X0 + i * GXstep, Y0 + j * GYstep, X0 + (i + 1) * GXstep, Y0 + (j + 1) * GYstep, GridLenght, GridLenght);
						break;
					}
				}
			}
			else ColorPixelFILL(Files, Intervals, X0 + i * GXstep, Y0 + j * GYstep, X0 + (i + 1) * GXstep, Y0 + (j + 1) * GYstep, GridLenght, GridLenght);
		}
	}

	for (int i = 0; i < NumberOfFiles; i++)fclose(Files[i]);

	printf("Computation time %.3fs", (clock() - ti) / CLOCKS_PER_SEC);
}