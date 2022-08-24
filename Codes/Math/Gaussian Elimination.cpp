double gaussian_elimination(int row, int col) {
    int basis[30];
    for (int j = 0; j < row; j++) {
        MAT[j][j + col] = 1;
    }
    memset(basis, -1, sizeof basis);
    double det = 1;
    for (int i = 0; i < col; i++) {
        for (int p = 0; p < row ; p++) {
            for (int q = 0; q < col; q++)
                cout << MAT[p][q] << ' ';
            cout << '\n';
        }
        int x = -1;
        for (int k = 0; k < row; k++) {
            if (abs(MAT[k][i]) > eps and basis[k] == -1) {
                x = k, det *= MAT[k][i], basis[x] = i;
                break;
            }
        }
        if (x < 0) continue;
        for (int j = 0; j < col; j++)
            if (j != i)  for (int k = 0; k < row; k++) if (k != x)
                        MAT[k][j] -= (MAT[k][i] * MAT[x][j]) / MAT[x][i];
        for (int k = 0; k < col; k++) if (k != i)
                MAT[x][k] /= MAT[x][i];
        for (int j = 0; j < row; j++)
            MAT[j][i] = (j == i);
    }
    for (int i = 0; i < row ; i++) {
        for (int j = 0; j < col; j++)
            cout << MAT[i][j] << ' ';
        cout << '\n';
    }
    for (int k = 0; k < row; k++)
        if (basis[k] == -1)
            return 0;
    return det;
}