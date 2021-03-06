project(fit)

#+++++++++++++++++++++++++++++++++
# Hydra fit                      |
#+++++++++++++++++++++++++++++++++
  ADD_HYDRA_EXAMPLE(basic_fit)
  ADD_HYDRA_EXAMPLE(extended_logLL_fit)
  ADD_HYDRA_EXAMPLE(binned_extended_logLL_fit)
  ADD_HYDRA_EXAMPLE(fractional_logLL_fit)
  ADD_HYDRA_EXAMPLE(phsp_unweighting_functor_and_fit)
  ADD_HYDRA_EXAMPLE(multidimensional_fit)
  ADD_HYDRA_EXAMPLE(splot)
          
                                      
#+++++++++++++++++++++++++
# CUDA TARGETS           |
#+++++++++++++++++++++++++
#if(BUILD_CUDA_TARGETS)
#
         #+++++++++++++++++++++++++++++++++
#         cuda_add_executable( basic_fit_cuda EXCLUDE_FROM_ALL  basic_fit.cu    
#            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
#            )
#         target_link_libraries(basic_fit_cuda  ${ROOT_LIBRARIES} )
#         add_dependencies(examples basic_fit_cuda)
#         
#          
         #+++++++++++++++++++++++++++++++++
#         cuda_add_executable( extended_logLL_fit_cuda EXCLUDE_FROM_ALL  extended_logLL_fit.cu    
#            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
#            )
#         target_link_libraries(extended_logLL_fit_cuda  ${ROOT_LIBRARIES} )
#         
#         add_dependencies(examples extended_logLL_fit_cuda)
#         
         #+++++++++++++++++++++++++++++++++
#         cuda_add_executable( binned_extended_logLL_fit_cuda EXCLUDE_FROM_ALL  binned_extended_logLL_fit.cu    
#            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
#            )
#         target_link_libraries(binned_extended_logLL_fit_cuda  ${ROOT_LIBRARIES} )
#         
#         add_dependencies(examples binned_extended_logLL_fit_cuda)
#         
#          
         #+++++++++++++++++++++++++++++++++
#         cuda_add_executable( fractional_logLL_fit_cuda EXCLUDE_FROM_ALL  fractional_logLL_fit.cu    
#            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
#            )
#         target_link_libraries(fractional_logLL_fit_cuda  ${ROOT_LIBRARIES} )
#         
#         add_dependencies(examples fractional_logLL_fit_cuda)
#         
#         
#          
         #+++++++++++++++++++++++++++++++++
#         cuda_add_executable( phsp_unweighting_functor_and_fit_cuda EXCLUDE_FROM_ALL  phsp_unweighting_functor_and_fit.cu    
#            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
#            )
#         target_link_libraries(phsp_unweighting_functor_and_fit_cuda  ${ROOT_LIBRARIES} )
#         
#         add_dependencies(examples phsp_unweighting_functor_and_fit_cuda)
#         
#          
         #+++++++++++++++++++++++++++++++++
#         cuda_add_executable( multidimensional_fit_cuda EXCLUDE_FROM_ALL  multidimensional_fit.cu    
#            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
#            )
#         target_link_libraries(multidimensional_fit_cuda  ${ROOT_LIBRARIES})
#         
#         add_dependencies(examples multidimensional_fit_cuda)
#         
         #+++++++++++++++++++++++++++++++++
#         cuda_add_executable( splot_cuda EXCLUDE_FROM_ALL  splot.cu    
#            OPTIONS -Xcompiler -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA  -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -lgomp
#            )
#         target_link_libraries(splot_cuda  ${ROOT_LIBRARIES})
#         
#         add_dependencies(examples splot_cuda)
#         
#         
#                        
#endif(BUILD_CUDA_TARGETS)
#
#+++++++++++++++++++++++++
# TBB TARGETS           |
#+++++++++++++++++++++++++
#if(BUILD_TBB_TARGETS)
#
    #+++++++++++++++++++++++++++++++
#    add_executable( basic_fit_tbb EXCLUDE_FROM_ALL
#     basic_fit.cpp
#    )
#    
#    set_target_properties( basic_fit_tbb PROPERTIES 
#    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
#    
#    target_link_libraries( basic_fit_tbb tbb  ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples basic_fit_tbb)
#    
    #+++++++++++++++++++++++++++++++
#    add_executable( extended_logLL_fit_tbb EXCLUDE_FROM_ALL
#     extended_logLL_fit.cpp
#    )
#    
#    set_target_properties( extended_logLL_fit_tbb PROPERTIES 
#    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
#    
#    target_link_libraries( extended_logLL_fit_tbb tbb  ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples extended_logLL_fit_tbb)
#    
    #+++++++++++++++++++++++++++++++
#    add_executable( binned_extended_logLL_fit_tbb EXCLUDE_FROM_ALL
#     binned_extended_logLL_fit.cpp
#    )
#    
#    set_target_properties( binned_extended_logLL_fit_tbb PROPERTIES 
#    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
#    
#    target_link_libraries( binned_extended_logLL_fit_tbb tbb  ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples binned_extended_logLL_fit_tbb)
#    
    #+++++++++++++++++++++++++++++++
#    add_executable( fractional_logLL_fit_tbb EXCLUDE_FROM_ALL
#     fractional_logLL_fit.cpp
#    )
#    
#    set_target_properties( fractional_logLL_fit_tbb PROPERTIES 
#    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
#    
#    target_link_libraries( fractional_logLL_fit_tbb tbb  ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples fractional_logLL_fit_tbb)
#    
#    
    #+++++++++++++++++++++++++++++++
#    add_executable( phsp_unweighting_functor_and_fit_tbb EXCLUDE_FROM_ALL
#     phsp_unweighting_functor_and_fit.cpp
#    )
#    
#    set_target_properties( phsp_unweighting_functor_and_fit_tbb PROPERTIES 
#    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
#    
#    target_link_libraries( phsp_unweighting_functor_and_fit_tbb tbb  ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples phsp_unweighting_functor_and_fit_tbb)
#    
#    
    #+++++++++++++++++++++++++++++++
#    add_executable( multidimensional_fit_tbb EXCLUDE_FROM_ALL multidimensional_fit.cpp )
#    
#    set_target_properties( multidimensional_fit_tbb PROPERTIES 
#    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
#    
#    target_link_libraries( multidimensional_fit_tbb tbb  ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples multidimensional_fit_tbb)
#    
#     
    #+++++++++++++++++++++++++++++++
#    add_executable( splot_tbb EXCLUDE_FROM_ALL splot.cpp )
#    
#    set_target_properties( splot_tbb PROPERTIES 
#    COMPILE_FLAGS "-DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_TBB")
#    
#    target_link_libraries( splot_tbb tbb  ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples splot_tbb)
#    
#    
#    
#    
#endif(BUILD_TBB_TARGETS)
#
#
#+++++++++++++++++++++++++
# OMP TARGETS            |
#+++++++++++++++++++++++++
#IF(BUILD_OMP_TARGETS)
#
    #+++++++++++++++++++++++++++++++
#    add_executable(basic_fit_omp EXCLUDE_FROM_ALL
#   basic_fit.cpp
#    )
#    
#    set_target_properties( basic_fit_omp PROPERTIES 
#    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
#    
#    target_link_libraries( basic_fit_omp   ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples  basic_fit_omp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(extended_logLL_fit_omp EXCLUDE_FROM_ALL extended_logLL_fit.cpp )
#    
#    set_target_properties( extended_logLL_fit_omp PROPERTIES 
#    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
#    
#    target_link_libraries( extended_logLL_fit_omp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  extended_logLL_fit_omp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(binned_extended_logLL_fit_omp EXCLUDE_FROM_ALL binned_extended_logLL_fit.cpp )
#    
#    set_target_properties( binned_extended_logLL_fit_omp PROPERTIES 
#    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
#    
#    target_link_libraries( binned_extended_logLL_fit_omp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  binned_extended_logLL_fit_omp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(fractional_logLL_fit_omp EXCLUDE_FROM_ALL fractional_logLL_fit.cpp )
#    
#    set_target_properties( fractional_logLL_fit_omp PROPERTIES 
#    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
#    
#    target_link_libraries( fractional_logLL_fit_omp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  fractional_logLL_fit_omp)
#     
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(phsp_unweighting_functor_and_fit_omp EXCLUDE_FROM_ALL phsp_unweighting_functor_and_fit.cpp )
#    
#    set_target_properties( phsp_unweighting_functor_and_fit_omp PROPERTIES 
#    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
#    
#    target_link_libraries( phsp_unweighting_functor_and_fit_omp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  phsp_unweighting_functor_and_fit_omp)
#     
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(multidimensional_fit_omp EXCLUDE_FROM_ALL multidimensional_fit.cpp )
#    
#    set_target_properties( multidimensional_fit_omp PROPERTIES 
#    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
#    
#    target_link_libraries( multidimensional_fit_omp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  multidimensional_fit_omp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(splot_omp EXCLUDE_FROM_ALL splot.cpp )
#    
#    set_target_properties( splot_omp PROPERTIES 
#    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
#    
#    target_link_libraries( splot_omp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  splot_omp)
#    
#    
#    
#endif(BUILD_OMP_TARGETS)
#
#
#+++++++++++++++++++++++++
# CPP TARGETS            |
#+++++++++++++++++++++++++
#IF(BUILD_CPP_TARGETS)
#
    #+++++++++++++++++++++++++++++++
#    add_executable(basic_fit_cpp EXCLUDE_FROM_ALL
#   basic_fit.cpp
#    )
#    
#    set_target_properties( basic_fit_cpp PROPERTIES 
#    COMPILE_FLAGS " -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CPP ")
#    
#    target_link_libraries( basic_fit_cpp   ${ROOT_LIBRARIES})
#    
#    add_dependencies(examples  basic_fit_cpp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(extended_logLL_fit_cpp EXCLUDE_FROM_ALL extended_logLL_fit.cpp )
#    
#    set_target_properties( extended_logLL_fit_cpp PROPERTIES 
#    COMPILE_FLAGS " -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CPP ")
#    
#    target_link_libraries( extended_logLL_fit_cpp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  extended_logLL_fit_cpp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(binned_extended_logLL_fit_cpp EXCLUDE_FROM_ALL binned_extended_logLL_fit.cpp )
#    
#    set_target_properties( binned_extended_logLL_fit_cpp PROPERTIES 
#    COMPILE_FLAGS " -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CPP ")
#    
#    target_link_libraries( binned_extended_logLL_fit_cpp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  binned_extended_logLL_fit_cpp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(fractional_logLL_fit_cpp EXCLUDE_FROM_ALL fractional_logLL_fit.cpp )
#    
#    set_target_properties( fractional_logLL_fit_cpp PROPERTIES 
#    COMPILE_FLAGS " -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CPP ")
#    
#    target_link_libraries( fractional_logLL_fit_cpp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  fractional_logLL_fit_cpp)
#     
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(phsp_unweighting_functor_and_fit_cpp EXCLUDE_FROM_ALL phsp_unweighting_functor_and_fit.cpp )
#    
#    set_target_properties( phsp_unweighting_functor_and_fit_cpp PROPERTIES 
#    COMPILE_FLAGS " -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CPP ")
#    
#    target_link_libraries( phsp_unweighting_functor_and_fit_cpp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  phsp_unweighting_functor_and_fit_cpp)
#     
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(multidimensional_fit_cpp EXCLUDE_FROM_ALL multidimensional_fit.cpp )
#    
#    set_target_properties( multidimensional_fit_cpp PROPERTIES 
#    COMPILE_FLAGS " -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CPP ")
#    
#    target_link_libraries( multidimensional_fit_cpp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  multidimensional_fit_cpp)
#    
    #+++++++++++++++++++++++++++++++
#    
#    add_executable(splot_cpp EXCLUDE_FROM_ALL splot.cpp )
#    
#    set_target_properties( splot_cpp PROPERTIES 
#    COMPILE_FLAGS " -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CPP ")
#    
#    target_link_libraries( splot_cpp   ${ROOT_LIBRARIES})
#  
#    add_dependencies(examples  splot_cpp)
#    
#    
#    
#endif(BUILD_CPP_TARGETS)

