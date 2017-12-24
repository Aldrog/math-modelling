/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

#include "solver.h"
#include <QElapsedTimer>
#include <QThread>
#include <QDebug>

Solver::Solver(QObject *parent) : QObject(parent)
{

}

void Solver::run()
{
//    QElapsedTimer timer;
//    timer.start();

    Model::State k1 = model.derivative(model.currentState, model.currentTime);
    Model::State k2 = model.derivative(model.currentState + k1 * stepSize / 2, model.currentTime + stepSize / 2);
    Model::State k3 = model.derivative(model.currentState + k2 * stepSize / 2, model.currentTime + stepSize / 2);
    Model::State k4 = model.derivative(model.currentState + k3 * stepSize    , model.currentTime + stepSize);
    model.currentState = model.currentState + (k1 + k2*2 + k3*2 + k4) * stepSize / 6;
    model.currentTime += stepSize;

    emit stateReady(model.currentState);
//    qint64 processTime = timer.elapsed();
//    qDebug() << "Time to process:" << processTime;
}
