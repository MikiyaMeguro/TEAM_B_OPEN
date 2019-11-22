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
 46;
 25.36367;15.52325;-5.78010;,
 -25.05367;13.96415;-5.78010;,
 23.09210;28.19920;-5.78010;,
 19.26482;28.75842;-5.78010;,
 14.71443;29.69016;-5.78010;,
 8.54932;29.62829;-5.78010;,
 0.13553;29.77122;-5.78010;,
 -5.81109;30.58952;-5.78010;,
 -12.24536;30.95949;-5.78010;,
 -20.10904;29.93261;-5.78010;,
 -25.14636;28.25267;-5.78010;,
 -25.37672;17.09842;-5.78010;,
 -25.81816;22.93394;-5.78010;,
 -5.89929;30.59265;5.78010;,
 0.17437;29.77057;5.78010;,
 25.36367;15.52325;5.78010;,
 23.09210;28.19920;5.78010;,
 -25.05367;13.96415;5.78010;,
 19.79387;28.73135;5.78010;,
 13.97814;29.72784;5.78010;,
 8.51383;29.63010;5.78010;,
 -12.27773;30.96076;5.78010;,
 -20.49760;29.92407;5.78010;,
 -25.14636;28.25267;5.78010;,
 -25.37672;16.88945;5.78010;,
 -25.81816;23.36870;5.78010;,
 25.36367;-0.11904;5.78010;,
 -24.93257;-0.11904;5.78010;,
 -24.93257;-0.11904;-5.78010;,
 25.36367;-0.11904;-5.78010;,
 -25.81816;23.36870;5.78010;,
 -25.14636;28.25267;5.78010;,
 25.36367;15.52325;5.78010;,
 23.09210;28.19920;5.78010;,
 25.36367;-0.11904;-5.78010;,
 -24.93257;-0.11904;-5.78010;,
 -24.93257;4.07535;-5.78010;,
 -25.49066;7.23511;-5.78010;,
 -25.49066;7.98904;5.78010;,
 -25.05367;13.96415;5.78010;,
 -24.93257;4.53933;5.78010;,
 -25.49066;7.98904;5.78010;,
 25.36367;-0.11904;5.78010;,
 -25.37672;16.88945;5.78010;,
 -24.93257;4.53933;5.78010;,
 -24.93257;-0.11904;5.78010;;
 
 47;
 3;0,1,2;,
 3;2,1,3;,
 3;3,1,4;,
 3;4,1,5;,
 3;5,1,6;,
 3;6,1,7;,
 3;7,1,8;,
 3;8,1,9;,
 3;9,1,10;,
 3;1,11,10;,
 3;11,12,10;,
 4;13,14,6,7;,
 3;15,16,17;,
 3;16,18,17;,
 3;18,19,17;,
 3;19,20,17;,
 3;20,14,17;,
 3;14,13,17;,
 3;13,21,17;,
 3;21,22,17;,
 3;22,23,17;,
 3;17,23,24;,
 3;23,25,24;,
 4;26,27,28,29;,
 4;12,30,31,10;,
 4;32,0,2,33;,
 3;34,35,0;,
 3;0,35,36;,
 3;0,36,1;,
 3;36,37,1;,
 4;37,38,39,1;,
 3;15,17,26;,
 3;26,17,40;,
 3;17,41,40;,
 3;40,27,26;,
 4;42,34,0,32;,
 4;2,3,18,16;,
 4;18,3,4,19;,
 4;19,4,5,20;,
 4;20,5,6,14;,
 4;21,8,9,22;,
 4;13,7,8,21;,
 4;22,9,10,23;,
 4;11,43,30,12;,
 4;1,39,43,11;,
 4;36,44,38,37;,
 4;35,45,44,36;;
 
 MeshMaterialList {
  1;
  47;
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
    data\\TEXTURE\\UV\\Snowwall.jpg";
   }
  }
 }
 MeshNormals {
  24;
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.076204;0.997092;0.000062;,
  0.096442;0.995339;0.000143;,
  -0.998778;-0.049316;0.003316;,
  -0.999559;0.029698;-0.000885;,
  -0.991407;0.130794;-0.002356;,
  0.996072;0.088544;0.000000;,
  0.984320;0.176393;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.999824;-0.018708;-0.001526;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.151935;0.988388;-0.002150;,
  0.168373;0.985723;-0.000911;,
  0.085830;0.996309;-0.000867;,
  0.001477;0.999998;-0.001054;,
  -0.035048;0.999385;-0.000935;,
  -0.228549;0.973526;-0.003488;,
  -0.327370;0.944883;-0.004967;,
  -0.996037;-0.088938;-0.000165;,
  -0.996481;-0.083701;0.004364;,
  -1.000000;0.000000;0.000000;;
  47;
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;4,3,3,4;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  4;0,0,0,0;,
  4;6,6,7,7;,
  4;8,8,9,9;,
  3;10,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;5,5,11,11;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,12,2;,
  4;13,13,8,8;,
  4;14,15,15,14;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;17,17,3,3;,
  4;18,18,19,19;,
  4;4,4,18,18;,
  4;19,19,20,20;,
  4;21,21,6,6;,
  4;11,11,21,21;,
  4;22,22,5,5;,
  4;23,23,22,22;;
 }
 MeshTextureCoords {
  46;
  0.375000;0.872936;,
  0.625000;0.872936;,
  0.375000;0.750000;,
  0.394924;0.750000;,
  0.418611;0.750000;,
  0.450705;0.750000;,
  0.494504;0.750000;,
  0.525460;0.750000;,
  0.558955;0.750000;,
  0.599890;0.750000;,
  0.625000;0.750000;,
  0.625000;0.857723;,
  0.625000;0.801366;,
  0.525919;0.500000;,
  0.494302;0.500000;,
  0.375000;0.377064;,
  0.375000;0.500000;,
  0.625000;0.377064;,
  0.392169;0.500000;,
  0.422444;0.500000;,
  0.450890;0.500000;,
  0.559123;0.500000;,
  0.601913;0.500000;,
  0.625000;0.500000;,
  0.625000;0.390259;,
  0.625000;0.452833;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.875000;0.797167;,
  0.875000;0.750000;,
  0.125000;0.872936;,
  0.125000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.965928;,
  0.625000;0.914349;,
  0.875000;0.908225;,
  0.875000;0.872936;,
  0.625000;0.287841;,
  0.625000;0.341775;,
  0.125000;1.000000;,
  0.875000;0.859741;,
  0.875000;0.962159;,
  0.875000;1.000000;;
 }
}
