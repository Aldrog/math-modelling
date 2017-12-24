/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

#include <QtQuick>

#include <sailfishapp.h>
#include "solver.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    auto app = SailfishApp::application(argc, argv);
    auto view = SailfishApp::createView();

    qRegisterMetaType<Model::State>();
    Model model;
    model.currentState = { M_PI_2, 0.5, 0.0, 0.0 };
    model.currentTime = 0;
    model.derivative = [](Model::State state, Model::Time time) {
        Q_UNUSED(time)
        Model::State drv;
        static constexpr double l1 = 1.0, l2 = 1.0, M = 1.0, m = 0.5, g = 9.81;
        const double &phi  = state[0];
        const double &x    = state[1];
        const double &dphi = state[2];
        const double &dx   = state[3];
        // phi'
        drv[0] = dphi;
        // x'
        drv[1] = dx;
        // phi''
        drv[2] = ( -4.*M*dphi*dx*x + 2.*M*l2*dphi*dx -
                   (m + 2.*M) * g*l1*cos(phi) + 2.*M*g*x*sin(phi) - M*g*l2*sin(phi) ) /
                 ( m*l1*l1 + 2.*M*x*x + 2.*M*l1*l1 + M*l2*l2 - 2.*M*l2*x );
        // x''
        drv[3] = (x - l2/2.)*dphi*dphi - g*cos(phi);
        if((x < 0 && drv[1] < 0) || (x > l2 && drv[1] > 0)) {
            drv[1] = 0;
        }
        return drv;
    };
    Solver *solver = new Solver();
    solver->model = model;
    Controller *controller = new Controller();
    controller->setSolver(solver);
    QObject::connect(app, &QGuiApplication::aboutToQuit, controller, &Controller::deleteLater);
    view->rootContext()->setContextProperty("dataSource", controller);

    view->setSource(SailfishApp::pathToMainQml());
    view->show();
    return app->exec();
}
