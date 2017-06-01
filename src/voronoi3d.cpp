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
  Vector3 ptOnPlane; //�������Χ��ĳ��Ľ���  
  //aabb��Χ����С������ min
  //aabb��Χ���������� max
    
  Vector3& origin = c; //������ʼ��  
  Vector3& dir = n; //����ʸ��  
    
  float t;  
    
  //�ֱ��ж������������ཻ���  
    
  //�ж��������Χ��x�᷽������Ƿ��н���  
  if (dir.X != 0.f) //����x�᷽�������Ϊ0 �����߷���ʸ����x�����Ϊ0�����߲����ܾ�����Χ�г�x�᷽���������  
  {  
    /* 
      ʹ��������ƽ���ཻ�Ĺ�ʽ�󽻵� 
     */  
    if (dir.X > 0)//��������x��������ƫ��  
      t = (min.X - origin.X) / dir.X;  
    else  //������x�Ḻ����ƫ��  
      t = (max.X - origin.X) / dir.X;  
      
    if (t > 0.f) //t>0ʱ��������ƽ���ཻ  
    {  
      ptOnPlane = origin + dir * t; //���㽻������  
      //�жϽ����Ƿ��ڵ�ǰ����  
      if (min.Y < ptOnPlane.Y && ptOnPlane.Y < max.Y && min.Z < ptOnPlane.Z && ptOnPlane.Z < max.Z)  
      {  
        return true; //�������Χ���н���  
      }  
    }  
  }  
  //��������y�᷽���з��� �ж��Ƿ����Χ��y�᷽���н���  
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
    
  //��������z�᷽���з��� �ж��Ƿ����Χ��y�᷽���н���  
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