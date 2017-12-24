/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "model.h"

class Solver;

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(double shift MEMBER shift NOTIFY shiftChanged)
    Q_PROPERTY(double rotation MEMBER rotation NOTIFY rotationChanged)
    Q_PROPERTY(double startingPhi READ startingPhi WRITE setStartingPhi NOTIFY startingPhiChanged)
    Q_PROPERTY(double startingX READ startingX WRITE setStartingX NOTIFY startingXChanged)
    Q_PROPERTY(double startingDotPhi READ startingDotPhi WRITE setStartingDotPhi NOTIFY startingDotPhiChanged)
    Q_PROPERTY(double startingDotX READ startingDotX WRITE setStartingDotX NOTIFY startingDotXChanged)

public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    void setSolver(Solver *solver);

    double shift;
    double rotation;
    bool isRunning() { return mSyncTimer->isActive(); }

    inline double startingPhi() { return mStartingState[0]; }
    inline void setStartingPhi(double phi) { mStartingState[0] = phi; emit startingPhiChanged(); }
    inline double startingX() { return mStartingState[1]; }
    inline void setStartingX(double x) { mStartingState[1] = x; emit startingXChanged(); }
    inline double startingDotPhi() { return mStartingState[2]; }
    inline void setStartingDotPhi(double dotPhi) { mStartingState[2] = dotPhi; emit startingDotPhiChanged(); }
    inline double startingDotX() { return mStartingState[3]; }
    inline void setStartingDotX(double dotX) { mStartingState[3] = dotX; emit startingDotXChanged(); }

signals:
    void isRunningChanged();
    void shiftChanged();
    void rotationChanged();
    void startingPhiChanged();
    void startingXChanged();
    void startingDotPhiChanged();
    void startingDotXChanged();

public slots:
    void updateState(const Model::State &state);
    void start();
    void pause();
    void reset();

private:
    Solver *mSolver = nullptr;
    QThread *mThread = nullptr;
    QTimer *mSyncTimer = nullptr;
    Model::State mStartingState;
};

#endif // CONTROLLER_H
