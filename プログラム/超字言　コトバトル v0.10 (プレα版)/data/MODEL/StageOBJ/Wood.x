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
 62;
 -4.71562;40.07341;3.42609;,
 -4.71562;0.00572;3.42609;,
 -1.80121;0.00572;5.54354;,
 -1.80121;40.07341;5.54354;,
 1.80121;0.00572;5.54353;,
 1.80121;40.07341;5.54353;,
 4.71562;0.00572;3.42609;,
 4.71562;40.07341;3.42609;,
 5.82882;0.00572;0.00000;,
 5.82882;40.07341;0.00000;,
 4.71562;0.00572;-3.42609;,
 4.71562;40.07341;-3.42609;,
 1.80121;0.00572;-5.54353;,
 1.80121;40.07341;-5.54353;,
 -1.80121;0.00572;-5.54353;,
 -1.80121;40.07341;-5.54353;,
 -4.71562;0.00572;-3.42609;,
 -4.71562;40.07341;-3.42609;,
 -5.82882;0.00572;0.00000;,
 -5.82882;40.07341;0.00000;,
 5.82882;0.00572;0.00000;,
 4.71562;0.00572;3.42609;,
 4.71562;0.00572;-3.42609;,
 1.80121;0.00572;5.54353;,
 1.80121;0.00572;-5.54353;,
 -1.80121;0.00572;5.54354;,
 -1.80121;0.00572;-5.54353;,
 -4.71562;0.00572;3.42609;,
 -4.71562;0.00572;-3.42609;,
 -5.82882;0.00572;0.00000;,
 5.82882;40.07341;0.00000;,
 4.71562;40.07341;-3.42609;,
 4.71562;40.07341;3.42609;,
 1.80121;40.07341;-5.54353;,
 1.80121;40.07341;5.54353;,
 -1.80121;40.07341;-5.54353;,
 -1.80121;40.07341;5.54354;,
 -4.71562;40.07341;-3.42609;,
 -4.71562;40.07341;3.42609;,
 -5.82882;40.07341;0.00000;,
 19.11263;23.04240;-6.21008;,
 19.11263;23.04240;6.21008;,
 11.81226;23.04240;-16.25817;,
 11.81227;23.04240;16.25817;,
 0.00000;23.04240;20.09621;,
 0.00000;23.04240;-20.09621;,
 -11.81227;23.04240;16.25819;,
 -11.81226;23.04240;-16.25816;,
 -19.11263;23.04240;-6.21008;,
 -19.11264;23.04240;6.21008;,
 0.00000;70.42557;0.00000;,
 -19.11264;23.04240;6.21008;,
 -11.81227;23.04240;16.25819;,
 0.00000;23.04240;20.09621;,
 11.81227;23.04240;16.25817;,
 19.11263;23.04240;6.21008;,
 19.11263;23.04240;-6.21008;,
 11.81226;23.04240;-16.25817;,
 0.00000;23.04240;-20.09621;,
 -11.81226;23.04240;-16.25816;,
 -19.11263;23.04240;-6.21008;,
 -19.11264;23.04240;6.21008;;
 
 44;
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
 3;21,23,22;,
 3;22,23,24;,
 3;23,25,24;,
 3;24,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;27,29,28;,
 3;30,31,32;,
 3;31,33,32;,
 3;32,33,34;,
 3;33,35,34;,
 3;34,35,36;,
 3;35,37,36;,
 3;36,37,38;,
 3;37,39,38;,
 3;40,41,42;,
 3;41,43,42;,
 3;43,44,42;,
 3;42,44,45;,
 3;44,46,45;,
 3;45,46,47;,
 3;47,46,48;,
 3;46,49,48;,
 3;50,51,52;,
 3;50,52,53;,
 3;50,53,54;,
 3;50,54,55;,
 3;50,55,56;,
 3;50,56,57;,
 3;50,57,58;,
 3;50,58,59;,
 3;50,59,60;,
 3;50,60,61;;
 
 MeshMaterialList {
  2;
  44;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   TextureFilename {
    "data\\TEXTURE\\UVWood.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   14.000000;
   0.110000;0.110000;0.110000;;
   0.060000;0.060000;0.060000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Leaf.jpg";
   }
  }
 }
 MeshNormals {
  26;
  -0.809018;0.000000;0.587784;,
  -0.309016;0.000000;0.951057;,
  0.309018;0.000000;0.951056;,
  0.809017;0.000000;0.587785;,
  1.000000;0.000000;0.000000;,
  0.809017;0.000000;-0.587785;,
  0.309017;0.000000;-0.951057;,
  -0.309017;0.000000;-0.951057;,
  -0.809017;0.000000;-0.587785;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.280502;0.419563;0.863299;,
  0.000000;1.000000;0.000000;,
  -0.875563;0.390456;0.284487;,
  -0.541127;0.390456;0.744799;,
  0.000000;0.390455;0.920622;,
  0.541128;0.390455;0.744799;,
  0.907726;0.419563;-0.000000;,
  0.875564;0.390455;0.284488;,
  0.875563;0.390455;-0.284488;,
  0.541128;0.390455;-0.744799;,
  -0.280503;0.419563;-0.863299;,
  -0.000000;0.390455;-0.920622;,
  -0.541128;0.390455;-0.744799;,
  -0.875563;0.390455;-0.284489;,
  -0.927397;0.374078;-0.000001;;
  44;
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
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;11,13,14;,
  3;11,14,15;,
  3;11,15,16;,
  3;17,16,18;,
  3;17,18,19;,
  3;17,19,20;,
  3;21,20,22;,
  3;21,22,23;,
  3;21,23,24;,
  3;25,24,13;;
 }
 MeshTextureCoords {
  62;
  0.385840;0.998570;,
  0.385840;0.622630;,
  0.410840;0.622630;,
  0.410840;0.998570;,
  0.435840;0.622630;,
  0.435840;0.998570;,
  0.460840;0.622630;,
  0.460840;0.998570;,
  0.485840;0.622630;,
  0.485840;0.998570;,
  0.510840;0.622630;,
  0.510840;0.998570;,
  0.535840;0.622630;,
  0.535840;0.998570;,
  0.560840;0.622630;,
  0.560840;0.998570;,
  0.585840;0.622630;,
  0.585840;0.998570;,
  0.610840;0.622630;,
  0.610840;0.998570;,
  0.342090;0.666660;,
  0.371930;0.574820;,
  0.371930;0.758500;,
  0.450050;0.518060;,
  0.450050;0.815260;,
  0.546620;0.518060;,
  0.546620;0.815260;,
  0.624750;0.574820;,
  0.624750;0.758500;,
  0.654590;0.666660;,
  0.342090;0.852740;,
  0.371930;0.760900;,
  0.371930;0.944580;,
  0.450050;0.704140;,
  0.450050;1.001340;,
  0.546620;0.704140;,
  0.546620;1.001340;,
  0.624750;0.760900;,
  0.624750;0.944580;,
  0.654590;0.852740;,
  0.304190;0.292480;,
  0.304190;0.165230;,
  0.378980;0.395420;,
  0.378980;0.062290;,
  0.500000;0.022960;,
  0.500000;0.434740;,
  0.621020;0.062290;,
  0.621020;0.395420;,
  0.695810;0.292480;,
  0.695810;0.165230;,
  0.500000;0.430560;,
  0.250000;-0.001260;,
  0.300000;-0.001260;,
  0.350000;-0.001260;,
  0.400000;-0.001260;,
  0.450000;-0.001260;,
  0.500000;-0.001260;,
  0.550000;-0.001260;,
  0.600000;-0.001260;,
  0.650000;-0.001260;,
  0.700000;-0.001260;,
  0.750000;-0.001260;;
 }
}
