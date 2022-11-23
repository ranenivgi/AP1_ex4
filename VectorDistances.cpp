#include "VectorDistances.h"

/**
 * @brief calculates the distance between two vectors by the eclidean algorithm:
 * lets notice that the algorithm is the same as minkowski when P = 2 so we will
 *                                    activate the minkowski function with P = 2
 *
 * @param vec1 first vector
 * @param vec2 second vector
 * @param p
 * @return the result
 */
double euclideanDistance(vector<double> vec1, vector<double> vec2)
{
    return minkowskiDistance(vec1, vec2, 2);
}

/**
 * @brief calculates the distance between two vectors by the manhattan algorithm:
 * lets notice that the algorithm is the same as minkowski when P = 1 so we will
 *                                    activate the minkowski function with P = 1
 *
 * @param vec1 first vector
 * @param vec2 second vector
 * @param p
 * @return the result
 */
double manhattanDistance(vector<double> vec1, vector<double> vec2)
{
    return minkowskiDistance(vec1, vec2, 1);
}

/**
 * @brief calculates the distance between two vectors by the chebyshev algorithm:
 * - split the vectors into pairs, meaning the first number from the first vector and the first number
 *                                                        from the second vector is a pair, and so on.
 * - decreasing the value of the first number from a pair by the value of the second number (in abs).
 * - search the pair with the biggest result of the above calculation, and return it.
 *
 * @param vec1 first vector
 * @param vec2 second vector
 * @param p
 * @return the result
 */
double chebyshevDistance(vector<double> vec1, vector<double> vec2)
{
    // initiallize sum with the first pair
    double sum = abs(vec1[0] - vec2[0]);

    // checking if there is bigger pair
    for (int i = 1; i < vec1.size(); i++)
    {
        (abs(vec1[i] - vec2[i]) > sum) && (sum = abs(vec1[i] - vec2[i]));
    }
    return sum;
}

/**
 * @brief calculates the distance between two vectors by the canberra algorithm:
 * - split the vectors into pairs, meaning the first number from the first vector and the first number
 *                                                        from the second vector is a pair, and so on.
 * - decreasing the value of the first number from a pair by the value of the second number (in abs), then divide
 *   the result in the sum of the number from the first vector (in abs) and the number from the second vector (in abs).
 * - repeat for every pair (by adding the result of each pair to a variable named sum).
 * - return the result (sum)
 *
 * @param vec1 first vector
 * @param vec2 second vector
 * @param p
 * @return the result
 */
double canberraDistance(vector<double> vec1, vector<double> vec2)
{
    double sum = 0;

    // calculate the sum
    for (int i = 0; i < vec1.size(); i++)
    {
        // dividing in 0 isn't defined so we will return 0
        if ((abs(vec1[i]) + abs(vec2[i])) == 0) {
            return 0;
        }
        sum += abs(vec1[i] - vec2[i]) / (abs(vec1[i]) + abs(vec2[i]));
    }
    return sum;
}

/**
 * @brief calculates the distance between two vectors by the minkowsi algorithm:
 * - split the vectors into pairs, meaning the first number from the first vector and the first number
 *                                                        from the second vector is a pair, and so on.
 * - decreasing the value of the first number from a pair by the value of the second number (in abs).
 * - add pow P(defined as a default value 2 in my program) to the sum and then repeat for every pair
 *                                      (by adding the result of each pair to a variable named sum).
 * - return the root P of the result (sum)
 *
 * @param vec1 first vector
 * @param vec2 second vector
 * @param p
 * @return the result
 */
double minkowskiDistance(vector<double> vec1, vector<double> vec2, const int p = 2)
{
    double sum = 0;
    // calculate the sum
    for (int i = 0; i < vec1.size(); i++)
    {
        sum += pow(abs(vec1[i] - vec2[i]), p);
    }
    // root the result
    return pow(sum, (double)1 / p);
}