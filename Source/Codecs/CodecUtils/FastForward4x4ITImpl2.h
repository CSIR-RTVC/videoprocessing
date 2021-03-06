/** @file

MODULE				: FastForward4x4ITImpl2

TAG						: FF4ITI2

FILE NAME			: FastForward4x4ITImpl2.h

DESCRIPTION		: A class to implement a fast forward 4x4 2-D integer
								transform defined by the H.264 standard on the input. 
								It implements the IForwardTransform interface. The 
								scaling	is part of the quantisation process.

LICENSE	: GNU Lesser General Public License

Copyright (c) 2008 - 2013, CSIR
All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

===========================================================================================
*/
#ifndef _FASTFORWARD4X4ITIMPL2_H
#define _FASTFORWARD4X4ITIMPL2_H

#pragma once

#include "IForwardTransform.h"

/*
---------------------------------------------------------------------------
	Class definition.
---------------------------------------------------------------------------
*/
class FastForward4x4ITImpl2 : public IForwardTransform
{
	public:
		FastForward4x4ITImpl2();
		virtual ~FastForward4x4ITImpl2()	{ }

	// Interface implementation.
	public:
		/** In-place forward IT.
		The IT is performed on the input and replaces it with the coeffs.
		@param ptr	: Data to transform.
		@return			:	none.
		*/
		virtual void Transform(void* ptr);

		/** Transfer forward IT.
		The IT is performed on the input and the coeffs are written to 
		the output.
		@param pIn		: Input data.
		@param pCoeff	: Output coeffs.
		@return				:	none.
		*/
		virtual void Transform(void* pIn, void* pCoeff);

		/** Set scaling array.
		Each coefficient may be scaled after transforming and therefore 
		requires setting up. Only the default scaling is used and 
		therefore this method is not implemented.
		@param	pScale:	Scale factor array.
		@return				:	none.
		*/
		virtual void	SetScale(void* pScale) { }
		virtual void* GetScale(void) { return(NULL); }

		/** Set/Get the mode of operation.
		The modes for this implementation set the combinations of 
		including or excluding the transform with or without quantisation.
		@param mode	: Mode to set.
		@return			: none.
		*/
		virtual void SetMode(int mode) { _mode = mode; }
		virtual int  GetMode(void) { return(_mode); }

		/** Set and get parameters for the implementation.
		An Intra and Inter parameter and the quantisation parameter are the 
		only requirement for this	implementation.
		@param paramID	: Parameter to set/get.
		@param paramVal	: Parameter value.
		@return					: None (Set) or the param value (Get).
		*/
		virtual void	SetParameter(int paramID, int paramVal);
		virtual int		GetParameter(int paramID);

    /// Internal methods
  private:
    /** Set internal quant members based on _q.
    @return: none.
    */
    void SetNewQP(void);

		/// Constants.
	protected:
		static const int NormAdjust[6][3];
		static const int ColSelector[16];

	protected:
		int _mode;	///< 0 = IT+Q, 1 = IT only, 2 = Q only.
		int _intra;	///< 0 = Inter, 1 = Intra.

		/// Hold these members that will only change when q or intra flag changes.
		int	_q;				///< Current quantisation parameter.
		int	_qm;			///< _q % 6.
		int _qe;			///< _q / 6.
		int _f;				///< Rounding shift = (1 << (15+_qe))/6.
		int _scale;		///< Scaling shift = 15+_qe;

};// end class FastForward4x4ITImpl2.

#endif	//_FASTFORWARD4X4ITIMPL2_H
