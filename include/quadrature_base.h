#ifndef FELIB_QUADRATURE_BASE_H_
#define FELIB_QUADRATURE_BASE_H_

#include <eigen3/Eigen/Dense>

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

namespace felib {
  template <unsigned Tdim, unsigned Tnquadratures>
class QuadratureBase;
}

// Quadrature base class
//! \brief Base class for quadrature
//! \tparam Tdim Dimension
//! \tparam Tnquadratures number of quadratures

template <unsigned Tdim, unsigned Tnquadratures>
class felib::QuadratureBase {
 public:
  //! Constructor
  //! Assign variables to zero
  QuadratureBase() {
    qpoints_.fill(std::numeric_limits<double>::quiet_NaN());
    weights_.resize(Tnquadratures);
    std::fill(weights_.begin(), weights_.end(), std::numeric_limits<double>::quiet_NaN());
  }

  //! Destructor
  virtual ~QuadratureBase() {}
  
  //! Return quadrature points
  //! \param[out] qpoints Quadrature points in local coordinates
  Eigen::Matrix<double, Tnquadratures, Tdim> quadratures() {return qpoints_; }
  
  //! Return weights
  //! \param[out] weights Weights for quadrature points
  std::vector<double> weights() { return weights_; }

 protected:
  Eigen::Matrix<double, Tnquadratures, Tdim> qpoints_;
  std::vector<double> weights_;
};

#endif  // FELIB_QUADRATURE_BASE_H_
