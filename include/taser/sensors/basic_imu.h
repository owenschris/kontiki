//
// Created by hannes on 2018-01-31.
//

#ifndef TASERV2_BASIC_IMU_H
#define TASERV2_BASIC_IMU_H

#include "imu.h"

namespace taser {
namespace sensors {
namespace internal {

struct BasicImuMeta : public entity::MetaData {
  size_t NumParameters() const override {
    return 0;
  }
};

template<typename T, typename MetaType>
class BasicImuView : public ImuView<T, MetaType, BasicImuView<T, MetaType>> {
  using Vector3 = Eigen::Matrix<T, 3, 1>;
  using Base = ImuView<T, MetaType, BasicImuView<T, MetaType>>;
 public:
  using Base::ImuView;

  template<typename TrajectoryModel>
  Vector3 Accelerometer(const type::Trajectory<TrajectoryModel, T> &trajectory, T t) const {
    return Base::template StandardAccelerometer<TrajectoryModel>(trajectory, t);
  }

  template<typename TrajectoryModel>
  Vector3 Gyroscope(const type::Trajectory<TrajectoryModel, T> &trajectory, T t) const {
    return Base::template StandardGyroscope<TrajectoryModel>(trajectory, t);
  }
};

template<template<typename...> typename ViewTemplate, typename MetaType, typename StoreType>
class BasicImuEntity : public ImuEntity<ViewTemplate, MetaType, StoreType> {
 public:
  using ImuEntity<ViewTemplate, MetaType, StoreType>::ImuEntity;

  void AddToProblem(ceres::Problem &problem,
                    time_init_t times,
                    MetaType &meta,
                    std::vector<entity::ParameterInfo<double>> &parameters) const override {
    // No parameters to add
  }
};


} // namespace internal

class BasicImu : public internal::BasicImuEntity<internal::BasicImuView,
                                                 internal::BasicImuMeta,
                                                 entity::EmptyParameterStore<double>> {
 public:
  static constexpr const char* CLASS_ID = "BasicImu";
};

} // namespace sensors
} // namespace taser


#endif //TASERV2_BASIC_IMU_H
