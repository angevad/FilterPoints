#include <set>
#include <functional>

//using namespace std;

class CPoint3D
  {
  public:
    CPoint3D ()
      {
      m_dX = 0;
      m_dY = 0;
      m_dZ = 0;
      }
    CPoint3D (double dX, double dY, double dZ)
      {
      m_dX = dX;
      m_dY = dY;
      m_dZ = dZ;
      }
    double SqDistance (const CPoint3D& v) const
      {
      return ((m_dX - v.m_dX) * (m_dX - v.m_dX) +
              (m_dY - v.m_dY) * (m_dY - v.m_dY) +
              (m_dZ - v.m_dZ) * (m_dZ - v.m_dZ));
      }
    inline bool operator < (const CPoint3D &right) const
      {
      if (m_dX < right.m_dX)
        return true;
      else
        return false;
      }
    void Set (const double &dX, const double &dY, const double &dZ)
      {
      m_dX = dX;
      m_dY = dY;
      m_dZ = dZ;
      }
    void Get (double &dX, double &dY, double &dZ)
      {
      dX = m_dX;
      dY = m_dY;
      dZ = m_dZ;
      }
	const CPoint3D Get() const
	  {
	  return CPoint3D(m_dX, m_dY, m_dZ);
	  }
    const double& GetX () { return m_dX; };
    const double& GetY () { return m_dY; };
    const double& GetZ () { return m_dZ; };

  private:
    double m_dX;
    double m_dY;
    double m_dZ;
  };

class CFilterPoints
  {
  public:
    CFilterPoints (double dTolerance);
    virtual void      InsPoint (CPoint3D *pPoint3D);
    virtual bool      InsPoint (CPoint3D *pPoint3D, double dTollerance);
    //virtual CPoint3D& GetPoint (int nPointNum);
    virtual std::set<CPoint3D>& GetFilteredPoints ();
    //virtual void      DelPoint (int nPointNum);
    virtual void      DelAllFilteredPoints ();
    virtual int       Size ();
    virtual bool      FilterPoints ();
    virtual void      GetFilteredPoints (std::set <CPoint3D> &ptFiltered);
  private:
    virtual bool FindNearestPoint (const CPoint3D &pPt, double dTolerance);
    virtual bool CheckSqDistance (const CPoint3D *pPt1, CPoint3D *pPt2, double dTolerance);

  private:
    std::set <CPoint3D> m_Point3d;
    std::set <CPoint3D> m_Point3d_filtred;
    double m_dTolerance;
  };