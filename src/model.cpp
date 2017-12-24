/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

#include "model.h"


Model::State operator +(const Model::State &left, const Model::State &right)
{
    Model::State result;
    for (std::size_t i = 0; i < left.size(); ++i)
        result[i] = left[i] + right[i];
    return result;
}

Model::State operator *(const Model::State &left, double right)
{
    Model::State result = left;
    for (auto &x : result)
        x *= right;
    return result;
}

Model::State operator /(const Model::State &left, double right)
{
    Model::State result = left;
    for (auto &x : result)
        x /= right;
    return result;
}
