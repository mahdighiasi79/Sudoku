#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int n, m;
char *colors;

typedef struct rv {

    int row;
    int column;
    int RV;
    int degree;
    bool number;

} RV;

typedef struct cell {

    bool *possibleColors;
    bool *possibleNumbers;
    int assignedNumber;
    int assignedColor;

} Cell;

void Consistent(Cell **map, int cr, int cc, int row, int column, RV **numberRVs, RV **colorRVs) {

    if ((row >= n) || (row < 0) || (column >= n) || (column < 0))
        return;

    Cell center = map[cr][cc];

    if ((center.assignedNumber != -1) && (center.assignedColor == -1)) {

        if (center.assignedNumber == 0) {

            if (map[row][column].possibleColors[m - 1]) {
                map[row][column].possibleColors[m - 1] = false;
                colorRVs[row][column].RV--;
            }

            if (center.possibleColors[0]) {
                map[cr][cc].possibleColors[0] = false;
                colorRVs[cr][cc].RV--;
            }
        } else if (center.assignedNumber == (n - 1)) {

            if (map[row][column].possibleColors[0]) {
                map[row][column].possibleColors[0] = false;
                colorRVs[row][column].RV--;
            }

            if (center.possibleColors[m - 1]) {
                map[cr][cc].possibleColors[m - 1] = false;
                colorRVs[cr][cc].RV--;
            }
        }
    } else if ((center.assignedNumber == -1) && (center.assignedColor != -1)) {

        if (center.assignedColor == 0) {

            if (map[row][column].possibleNumbers[n - 1]) {
                map[row][column].possibleNumbers[n - 1] = false;
                numberRVs[row][column].RV--;
            }

            if (map[cr][cc].possibleNumbers[0]) {
                map[cr][cc].possibleNumbers[0] = false;
                numberRVs[cr][cc].RV--;
            }
        } else if (center.assignedColor == m - 1) {

            if (map[row][column].possibleNumbers[0]) {
                map[row][column].possibleNumbers[0] = false;
                numberRVs[row][column].RV--;
            }

            if (map[cr][cc].possibleNumbers[n - 1]) {
                map[cr][cc].possibleNumbers[n - 1] = false;
                numberRVs[cr][cc].RV--;
            }
        }
    } else if ((center.assignedNumber != -1) && (center.assignedColor != -1)) {

        if ((map[row][column].assignedNumber == -1) && (map[row][column].assignedColor == -1)) {

            if (center.assignedNumber == 0) {

                if (map[row][column].possibleColors[m - 1]) {
                    map[row][column].possibleColors[m - 1] = false;
                    colorRVs[row][column].RV--;
                }
            } else if (center.assignedNumber == (n - 1)) {

                if (map[row][column].possibleColors[0]) {
                    map[row][column].possibleColors[0] = false;
                    colorRVs[row][column].RV--;
                }
            }

            if (center.assignedColor == 0) {

                if (map[row][column].possibleNumbers[n - 1]) {
                    map[row][column].possibleNumbers[n - 1] = false;
                    numberRVs[row][column].RV--;
                }
            } else if (center.assignedColor == m - 1) {

                if (map[row][column].possibleNumbers[0]) {
                    map[row][column].possibleNumbers[0] = false;
                    numberRVs[row][column].RV--;
                }
            }
        } else if ((map[row][column].assignedNumber != -1) && (map[row][column].assignedColor == -1)) {

            if (map[row][column].assignedNumber > center.assignedNumber) {

                for (int i = m - 1; i > center.assignedColor; i--) {

                    if (map[row][column].possibleColors[i]) {
                        map[row][column].possibleColors[i] = false;
                        colorRVs[row][column].RV--;
                    }
                }
            } else {

                for (int i = 0; i < center.assignedColor; i++) {

                    if (map[row][column].possibleColors[i]) {
                        map[row][column].possibleColors[i] = false;
                        colorRVs[row][column].RV--;
                    }
                }
            }
        } else if ((map[row][column].assignedNumber == -1) && (map[row][column].assignedColor != -1)) {

            if (map[row][column].assignedColor > center.assignedColor) {

                for (int i = m - 1; i > center.assignedNumber; i--) {

                    if (map[row][column].possibleNumbers[i]) {
                        map[row][column].possibleNumbers[i] = false;
                        numberRVs[row][column].RV--;
                    }
                }
            } else {

                for (int i = 0; i < center.assignedNumber; i++) {

                    if (map[row][column].possibleNumbers[i]) {
                        map[row][column].possibleNumbers[i] = false;
                        numberRVs[row][column].RV--;
                    }
                }
            }
        }
    }
}

void Forward_Checking(Cell **map, int row, int column, RV **numberRVs, RV **colorRVs) {

    int number = map[row][column].assignedNumber;
    int color = map[row][column].assignedColor;

    if (number != -1) {

        for (int i = 0; i < n; i++) {

            if (map[i][column].possibleNumbers[number]) {
                map[i][column].possibleNumbers[number] = false;
                numberRVs[i][column].RV--;
            }
        }

        for (int j = 0; j < n; j++) {

            if (map[row][j].possibleNumbers[number]) {
                map[row][j].possibleNumbers[number] = false;
                numberRVs[row][j].RV--;
            }
        }
    }

    if (color != -1) {

        if (column < (n - 1)) {
            if (map[row][column + 1].possibleColors[color]) {
                map[row][column + 1].possibleColors[color] = false;
                colorRVs[row][column + 1].RV--;
            }
        }

        if (column > 0) {
            if (map[row][column - 1].possibleColors[color]) {
                map[row][column - 1].possibleColors[color] = false;
                colorRVs[row][column - 1].RV--;
            }
        }

        if (row > 0) {
            if (map[row - 1][column].possibleColors[color]) {
                map[row - 1][column].possibleColors[color] = false;
                colorRVs[row - 1][column].RV--;
            }
        }

        if (row < (n - 1)) {
            if (map[row + 1][column].possibleColors[color]) {
                map[row + 1][column].possibleColors[color] = false;
                colorRVs[row + 1][column].RV--;
            }
        }
    }

    Consistent(map, row, column, row, column - 1, numberRVs, colorRVs);
    Consistent(map, row, column, row, column + 1, numberRVs, colorRVs);
    Consistent(map, row, column, row - 1, column, numberRVs, colorRVs);
    Consistent(map, row, column, row + 1, column, colorRVs, colorRVs);
}

int Partition(RV *rv, int p, int r) {

    RV x = rv[r];
    int i = p - 1;

    RV temp;

    for (int j = p; j < r; j++) {

        if (rv[j].RV <= x.RV) {

            i++;

            temp = rv[i];
            rv[i] = rv[j];
            rv[j] = temp;
        }
    }
    temp = rv[i + 1];
    rv[i + 1] = rv[r];
    rv[r] = temp;
    return (i + 1);
}

void QuickSort(RV *rv, int p, int r) {
    if (p < r) {
        int q = Partition(rv, p, r);
        QuickSort(rv, p, q - 1);
        QuickSort(rv, q + 1, r);
    }
}

RV *MRV(RV **numberRVs, RV **colorRVs) {

    RV *rv = (RV *) malloc((2 * n * n) * sizeof(RV));

    int counter = 0;
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            rv[counter] = numberRVs[i][j];
            counter++;
            rv[counter] = colorRVs[i][j];
            counter++;
        }
    }

    QuickSort(rv, 0, (n * n) - 1);
    return rv;
}

int Partition2(RV *rv, int p, int r) {

    RV x = rv[r];
    int i = p - 1;

    RV temp;

    for (int j = p; j < r; j++) {

        if (rv[j].degree >= x.degree) {

            i++;

            temp = rv[i];
            rv[i] = rv[j];
            rv[j] = temp;
        }
    }
    temp = rv[i + 1];
    rv[i + 1] = rv[r];
    rv[r] = temp;
    return (i + 1);
}

void QuickSort2(RV *rv, int p, int r) {
    if (p < r) {
        int q = Partition2(rv, p, r);
        QuickSort2(rv, p, q - 1);
        QuickSort2(rv, q + 1, r);
    }
}

void Degree(RV *rv) {

    int start = 0, end = -1;

    for (int i = 0; i < (n * n); i++) {

        if (rv[i].RV == rv[start].RV)
            end++;
        else {
            QuickSort2(rv, start, end);
            end++;
            start = end;
        }
    }
}

void CopyMap(Cell **destination, Cell **departure) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            destination[i][j].possibleColors = (bool *) malloc(m * sizeof(bool));
            destination[i][j].possibleNumbers = (bool *) malloc(n * sizeof(bool));
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++)
                destination[i][j].possibleNumbers[k] = departure[i][j].possibleNumbers[k];
            for (int k = 0; k < m; k++)
                destination[i][j].possibleColors[k] = departure[i][j].possibleColors[k];
            destination[i][j].assignedColor = departure[i][j].assignedColor;
            destination[i][j].assignedNumber = departure[i][j].assignedNumber;
        }
    }
}

void CopyRV(RV **destination, RV **departure) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            destination[i][j] = departure[i][j];
        }
    }
}

bool Backtrack(Cell **map, RV **numberRVs, RV **colorRVs) {

    Cell **myMap = (Cell **) malloc(n * sizeof(Cell *));
    for (int i = 0; i < n; i++)
        myMap[i] = (Cell *) malloc(n * sizeof(Cell));

    RV **myNumberRVs = (RV **) malloc(n * sizeof(Cell *));
    for (int i = 0; i < n; i++)
        myNumberRVs[i] = (RV *) malloc(n * sizeof(Cell));

    RV **myColorRVs = (RV **) malloc(n * sizeof(Cell *));
    for (int i = 0; i < n; i++)
        myColorRVs[i] = (RV *) malloc(n * sizeof(Cell));


    // calling related heuristics
    RV *rv = MRV(numberRVs, colorRVs);
    Degree(rv);


//  iterating the map according to heuristics
//  for (each of cells){}
    for (int i = 0; i < 2 * (n * n); i++) {

        int row = rv[i].row;
        int column = rv[i].column;
        Cell cell = map[row][column];

        if (rv[i].number) {

            // for each of possible values
            if (cell.assignedNumber == -1) {

                for (int j = 0; j < n; j++) {

                    if (cell.possibleNumbers[j]) {

                        // call the input by its value
                        CopyMap(myMap, map);

                        // assign the value
                        myMap[row][column].assignedNumber = j;

                        // call the RVs by their values
                        CopyRV(myNumberRVs, numberRVs);
                        CopyRV(myColorRVs, colorRVs);

                        // maintain arc consistency
                        Forward_Checking(myMap, row, column, myNumberRVs, myColorRVs);

                        // recurse the function
                        if (Backtrack(myMap, myNumberRVs, myColorRVs))
                            return true;
                    }
                }
            }
        } else {

            if (cell.assignedColor == -1) {

                for (int j = 0; j < m; j++) {

                    if (cell.possibleColors[j]) {

                        // call the input by its value
                        CopyMap(myMap, map);

                        // assign the value
                        myMap[row][column].assignedColor = j;

                        // call the RVs by their values
                        CopyRV(myNumberRVs, numberRVs);
                        CopyRV(myColorRVs, colorRVs);

                        // maintain arc consistency
                        Forward_Checking(myMap, row, column, myNumberRVs, myColorRVs);

                        // recurse the function
                        if (Backtrack(myMap, myNumberRVs, myColorRVs))
                            return true;
                    }
                }
            }
        }
    }


//     if (!AllAssigned)
//         (//we have failed, so we have to go back//)
//         return false

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((map[i][j].assignedNumber == -1) || (map[i][j].assignedColor == -1))
                return false;
        }
    }



//     if (AllAssigned)
//         (// we have reached a goal state//)
//         print values
//         return true

    printf("\n");
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            printf("%d%c ", (map[i][j].assignedNumber + 1), colors[map[i][j].assignedColor]);
        }
        printf("\n");
    }
    return true;
}

int main() {

    scanf("%d %d", &m, &n);

    char *c = (char *) malloc(sizeof(char));
    gets(c);

    RV **numberRVs = (RV **) malloc(n * sizeof(RV *));
    for (int i = 0; i < n; i++)
        numberRVs[i] = (RV *) malloc(n * sizeof(RV));

    RV **colorRVs = (RV **) malloc(n * sizeof(RV *));
    for (int i = 0; i < n; i++)
        colorRVs[i] = (RV *) malloc(n * sizeof(RV));


    // getting colors
    colors = (char *) malloc(((2 * m) - 1) * sizeof(char));
    gets(colors);

    int counter = 0;
    for (int i = 0; i < (2 * m) - 1; i++) {
        if (colors[i] != ' ') {
            colors[counter] = colors[i];
            counter++;
        }
    }


    // initializing the map
    // memory allocation
    Cell **map = (Cell **) malloc(n * sizeof(Cell *));
    for (int i = 0; i < n; i++)
        map[i] = (Cell *) malloc(n * sizeof(Cell));


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            // for each cell
            map[i][j].possibleColors = (bool *) malloc(m * sizeof(bool));
            for (int k = 0; k < m; k++)
                map[i][j].possibleColors[k] = true;

            // initializing possibleNumbers
            map[i][j].possibleNumbers = (bool *) malloc(n * sizeof(bool));
            for (int k = 0; k < n; k++)
                map[i][j].possibleNumbers[k] = true;

            // initializing assignedNumber and assignedColor
            map[i][j].assignedNumber = -1;
            map[i][j].assignedColor = -1;

            // initializing the RVs
            numberRVs[i][j].row = i;
            numberRVs[i][j].column = j;
            numberRVs[i][j].RV = n;
            numberRVs[i][j].number = true;
            colorRVs[i][j].RV = m;
            colorRVs[i][j].number = false;
            colorRVs[i][j].row = i;
            colorRVs[i][j].column = j;

            // indicating the degree of that cell
            if (((i == 0) && (j == 0)) || ((i == 0) && (j == n - 1)) || ((i == n - 1) && (j == 0)) ||
                ((i == n - 1) && (j == n - 1)))
                numberRVs[i][j].degree = colorRVs[i][j].degree = 2;
            else if ((i == 0) || (j == 0) || (i == n - 1) || (j == n - 1))
                numberRVs[i][j].degree = colorRVs[i][j].degree = 3;
            else
                numberRVs[i][j].degree = colorRVs[i][j].degree = 4;
        }
    }


    // receiving inputs
    char *c1 = (char *) malloc(((3 * n) - 1) * sizeof(char));
    int number, count, color = -1;

    for (int i = 0; i < n; i++) {

        // getting the i'th row
        gets(c1);

        // extracting values from the given string
        for (int j = 0; j < (3 * n) - 1; j++) {

            if (j % 3 == 0) {
                // it's a number
                if (c1[j] != '*') {
                    number = (int) c1[j];
                    number -= 49;
                    count = j / 3;
                    map[i][count].assignedNumber = number;
                    numberRVs[i][count].RV = 0;
                }
            } else if (j % 3 == 1) {
                // it's a color
                if (c1[j] != '#') {
                    count = j / 3;
                    for (int k = 0; k < m; k++) {
                        if (c1[j] == colors[k]) {
                            color = k;
                            break;
                        }
                    }
                    map[i][count].assignedColor = color;
                    colorRVs[i][count].RV = 0;
                }
            }
        }
    }

    // maintain arc consistency
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((map[i][j].assignedColor != -1) || (map[i][j].assignedNumber != -1))
                Forward_Checking(map, i, j, numberRVs, colorRVs);
        }
    }

//    // printing input
//    printf("%d %d\n", m, n);
//    for (int i = 0; i < m; i++)
//        printf("%c ", colors[i]);
//    printf("\n");
//    for (int i = 0; i < n; i++){
//        for (int j = 0; j < n; j++){
//            printf("%d,%d:\n", i, j);
//            printf("PC: ");
//            for (int k = 0; k < m; k++)
//                printf("%d ", map[i][j].possibleColors[k]);
//            printf("\n");
//            printf("PN: ");
//            for (int k = 0; k < n; k++)
//                printf("%d ", map[i][j].possibleNumbers[k]);
//            printf("\n");
//            printf("AN: %d\n", map[i][j].assignedNumber);
//            printf("AC: %d\n", map[i][j].assignedColor);
//            printf("RV: %d\n", map[i][j].RV);
//            printf("d: %d\n", map[i][j].degree);
//        }
//        printf("\n");
//    }


    // run the program
    if (!Backtrack(map, numberRVs, colorRVs))
        printf("There are no answers\n");

    return 0;
}