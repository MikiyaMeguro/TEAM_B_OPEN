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
 96;
 3.03755;6.19847;-1.46005;,
 -1.76040;6.19370;-2.86709;,
 -1.78406;11.19324;-2.80335;,
 3.01388;11.19801;-1.39632;,
 3.01388;11.19801;-1.39632;,
 -1.78406;11.19324;-2.80335;,
 -3.19091;11.12542;1.99417;,
 1.60703;11.13020;3.40120;,
 1.60703;11.13020;3.40120;,
 -3.19091;11.12542;1.99417;,
 -3.16724;6.12589;1.93043;,
 1.63070;6.13066;3.33746;,
 1.63070;6.13066;3.33746;,
 -3.16724;6.12589;1.93043;,
 -1.76040;6.19370;-2.86709;,
 3.03755;6.19847;-1.46005;,
 -1.76040;6.19370;-2.86709;,
 -3.16724;6.12589;1.93043;,
 -3.19091;11.12542;1.99417;,
 -1.78406;11.19324;-2.80335;,
 1.63070;6.13066;3.33746;,
 3.03755;6.19847;-1.46005;,
 3.01388;11.19801;-1.39632;,
 1.60703;11.13020;3.40120;,
 5.25836;0.86326;-1.75976;,
 0.25836;0.86326;-1.75976;,
 0.25836;5.86326;-1.75976;,
 5.25836;5.86326;-1.75976;,
 5.25836;5.86326;-1.75976;,
 0.25836;5.86326;-1.75976;,
 0.25836;5.86326;3.24024;,
 5.25836;5.86326;3.24024;,
 5.25836;5.86326;3.24024;,
 0.25836;5.86326;3.24024;,
 0.25836;0.86326;3.24024;,
 5.25836;0.86326;3.24024;,
 5.25836;0.86326;3.24024;,
 0.25836;0.86326;3.24024;,
 0.25836;0.86326;-1.75976;,
 5.25836;0.86326;-1.75976;,
 0.25836;0.86326;-1.75976;,
 0.25836;0.86326;3.24024;,
 0.25836;5.86326;3.24024;,
 0.25836;5.86326;-1.75976;,
 5.25836;0.86326;3.24024;,
 5.25836;0.86326;-1.75976;,
 5.25836;5.86326;-1.75976;,
 5.25836;5.86326;3.24024;,
 -0.36851;0.86326;0.81107;,
 -5.36851;0.86326;0.81107;,
 -5.36851;5.86326;0.81107;,
 -0.36851;5.86326;0.81107;,
 -0.36851;5.86326;0.81107;,
 -5.36851;5.86326;0.81107;,
 -5.36851;5.86326;5.81107;,
 -0.36851;5.86326;5.81107;,
 -0.36851;5.86326;5.81107;,
 -5.36851;5.86326;5.81107;,
 -5.36851;0.86326;5.81107;,
 -0.36851;0.86326;5.81107;,
 -0.36851;0.86326;5.81107;,
 -5.36851;0.86326;5.81107;,
 -5.36851;0.86326;0.81107;,
 -0.36851;0.86326;0.81107;,
 -5.36851;0.86326;0.81107;,
 -5.36851;0.86326;5.81107;,
 -5.36851;5.86326;5.81107;,
 -5.36851;5.86326;0.81107;,
 -0.36851;0.86326;5.81107;,
 -0.36851;0.86326;0.81107;,
 -0.36851;5.86326;0.81107;,
 -0.36851;5.86326;5.81107;,
 -0.15646;0.86326;-5.30167;,
 -5.15645;0.86326;-5.30167;,
 -5.15645;5.86326;-5.30167;,
 -0.15646;5.86326;-5.30167;,
 -0.15646;5.86326;-5.30167;,
 -5.15645;5.86326;-5.30167;,
 -5.15645;5.86326;-0.30167;,
 -0.15646;5.86326;-0.30167;,
 -0.15646;5.86326;-0.30167;,
 -5.15645;5.86326;-0.30167;,
 -5.15645;0.86326;-0.30167;,
 -0.15646;0.86326;-0.30167;,
 -0.15646;0.86326;-0.30167;,
 -5.15645;0.86326;-0.30167;,
 -5.15645;0.86326;-5.30167;,
 -0.15646;0.86326;-5.30167;,
 -5.15645;0.86326;-5.30167;,
 -5.15645;0.86326;-0.30167;,
 -5.15645;5.86326;-0.30167;,
 -5.15645;5.86326;-5.30167;,
 -0.15646;0.86326;-0.30167;,
 -0.15646;0.86326;-5.30167;,
 -0.15646;5.86326;-5.30167;,
 -0.15646;5.86326;-0.30167;;
 
 24;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;;
 
 MeshMaterialList {
  1;
  24;
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
   0.750000;0.750000;0.750000;1.000000;;
   25.000000;
   0.450000;0.450000;0.450000;;
   0.100000;0.100000;0.100000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Xarame2.jpg";
   }
  }
 }
 MeshNormals {
  12;
  0.281368;0.013563;-0.959504;,
  -0.004734;0.999908;0.012747;,
  -0.281368;-0.013563;0.959504;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.004733;-0.999908;-0.012746;,
  -0.959588;-0.000955;-0.281407;,
  0.959588;0.000955;0.281407;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  24;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;;
 }
 MeshTextureCoords {
  96;
  0.531827;0.473241;,
  0.559647;0.473241;,
  0.559647;0.501061;,
  0.531827;0.501061;,
  0.531827;0.473148;,
  0.559647;0.473148;,
  0.559647;0.500968;,
  0.531827;0.500968;,
  0.531827;0.473096;,
  0.559647;0.473096;,
  0.559647;0.500916;,
  0.531827;0.500916;,
  0.531827;0.473044;,
  0.559647;0.473044;,
  0.559647;0.500864;,
  0.531827;0.500864;,
  0.531775;0.473066;,
  0.559595;0.473066;,
  0.559595;0.500886;,
  0.531775;0.500886;,
  0.531879;0.472715;,
  0.559699;0.472715;,
  0.559699;0.500535;,
  0.531879;0.500535;,
  0.531827;0.472715;,
  0.559647;0.472715;,
  0.559647;0.500535;,
  0.531827;0.500535;,
  0.531827;0.473148;,
  0.559647;0.473148;,
  0.559647;0.500968;,
  0.531827;0.500968;,
  0.531827;0.473096;,
  0.559647;0.473096;,
  0.559647;0.500916;,
  0.531827;0.500916;,
  0.531827;0.473044;,
  0.559647;0.473044;,
  0.559647;0.500864;,
  0.531827;0.500864;,
  0.531775;0.473241;,
  0.559595;0.473241;,
  0.559595;0.501061;,
  0.531775;0.501061;,
  0.531879;0.472715;,
  0.559699;0.472715;,
  0.559699;0.500535;,
  0.531879;0.500535;,
  0.531827;0.472715;,
  0.559647;0.472715;,
  0.559647;0.500535;,
  0.531827;0.500535;,
  0.531827;0.472906;,
  0.559647;0.472906;,
  0.559647;0.500726;,
  0.531827;0.500726;,
  0.531827;0.473096;,
  0.559647;0.473096;,
  0.559647;0.500916;,
  0.531827;0.500916;,
  0.531827;0.473044;,
  0.559647;0.473044;,
  0.559647;0.500864;,
  0.531827;0.500864;,
  0.531775;0.473241;,
  0.559595;0.473241;,
  0.559595;0.501061;,
  0.531775;0.501061;,
  0.531879;0.472715;,
  0.559699;0.472715;,
  0.559699;0.500535;,
  0.531879;0.500535;,
  0.531827;0.472715;,
  0.559647;0.472715;,
  0.559647;0.500535;,
  0.531827;0.500535;,
  0.531827;0.473148;,
  0.559647;0.473148;,
  0.559647;0.500968;,
  0.531827;0.500968;,
  0.531827;0.473096;,
  0.559647;0.473096;,
  0.559647;0.500916;,
  0.531827;0.500916;,
  0.531827;0.473044;,
  0.559647;0.473044;,
  0.559647;0.500864;,
  0.531827;0.500864;,
  0.531775;0.472715;,
  0.559595;0.472715;,
  0.559595;0.500535;,
  0.531775;0.500535;,
  0.531879;0.472715;,
  0.559699;0.472715;,
  0.559699;0.500535;,
  0.531879;0.500535;;
 }
}
