/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

#ifndef MODEL_H
#define MODEL_H

#include <array>
#include <functional>
#include <QMetaType>

struct Model
{
    typedef std::array<double, 4> State;
    typedef double Time;

    State currentState;
    Time currentTime;
    std::function<State(State, Time)> derivative;
};

Model::State operator +(const Model::State &left, const Model::State &right);
Model::State operator *(const Model::State &left, double right);
Model::State operator /(const Model::State &left, double right);

Q_DECLARE_METATYPE(Model::State)

#endif // MODEL_H
