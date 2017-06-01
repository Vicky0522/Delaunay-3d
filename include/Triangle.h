/**
 * Triangle class
 *
 * @author Ruilong Li
 */
#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Line.h"
#include <vector>
using namespace std;

class Triangle {
public:
    Vector3 v1, v2, v3;
    Triangle(Vector3 v1, Vector3 v2, Vector3 v3) {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    Vector3 getNormal() {
        Vector3 edge1 = Vector3(v2.X-v1.X, v2.Y-v1.Y, v2.Z-v1.Z);
        Vector3 edge2 = Vector3(v3.X-v1.X, v3.Y-v1.Y, v3.Z-v1.Z);

        Vector3 normal = edge1.cross(edge2);
        normal.Normalize();
        return normal;
    }
	Vector3 getCentre() {
		Vector3 c1 = (v1+v2)*0.5f;
		Vector3 c2 = (v2+v3)*0.5f;
		Vector3 c3 = (v1+v3)*0.5f;

		Vector3 l1 = v2-v1;
		Vector3 l2 = v3-v2;
		Vector3 l3 = v1-v3;
		
		float c1l1 = c1.dot(l1);
		float c2l2 = c2.dot(l2);
		float c3l3 = c3.dot(l3);

		float D = l1.X*(l2.Y*l3.Z-l2.Z*l3.Y)-
			      l1.Y*(l2.X*l3.Z-l2.Z*l3.X)+
				  l1.Z*(l2.X*l3.Y-l2.Y*l3.X);

		float Dx= c1l1*(l2.Y*l3.Z-l2.Z*l3.Y)-
			      l1.Y*(c2l2*l3.Z-l2.Z*c3l3)+
				  l1.Z*(c2l2*l3.Y-l2.Y*c3l3);

		float Dy= l1.X*(c2l2*l3.Z-l2.Z*c3l3)-
			      c1l1*(l2.X*l3.Z-l2.Z*l3.X)+
				  l1.Z*(l2.X*c3l3-c2l2*l3.X);

		float Dz= l1.X*(l2.Y*c3l3-c2l2*l3.Y)-
			      l1.Y*(l2.X*c3l3-c2l2*l3.X)+
				  c1l1*(l2.X*l3.Y-l2.Y*l3.X);

		return Vector3(Dx/D,Dy/D,Dz/D);
	}
	
    void turnBack() {
        Vector3 tmp = this->v3;
        this->v3 = this->v1;
        this->v1 = tmp;
    }

    vector<Line> getLines() {
        vector<Line> l;
        l.push_back(Line(v1, v2));
        l.push_back(Line(v2, v3));
        l.push_back(Line(v3, v1));
        return l;
    }

    bool equals(Triangle t) {
        vector<Line> lines1 = this->getLines();
        vector<Line> lines2 = t.getLines();

        int cnt = 0;
        for(int i = 0; i < lines1.size(); i++) {
            for(int j = 0; j < lines2.size(); j++) {
                if (lines1[i].equals(lines2[j]))
                    cnt++;
            }
        }
        if (cnt == 3) return true;
        else return false;
    }
};
#endif