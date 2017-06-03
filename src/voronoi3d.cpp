/*This cpp file mainly contains function voronoi3d
  
 */

#include"point_sets.h"
#include"Tetrahedron.h"
#include<time.h>




vector<vector<array<Vector3,3>>> PointSets3D::Voronoi3d(Vector3 min, Vector3 max){
	if(!Polytope.empty()) return Polytope;
	if(S.empty()) {printf("no points set input!");return Polytope;}
	if(dln.tetras.empty()) delaunay();

	vector<vector<int>> polyindex;
	vector<int> index;
	for(int i=0;i<S.size();i++) {
		polyindex.push_back( index );
	}
	
	for(int i=0;i<TETRA.size();i++) {
		for(int j=0;j<4;j++)
			polyindex[TETRA[i][j]].push_back(i);
	}
	vector<vector<Vector3>> polyvec;
	vector<Vector3> vec;
	for(int i=0;i<polyindex.size();i++) {
		polyvec.push_back(vec);
		for(int j=0;j<polyindex[i].size();j++)
			polyvec[i].push_back( dln.tetras[polyindex[i][j]].o );
	}
	
	//find out tetrahedron on the convhull
	Vector3 p; vector<int> v; int p_in;
	if(K.empty()) Quick_Hull3D();
	for( int i=0;i<TETRA.size();i++) {
		if(exm_pnts[TETRA[i][0]]+exm_pnts[TETRA[i][1]]+
		   exm_pnts[TETRA[i][2]]+exm_pnts[TETRA[i][3]]>2){ // three points on the convhull
			v.clear();
			for(int j=0;j<4;j++) 
				if(exm_pnts[TETRA[i][j]]) v.push_back(TETRA[i][j]); 
				else p_in = TETRA[i][j];
			Triangle t = Triangle(S[v[0]],S[v[1]],S[v[2]]);
			if(dist_p2plane(S[p_in],S[v[0]],S[v[1]],S[v[2]])>0)
				t = Triangle(S[v[2]],S[v[1]],S[v[0]]);
			printf("%d\n", i);
			if(is_hit(t.o,t.getNormal(),min,max,p))
				for(int j=0;j<3;j++) polyvec[v[j]].push_back(p);
		}
	}
	
	// construct polytope
	vector<array<Vector3,3>> trivec;
	PointSets3D plt; array<Vector3,3> a;
	for(int i=0;i<polyvec.size();i++) {
		Polytope.push_back( trivec );
		plt.set_points( polyvec[i] );
		plt.Quick_Hull3D();
		for(int j=0; j<plt.K.size(); j++) {
			a[0]=polyvec[i][plt.K[j][0]]; 
			a[1]=polyvec[i][plt.K[j][1]]; 
			a[2]=polyvec[i][plt.K[j][2]];
			Polytope[i].push_back( a );
		}
	}
}
	
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

	for(int i=0;i<S.size();i++) S[i].index=i;

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

int voronoi3d_demo() {
	srand((unsigned)time(0));
	//vector<Vector3> s;
	Triangle TT = Triangle(Vector3(0.0f,0.0f,0.0f),Vector3(1.0f,0.0f,0.0f),
		            Vector3(0.0f,1.0f,0.0f));
	printf("center %f %f %f\n",TT.o.X,TT.o.Y,TT.o.Z);
	Vector3 s[8] = {Vector3(0,0,0),Vector3(1,0,0),
		            Vector3(0,1,0),Vector3(0,0,1),
					Vector3(0.3f,0.3f,0.3f),
					Vector3(0.5f,0.5f,0.5f),
					Vector3(0.5f,0.5f,1.5f),
					Vector3(0.3f,0.8f,0.8f)
	                
	};
	//Vector3 v;
	//for(int i=0;i<8;i++) s.push_back( v.Rand_Vector(0,10) );

	PointSets3D PS( s,8 ); 

	// print S
	for(int i=0;i<8;i++) printf("(%f %f %f)\n",s[i].X,s[i].Y,s[i].Z);

	PS.Voronoi3d( Vector3(-1,-1,-1),Vector3(2,2,2) );

	


	return 0;
}