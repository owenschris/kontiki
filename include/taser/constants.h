//
// Created by hannes on 2018-01-31.
//

#ifndef TASERV2_CONSTANTS_H
#define TASERV2_CONSTANTS_H

#include <Eigen/Dense>

namespace taser {

namespace _constants {
  static const double STANDARD_GRAVITY = 9.80665;
}

template<typename T>
class Constants {
  using Vector3 = Eigen::Matrix<T, 3, 1>;
 public:
  static const Vector3 Gravity;
};

template<typename T>
const Eigen::Matrix<T, 3, 1> Constants<T>::Gravity = Eigen::Matrix<T, 3, 1>(T(0), T(0), T(-_constants::STANDARD_GRAVITY));

} // namespace taser

#endif //TASERV2_CONSTANTS_H
