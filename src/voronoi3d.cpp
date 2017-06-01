/*This cpp file mainly contains function voronoi3d
  
 */

#include"point_sets.h"
#include"Tetrahedron.h"



/*
vector<vector<array<Vector3,3>>> PointSets3D::Voronoi3d(Vector3 min, Vector3 max){
	if(S.empty()) {printf("no points set input!");return Polytope;}
	if(dln.tetras.empty()) delaunay();

	vector<vector<int>> polyindex;
	polyindex.resize( S.size() );
	for(int i=0;i<TETRA.size();i++) {
		for(int j=0;j<4;j++)
			polyindex[TETRA[i][j]].push_back(i);
	}
	vector<vector<Vector3>> polyvec;
	
	for(int i=0;i<polyindex.size();i++) 
		for(int j=0;j<polyindex[i].size();j++)
			polyvec[i].push_back( dln.tetras[polyindex[i][j]].o );
	
	//find out tetrahedron on the convhull
	if(K.empty()) Quick_Hull3D();
	PointSets3D PLT;
	Polytope.clear();
	PLT.set_points(plt);
		PLT.Quick_Hull3D();
		for(int k=0;k<PLT.K.size();k++) {
			array<Vector3,3> tri={plt[K[k][0]],plt[K[k][1]],plt[K[k][2]]};
			Polytope[i].push_back(tri);
		}
}*/
	
int PointSets3D::get_Biggest_Inscribed_Circle() {
	if(S.empty()) {printf("no points set input!");return 0;}
	if(dln.tetras.empty()) delaunay();

	float max_r = 0.0; int max_id = 0;
	for(int i=0;i<dln.tetras.size();i++)  
		if(dln.tetras[i].r>max_r) {max_r=dln.tetras[i].r;max_id=i;}
	
	return max_id;
}

vector<Tetrahedron> PointSets3D::delaunay() {
	if(S.empty()) {printf("no points set input!");return dln.tetras;}
	if(!dln.tetras.empty()) return dln.tetras;

	dln.SetData( S );

	TETRA.clear();
	for(int i=0;i<dln.tetras.size();i++) {
		TETRA.push_back(dln.tetras[i].getVerticesIndex());
	}

	return dln.tetras;
}






bool PointSets3D::is_hit(Vector3 c,Vector3 n,Vector3 min,Vector3 max,Vector3 &p){
{  
  Vector3 ptOnPlane; //射线与包围盒某面的交点  
  //aabb包围盒最小点坐标 min
  //aabb包围盒最大点坐标 max
    
  Vector3& origin = c; //射线起始点  
  Vector3& dir = n; //方向矢量  
    
  float t;  
    
  //分别判断射线与各面的相交情况  
    
  //判断射线与包围盒x轴方向的面是否有交点  
  if (dir.X != 0.f) //射线x轴方向分量不为0 若射线方向矢量的x轴分量为0，射线不可能经过包围盒朝x轴方向的两个面  
  {  
    /* 
      使用射线与平面相交的公式求交点 
     */  
    if (dir.X > 0)//若射线沿x轴正方向偏移  
      t = (min.X - origin.X) / dir.X;  
    else  //射线沿x轴负方向偏移  
      t = (max.X - origin.X) / dir.X;  
      
    if (t > 0.f) //t>0时则射线与平面相交  
    {  
      ptOnPlane = origin + dir * t; //计算交点坐标  
      //判断交点是否在当前面内  
      if (min.Y < ptOnPlane.Y && ptOnPlane.Y < max.Y && min.Z < ptOnPlane.Z && ptOnPlane.Z < max.Z)  
      {  
        return true; //射线与包围盒有交点  
      }  
    }  
  }  
  //若射线沿y轴方向有分量 判断是否与包围盒y轴方向有交点  
  if (dir.Y != 0.f)  
  {  
    if (dir.Y > 0)  
      t = (min.Y - origin.Y) / dir.Y;  
    else  
      t = (max.Y - origin.Y) / dir.Y;  
      
    if (t > 0.f)  
    {  
      ptOnPlane = origin + dir * t;  
  
      if (min.Z < ptOnPlane.Z && ptOnPlane.Z < max.Z && min.X < ptOnPlane.X && ptOnPlane.X < max.X)  
      {  
        return true;  
      }  
    }  
  }  
    
  //若射线沿z轴方向有分量 判断是否与包围盒y轴方向有交点  
  if (dir.Z != 0.f)  
  {  
    if (dir.Z > 0)  
      t = (min.Z - origin.Z) / dir.Z;  
    else  
      t = (max.Z - origin.Z) / dir.Z;  
      
    if (t > 0.f)  
    {  
      ptOnPlane = origin + dir * t;  
        
      if (min.X < ptOnPlane.X && ptOnPlane.X < max.X && min.Y < ptOnPlane.Y && ptOnPlane.Y < max.Y)  
      {  
        return true;  
      }  
    }  
  }  
    
  return false;  
}  
}