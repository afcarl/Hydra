/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2016 - 2017 Antonio Augusto Alves Junior
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
 * Chebychev.h
 *
 *  Created on: 09/04/2018
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef CHEBYCHEV_POLY_H_
#define CHEBYCHEV_POLY_H_


#include <hydra/Types.h>
#include <hydra/Function.h>
#include <hydra/Pdf.h>
#include <hydra/detail/Integrator.h>
#include <hydra/Parameter.h>
#include <hydra/Tuple.h>
#include <hydra/functions/Math.h>
#include <tuple>
#include <limits>
#include <stdexcept>
#include <cassert>
#include <utility>

#include <hydra/functions/Utils.h>


namespace hydra {

template< unsigned int Order, unsigned int ArgIndex=0>
class  Chebychev:public BaseFunctor<Chebychev<Order, ArgIndex>, double, Order+1>
{
	using BaseFunctor<Chebychev<Order, ArgIndex>, double, Order+1>::_par;

public:
	Chebychev() = delete;

	Chebychev(double min, double max, std::array<Parameter,Order+1> const& coeficients):
		BaseFunctor<Chebychev<Order, ArgIndex>, double, Order+1>( coeficients),
		fMinimum(min),
		fMaximum(max)
	{}

	__hydra_host__ __hydra_device__
	Chebychev(Chebychev<Order, ArgIndex> const& other):
		BaseFunctor<Chebychev<Order, ArgIndex>, double, Order+1>(other),
		fMinimum(other.GetMinimum()),
		fMaximum(other.GetMaximum())
	{}

	__hydra_host__ __hydra_device__
	inline Chebychev<Order, ArgIndex>&
	operator=( Chebychev<ArgIndex, Order> const& other)
	{
		if(this == &other) return *this;
		BaseFunctor<Chebychev<ArgIndex, Order>,double, Order+1>::operator=(other);
		fMinimum = other.GetMinimum();
		fMaximum = other.GetMaximum();
		return *this;
	}

	template<typename T>
	__hydra_host__ __hydra_device__
	inline double Evaluate(unsigned int , T* x)  const
	{
		double coefs[Order+1]{};
		for(unsigned int i =0; i<Order+1; i++)
			coefs[i]=CHECK_VALUE(_par[i], "par[%d]=%f", i, _par[i]) ;

		double y = -1.0 + 2.0*(x[ArgIndex] - fMinimum)/( fMaximum- fMinimum);

		double r = polynomial(coefs, y);
		return  CHECK_VALUE(r, "result =%f", r) ;
	}

	double GetMaximum() const {
		return fMaximum;
	}

	void SetMaximum(double maximum) {
		fMaximum = maximum;
	}

	double GetMinimum() const {
		return fMinimum;
	}

	void SetMinimum(double minimum) {
		fMinimum = minimum;
	}

	template<typename T>
	__hydra_host__ __hydra_device__ inline
	double Evaluate(T x)  const
	{
		double coefs[Order+1]{};
		for(unsigned int i =0; i<Order+1; i++)
			coefs[i]=CHECK_VALUE(_par[i], "par[%d]=%f", i, _par[i]) ;

		double y = -1.0 + 2.0*(hydra::get<ArgIndex>(x) - fMinimum)/( fMaximum- fMinimum);

		double r = polynomial(coefs, y);
		return  CHECK_VALUE(r, "result =%f", r) ;
	}

private:

	template<unsigned int I>
	__hydra_host__ __hydra_device__ inline
	typename std::enable_if<(I==Order+1), void >::type
	polynomial_helper( const double(&)[Order+1],  const double, double&)  const {}

	template<unsigned int I=0>
	__hydra_host__ __hydra_device__ inline
	typename std::enable_if<(I<Order+1), void >::type
	polynomial_helper( const double(&coef)[Order+1],  const double x, double& r)  const {

		r += coef[I]*chebychev_1st_kind(I, x);
		polynomial_helper<I+1>( coef, x, r);
	}

	__hydra_host__ __hydra_device__ inline double polynomial( const double(&coef)[Order+1],  const double x) const {

		double r=0.0;
		polynomial_helper( coef,x, r);
		return r;
	}

	double fMinimum;
	double fMaximum;

};


class ChebychevAnalyticalIntegral:public Integrator<ChebychevAnalyticalIntegral>
{

public:

	ChebychevAnalyticalIntegral(double min, double max):
	fLowerLimit(min),
	fUpperLimit(max)
	{
		assert(fLowerLimit < fUpperLimit
				&& "hydra::ChebychevAnalyticalIntegral: MESSAGE << LowerLimit >= fUpperLimit >>");

	}

	inline ChebychevAnalyticalIntegral(ChebychevAnalyticalIntegral const& other):
	fLowerLimit(other.GetLowerLimit()),
	fUpperLimit(other.GetUpperLimit())
	{}

	inline ChebychevAnalyticalIntegral&
	operator=( ChebychevAnalyticalIntegral const& other)
	{
		if(this == &other) return *this;
		this->fLowerLimit = other.GetLowerLimit();
		this->fUpperLimit = other.GetUpperLimit();
		return *this;
	}

	double GetLowerLimit() const {
		return fLowerLimit;
	}

	void SetLowerLimit(double lowerLimit) {
		fLowerLimit = lowerLimit;
	}

	double GetUpperLimit() const {
		return fUpperLimit;
	}

	void SetUpperLimit(double upperLimit) {
		fUpperLimit = upperLimit;
	}

	template<unsigned int Order, unsigned int ArgIndex >
	inline std::pair<double, double> Integrate(Chebychev<Order, ArgIndex> const& functor) const
	{
		double coefs[Order+1]{};
		for(unsigned int i =0; i<Order+1; i++)
			coefs[i]=functor[i];

		double r=0;

		if(fUpperLimit <=  functor.GetMaximum() && fLowerLimit >=  functor.GetMinimum() ){


			r   =  polynomial_integral<Order+1>(coefs, fUpperLimit, functor.GetMinimum(), functor.GetMaximum()) -
					polynomial_integral<Order+1>(coefs,fLowerLimit, functor.GetMinimum(), functor.GetMaximum()) ;
		}
		else {

			r   =  polynomial_integral<Order+1>(coefs, (fUpperLimit >  functor.GetMaximum()) ? functor.GetMaximum():fUpperLimit, functor.GetMinimum(), functor.GetMaximum()) -
				   polynomial_integral<Order+1>(coefs, (fLowerLimit <  functor.GetMinimum()) ? functor.GetMinimum():fLowerLimit, functor.GetMinimum(), functor.GetMaximum()) ;
		}


		return std::make_pair( 0.5*(fUpperLimit-fLowerLimit)*r,0.0);
	}

private:

	template<unsigned int N, unsigned int I>
	__hydra_host__ __hydra_device__ inline
	typename std::enable_if<(I==N), void >::type
	polynomial_integral_helper( const double, const double(&)[N], double&) const {}

	template<unsigned int N, unsigned int I=2>
	__hydra_host__ __hydra_device__ inline
	typename std::enable_if<(I<N), void >::type
	polynomial_integral_helper( const double x, const double(&coef)[N], double& r) const {

		r += 0.5*coef[I]*(chebychev_1st_kind(I+1,x)/(I+1) - chebychev_1st_kind(I-1,x)/(I-1) );
		polynomial_integral_helper<N, I+1>(x,coef, r);
	}

	template<unsigned int N>
	__hydra_host__ __hydra_device__ inline double polynomial_integral(const double(&coef)[N], double x, double min, double max) const {

		double y = -1.0 + 2.0*(x - min)/( max- min);

		double r= coef[0]*chebychev_1st_kind(1,y)+0.25*coef[1]*chebychev_1st_kind(2,y);

		polynomial_integral_helper<N,2>(y,coef, r);

		return r;
	}

	double fLowerLimit;
	double fUpperLimit;
};

}  // namespace hydra


#endif /* CHEBYCHEV_H_ */
