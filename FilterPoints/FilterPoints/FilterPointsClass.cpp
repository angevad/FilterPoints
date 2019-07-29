#include "stdafx.h"

//#include <map>

#include "FilterPointsClass.h"

//////////////////////////////////////////////////
CFilterPoints::CFilterPoints (double dTolerance)
  {
  m_dTolerance = dTolerance;
  }
//////////////////////////////////////////////////
void CFilterPoints::InsPoint (CPoint3D *pPoint3D)
  {
  m_Point3d.insert (*pPoint3D);
  }
//////////////////////////////////////////////////
bool CFilterPoints::InsPoint (CPoint3D *pPoint3D, double dTollerance)
  {
  bool bSuccess (false);

  if (m_Point3d_filtred.empty ())
    {
    m_Point3d_filtred.insert (*pPoint3D);
    bSuccess = true;
    }
  else
    {
    std::set<CPoint3D>::iterator iter;
    for (iter = m_Point3d_filtred.begin (); iter != m_Point3d_filtred.end (); iter++)
      {
      if (FindNearestPoint (*iter, dTollerance))
        {
        m_Point3d_filtred.insert (*iter);
        bSuccess = true;
        break;
        }
      }
    }
  return bSuccess;
  }
//////////////////////////////////////////////////
void CFilterPoints::DelAllFilteredPoints ()
  {
  m_Point3d_filtred.clear ();
  }
//////////////////////////////////////////////////
std::set<CPoint3D>& CFilterPoints::GetFilteredPoints ()
  {
  return (m_Point3d_filtred);
  }
//////////////////////////////////////////////////
int CFilterPoints::Size ()
  {
  return (m_Point3d_filtred.size ());
  }
//////////////////////////////////////////////////
bool CFilterPoints::FilterPoints ()
  {
  bool bSuccess (false);

  std::set<CPoint3D>::iterator iter;
  for (iter = m_Point3d.begin (); iter != m_Point3d.end (); iter++)
    {
    if (m_Point3d_filtred.empty ())
      m_Point3d_filtred.insert (*m_Point3d.begin ());

    if (FindNearestPoint (*iter, m_dTolerance))
      {
      m_Point3d_filtred.insert (*iter);
      }
    }
  bSuccess = true;
  return bSuccess;
  }
//////////////////////////////////////////////////
bool CFilterPoints::FindNearestPoint (const CPoint3D &pPt, double dTolerance)
  {
  bool bSuccess (false);
  CPoint3D Pt2;
  for (std::set <CPoint3D>::const_iterator iter = m_Point3d_filtred.cbegin (); iter != m_Point3d_filtred.cend (); iter++)
    {
	CPoint3D _pt (iter->Get());
	Pt2 = _pt;
    if (!CheckSqDistance (&pPt, &Pt2, dTolerance))
      {
      bSuccess = true;
      break;
      }
    }
  return bSuccess;
  }
//////////////////////////////////////////////////
bool CFilterPoints::CheckSqDistance (const CPoint3D *pPt1, CPoint3D *pPt2, double dTolerance)
  {
  bool bFound (false);
  if (pPt1->SqDistance (*pPt2) <= dTolerance * dTolerance)
    bFound = true;
  return bFound;
  };
//////////////////////////////////////////////////
void CFilterPoints::GetFilteredPoints (std::set <CPoint3D> &ptFiltered)
  {
  ptFiltered = m_Point3d_filtred;
  }