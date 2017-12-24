/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>
#include "model.h"

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = nullptr);
    Model model;
    double stepSize = 0.01;

signals:
    void stateReady(const Model::State &state);

public slots:
    void run();

};

#endif // SOLVER_H
