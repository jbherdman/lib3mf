/*++

Copyright (C) 2018 3MF Consortium

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

NMR_ModelReaderNode_ExactGeometry1901_NurbsSurface.cpp covers the official 3MF Exact Geometry Extension.

--*/

#include "Model/Reader/ExactGeometry1901/NMR_ModelReader_ExactGeometry1901_Knot.h"

#include "Model/Classes/NMR_ModelConstants.h"
#include "Model/Classes/NMR_ModelMeshObject.h"
#include "Model/Classes/NMR_ModelNurbsSurface.h"

#include "Common/NMR_StringUtils.h"
#include "Common/NMR_Exception.h"
#include "Common/NMR_Exception_Windows.h"
#include <cmath>

namespace NMR {

	CModelReaderNode_ExactGeometry1901_Knot::CModelReaderNode_ExactGeometry1901_Knot(_In_ CModel * pModel, _In_ PModelReaderWarnings pWarnings)
		: CModelReaderNode(pWarnings)
	{
		m_pModel = pModel;
		m_pWarnings = pWarnings;

		m_bHasMultiplicity = false;
		m_nMultiplicity = 0;
		m_bHasValue = false;
		m_dValue = 0.0;

	}

	void CModelReaderNode_ExactGeometry1901_Knot::parseXML(_In_ CXmlReader * pXMLReader)
	{
		// Parse name
		parseName(pXMLReader);

		// Parse attribute
		parseAttributes(pXMLReader);

		// Parse Content
		parseContent(pXMLReader);

	}

	
	void CModelReaderNode_ExactGeometry1901_Knot::OnAttribute(_In_z_ const nfChar * pAttributeName, _In_z_ const nfChar * pAttributeValue)
	{
		__NMRASSERT(pAttributeName);
		__NMRASSERT(pAttributeValue);

		if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_NURBS_MULTIPLICITY) == 0) {
			if (m_bHasMultiplicity)
				throw CNMRException(NMR_ERROR_NURBSDUPLICATEATTRIBUTE);

			nfUint32 nValue = fnStringToUint32(pAttributeValue);
			if ((nValue == 0) || (nValue >= MAXNURBSMULTIPLICITY))
				throw CNMRException(NMR_ERROR_INVALIDNURBSDEGREE);

			m_nMultiplicity = nValue;
			m_bHasMultiplicity = true;
		}
		else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_NURBS_VALUE) == 0) {
			if (m_bHasValue)
				throw CNMRException(NMR_ERROR_NURBSDUPLICATEATTRIBUTE);

			nfDouble dValue = fnStringToDouble(pAttributeValue);
			if ( std::isnan(dValue) || (dValue <= 0) || (dValue > XML_3MF_MAXIMUMCOORDINATEVALUE) )
				throw CNMRException(NMR_ERROR_NURBSINVALIDATTRIBUTE);
			
			m_dValue = dValue;
			m_bHasValue = true;
		} 
		else
			m_pWarnings->addException(CNMRException(NMR_ERROR_BEAMLATTICEINVALIDATTRIBUTE), mrwInvalidOptionalValue);
	}

	void CModelReaderNode_ExactGeometry1901_Knot::OnNSAttribute(_In_z_ const nfChar * pAttributeName, _In_z_ const nfChar * pAttributeValue, _In_z_ const nfChar * pNameSpace)
	{
		

	}
	
	void CModelReaderNode_ExactGeometry1901_Knot::OnNSChildElement(_In_z_ const nfChar * pChildName, _In_z_ const nfChar * pNameSpace, _In_ CXmlReader * pXMLReader)
	{
		__NMRASSERT(pChildName);
		__NMRASSERT(pXMLReader);
		__NMRASSERT(pNameSpace);

		if (strcmp(pNameSpace, XML_3MF_NAMESPACE_NURBSSPEC) == 0) {
			m_pWarnings->addException(CNMRException(NMR_ERROR_NAMESPACE_INVALID_ELEMENT), mrwInvalidOptionalValue); 
		}
	}

	void CModelReaderNode_ExactGeometry1901_Knot::retrieveValues(nfUint32 & nMultiplicity, nfDouble & dValue)
	{
		if (!m_bHasMultiplicity)
			throw CNMRException(NMR_ERROR_NURBSMULTIPLICITYMISSING);
		if (!m_bHasValue)
			throw CNMRException(NMR_ERROR_NURBSVALUEMISSING);

		nMultiplicity = m_nMultiplicity;
		dValue = m_dValue;
	}

}
