#ifndef FELIB_ELEMENT_BASE_H_
#define FELIB_ELEMENT_BASE_H_

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "node_base.h"
#include "quadrature_base.h"
#include "shapefn_base.h"

namespace felib {
template <unsigned Tdim, unsigned Tnumnodes, unsigned Tnquadratures>
class ElementBase;
}

// Element Base class
//! \brief Element class that stores the information about elements
//! \details ElementBase class: id_ and nodes. test test test
//! \tparam Tdim Dimension
//! \tparam Tnumnodes Number of nodes
//! \tparam Tnquadratures Number of quadrature points
template <unsigned Tdim, unsigned Tnumnodes, unsigned Tnquadratures>
class felib::ElementBase {
 public:

  // Constructor with id, num_nodes, nodes, num_edge_nodes and edge_nodes
  //! \param[in] id assign as the id_ of the element
  //! \param[in] num_nodes number of nodes of the element
  //! \param[in] num_edge_nodes number of edge_ nodes of the element
  ElementBase(const unsigned& id, const unsigned& num_nodes)
      : id_{id}, num_nodes_{num_nodes} {
    // initialise the size of vector of node pointers and set it to null_ptr
    vec_nodes_ptr_.resize(num_nodes_);
    // vec_nodes_ptr_.fill(nullptr);
    // shapefn_ptr_ = nullptr;
    // quadrature_ptr_ = nullptr;
  }

  

  //! Destructor
  virtual ~ElementBase() {}

  //! Return id of the element
  //! \return id_ id of the element
  unsigned id() const { return id_; }

  //! Call a node base function for a particular node
  //! \tparam Func Function type
  //! \param[in] nnode Node number
  //! \param[in] func A node base function
  template <typename Func>
  Func call_function_node(const unsigned& nnode, Func func);

  //! Iterate over nodes
  //! \tparam Func Function type
  //! \param[in] func A node base function
  template <typename Func>
  Func iterate_over_nodes(Func func);

  //! Iterate over neighbour elements
  //! \tparam Func Function type
  //! \param[in] func Element base function
  template <typename Func>
  Func iterate_over_neighbours(Func func);

  //! Assign nodes
  //! \param[in] nodes Assign nodes as nodes of the element

  //! Insert a node pointer at a specific index
  //! \param[in] node_ptr Pointer to a node in the element
  //! \param[in] index Index at which the node pointer will be assigned
  bool insert_node_ptr(std::shared_ptr<NodeBase<Tdim>>& node_ptr_,
                       const unsigned& index);

  //! Info
  void info() {
    std::cout << "Element id: " << id_ << "\nnodes: ";
    for (const auto& node_ptr : vec_nodes_ptr_)
      std::cout << node_ptr->id() << ", ";
    std::cout << std::endl;
  }

  //! Add node pointers to element base class
  //! \brief Virtual function to add node pointers to the element
  //! \param[in] node_ptr Pointer to a node in the element
  virtual bool add_node_ptr(std::shared_ptr<NodeBase<Tdim>>& node_ptr) = 0;

  //! Add node pointer to a given index
  //! \brief Add a node pointer at a given index of the element
  bool insert_node_ptr_at(std::shared_ptr<NodeBase<Tdim>>& node_ptr,
                          const unsigned index);

  //! Add edge_node pointers to element base class
  //! \brief Virtual function to add edge_node pointers to the element
  //! \param[in] edge_node_ptr Pointer to an edge_node in the element
  virtual bool add_edge_node_ptr(std::shared_ptr<NodeBase<Tdim>>& edge_node_ptr) = 0;

  //! Add edge_node pointer to a given index
  //! \brief Add an edge_node pointer at a given index of the element
  bool insert_edge_node_ptr_at(std::shared_ptr<NodeBase<Tdim>>& edge_node_ptr,
                          const unsigned index);

  //! Compute centroid
  std::array<double, Tdim> centroid();
  
  //! \brief Return the volume of the element
  //! \detail Return volume in 3D, area in 2D and length in 1D
  virtual double volume() = 0;

 private:
  //! Copy constructor
  ElementBase(const ElementBase<Tdim, Tnumnodes, Tnquadratures>&);

  //! Assignement operator
  ElementBase& operator=(const ElementBase<Tdim, Tnumnodes, Tnquadratures>&);

 protected:
  //! element id
  unsigned id_;
  //! element nodes number
  unsigned num_nodes_;
  //! element edge_nodes number
  unsigned num_edge_nodes_;  
  //! vector of node pointers
  std::vector<std::shared_ptr<NodeBase<Tdim>>> vec_nodes_ptr_;
  //! vector of neighbour element pointers
  std::vector<std::shared_ptr<ElementBase<Tdim, Tnumnodes, Tnquadratures>>> vec_neighbours_;
  //! element centroid
  std::array<double, Tdim> centroid_;
  //! element centroid_edge_nodes (based on edge nodes only)
  std::array<double, Tdim> centroid_edge_nodes_;
  //! element volume
  double volume_;
  //! shape function base class pointer
  std::unique_ptr<felib::ShapeFnBase<Tdim, Tnumnodes>> shapefn_ptr_;
  //! quadrature points base class pointer
  std::unique_ptr<felib::QuadratureBase<Tdim, Tnquadratures>> quadrature_ptr_;

};

#include "element_base.tcc"
#endif  // FELIB_ELEMENT_BASE_H_
