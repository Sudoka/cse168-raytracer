#ifndef CSE168_TRIANGLE_H_INCLUDED
#define CSE168_TRIANGLE_H_INCLUDED

#include <limits>
#include "TriangleMesh.h"
#include "Object.h"

/*
    The Triangle class stores a pointer to a mesh and an index into its
    triangle array. The mesh stores all data needed by this Triangle.
*/
class Triangle : public Object
{
public:
    Triangle(TriangleMesh * m = 0, unsigned int i = 0);
    virtual ~Triangle();
    
    //Object boundaries used with bounding box creation
    virtual Vector3 coordsMin() const { return m_cachedMin; }
    virtual Vector3 coordsMax() const { return m_cachedMax; }
    virtual Vector3 center() const { return m_cachedCenter; }

    virtual void preCalc();

    void setIndex(unsigned int i) { m_index = i; }
    unsigned int getIndex() { return m_index; }
    void setMesh(TriangleMesh* m) { m_mesh = m; }
    const TriangleMesh* getMesh() { return m_mesh; }


    virtual void renderGL();
    virtual bool intersect(HitInfo& result, const Ray& ray,
                           float tMin = 0.0f, float tMax = MIRO_TMAX);
    
protected:
    TriangleMesh* m_mesh;
    unsigned int m_index;
    Vector3 m_cachedMin, m_cachedMax;
    Vector3 m_cachedCenter;
private:
    void updateMinMax(); 
};

#endif // CSE168_TRIANGLE_H_INCLUDED
