import numpy as np
cimport numpy as cnp
from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "include/Library.hpp":
    vector[double] data_potential(string solver_name, 
                                   vector[double] boundary_conditions, 
                                   vector[double] source, 
                                   int nod_number, 
                                   int iteration, 
                                   double precision)

cdef vector[double] python_list_to_vector(cnp.ndarray[cnp.double_t, ndim=1] np_array):
    cdef vector[double] cpp_vector
    for i in range(np_array.shape[0]):
        cpp_vector.push_back(np_array[i])
    return cpp_vector

def vector_to_python_list(vector[double] cpp_vector):
    return [cpp_vector[i] for i in range(cpp_vector.size())]

def potential_result(solver_name: str, boundary_conditions, 
                     source, nod_number: int, 
                     iteration: int, precision: float):
    all_solvers = ['Solver_Jacobi']
    
    if solver_name not in all_solvers:
        print(f"Не существует метода решения {solver_name}. Проверьте правильность написания!")
        print(f"Допустимые решатели: {all_solvers}")
        return 0    


    if isinstance(boundary_conditions, list):
        boundary_conditions = np.array(boundary_conditions, dtype=np.float64)
    if isinstance(source, list):
        source = np.array(source, dtype=np.float64)

    cdef string cpp_solver_name = solver_name.encode('utf-8')
    cdef vector[double] cpp_boundary_conditions = python_list_to_vector(boundary_conditions)
    cdef vector[double] cpp_source = python_list_to_vector(source)


    cdef vector[double] result_vector = data_potential(cpp_solver_name, 
                                                       cpp_boundary_conditions, 
                                                       cpp_source, 
                                                       nod_number, 
                                                       iteration, 
                                                       precision)

    return vector_to_python_list(result_vector)
