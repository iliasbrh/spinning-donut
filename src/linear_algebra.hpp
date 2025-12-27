#ifndef LINEAR_ALGEBRA
#define LINEAR_ALGEBRA

#include <vector>
using namespace std;

vector<float> linearTransform(const vector<vector<float>>& matrix, const vector<float>& vect);
vector<vector<float>> matrixMultiplication(const vector<vector<float>>& M1, const vector<vector<float>>& M2);
vector<float> projection(vector<float>& v);
float dotProduct(const vector<float>& v1, const vector<float>& v2);
vector<float> normalize(vector<float> v);


#endif