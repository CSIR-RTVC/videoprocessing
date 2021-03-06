/** @file

MODULE				: H264Properties

FILE NAME			: H264Properties.h

DESCRIPTION			: Properties dialog for H264 Source Filter

LICENSE: Software License Agreement (BSD License)

Copyright (c) 2012, CSIR
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

#include <DirectShow/FilterPropertiesBase.h>
#include "resource.h"


/**
* \ingroup DirectShowFilters
* Properties dialog for H264 Source Filter
*/
class H264Properties : public FilterPropertiesBase
{
public:

  static CUnknown * WINAPI CreateInstance(LPUNKNOWN pUnk, HRESULT *pHr) 
  {
    H264Properties *pNewObject = new H264Properties(pUnk);
    if (pNewObject == NULL) 
    {
      *pHr = E_OUTOFMEMORY;
    }
    return pNewObject;
  }

  H264Properties::H264Properties(IUnknown *pUnk) : 
  FilterPropertiesBase(NAME("H264 Source Properties"), pUnk, IDD_H264_DIALOG, IDS_H264_CAPTION)
  {;}

  HRESULT ReadSettings()
  {
    int nLength = 0;
		char szBuffer[BUFFER_SIZE];
		HRESULT hr = m_pSettingsInterface->GetParameter(USE_RTVC_H264, sizeof(szBuffer), szBuffer, &nLength);
		if (SUCCEEDED(hr))
		{
			WPARAM wParam;
			if (szBuffer[0] == '0')
				wParam = 0;	
			else
				wParam = 1;
			long lResult = SendMessage(				// returns LRESULT in lResult
				GetDlgItem(m_Dlg, IDC_USE_RTVC_H264),	// handle to destination control
				(UINT) BM_SETCHECK,					// message ID
				(WPARAM) wParam,							// = 0; not used, must be zero
				(LPARAM) 0							// = (LPARAM) MAKELONG ((short) nUpper, (short) nLower)
				);
		}

    hr = m_pSettingsInterface->GetParameter(SOURCE_FPS, sizeof(szBuffer), szBuffer, &nLength);
    if (SUCCEEDED(hr))
      SetDlgItemText(m_Dlg, IDC_FPS, szBuffer);

    hr = m_pSettingsInterface->GetParameter(SOURCE_DIMENSIONS, sizeof(szBuffer), szBuffer, &nLength);
    if (SUCCEEDED(hr))
      SetDlgItemText(m_Dlg, IDC_CMB_DIMENSIONS, szBuffer);

		return hr;
  }

  HRESULT OnApplyChanges(void)
  {
    HRESULT hr;
		int iCheck = SendMessage( GetDlgItem(m_Dlg, IDC_USE_RTVC_H264),	(UINT) BM_GETCHECK,	0, 0);
		if (iCheck == 0)
		{
			hr = m_pSettingsInterface->SetParameter(USE_RTVC_H264, "false");
		}
		else
		{
			hr = m_pSettingsInterface->SetParameter(USE_RTVC_H264, "true");
		}
		return hr;
  } 

private:
  void initialiseControls()
  {
    InitCommonControls();

    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_RESETCONTENT, 0, 0);
    ////Add default option
    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_ADDSTRING,	 0, (LPARAM)"Select");
    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_SELECTSTRING,  0, (LPARAM)"Select");
    //// Now populate the graphs
    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_INSERTSTRING,  1, (LPARAM)"176x144");
    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_INSERTSTRING,  2, (LPARAM)"320x240");
    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_INSERTSTRING,  3, (LPARAM)"352x288");
    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_INSERTSTRING,  4, (LPARAM)"704x576");
    //SendMessage(GetDlgItem(m_Dlg, IDC_CMB_DIMENSIONS), CB_SETMINVISIBLE, 5, 0);

    //// Init frames per second
    //short lower = 1;
    //short upper = 60;

    //// Init UI
    //long lResult = SendMessage(			// returns LRESULT in lResult
    //  GetDlgItem(m_Dlg, IDC_SPIN_FPS),	// handle to destination control
    //  (UINT) UDM_SETRANGE,			// message ID
    //  (WPARAM) 0,						// = 0; not used, must be zero
    //  (LPARAM) MAKELONG ( upper, lower)      // = (LPARAM) MAKELONG ((short) nUpper, (short) nLower)
    //  );
    //// Default value of 30 FPS
    //SetDlgItemText(m_Dlg, IDC_FPS, "30");

  }
};

