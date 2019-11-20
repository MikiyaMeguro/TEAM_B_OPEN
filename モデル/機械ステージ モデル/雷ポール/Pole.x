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
 20;
 4.72809;0.14483;2.03182;,
 5.01938;0.14483;-1.13533;,
 5.01938;65.16690;-1.13533;,
 4.72809;65.16690;2.03182;,
 3.39343;0.14483;-3.86881;,
 3.39343;65.16690;-3.86881;,
 0.47131;0.14483;-5.12455;,
 0.47131;65.16690;-5.12455;,
 -1.13532;0.14483;-5.01938;,
 -1.13532;65.16690;-5.01938;,
 -3.86881;0.14483;-3.39343;,
 -3.86881;65.16690;-3.39343;,
 -5.12455;0.14483;-0.47132;,
 -5.12455;65.16690;-0.47132;,
 -5.01938;0.14483;1.13532;,
 -5.01938;65.16690;1.13532;,
 -3.39343;0.14483;3.86881;,
 -3.39343;65.16690;3.86881;,
 1.13532;0.14483;5.01938;,
 1.13532;65.16690;5.01938;;
 
 26;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,0,3,19;,
 3;1,0,4;,
 3;0,18,4;,
 3;4,18,6;,
 3;18,16,6;,
 3;6,16,8;,
 3;8,16,10;,
 3;16,14,10;,
 3;14,12,10;,
 3;2,5,3;,
 3;3,5,19;,
 3;5,7,19;,
 3;19,7,17;,
 3;7,9,17;,
 3;9,11,17;,
 3;17,11,15;,
 3;11,13,15;;
 
 MeshMaterialList {
  1;
  26;
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
  0;;
  Material {
   0.567843;0.574118;0.592941;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\iron.jpg";
   }
  }
 }
 MeshNormals {
  12;
  0.975361;0.000000;-0.220617;,
  0.659409;0.000000;-0.751785;,
  0.169433;0.000000;-0.985542;,
  -0.296463;0.000000;-0.955045;,
  -0.751784;0.000000;-0.659410;,
  -0.985542;0.000000;-0.169434;,
  -0.955045;0.000000;0.296462;,
  -0.598392;0.000000;0.801203;,
  0.220614;0.000000;0.975361;,
  0.884948;0.000000;0.465689;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  26;
  4;9,0,0,9;,
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
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
  3;11,11,11;;
 }
 MeshTextureCoords {
  20;
  0.977126;0.986440;,
  0.047874;0.986440;,
  0.047874;0.012620;,
  0.977126;0.012620;,
  0.151124;0.986440;,
  0.151124;0.012620;,
  0.254374;0.986440;,
  0.254374;0.012620;,
  0.305999;0.986440;,
  0.305999;0.012620;,
  0.409250;0.986440;,
  0.409250;0.012620;,
  0.512500;0.986440;,
  0.512500;0.012620;,
  0.564125;0.986440;,
  0.564125;0.012620;,
  0.667375;0.986440;,
  0.667375;0.012620;,
  0.822251;0.986440;,
  0.822251;0.012620;;
 }
}
