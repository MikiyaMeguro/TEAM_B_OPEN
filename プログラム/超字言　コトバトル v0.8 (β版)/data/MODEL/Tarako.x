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
 74;
 -3.42824;2.96449;-0.96481;,
 -3.42824;0.61901;-0.96481;,
 -4.45461;1.20676;-0.96481;,
 -5.02485;2.51913;-0.96481;,
 -3.42824;2.96449;0.96481;,
 -3.42824;3.36311;0.01280;,
 -4.55201;3.11747;0.01280;,
 -5.02485;2.51913;0.96481;,
 -3.42824;0.61901;0.96481;,
 -3.42824;2.96449;0.96481;,
 -5.02485;2.51913;0.96481;,
 -4.28126;1.46521;0.96481;,
 -3.42824;0.22039;0.01280;,
 -3.42824;0.61901;0.96481;,
 -4.28126;1.46521;0.96481;,
 -4.15058;0.58417;0.01280;,
 -4.55201;3.11747;0.01280;,
 -5.25787;2.56077;0.01280;,
 -5.02485;2.51913;0.96481;,
 5.51931;0.99541;0.96481;,
 5.34945;0.69670;0.01280;,
 6.16362;1.80660;0.01280;,
 5.51931;1.82045;1.09058;,
 -3.42824;0.61901;-0.96481;,
 -4.45461;1.20676;-0.96481;,
 5.71634;2.76787;0.01280;,
 6.16362;1.80660;0.01280;,
 5.51931;1.79237;-1.09058;,
 5.51931;2.58809;-0.96481;,
 0.06467;0.44555;-0.96481;,
 0.06467;-0.01202;0.01280;,
 -3.42824;0.22039;0.01280;,
 -3.42824;0.61901;-0.96481;,
 0.06467;0.44555;0.96481;,
 -3.42824;0.61901;0.96481;,
 0.06467;0.44555;0.96481;,
 0.06467;3.13795;0.96481;,
 -3.42824;2.96449;0.96481;,
 -3.42824;0.61901;0.96481;,
 0.06467;3.13795;0.96481;,
 0.06467;3.59552;0.01280;,
 0.06467;3.13795;-0.96481;,
 0.06467;3.13795;-0.96481;,
 0.06467;0.44555;-0.96481;,
 -3.42824;0.61901;-0.96481;,
 -3.42824;2.96449;-0.96481;,
 3.50294;0.64738;-0.96481;,
 3.50294;0.25840;0.01280;,
 3.50294;0.64738;0.96481;,
 3.50294;0.64738;0.96481;,
 3.50294;2.93612;0.96481;,
 3.50294;2.93612;0.96481;,
 3.50294;3.32509;0.01280;,
 3.50294;2.93612;-0.96481;,
 3.50294;2.93612;-0.96481;,
 3.50294;0.64738;-0.96481;,
 5.34945;0.69670;0.01280;,
 5.51931;0.99541;-0.96481;,
 5.51931;0.99541;0.96481;,
 5.51931;1.82045;1.09058;,
 5.51931;2.58809;0.96481;,
 5.51931;0.99541;0.96481;,
 3.50294;2.93612;0.96481;,
 3.50294;0.64738;0.96481;,
 5.71634;2.76787;0.01280;,
 5.51931;2.58809;0.96481;,
 3.50294;0.64738;-0.96481;,
 5.51931;0.99541;-0.96481;,
 -4.15058;0.58417;0.01280;,
 -4.28126;1.46521;0.96481;,
 5.51931;1.82045;1.09058;,
 5.51931;2.58809;0.96481;,
 5.51931;1.79237;-1.09058;,
 5.51931;0.99541;-0.96481;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 3;16,17,18;,
 4;19,20,21,22;,
 4;5,0,3,6;,
 3;3,17,16;,
 4;23,12,15,24;,
 4;25,26,27,28;,
 4;29,30,31,32;,
 4;30,33,34,31;,
 4;35,36,37,38;,
 4;39,40,5,4;,
 4;40,41,0,5;,
 4;42,43,44,45;,
 4;46,47,30,29;,
 4;47,48,33,30;,
 4;49,50,36,35;,
 4;51,52,40,39;,
 4;52,53,41,40;,
 4;54,55,43,42;,
 4;56,47,46,57;,
 4;58,48,47,56;,
 3;59,60,61;,
 3;60,62,61;,
 3;62,63,61;,
 4;64,52,51,65;,
 4;28,53,52,64;,
 3;53,28,66;,
 3;66,28,67;,
 3;28,27,67;,
 4;2,68,17,3;,
 4;18,17,68,69;,
 4;70,26,25,71;,
 4;72,21,20,73;;
 
 MeshMaterialList {
  1;
  36;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Tarako.jpg";
   }
  }
 }
 MeshNormals {
  42;
  0.604403;-0.721910;-0.336962;,
  0.000000;0.000000;-1.000000;,
  0.622766;0.678353;-0.389872;,
  -1.000000;0.000000;0.000000;,
  -0.426136;0.853116;0.300999;,
  0.602494;-0.719922;0.344548;,
  0.000000;0.000000;1.000000;,
  0.802969;0.584388;-0.117179;,
  -0.446699;0.894677;0.003637;,
  -0.726995;-0.684608;0.052827;,
  0.760943;-0.636398;0.126347;,
  -0.301966;-0.953066;0.021920;,
  -0.137140;0.902812;0.407583;,
  -0.150180;0.988647;0.004895;,
  0.004870;-0.916977;-0.398910;,
  0.005312;-0.999974;0.004893;,
  0.004851;-0.913032;0.407858;,
  0.005312;0.999974;0.004893;,
  0.004870;0.916978;-0.398908;,
  0.126817;-0.926155;-0.355183;,
  0.135680;-0.990743;0.004410;,
  0.126422;-0.923007;0.363423;,
  0.140037;0.990137;0.004295;,
  0.131317;0.928778;-0.346593;,
  -0.619254;0.785187;0.002355;,
  0.933264;-0.056629;-0.354698;,
  0.930616;-0.055708;0.361734;,
  0.998182;-0.060161;0.003719;,
  -0.298342;-0.851588;0.431034;,
  -0.686721;-0.641322;0.342227;,
  -0.137734;0.906707;-0.398637;,
  -0.426809;0.855219;-0.293997;,
  -0.252879;-0.887102;-0.386137;,
  -0.702002;-0.666604;-0.250662;,
  0.004851;0.913033;0.407856;,
  0.130975;0.925778;0.354656;,
  0.190100;-0.930838;-0.312094;,
  0.198464;0.932552;0.301593;,
  0.619611;0.676994;0.397193;,
  -0.870218;-0.488503;0.063924;,
  -0.889320;-0.441447;-0.119313;,
  -0.819653;-0.517898;0.244849;;
  36;
  4;1,1,1,1;,
  4;12,13,8,4;,
  4;6,6,6,6;,
  4;11,28,29,9;,
  3;8,24,4;,
  4;5,10,27,26;,
  4;13,30,31,8;,
  3;31,24,8;,
  4;32,11,9,33;,
  4;7,27,25,2;,
  4;14,15,11,32;,
  4;15,16,28,11;,
  4;6,6,6,6;,
  4;34,17,13,12;,
  4;17,18,30,13;,
  4;1,1,1,1;,
  4;19,20,15,14;,
  4;20,21,16,15;,
  4;6,6,6,6;,
  4;35,22,17,34;,
  4;22,23,18,17;,
  4;1,1,1,1;,
  4;36,20,19,0;,
  4;5,21,20,10;,
  3;3,3,3;,
  3;6,6,6;,
  3;6,6,6;,
  4;37,22,35,38;,
  4;2,23,22,7;,
  3;1,1,1;,
  3;1,1,1;,
  3;3,3,3;,
  4;33,9,39,40;,
  4;41,39,9,29;,
  4;26,27,7,38;,
  4;25,27,10,0;;
 }
 MeshTextureCoords {
  74;
  0.589735;0.250000;,
  0.589735;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.589735;0.500000;,
  0.589735;0.376658;,
  0.625000;0.376658;,
  0.625000;0.500000;,
  0.589735;0.895948;,
  0.589735;0.645948;,
  0.625000;0.645948;,
  0.625000;0.895948;,
  0.035133;0.873342;,
  0.035133;0.750000;,
  0.070398;0.750000;,
  0.070398;0.873342;,
  0.751658;0.250000;,
  0.751659;0.218291;,
  0.875000;0.250000;,
  0.699062;0.000000;,
  0.822403;0.000000;,
  0.822403;0.126739;,
  0.699062;0.129505;,
  0.035133;1.000000;,
  0.070398;1.000000;,
  0.248342;0.250000;,
  0.248342;0.126739;,
  0.375000;0.125098;,
  0.375000;0.250000;,
  0.498307;1.000000;,
  0.498307;0.873342;,
  0.589735;0.873342;,
  0.589735;1.000000;,
  0.498307;0.750000;,
  0.589735;0.750000;,
  0.534951;0.773119;,
  0.534951;0.340663;,
  0.836219;0.340663;,
  0.836219;0.773119;,
  0.498307;0.500000;,
  0.498307;0.376658;,
  0.498307;0.250000;,
  0.531552;0.778187;,
  0.531552;0.339716;,
  0.870416;0.339716;,
  0.870416;0.778187;,
  0.413949;1.000000;,
  0.413949;0.873342;,
  0.413949;0.750000;,
  0.256979;0.773119;,
  0.256979;0.340663;,
  0.413949;0.500000;,
  0.413949;0.376658;,
  0.413949;0.250000;,
  0.218891;0.778187;,
  0.218891;0.339716;,
  0.375000;0.873342;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.375000;0.766443;,
  0.375000;0.645948;,
  0.375000;0.895948;,
  0.413949;0.645948;,
  0.413949;0.895948;,
  0.375000;0.376658;,
  0.375000;0.500000;,
  0.413949;0.000000;,
  0.375000;0.000000;,
  0.751658;0.000000;,
  0.875000;0.000000;,
  0.125000;0.129505;,
  0.125000;0.250000;,
  0.949062;0.125098;,
  0.949062;0.000000;;
 }
}
