/*
 *  Copyright 2008-2013 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file trivial_copy.h
 *  \brief Sequential copy algorithms for plain-old-data.
 */

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>
#include <cstring>
#include <hydra/detail/external/thrust/system/detail/sequential/general_copy.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace system
{
namespace detail
{
namespace sequential
{


template<typename T>
__hydra_host__ __hydra_device__
  T *trivial_copy_n(const T *first,
                    std::ptrdiff_t n,
                    T *result)
{
#ifndef __CUDA_ARCH__
  if(first)
	  std::memmove(result, first, n * sizeof(T));
  return result + n;
#else
  return thrust::system::detail::sequential::general_copy_n(first, n, result);
#endif
} // end trivial_copy_n()


} // end namespace sequential
} // end namespace detail
} // end namespace system
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END
