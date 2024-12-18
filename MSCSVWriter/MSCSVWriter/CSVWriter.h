#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <afxstr.h> // CString ���
#include <fstream>
#include <vector>
#include <iostream>
#include <type_traits>

/////////////////////////////////////
// 24-12-18 �ڼҿ� ������

class CSVWriter
{
public:
	CSVWriter() = default;

	// �����͸� �߰��ϴ� �Լ� (������ ������ ���� ���� ����)
	template<typename T>
	void add(const T& data, bool bLast = false, int nPoint = 1)
	{
		CString strData = SumCSVData(data, bLast, nPoint);
		m_CurrentRow += strData;
	}

	// �� �� �߰�
	void addRow()
	{
		if (!m_CurrentRow.IsEmpty())
		{
			m_Rows.push_back(m_CurrentRow);
			m_CurrentRow.Empty();
		}
	}

	// ��� ����
	void AddHeader(const CString& header)
	{
		m_Header = header;
	}

	// ���� �����͸� CSV ������ ���ڿ��� ��ȯ
	CString ToString() const
	{
		CString result;

		// ����� �����ϸ� ��� �߰�
		if (!m_Header.IsEmpty())
		{
			result += m_Header + _T("\n");
		}

		// ������ �� �߰�
		for (const auto& row : m_Rows)
		{
			result += row + _T("\n");
		}
		return result;
	}

	// CSV �����͸� ���Ϸ� ����
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
	// SumCSVData int��
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

	// SumCSVData float��
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

	// SumCSVData double��
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

	// SumCSVData CString��
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




	//// SumCSVData �Լ� (���ø�ȭ)
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
	//		// ��Ÿ Ÿ���� ���ڿ��� ��ȯ�Ͽ� ó��
	//		strFormat = _T("%s");
	//	}

	//	if (!bLast)
	//		strFormat += _T(",");

	//	strData.Format(strFormat, data);

	//	return strData;
	//}

	CString m_CurrentRow;             // ���� �ۼ� ���� ��
	std::vector<CString> m_Rows;      // �ۼ��� ���
	CString m_Header;                 // ���
};

#endif 
