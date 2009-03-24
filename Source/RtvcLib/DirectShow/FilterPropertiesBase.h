/** @file

MODULE				: FilterPropertiesBase

FILE NAME			: FilterPropertiesBase.h

DESCRIPTION			: Filter Property base class that has a pointer to the filter's ISettingInterface COM interface.
					Subclasses must then still implement the ReadSettings and OnApplyChanges to read and write the filter settings.
					  
LICENSE: Software License Agreement (BSD License)

Copyright (c) 2008, Meraka Institute
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* Neither the name of the Meraka Institute nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

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

#pragma warning(push)     // disable for this header only
#pragma warning(disable:4312)
// DirectShow
#include <streams.h>
#pragma warning(pop)      // restore original warning level

#include <Commctrl.h>

#include <DirectShow/SettingsInterface.h>

#include "resource.h"

/*
* From: http://msdn.microsoft.com/en-us/library/dd375010(VS.85).aspx Creating a Filter Property Page
* OnConnect is called when the client creates the property page. It sets the IUnknown pointer to the filter.
* OnActivate is called when the dialog is created.
* OnReceiveMessage is called when the dialog receives a window message.
* OnApplyChanges is called when the user commits the property changes by clicking the OK or Apply button.
* OnDisconnect is called when the user dismisses the property sheet.
*/

#define BUFFER_SIZE 256

class FilterPropertiesBase : public CBasePropertyPage
{
public:
	HRESULT OnConnect(IUnknown *pUnk)
	{
		if (pUnk == NULL)
		{
			return E_POINTER;
		}
		ASSERT(m_pSettingsInterface == NULL);

		return pUnk->QueryInterface(IID_ISettingsInterface, 
			reinterpret_cast<void**>(&m_pSettingsInterface));
	}

	HRESULT OnActivate(void)
	{
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icc.dwICC = ICC_BAR_CLASSES;
		if (InitCommonControlsEx(&icc) == FALSE)
		{
			return E_FAIL;
		}

		ASSERT(m_pSettingsInterface != NULL);

		return ReadSettings();
	}

	BOOL OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//TODO: only SetDirty if the spin message was intercepted
		SetDirty();
		// Let the parent class handle the message.
		return CBasePropertyPage::OnReceiveMessage(hwnd,uMsg,wParam,lParam);
	} 

	HRESULT OnApplyChanges(void) = 0;

	HRESULT OnDisconnect(void)
	{
		if (m_pSettingsInterface)
		{
			m_pSettingsInterface->Release();
			m_pSettingsInterface = NULL;
		}
		return S_OK;
	}
protected:

	FilterPropertiesBase::FilterPropertiesBase(char* szName, IUnknown *pUnk, int nDialogId, int nTitleId) : 
	CBasePropertyPage(szName, pUnk, nDialogId, nTitleId),
		m_pSettingsInterface(NULL)
	{;}

	virtual HRESULT ReadSettings() = 0;


	void SetDirty()
	{
		m_bDirty = TRUE;
		if (m_pPageSite)
		{
			m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
		}
	}


	ISettingsInterface* m_pSettingsInterface;    // Pointer to the filter's custom interface.
};

