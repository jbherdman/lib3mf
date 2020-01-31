/*++

Copyright (C) 2019 3MF Consortium

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Abstract:

NMR_ModelReaderNode_KeyStoreCipherValue.h defines the Model Reader Node class that is related to <xenc:CipherValue>.

--*/

#ifndef __NMR_MODELREADERNODE_KEYSTORECIPHERVALUE
#define __NMR_MODELREADERNODE_KEYSTORECIPHERVALUE

#include "Model/Reader/NMR_ModelReaderNode_KeyStoreBase.h"
#include "Model/Reader/NMR_ModelReaderNode.h"
#include "Model/Classes/NMR_KeyStore.h"
#include "Model/Classes/NMR_KeyStoreDecryptRight.h"

namespace NMR {

	class CModelReaderNode_KeyStoreCipherValue: public CModelReaderNode_KeyStoreBase {
	private:
		CIPHERVALUE m_sCipherValue;
		std::string m_sCipherValueAccumulator;
	protected:
		virtual void OnText(_In_z_ const nfChar * pText, _In_ CXmlReader * pXMLReader);
	public:
		CModelReaderNode_KeyStoreCipherValue() = delete;
		CModelReaderNode_KeyStoreCipherValue(_In_ CKeyStore * pKeyStore, _In_ PModelReaderWarnings pWarnings);

		CIPHERVALUE getCipherValue();

		virtual void parseXML(_In_ CXmlReader * pXMLReader);
	};

	typedef std::shared_ptr <CModelReaderNode_KeyStoreCipherValue> PModelReaderNode_KeyStoreCipherValue;
}

#endif // __NMR_MODELREADERNODE_KEYSTORECIPHERVALUE
