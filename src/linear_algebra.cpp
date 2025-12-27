#include <linear_algebra.hpp>
#include <vector>
#include <assert.h>
#include <cmath>

using namespace std;





vector<float> linearTransform(const vector<vector<float>>& matrix, const vector<float>& vect) {
    assert(("Wrong matrix size for matrix multiplication", matrix[0].size() == vect.size()));

    int n = matrix.size();
    int m = vect.size();

    vector<float> res(m, 0);
    for (int i=0; i<n; ++i)
        for (int k=0; k<m; ++k)
            res[i] += matrix[i][k] * vect[k];
    
    return res;
}

vector<vector<float>> matrixMultiplication(const vector<vector<float>>& M1, const vector<vector<float>>& M2) {
    assert(("Wrong matrix size for matrix multiplication", M1[0].size() == M2.size()));

    int n = M1.size();
    int m = M1[0].size();
    int p = M2[0].size();

    vector<vector<float>> res(n, vector<float>(p, 0));
    for (int i=0; i<n; ++i)
        for (int j=0; j<p; ++j)
            for (int k=0; k<m; ++k)
                res[i][j] += M1[i][k] * M2[k][j];
    
    return res;
}

vector<float> projection(vector<float>& v) {
    return {v[0], v[1]};
}

float dotProduct(const vector<float>& v1, const vector<float>& v2) {
    assert(("Not same vector sizes", v1.size() == v2.size()));
    float res = 0;
    for (int i=0; i<v1.size(); ++i)
        res += v1[i] * v2[i];
    return res;
}

vector<float> normalize(vector<float> v) {
    float norm = sqrt(dotProduct(v, v));
    vector<float> res;
    for (auto val : v)
        res.push_back(val / norm);
    return res;
}