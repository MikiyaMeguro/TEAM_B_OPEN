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
 24;
 19.96490;0.14426;-2.37702;,
 -19.96490;0.14426;-2.37702;,
 -19.96490;40.07405;-2.37702;,
 19.96490;40.07405;-2.37702;,
 19.96490;40.07405;-2.37702;,
 -19.96490;40.07405;-2.37702;,
 -19.96490;40.07405;2.37702;,
 19.96490;40.07405;2.37702;,
 19.96490;40.07405;2.37702;,
 -19.96490;40.07405;2.37702;,
 -19.96490;0.14426;2.37702;,
 19.96490;0.14426;2.37702;,
 19.96490;0.14426;2.37702;,
 -19.96490;0.14426;2.37702;,
 -19.96490;0.14426;-2.37702;,
 19.96490;0.14426;-2.37702;,
 -19.96490;0.14426;-2.37702;,
 -19.96490;0.14426;2.37702;,
 -19.96490;40.07405;2.37702;,
 -19.96490;40.07405;-2.37702;,
 19.96490;0.14426;2.37702;,
 19.96490;0.14426;-2.37702;,
 19.96490;40.07405;-2.37702;,
 19.96490;40.07405;2.37702;;
 
 6;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;;
 
 MeshMaterialList {
  1;
  6;
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Nazca.jpg";
   }
  }
 }
 MeshNormals {
  6;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  6;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  24;
  0.006526;1.000068;,
  0.993474;1.000068;,
  0.993474;0.013120;,
  0.006526;0.013120;,
  0.428213;0.937502;,
  0.571787;0.937502;,
  0.571787;0.793928;,
  0.428213;0.793928;,
  0.007530;1.014307;,
  0.992470;1.014307;,
  0.992470;0.029367;,
  0.007530;0.029367;,
  0.183687;0.298790;,
  0.263005;0.298790;,
  0.263005;0.219472;,
  0.183687;0.219472;,
  0.686245;0.936990;,
  0.813755;0.936990;,
  0.813755;0.809480;,
  0.686245;0.809480;,
  0.174935;0.276819;,
  0.325065;0.276819;,
  0.325065;0.126688;,
  0.174935;0.126688;;
 }
}
