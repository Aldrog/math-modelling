/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

#include "controller.h"
#include "solver.h"
#include <QThread>
#include <QTimer>
#include <QDebug>

Controller::Controller(QObject *parent) :
    QObject(parent),
    mSyncTimer(new QTimer())
{
    mSyncTimer->setInterval(10);
}

Controller::~Controller()
{
    mSyncTimer->stop();
    mSyncTimer->deleteLater();
    emit pause();
    mThread->quit();
    mThread->wait();
}

void Controller::setSolver(Solver *solver)
{
    mSolver = solver;
    mStartingState = mSolver->model.currentState;
    emit startingPhiChanged();
    emit startingXChanged();
    emit startingDotPhiChanged();
    emit startingDotXChanged();
    updateState(mSolver->model.currentState);

    mThread = new QThread();
    solver->moveToThread(mThread);
    QObject::connect(mThread, &QThread::finished, solver, &Solver::deleteLater);
    QObject::connect(mSyncTimer, &QTimer::timeout, mSolver, &Solver::run);
    QObject::connect(mSolver, &Solver::stateReady, this, &Controller::updateState);
    mThread->start();
}

void Controller::updateState(const Model::State &state)
{
    rotation = state[0];
    emit rotationChanged();
    shift = state[1];
    emit shiftChanged();
}

void Controller::start()
{
    mSyncTimer->start();
    emit isRunningChanged();
}

void Controller::pause()
{
    mSyncTimer->stop();
    emit isRunningChanged();
}

void Controller::reset()
{
    pause();
    mSolver->model.currentState = mStartingState;
    mSolver->model.currentTime = 0;
    updateState(mStartingState);
}
