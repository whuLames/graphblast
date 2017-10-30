#ifndef GRB_MATRIX_HPP
#define GRB_MATRIX_HPP

#include <vector>

#include "graphblas/types.hpp"
#include "graphblas/Descriptor.hpp"

// Opaque data members from the right backend
#define __GRB_BACKEND_MATRIX_HEADER <graphblas/backend/__GRB_BACKEND_ROOT/Matrix.hpp>
#include __GRB_BACKEND_MATRIX_HEADER
#undef __GRB_BACKEND_MATRIX_HEADER

namespace graphblas
{
  template <typename T>
  class Matrix
  {
    public:
    // Default Constructor, Standard Constructor (Replaces new in C++)
    //   -it's imperative to call constructor using matrix_ or the constructed 
    //     object won't be tied to this outermost layer
    Matrix() : matrix_() {}
    Matrix( Index nrows, Index ncols ) : matrix_( nrows, ncols ) {}

    // Default Destructor is good enough for this layer
    ~Matrix() {}

    // C API Methods
    Info nnew(  Index nrows, Index ncols );
    Info dup(   const Matrix* rhs );
    Info clear();
    Info nrows( Index* nrows_ );
    Info ncols( Index* ncols_ );
    Info nvals( Index* nvals_ );
    Info build( const std::vector<Index>* row_indices,
                const std::vector<Index>* col_indices,
                const std::vector<T>*     values,
                Index                     nvals,
                const BinaryOp            dup );
    Info build( const std::vector<T>*     values,
                Index                     nvals );
    Info setElement(     Index row_index,
                         Index col_index );
    Info extractElement( T*    val,
                         Index row_index,
                         Index col_index );
    Info extractTuples(  std::vector<Index>* row_indices,
                         std::vector<Index>* col_indices,
                         std::vector<T>*     values,
                         Index*              n );
    Info extractTuples(  std::vector<T>* values, 
                         Index* n );

    // Handy methods
    void operator=(   const Matrix* rhs );
    Info print();
    Info set_storage( Storage  mat_type ); 
    Info get_storage( Storage* mat_type ) const;

    private:
    // Data members that are same for all backends
    backend::Matrix<T> matrix_;

    /*template <typename c, typename m, typename a, typename b>
    friend Info mxm( Matrix<c>&        C,
                     const Matrix<m>&  mask,
                     const BinaryOp&   accum,
                     const Semiring&   op,
                     const Matrix<a>&  A,
                     const Matrix<b>&  B,
                     const Descriptor& desc );

    template <typename c, typename a, typename b>
    friend Info mxm( Matrix<c>&        C,
                     const int         mask,
                     const int         accum,
                     const Semiring&   op,
                     const Matrix<a>&  A,
                     const Matrix<b>&  B,
                     const Descriptor& desc );*/

  };

  template <typename T>
  Info Matrix<T>::nnew( Index nrows, Index ncols )
  {
    matrix_.nnew( nrows, ncols );
  }

  template <typename T>
  Info Matrix<T>::dup( Index* rhs )
  {
    matrix_.dup( rhs->matrix_ );
  }

  template <typename T>
  Info Matrix<T>::clear()
  {
    return matrix_.clear();
  }

  template <typename T>
  Info Matrix<T>::nrows( Index* nrows ) const
  {
    return matrix_.nrows( nrows );
  }

  template <typename T>
  Info Matrix<T>::ncols( Index* ncols ) const
  {
    return matrix_.ncols( ncols );
  }

  template <typename T>
  Info Matrix<T>::nvals( Index* nvals ) const
  {
    return matrix_.nvals( nvals );
  }

  template <typename T>
  Info Matrix<T>::build( const std::vector<Index>* row_indices,
                         const std::vector<Index>* col_indices,
                         const std::vector<T>*     values,
                         Index                     nvals,
                         const BinaryOp            dup )
  {
    return matrix_.build( row_indices, col_indices, values, nvals, dup );
  }

  template <typename T>
  Info Matrix<T>::build( const std::vector<T>* values, Index nvals )
  {
    return matrix_.build( values, nvals );
  }

  template <typename T>
  Info Matrix<T>::setElement( Index row_index,
                              Index col_index )
  {
    return matrix_.setElement( row_index, col_index );
  }

  template <typename T>
  Info Matrix<T>::extractElement( T*    val,
                                  Index row_index,
                                  Index col_index )
  {
    return matrix_.extractElement( val, row_index, col_index );
  }

  template <typename T>
  Info Matrix<T>::extractTuples( std::vector<Index>* row_indices,
                                 std::vector<Index>* col_indices,
                                 std::vector<T>*     values,
                                 Index*              n )
  {
    return matrix_.extractTuples( row_indices, col_indices, values, n );
  }
  
  template <typename T>
  Info Matrix<T>::extractTuples( std::vector<T>* values, 
                                 Index*          n )
  {
    return matrix_.extractTuples( values, n );
  }

  // Handy methods
  template <typename T>
  void Matrix<T>::operator=( const Matrix* rhs )
  {
    matrix_.dup( rhs->matrix_ );
  }

  template <typename T>
  Info Matrix<T>::print()
  {
    return matrix_.print();
  }

  template <typename T>
  Info Matrix<T>::set_storage( Storage mat_type )
  {
    return matrix_.set_storage( mat_type );
  }

  template <typename T>
  Info Matrix<T>::get_storage( Storage* mat_type ) const
  {
    return matrix_.get_storage( mat_type );
  }

}  // graphblas

#endif  // GRB_MATRIX_HPP
