/*
 * Operators.h
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef MAIN_OPERATORS_H_
#define MAIN_OPERATORS_H_



/**
*  @brief This does what you think it does.
*  https://help.codesys.com/webapp/_cds_operator_min;product=codesys;version=3.5.17.0
*  @ingroup sorting_algorithms
*  @param  IN0  A thing of arbitrary type.
*  @param  IN1  Another thing of arbitrary type.
*  @return   The lesser of the parameters.
*/
template<typename _Tp>
inline const _Tp&
MIN(const _Tp& IN0, const _Tp& IN1)
{
  return (IN1 < IN0 ? IN1 : IN0);
}

/**
*  @brief This does what you think it does.
*
*  @ingroup sorting_algorithms
*  @param  IN0  A thing of arbitrary type.
*  @param  IN1  Another thing of arbitrary type.
*  @return   The greater of the parameters.
*/
template<typename _Tp>
inline const _Tp&
MAX(const _Tp& IN0, const _Tp& IN1)
{
  return  (IN0 < IN1 ? IN1 : IN0);
}

//https://help.codesys.com/webapp/_cds_operator_limit;product=codesys;version=3.5.17.0
template<typename _Tp>
inline const _Tp&
LIMIT(const _Tp& Min, const _Tp& IN, const _Tp& Max)
{
  return  (MIN (MAX (IN, Min), Max));
}










#endif /* MAIN_OPERATORS_H_ */
