#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <afxstr.h> // CString 사용
#include <fstream>
#include <vector>
#include <iostream>
#include <type_traits>

/////////////////////////////////////
// 24-12-18 박소연 수정중

class CSVWriter
{
public:
	CSVWriter() = default;

	// 데이터를 추가하는 함수 (마지막 열인지 여부 지정 가능)
	template<typename T>
	void add(const T& data, bool bLast = false, int nPoint = 1)
	{
		CString strData = SumCSVData(data, bLast, nPoint);
		m_CurrentRow += strData;
	}

	// 새 행 추가
	void addRow()
	{
		if (!m_CurrentRow.IsEmpty())
		{
			m_Rows.push_back(m_CurrentRow);
			m_CurrentRow.Empty();
		}
	}

	// 헤더 설정
	void AddHeader(const CString& header)
	{
		m_Header = header;
	}

	// 현재 데이터를 CSV 형식의 문자열로 반환
	CString ToString() const
	{
		CString result;

		// 헤더가 존재하면 헤더 추가
		if (!m_Header.IsEmpty())
		{
			result += m_Header + _T("\n");
		}

		// 데이터 행 추가
		for (const auto& row : m_Rows)
		{
			result += row + _T("\n");
		}
		return result;
	}

	// CSV 데이터를 파일로 저장
	bool SaveToFile(const CString& filePath, bool append = false) const
	{
		CStdioFile file;

		if (!file.Open(filePath, CFile::modeReadWrite | CFile::typeText)) {
			if (file.Open(filePath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText)) {

				CString strData = ToString();
				file.WriteString(strData);
				file.Close();
				return true;
			}
		}
		else {
			return false;
		}

	}

private:
	// SumCSVData int형
	CString SumCSVData(int data, bool bLast = false, int nPoint = 1) const
	{
		CString strData{};
		CString strFormat{};

		strFormat = _T("%d");

		if (!bLast)
			strFormat += _T(",");

		strData.Format(strFormat, data);

		return strData;
	}

	// SumCSVData float형
	CString SumCSVData(float data, bool bLast = false, int nPoint = 1) const
	{
		CString strData{};
		CString strFormat{};
		strFormat.Format(_T("%%.%df"), nPoint);

		if (!bLast)
			strFormat += _T(",");

		strData.Format(strFormat, data);

		return strData;
	}

	// SumCSVData double형
	CString SumCSVData(double data, bool bLast = false, int nPoint = 1) const
	{
		CString strData{};
		CString strFormat{};
		strFormat.Format(_T("%%.%df"), nPoint);

		if (!bLast)
			strFormat += _T(",");

		strData.Format(strFormat, data);

		return strData;
	}

	// SumCSVData CString형
	CString SumCSVData(CString data, bool bLast = false, int nPoint = 1) const
	{
		CString strData{};
		CString strFormat{};
		strFormat = _T("%s");

		if (!bLast)
			strFormat += _T(",");

		strData.Format(strFormat, data);

		return strData;
	}




	//// SumCSVData 함수 (템플릿화)
	//template<typename T>
	//CString SumCSVData(const T& data, bool bLast = false, int nPoint = 1) const
	//{
	//	CString strData;
	//	CString strFormat;

	//	if (std::is_same_v<T, int>) {
	//		strFormat = _T("%d");
	//	}
	//	else if (std::is_same_v<T, double> || std::is_same_v<T, float>) {
	//		strFormat.Format(_T("%%.%df"), nPoint);
	//	}
	//	else if (std::is_same_v<T, bool>) {
	//		strFormat = _T("%d");
	//	}
	//	else {
	//		// 기타 타입은 문자열로 변환하여 처리
	//		strFormat = _T("%s");
	//	}

	//	if (!bLast)
	//		strFormat += _T(",");

	//	strData.Format(strFormat, data);

	//	return strData;
	//}

	CString m_CurrentRow;             // 현재 작성 중인 행
	std::vector<CString> m_Rows;      // 작성된 행들
	CString m_Header;                 // 헤더
};

#endif 
