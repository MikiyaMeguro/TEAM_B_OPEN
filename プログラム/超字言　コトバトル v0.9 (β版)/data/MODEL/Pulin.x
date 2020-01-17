xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 42;
 -2.51406;6.18603;1.82657;,
 -4.13171;-0.02905;3.00185;,
 -1.57817;-0.02905;4.85707;,
 -0.96028;6.18603;2.95544;,
 1.57815;-0.02905;4.85707;,
 0.96028;6.18603;2.95544;,
 4.13169;-0.02905;3.00185;,
 2.51405;6.18603;1.82656;,
 5.10703;-0.02905;-0.00000;,
 3.10754;6.18603;-0.00000;,
 4.13169;-0.02905;-3.00185;,
 2.51405;6.18603;-1.82657;,
 1.57816;-0.02905;-4.85707;,
 0.96028;6.18603;-2.95545;,
 -1.57816;-0.02905;-4.85707;,
 -0.96028;6.18603;-2.95545;,
 -4.13169;-0.02905;-3.00185;,
 -2.51405;6.18603;-1.82657;,
 -5.10703;-0.02905;-0.00000;,
 -3.10754;6.18603;-0.00000;,
 -4.13171;-0.02905;3.00185;,
 -0.00000;-0.02905;-0.00000;,
 -1.57817;-0.02905;4.85707;,
 1.57815;-0.02905;4.85707;,
 4.13169;-0.02905;3.00185;,
 5.10703;-0.02905;-0.00000;,
 4.13169;-0.02905;-3.00185;,
 1.57816;-0.02905;-4.85707;,
 -1.57816;-0.02905;-4.85707;,
 -4.13169;-0.02905;-3.00185;,
 -5.10703;-0.02905;-0.00000;,
 -0.00000;6.18603;-0.00000;,
 -2.51406;6.18603;1.82657;,
 -0.96028;6.18603;2.95544;,
 0.96028;6.18603;2.95544;,
 2.51405;6.18603;1.82656;,
 3.10754;6.18603;-0.00000;,
 2.51405;6.18603;-1.82657;,
 0.96028;6.18603;-2.95545;,
 -0.96028;6.18603;-2.95545;,
 -2.51405;6.18603;-1.82657;,
 -3.10754;6.18603;-0.00000;;
 
 30;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;0,19,18,1;,
 3;20,21,22;,
 3;22,21,23;,
 3;23,21,24;,
 3;24,21,25;,
 3;25,21,26;,
 3;26,21,27;,
 3;27,21,28;,
 3;28,21,29;,
 3;29,21,30;,
 3;20,30,21;,
 3;31,32,33;,
 3;31,33,34;,
 3;31,34,35;,
 3;31,35,36;,
 3;31,36,37;,
 3;31,37,38;,
 3;31,38,39;,
 3;31,39,40;,
 3;31,40,41;,
 3;31,41,32;;
 
 MeshMaterialList {
  2;
  30;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Puling.jpg";
   }
  }
 }
 MeshNormals {
  12;
  -0.770142;0.306260;0.559540;,
  -0.294166;0.306258;0.905358;,
  0.294167;0.306258;0.905358;,
  0.770142;0.306259;0.559541;,
  0.951948;0.306259;-0.000000;,
  0.770142;0.306259;-0.559541;,
  0.294166;0.306258;-0.905357;,
  -0.294166;0.306258;-0.905357;,
  -0.770142;0.306259;-0.559541;,
  -0.951948;0.306259;-0.000001;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  30;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;0,9,9,0;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;;
 }
 MeshTextureCoords {
  42;
  0.005469;0.688440;,
  0.008079;0.312491;,
  0.079838;0.312490;,
  0.123759;0.688440;,
  0.235931;0.312496;,
  0.241113;0.688440;,
  0.334180;0.312490;,
  0.342451;0.688440;,
  0.441259;0.312491;,
  0.487500;0.688440;,
  0.582918;0.312491;,
  0.522716;0.688440;,
  0.702598;0.312491;,
  0.695165;0.688440;,
  0.839600;0.312491;,
  0.786198;0.688440;,
  0.934806;0.312491;,
  0.904280;0.688440;,
  0.985608;0.312491;,
  0.985049;0.688440;,
  0.277942;0.065074;,
  0.160313;0.149223;,
  0.205243;0.012368;,
  0.115383;0.012441;,
  0.042684;0.065186;,
  0.014916;0.150537;,
  0.042683;0.235952;,
  0.115382;0.288764;,
  0.205243;0.288764;,
  0.277942;0.235946;,
  0.305710;0.150490;,
  0.909317;0.900398;,
  0.976837;0.952792;,
  0.935107;0.983110;,
  0.883527;0.983110;,
  0.841798;0.952792;,
  0.825858;0.903736;,
  0.841798;0.854680;,
  0.883527;0.824362;,
  0.935107;0.824362;,
  0.976837;0.854680;,
  0.992776;0.903736;;
 }
}
