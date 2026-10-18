// Solves linear equations Ax = b
// mat: Augmented matrix of size n x (n + 1) where the last column is b
// ans: Vector to store the unique solution (if it exists)
// Returns: 0 if no solution, 1 if unique solution, 2 if infinite solutions
int gaussJordan(vector<vector<double>>& mat, vector<double>& ans) {
    int n = mat.size();
    int m = mat[0].size() - 1; // Number of variables

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        // Find pivot for current column
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (abs(mat[i][col]) > abs(mat[sel][col])) {
                sel = i;
            }
        }
        if (abs(mat[sel][col]) < EPS) {
            continue; // No pivot in this column, skip
        }
        
        // Swap rows to bring pivot to the current row
        for (int i = col; i <= m; ++i) {
            swap(mat[sel][i], mat[row][i]);
        }
        where[col] = row;

        // Eliminate all other rows (Gauss-Jordan eliminates both above and below)
        for (int i = 0; i < n; ++i) {
            if (i != row) {
                double c = mat[i][col] / mat[row][col];
                for (int j = col; j <= m; ++j) {
                    mat[i][j] -= mat[row][j] * c;
                }
            }
        }
        ++row;
    }

    // Extract solution values
    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = mat[where[i]][m] / mat[where[i]][i];
        }
    }

    // Check for consistency (no solution case)
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += ans[j] * mat[i][j];
        }
        if (abs(sum - mat[i][m]) > EPS) {
            return 0; // No solution
        }
    }

    // Check for free variables (infinite solutions case)
    for (int i = 0; i < m; ++i) {
        if (where[i] == -1) {
            return 2; // Infinite solutions
        }
    }

    return 1; // Unique solution
}
