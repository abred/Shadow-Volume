#version 410

layout (triangles_adjacency) in;
layout (triangle_strip) out;
layout (max_vertices = 18) out;


uniform mat4 projectionMatrix;


uniform vec3 lightPos;	// Light position, eye space
uniform int zPass;

//in vec4 passNormal[];

void main()	
{	
	vec3 normals[3];	// Normals	
	vec3 lightDir[3];	// Vertex -> Light Direction
	vec4 vertexTemp[4];	// Temp
			   
	// gl_in: 0,2,4 "real" triangle, other (adjacent): 012, 234, 450	
	// Compute normal at each vertex.	
	normals[0] = cross(	
		gl_in[4].gl_Position.xyz - gl_in[0].gl_Position.xyz,	
		gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz );	
	normals[1] = cross(	
		gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz,	
		gl_in[4].gl_Position.xyz - gl_in[2].gl_Position.xyz );	
	normals[2] = cross(	
		gl_in[2].gl_Position.xyz - gl_in[4].gl_Position.xyz,	
		gl_in[0].gl_Position.xyz - gl_in[4].gl_Position.xyz );
//	normals[0] = passNormal[0];
//	normals[1] = passNormal[2];
//	normals[2] = passNormal[4];
			
	// Compute direction from vertices to light.	
	lightDir[0] = lightPos - gl_in[0].gl_Position.xyz;	
	lightDir[1] = lightPos - gl_in[2].gl_Position.xyz;	
	lightDir[2] = lightPos - gl_in[4].gl_Position.xyz;	
	
	// Check if the main triangle faces the light.	
//	bool facesLight = true;
	
	if ( !(dot(normals[0], lightDir[0]) > 0 || 
	       dot(normals[1], lightDir[1]) > 0 ||	
	       dot(normals[2], lightDir[2]) > 0) ) 
	{	
		return;
	}	

	// Render caps. z-fail
	if ( zPass == 0 ) {
	 	//start near cap
		 	gl_Position = projectionMatrix * gl_in[0].gl_Position;
//		 	gl_Position.y += 20;
		 	EmitVertex();
		 	gl_Position = projectionMatrix * gl_in[2].gl_Position;
//		 	gl_Position.y += 20;
		 	EmitVertex();
		 	gl_Position = projectionMatrix * gl_in[4].gl_Position;
//		 	gl_Position.y += 20;
		 	EmitVertex(); 
	 	EndPrimitive();
	 	
	 	//start far cap
	 	vertexTemp[0] = vec4(gl_in[0].gl_Position.xyz - lightPos, 0);
	 	vertexTemp[1] = vec4(gl_in[2].gl_Position.xyz - lightPos, 0);
	 	vertexTemp[2] = vec4(gl_in[4].gl_Position.xyz - lightPos, 0);
	 	
//	 	vertexTemp[0] = gl_in[0].gl_Position + 1000*vec4(gl_in[0].gl_Position.xyz - lightPos, 0);
//	 	vertexTemp[1] = gl_in[4].gl_Position + 1000*vec4(gl_in[4].gl_Position.xyz - lightPos, 0);
//	 	vertexTemp[2] = gl_in[2].gl_Position + 1000*vec4(gl_in[2].gl_Position.xyz - lightPos, 0);

		 	gl_Position = projectionMatrix * vertexTemp[0];
		 	EmitVertex();
		 	gl_Position = projectionMatrix * vertexTemp[1];
		 	EmitVertex();
		 	gl_Position = projectionMatrix * vertexTemp[2];
		 	EmitVertex(); 
	 	EndPrimitive();
	}	

	// extrude edges (if neccessary)
	for (int i = 0; i < 3; i++)
	{	
		// Compute indices of adjacent triangle.	
		int vA    =  i*2;	
		int vBAdj = (i*2 + 1);	
		int vC    = (i*2 +2) % 6;	
		// Compute normals at vertices, same way as above
		normals[0] = cross(	
			gl_in[vC].gl_Position.xyz-gl_in[vA].gl_Position.xyz,
			gl_in[vBAdj].gl_Position.xyz-gl_in[vA].gl_Position.xyz);
		normals[1] = cross(	
			gl_in[vA].gl_Position.xyz-gl_in[vBAdj].gl_Position.xyz,
			gl_in[vC].gl_Position.xyz-gl_in[vBAdj].gl_Position.xyz);
		normals[2] = cross(
			gl_in[vBAdj].gl_Position.xyz-gl_in[vC].gl_Position.xyz,
			gl_in[vA].gl_Position.xyz-gl_in[vC].gl_Position.xyz);
//		normals[0] = passNormal[vA];
//		normals[1] = passNormal[VBAdj];
//		normals[2] = passNormal[vC];
			
		// Compute direction to light, same way as above.	
		lightDir[0] = lightPos - gl_in[vA].gl_Position.xyz;	
		lightDir[1] = lightPos - gl_in[vBAdj].gl_Position.xyz;	
		lightDir[2] = lightPos - gl_in[vC].gl_Position.xyz;

		// Extrude the edge if it's a part of the silhouette.	
		if (!(dot(normals[0], lightDir[0]) > 0 || 
		      dot(normals[1], lightDir[1]) > 0 || 
		      dot(normals[2], lightDir[2]) > 0) )	
		{	
			vertexTemp[0] = gl_in[vA].gl_Position;	
			vertexTemp[1] = vec4(gl_in[vA].gl_Position.xyz - lightPos, 0);	
			vertexTemp[2] = gl_in[vC].gl_Position;	
			vertexTemp[3] = vec4(gl_in[vC].gl_Position.xyz - lightPos, 0);	
			
			// emit extruded edge (triangle strip)
				gl_Position = projectionMatrix * vertexTemp[0];	
				EmitVertex();	
				gl_Position = projectionMatrix * vertexTemp[1];	
				EmitVertex();	
				gl_Position = projectionMatrix * vertexTemp[2];	
				EmitVertex();	
				gl_Position = projectionMatrix * vertexTemp[3];	
				EmitVertex();	
			EndPrimitive();	
		}	
	}	
}	




