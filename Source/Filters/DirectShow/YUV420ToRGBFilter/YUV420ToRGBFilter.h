/** @file

MODULE				: YUV420ToRGBFilter

FILE NAME			: YUV420ToRGBFilter.h

DESCRIPTION			: This Filter converts the YUV420 Planar media back into RGB24 media.

LICENSE: Software License Agreement (BSD License)

Copyright (c) 2008 - 2014, CSIR
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* Neither the name of the CSIR nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

===========================================================================
*/
#pragma once

// CSIR includes
#include <DirectShow/CustomBaseFilter.h>

// Parameters
#define CHROMINANCE_OFFSET "chrominanceoffset"
#define INVERT "invert"

// GUID

// {FF539CF3-CB7A-4121-92C2-5A3EB8E7FE5E}
static const GUID CLSID_VPP_YUV420toRGBColorConverter = 
{ 0xff539cf3, 0xcb7a, 0x4121, { 0x92, 0xc2, 0x5a, 0x3e, 0xb8, 0xe7, 0xfe, 0x5e } };

// {B1F14AD0-B641-4fc1-A3B6-692A8B2FC67D}
static const GUID CLSID_YUVtoRGB420Properties = 
{ 0xb1f14ad0, 0xb641, 0x4fc1, { 0xa3, 0xb6, 0x69, 0x2a, 0x8b, 0x2f, 0xc6, 0x7d } };

// Forward declarations
class YUV420toRGBConverter;

/**
* \ingroup DirectShowFilters
* This Filter converts the YUV420 Planar media back into RGB24 media.
*/
class YUV420toRGBFilter :   public CCustomBaseFilter,
  public ISpecifyPropertyPages
{
public:
  DECLARE_IUNKNOWN

  /// Constructor
  YUV420toRGBFilter();
  /// Destructor
  ~YUV420toRGBFilter();

  /// Static object-creation method (for the class factory)
  static CUnknown * WINAPI CreateInstance(LPUNKNOWN pUnk, HRESULT *pHr); 

  /**
  * Overriding this so that we can set whether this is an RGB24 or an RGB32 Filter
  */
  HRESULT SetMediaType(PIN_DIRECTION direction, const CMediaType *pmt);

  /**
  * Used for Media Type Negotiation.
  * Returns an HRESULT value. Possible values include those shown in the following table.
  * <table border="0" cols="2"><tr valign="top"><td><b>Value</b></td><td><b>Description</b></td></TR><TR><TD>S_OK</TD><TD>Success</TD></TR><TR><TD>VFW_S_NO_MORE_ITEMS</TD><TD>Index out of range</TD></TR><TR><TD>E_INVALIDARG</TD><TD>Index less than zero</TD></TR></TABLE>
  * The output pin's CTransformOutputPin::GetMediaType method calls this method. The derived class must implement this method. For more information, see CBasePin::GetMediaType.
  * To use custom media types, the media type can be manipulated in this method.
  */
  HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);

  /// Buffer Allocation
  /**
  * The output pin's CTransformOutputPin::DecideBufferSize method calls this method. The derived class must implement this method. For more information, see CBaseOutputPin::DecideBufferSize. 
  * @param pAlloc Pointer to the IMemAllocator interface on the output pin's allocator.
  * @param pProp Pointer to an ALLOCATOR_PROPERTIES structure that contains buffer requirements from the downstream input pin.
  * @return Value: Returns S_OK or another HRESULT value.
  */
  HRESULT DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *pProp);

  /**
  * The CheckTransform method checks whether an input media type is compatible with an output media type.
  * <table border="0" cols="2"> <tr valign="top"> <td  width="50%"><b>Value</b></td> <td width="50%"><b>Description</b></td> </tr> <tr valign="top"> <td width="50%">S_OK</td> <td width="50%">The media types are compatible.</td> </tr> <tr valign="top"> <td width="50%">VFW_E_TYPE_NOT_ACCEPTED</td> <td width="50%">The media types are not compatible.</td> </tr> </table>
  */
  HRESULT CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut);

  /// Overridden from CCustomBaseFilter
  virtual void InitialiseInputTypes();

  /// Overridden from CSettingsInterface
  STDMETHODIMP SetParameter( const char* type, const char* value);

  /// Overridden from CSettingsInterface
  virtual void initParameters()
  {
    addParameter(CHROMINANCE_OFFSET, &m_nChrominanceOffset, 128);
    addParameter(INVERT, &m_bInvert, true);
  }

  STDMETHODIMP GetPages(CAUUID *pPages)
  {
    if (pPages == NULL) return E_POINTER;
    pPages->cElems = 1;
    pPages->pElems = (GUID*)CoTaskMemAlloc(sizeof(GUID));
    if (pPages->pElems == NULL) 
    {
      return E_OUTOFMEMORY;
    }
    pPages->pElems[0] = CLSID_YUVtoRGB420Properties;
    return S_OK;
  }

  STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv)
  {
    if (riid == IID_ISpecifyPropertyPages)
    {
      return GetInterface(static_cast<ISpecifyPropertyPages*>(this), ppv);
    }
    else
    {
      // Call the parent class.
      return CCustomBaseFilter::NonDelegatingQueryInterface(riid, ppv);
    }
  }
protected:


private:
  /**
  * This method converts the input buffer from RGB24 | 32 to YUV420P
  * @param pSource The source buffer
  * @param pDest The destination buffer
  */
  virtual HRESULT ApplyTransform(BYTE* pBufferIn, long lInBufferSize, long lActualDataLength, BYTE* pBufferOut, long lOutBufferSize, long& lOutActualDataLength);

  /// Pointer to our RGB24 | 32 to YUV420 converter
  YUV420toRGBConverter* m_pConverter;
  // Size of YUV image
  int m_nSizeUV;
  // Chrominance offset
  int m_nChrominanceOffset;
  // YUV is always top down: the invert flag determines whether the image
  // is flipped during conversion, or whether the sign is simply set
  bool m_bInvert;
};
