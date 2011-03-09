#ifndef CSE168_POINTLIGHT_H_INCLUDED
#define CSE168_POINTLIGHT_H_INCLUDED

#include <vector>
#include "Vector3.h"
#include "Utility.h"

class PointLight
{
public:
    void setPosition(const Vector3& v)  {m_position = v;}
    void setColor(const Vector3& v)     {m_color = v;}
    void setWattage(float f)            {m_wattage = f;}
    
    float wattage() const               {return m_wattage;}
    const Vector3 & color() const       {return m_color;}
    const Vector3& position() const     {return m_position;}

	virtual float GetLightRatio(float objArea, const Vector3& objCenter) const 
	{
		float dist = (m_position - objCenter).length();
		return (objArea / (dist * dist) / (4 * PI));
	}

    //Generate a photon in a direction determined by the light type.
    //For point lights, it's a random direction in either direction.
    virtual Vector3 samplePhotonDirection() const  
    {
        return sampleSphericalDirection();
    }

	virtual Vector3 samplePhotonDirection(Object *pObj) const
    {
		return (pObj->center() - m_position).normalize();
    }
    
    //Sample a position on the surface of the light source.
    //For point lights, it's m_position. For area lights, a random position on the surface should be generated.
    //The parameters can be used to produce a more evenly distributed sampling for area lights.
    virtual Vector3 samplePhotonOrigin(int sampleNumber = 0, int totalSamples = 1) const  
    {
        return m_position;
    }

    virtual void preCalc() {} // use this if you need to

protected:
    Vector3 m_position;
    Vector3 m_color;
    float m_wattage;
};

typedef std::vector<PointLight*> Lights;

#endif // CSE168_POINTLIGHT_H_INCLUDED
