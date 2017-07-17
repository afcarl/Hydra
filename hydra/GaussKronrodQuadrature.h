/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2016 Antonio Augusto Alves Junior
 *
 *   This file is part of Hydra Data Analysis Framework.
 *
 *   Hydra is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hydra is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hydra.  If not, see <http://www.gnu.org/licenses/>.
 *
 *---------------------------------------------------------------------------*/

/*
 * GaussKronrodQuadrature.h
 *
 *  Created on: 31/01/2017
 *      Author: Antonio Augusto Alves Junior
 */

/**
 * \file
 * \ingroup numerical_integration
 */

#ifndef GAUSSKRONRODQUADRATURE_H_
#define GAUSSKRONRODQUADRATURE_H_

#include <hydra/detail/Config.h>
#include <hydra/detail/BackendPolicy.h>
#include <hydra/Types.h>
#include <hydra/GaussKronrodRules.h>
#include <hydra/detail/functors/ProcessGaussKronrodQuadrature.h>
#include <hydra/multivector.h>
#include <hydra/detail/Integrator.h>

#include <hydra/detail/Print.h>
#include <tuple>

namespace hydra {


template< size_t NRULE, size_t NBIN, typename  BACKEND>
class GaussKronrodQuadrature;

/**
 *  @ingroup numerical_integration
 *
 *  @brief  Gauss-Kronrod Quadrature.
 *  @tparam NRULE Order of the Gauss-Kronrod rule, specified as the number of Kronrod nodes.
 *  @tparam NBIN  Maximum number of multidimensional subdivisions of the integration region.
 *  @tparam BACKEND parallel back end. Can be hydra::omp::sys , hydra::cuda::sys , hydra::tbb::sys , hydra::cpp::sys ,hydra::host::sys and hydra::device::sys
 *
[*Description mostly copied From Wikipedia*](https://en.wikipedia.org/wiki/Gauss%E2%80%93Kronrod_quadrature_formula)

###Introduction###

In numerical mathematics, the Gauss–Kronrod quadrature formula is a method for numerical integration
(calculating approximate values of integrals). Gauss–Kronrod quadrature is a variant of Gaussian quadrature,
in which the evaluation points are chosen so that an accurate approximation can be computed by re-using the
information produced by the computation of a less accurate approximation. It is an example of what is called a
nested quadrature rule: for the same set of function evaluation points, it has two quadrature rules, one higher order
and one lower order (the latter called an embedded rule). The difference between these two approximations is used to estimate
the calculational error of the integration.
These formulas are named after Alexander Kronrod, who invented them in the 1960s, and Carl Friedrich Gauss.

###Description###

The problem in numerical integration is to approximate definite integrals of the form

\f[ I = \int_a^b f(x)\,dx \f]

Such integrals can be approximated, for example, by \f$n\f$-point [Gaussian quadrature](https://en.wikipedia.org/wiki/Gaussian_quadrature)

\f[ \int_a^b f(x)\,dx \approx \sum_{i=1}^n w_i f(x_i), \f]

where \f$w_i\f$, \f$x_i\f$ are the weights and points at which to evaluate the function \f$f(x)\f$.

If the interval \f$[a,b]\f$ is subdivided, the Gauss evaluation points of the new subintervals never coincide with the previous
evaluation points (except at the midpoint for odd numbers of evaluation points), and thus the integrand must be evaluated at every point.
Gauss–Kronrod formulas are extensions of the Gauss quadrature formulas generated by adding \f$n+1\f$ points to an \f$n\f$-point
rule in such a way that the resulting rule is of order \f$2n+1\f$
[[Math. Comp. 66 (1997), 1133-1145] ](http://www.ams.org/journals/mcom/1997-66-219/S0025-5718-97-00861-2/home.html)
the corresponding Gauss rule is of order \f$2n-1\f$. These extra points are the zeros of [Stieltjes polynomials](https://en.wikipedia.org/wiki/Stieltjes_polynomials).
This allows for computing higher-order estimates while reusing the function values of a lower-order estimate.
The difference between a Gauss quadrature rule and its Kronrod extension are often used as an estimate of the approximation error.
 */
template<size_t NRULE, size_t NBIN, hydra::detail::Backend  BACKEND>
class GaussKronrodQuadrature<NRULE,NBIN, hydra::detail::BackendPolicy<BACKEND>>:
public Integrator< GaussKronrodQuadrature<NRULE, NBIN, hydra::detail::BackendPolicy<BACKEND> > >
{
public:
	//tag
		typedef void hydra_integrator_tag;
	    typedef thrust::tuple<double, double, double, double, double> row_t;

		typedef thrust::host_vector<row_t>   row_list_h;
		typedef thrust::device_vector<row_t> row_list_d;

		typedef multivector<row_list_h> table_h;
		typedef multivector<row_list_d> table_d;


	GaussKronrodQuadrature(GReal_t xlower, GReal_t xupper):
		fXLower(xlower),
		fXUpper(xupper),
		fRule(GaussKronrodRuleSelector<NRULE>().fRule)
	{

		this->SetBins();
		this->SetCallTable();
	}

	GaussKronrodQuadrature(GaussKronrodQuadrature<NRULE,NBIN, hydra::detail::BackendPolicy<BACKEND> > const& other)
	{
		this->fXLower = other.GetXLower();
		this->fXUpper = other.GetXUpper();
		this->fRule   = other.GetfRule();
		this->SetBins();
		this->SetCallTable();
	}

	GaussKronrodQuadrature<NRULE,NBIN, hydra::detail::BackendPolicy<BACKEND> >&
	operator=(GaussKronrodQuadrature<NRULE,NBIN, hydra::detail::BackendPolicy<BACKEND> > const& other)
	{
		if(this==&other) return *this;

			this->fXLower = other.GetXLower();
			this->fXUpper = other.GetXUpper();
			this->fRule   = other.GetfRule();
			this->SetBins();
			this->SetCallTable();

			return *this;
	}

	template< hydra::detail::Backend  BACKEND2 >
	GaussKronrodQuadrature(GaussKronrodQuadrature<NRULE,NBIN, hydra::detail::BackendPolicy<BACKEND2> > const& other)
	{
            this->fXLower = other.GetXLower();
            this->fXUpper = other.GetXUpper();
            this->fRule   = other.GetfRule();
			this->SetBins();
			this->SetCallTable();
	}

	template< hydra::detail::Backend  BACKEND2 >
	GaussKronrodQuadrature<NRULE,NBIN, hydra::detail::BackendPolicy<BACKEND> >&
	operator=(GaussKronrodQuadrature<NRULE,NBIN, hydra::detail::BackendPolicy<BACKEND2> > const& other)
	{
		if(this==&other) return *this;

		this->fXLower = other.GetXLower();
		this->fXUpper = other.GetXUpper();
		this->fRule   = other.GetfRule();
		this->SetBins();
		this->SetCallTable();

		return *this;
	}

	template<typename FUNCTOR>
	std::pair<GReal_t, GReal_t> Integrate(FUNCTOR const& functor);

	void Print()
	{
		HYDRA_CALLER ;
		HYDRA_MSG << "GaussKronrodQuadrature begin: " << HYDRA_ENDL;
		HYDRA_MSG << "XLower: " << fXLower << HYDRA_ENDL;
		HYDRA_MSG << "XUpper: " << fXUpper << HYDRA_ENDL;
		HYDRA_MSG << "NBins: " << NBIN << HYDRA_ENDL;
		for(size_t i=0; i<NBIN; i++ ){
			HYDRA_MSG << "bin " << i <<" = ["<< fBins[i] <<", " << fBins[i+1]<< "]"<< HYDRA_ENDL;
		    	}
		fRule.Print();
		HYDRA_MSG << "GaussKronrodQuadrature end. " << HYDRA_ENDL;
	}

	GReal_t GetXLower() const
	{
		return fXLower;
	}

	void SetXLower(GReal_t xLower)
	{
		fXLower = xLower;
		this->SetBins();
		this->SetCallTable();
	}

	GReal_t GetXUpper() const
	{
		return fXUpper;
	}

	void SetXUpper(GReal_t xUpper)
	{
		fXUpper = xUpper;
		this->SetBins();
		this->SetCallTable();
	}

	const GaussKronrodRule<NRULE>& GetRule() const
	{
		return fRule;
	}

private:

    void SetBins()
    {

    	GReal_t delta = (fXUpper - fXLower)/NBIN;

    	for(size_t i=0; i<NBIN; i++ )
    	{
    		this->fBins[i] = this->fXLower + i*delta;
    	}

    	this->fBins[NBIN] = this->fXUpper;

    }


    void SetCallTable()
    {

    	fCallTable.resize(NBIN*(NRULE+1)/2);
    	table_h temp_table(NBIN*(NRULE+1)/2);

    	for(size_t bin=0; bin<NBIN; bin++)
    	{
    		for(size_t call=0; call<(NRULE+1)/2; call++)
    		{
    			GReal_t lower_lim = fBins[bin];
    			GReal_t upper_lim = fBins[bin+1];
    			GReal_t abscissa_X_P = 0;
    			GReal_t abscissa_X_M = 0;
    			GReal_t abscissa_Weight = 0;

    			thrust::tie(abscissa_X_P, abscissa_X_M, abscissa_Weight) = fRule.GetAbscissa(call , lower_lim, upper_lim);

    			GReal_t rule_GaussKronrod_Weight   = fRule.KronrodWeight[call];
    			GReal_t rule_Gauss_Weight          = fRule.GaussWeight[call];

    			size_t index = call*NBIN + bin;

    			temp_table[index]= row_t( abscissa_X_P, abscissa_X_M, abscissa_Weight, rule_GaussKronrod_Weight, rule_Gauss_Weight);
    		}
    	}

    	///for(auto row: temp_table) std::cout << row << std::endl;
    	thrust::copy( temp_table.begin(), temp_table.end(), fCallTable.begin() );

    }

	GReal_t fXLower;
	GReal_t fXUpper;
	GReal_t fBins[NBIN+1];
	GaussKronrodRule<NRULE> fRule;
	table_d fCallTable;


};


} // namespace hydra

#include <hydra/detail/GaussKronrodQuadrature.inl>

#endif /* GAUSSKRONRODQUADRATURE_H_ */
