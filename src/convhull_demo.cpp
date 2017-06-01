# include<iostream>
# include<stdio.h>
# include<stdlib.h>
# include<vector>
# include<array>
# include"Vector3.h"
# include<time.h>
# include"point_sets.h"

using namespace std;

int convhull_demo() {
	srand((unsigned)time(0));
	vector<Vector3> s;
	/*Vector3 s[6] = {Vector3(0,0,0),Vector3(1,0,0),
		            Vector3(1,1,0),Vector3(0,1,0),
					Vector3(0.5f,0.5f,0.5f),
	                Vector3(0.5f,0.5f,-0.5f),
	};*/
	Vector3 v;
	for(int i=0;i<8;i++) s.push_back( v.Rand_Vector(0,10) );

	PointSets3D PS( s ); 

    vector<array<int,3>>K = PS.Quick_Hull3D();

	// print K
	printf("%d\n", K.size());
	for( int i=0; i<K.size(); i++ ) {
		printf("Facet <%d, %d, %d>\n", K[i][0], K[i][1], K[i][2] );
	}



	return 0;
}