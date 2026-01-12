/**
 * Chapter 3.9: Practical - Pose Composition Chain
 *
 * Topics: Chaining transformations for robot arm, sensor chains
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.9 Pose Composition Chain ===\n\n";

    // Robot with base, arm link 1, arm link 2, end effector
    // T_world_ee = T_world_base * T_base_link1 * T_link1_link2 * T_link2_ee

    Isometry3d T_world_base = Isometry3d::Identity();
    T_world_base.translation() = Vector3d(1, 0, 0);

    Isometry3d T_base_link1 = Isometry3d::Identity();
    T_base_link1.rotate(AngleAxisd(M_PI/4, Vector3d::UnitZ()));
    T_base_link1.translation() = Vector3d(0.5, 0, 0.1);

    Isometry3d T_link1_link2 = Isometry3d::Identity();
    T_link1_link2.rotate(AngleAxisd(-M_PI/6, Vector3d::UnitY()));
    T_link1_link2.translation() = Vector3d(0.3, 0, 0);

    Isometry3d T_link2_ee = Isometry3d::Identity();
    T_link2_ee.translation() = Vector3d(0.2, 0, 0);

    // Chain composition
    Isometry3d T_world_ee = T_world_base * T_base_link1 * T_link1_link2 * T_link2_ee;

    cout << "End effector position in world: "
         << T_world_ee.translation().transpose() << "\n";

    return 0;
}
