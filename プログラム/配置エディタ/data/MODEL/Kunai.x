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
 120;
 -1.34629;1.15371;15.07661;,
 -1.66411;0.83590;13.69332;,
 -3.64500;1.26394;13.69332;,
 -3.17890;1.73004;15.72202;,
 -1.95864;2.95031;16.97582;,
 -0.51424;1.98576;15.93154;,
 -0.45031;4.45864;16.97582;,
 0.51424;3.01424;15.93154;,
 0.76996;5.67891;15.72202;,
 1.34629;3.84629;15.07661;,
 1.23606;6.14500;13.69332;,
 0.76996;5.67890;11.66462;,
 1.34629;3.84629;12.31002;,
 1.66411;4.16411;13.69332;,
 -0.45031;4.45864;10.41082;,
 0.51424;3.01424;11.45510;,
 -1.95864;2.95031;10.41082;,
 -0.51424;1.98576;11.45510;,
 -3.17890;1.73004;11.66462;,
 -1.34629;1.15371;12.31002;,
 -5.52147;0.20007;13.69332;,
 -4.77459;0.94695;16.94410;,
 -2.81924;2.90229;18.95320;,
 -0.40230;5.31924;18.95320;,
 1.55306;7.27459;16.94410;,
 2.29993;8.02147;13.69332;,
 1.55306;7.27459;10.44253;,
 -0.40230;5.31924;8.43344;,
 -4.77459;0.94695;10.44253;,
 -2.81924;2.90230;8.43344;,
 -4.99232;-2.49232;13.69332;,
 -4.03888;-1.53887;17.84321;,
 -1.54272;0.95729;20.40797;,
 1.54272;4.04272;20.40797;,
 4.03888;6.53887;17.84321;,
 4.99232;7.49232;13.69332;,
 4.03888;6.53887;9.54343;,
 1.54272;4.04272;6.97865;,
 -1.54271;0.95729;6.97866;,
 -4.03888;-1.53887;9.54343;,
 -2.29993;-3.02147;13.69332;,
 -1.55306;-2.27460;16.94410;,
 0.40230;-0.31925;18.95320;,
 2.81924;2.09770;18.95320;,
 4.77459;4.05306;16.94410;,
 5.52148;4.79993;13.69332;,
 4.77459;4.05306;10.44253;,
 2.81924;2.09770;8.43344;,
 0.40230;-0.31925;8.43344;,
 -1.55305;-2.27460;10.44253;,
 -1.23606;-1.14500;13.69332;,
 -0.76996;-0.67891;15.72202;,
 0.45031;0.54136;16.97582;,
 1.95864;2.04969;16.97582;,
 3.17890;3.26996;15.72202;,
 3.64500;3.73606;13.69332;,
 3.17890;3.26996;11.66462;,
 1.95864;2.04969;10.41081;,
 0.45031;0.54136;10.41081;,
 -0.76996;-0.67890;11.66462;,
 -1.66411;0.83590;13.69332;,
 -1.34629;1.15371;15.07661;,
 -0.51424;1.98576;15.93154;,
 0.51424;3.01424;15.93154;,
 1.34629;3.84629;15.07661;,
 1.66411;4.16411;13.69332;,
 1.34629;3.84629;12.31002;,
 0.51424;3.01424;11.45510;,
 -0.51424;1.98576;11.45510;,
 -1.34629;1.15371;12.31002;,
 -1.87085;2.20369;-11.56561;,
 -1.87085;2.20369;8.16612;,
 -1.68772;3.35994;8.16612;,
 -1.68772;3.35994;-11.56561;,
 -0.85994;4.18772;8.16612;,
 -0.85994;4.18772;-11.56561;,
 0.29632;4.37085;8.16612;,
 0.29632;4.37085;-11.56561;,
 1.33937;3.83937;8.16612;,
 1.33937;3.83937;-11.56561;,
 1.87085;2.79632;8.16612;,
 1.87085;2.79632;-11.56561;,
 1.68772;1.64007;8.16612;,
 1.68772;1.64007;-11.56561;,
 0.85994;0.81229;8.16612;,
 0.85994;0.81229;-11.56561;,
 -0.29632;0.62915;8.16612;,
 -0.29632;0.62915;-11.56561;,
 -1.33937;1.16062;8.16612;,
 -1.33937;1.16062;-11.56561;,
 1.87085;2.79632;8.16612;,
 1.33937;3.83937;8.16612;,
 1.68772;1.64007;8.16612;,
 0.85994;0.81229;8.16612;,
 0.29632;4.37085;8.16612;,
 -0.29632;0.62915;8.16612;,
 -0.85994;4.18772;8.16612;,
 -1.33937;1.16062;8.16612;,
 -1.68772;3.35994;8.16612;,
 -1.87085;2.20369;8.16612;,
 1.87085;2.79632;-11.56561;,
 1.68772;1.64007;-11.56561;,
 1.33937;3.83937;-11.56561;,
 0.85994;0.81229;-11.56561;,
 0.29632;4.37085;-11.56561;,
 -0.29632;0.62915;-11.56561;,
 -0.85994;4.18772;-11.56561;,
 -1.33937;1.16062;-11.56561;,
 -1.68772;3.35994;-11.56561;,
 -1.87085;2.20369;-11.56561;,
 0.18375;2.31626;-9.42739;,
 2.13300;0.36700;-16.73267;,
 4.65671;6.74186;-16.77570;,
 0.18375;2.31626;-9.42739;,
 4.65671;6.74186;-16.77570;,
 -2.34536;4.84536;-16.73267;,
 0.18375;2.31626;-42.47626;,
 -4.24186;-2.15670;-16.77570;,
 0.18375;2.31626;-9.42739;,
 -4.24186;-2.15670;-16.77570;;
 
 94;
 4;0,1,2,3;,
 4;3,4,5,0;,
 4;5,4,6,7;,
 4;6,8,9,7;,
 4;10,11,12,13;,
 4;11,14,15,12;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,2,1,19;,
 4;9,8,10,13;,
 4;3,2,20,21;,
 4;4,3,21,22;,
 4;6,4,22,23;,
 4;8,6,23,24;,
 4;25,10,8,24;,
 4;11,10,25,26;,
 4;27,14,11,26;,
 4;20,2,18,28;,
 4;29,16,14,27;,
 4;21,20,30,31;,
 4;22,21,31,32;,
 4;23,22,32,33;,
 4;24,23,33,34;,
 4;25,24,34,35;,
 4;26,25,35,36;,
 4;27,26,36,37;,
 4;29,27,37,38;,
 4;38,39,28,29;,
 4;20,28,39,30;,
 4;31,30,40,41;,
 4;32,31,41,42;,
 4;33,32,42,43;,
 4;34,33,43,44;,
 4;35,34,44,45;,
 4;36,35,45,46;,
 4;37,36,46,47;,
 4;38,37,47,48;,
 4;30,39,49,40;,
 4;41,40,50,51;,
 4;42,41,51,52;,
 4;43,42,52,53;,
 4;44,43,53,54;,
 4;45,44,54,55;,
 4;46,45,55,56;,
 4;47,46,56,57;,
 4;48,47,57,58;,
 4;49,48,58,59;,
 4;40,49,59,50;,
 4;50,60,61,51;,
 4;61,62,52,51;,
 4;62,63,53,52;,
 4;63,64,54,53;,
 4;54,64,65,55;,
 4;65,66,56,55;,
 4;66,67,57,56;,
 4;67,68,58,57;,
 4;68,69,59,58;,
 4;69,60,50,59;,
 4;18,16,29,28;,
 4;39,38,48,49;,
 4;70,71,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;77,76,78,79;,
 4;79,78,80,81;,
 4;81,80,82,83;,
 4;83,82,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;70,89,88,71;,
 3;90,91,92;,
 3;92,91,93;,
 3;91,94,93;,
 3;93,94,95;,
 3;94,96,95;,
 3;95,96,97;,
 3;96,98,97;,
 3;98,99,97;,
 3;100,101,102;,
 3;101,103,102;,
 3;102,103,104;,
 3;103,105,104;,
 3;104,105,106;,
 3;105,107,106;,
 3;106,107,108;,
 3;107,109,108;,
 3;110,111,112;,
 3;113,114,115;,
 3;114,116,115;,
 3;116,117,115;,
 3;117,118,115;,
 3;112,111,116;,
 3;110,119,111;,
 3;116,111,119;;
 
 MeshMaterialList {
  1;
  94;
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
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Kunai.jpg";
   }
  }
 }
 MeshNormals {
  103;
  0.097707;0.863934;-0.494036;,
  -0.199456;0.566769;-0.799369;,
  -0.566770;0.199454;-0.799369;,
  -0.863933;-0.097709;-0.494037;,
  -0.977439;-0.211216;0.000000;,
  -0.863932;-0.097710;0.494038;,
  -0.566768;0.199453;0.799370;,
  -0.199454;0.566768;0.799370;,
  0.097708;0.863933;0.494037;,
  0.211214;0.977440;0.000001;,
  -0.236288;0.908285;-0.345234;,
  -0.443946;0.700626;-0.558601;,
  -0.700626;0.443946;-0.558601;,
  -0.908285;0.236287;-0.345235;,
  -0.987604;0.156968;-0.000000;,
  -0.908285;0.236287;0.345235;,
  -0.700626;0.443946;0.558602;,
  -0.443946;0.700626;0.558602;,
  -0.236287;0.908285;0.345235;,
  -0.156969;0.987604;0.000000;,
  -0.529176;0.833941;-0.156571;,
  -0.623354;0.739763;-0.253337;,
  -0.739764;0.623354;-0.253337;,
  -0.833941;0.529176;-0.156571;,
  -0.869914;0.493203;-0.000000;,
  -0.833941;0.529176;0.156571;,
  -0.739763;0.623354;0.253337;,
  -0.623354;0.739763;0.253338;,
  -0.529176;0.833941;0.156572;,
  -0.493203;0.869915;0.000000;,
  -0.869115;-0.080732;0.487977;,
  -0.575596;0.212787;0.789564;,
  -0.212787;0.575596;0.789563;,
  0.080731;0.869115;0.487977;,
  0.192845;0.981229;0.000000;,
  0.080731;0.869115;-0.487977;,
  -0.212788;0.575596;-0.789564;,
  -0.575596;0.212787;-0.789564;,
  -0.869115;-0.080732;-0.487977;,
  -0.981229;-0.192846;-0.000000;,
  -0.080732;-0.869115;0.487977;,
  0.212787;-0.575596;0.789564;,
  0.575596;-0.212787;0.789564;,
  0.869115;0.080731;0.487977;,
  0.981229;0.192846;0.000000;,
  0.869115;0.080731;-0.487977;,
  0.575596;-0.212788;-0.789564;,
  0.212787;-0.575596;-0.789564;,
  -0.080732;-0.869115;-0.487977;,
  -0.192846;-0.981229;-0.000000;,
  0.908285;-0.236287;-0.345234;,
  0.700626;-0.443946;-0.558601;,
  0.443946;-0.700626;-0.558601;,
  0.236287;-0.908285;-0.345235;,
  0.156968;-0.987604;-0.000000;,
  0.236286;-0.908285;0.345235;,
  0.443945;-0.700626;0.558601;,
  0.700626;-0.443945;0.558602;,
  0.908285;-0.236287;0.345235;,
  0.987604;-0.156968;0.000000;,
  -0.987688;-0.156437;0.000000;,
  -0.891007;0.453990;0.000000;,
  -0.453990;0.891007;0.000000;,
  0.156437;0.987688;0.000000;,
  0.707107;0.707107;0.000000;,
  0.987688;0.156437;0.000000;,
  0.891007;-0.453990;-0.000000;,
  0.453990;-0.891007;-0.000000;,
  -0.156437;-0.987688;0.000000;,
  -0.707107;-0.707107;0.000000;,
  0.661572;-0.661572;0.353052;,
  0.923644;-0.364864;0.117284;,
  -0.700379;0.700379;-0.137613;,
  -0.955922;0.258049;0.140083;,
  -0.535644;0.804975;0.255148;,
  0.701320;-0.701320;0.127673;,
  0.833941;-0.529176;-0.156571;,
  0.869914;-0.493203;0.000000;,
  0.739763;-0.623354;-0.253338;,
  0.623354;-0.739764;-0.253338;,
  0.529176;-0.833941;-0.156571;,
  0.493203;-0.869914;-0.000000;,
  0.529176;-0.833942;0.156572;,
  0.623354;-0.739763;0.253339;,
  0.739764;-0.623353;0.253339;,
  0.833942;-0.529175;0.156573;,
  0.977440;0.211215;0.000000;,
  0.863934;0.097708;-0.494037;,
  0.566769;-0.199455;-0.799369;,
  0.199454;-0.566770;-0.799369;,
  -0.097709;-0.863933;-0.494037;,
  -0.211216;-0.977439;0.000000;,
  -0.097709;-0.863933;0.494037;,
  0.199455;-0.566770;0.799368;,
  0.566770;-0.199455;0.799368;,
  0.863934;0.097708;0.494037;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.635074;0.635074;0.439728;,
  -0.258049;0.955922;0.140083;,
  -0.958098;0.260235;-0.119692;,
  0.703087;-0.703087;-0.106473;,
  0.364864;-0.923644;0.117284;;
  94;
  4;0,9,19,10;,
  4;10,11,1,0;,
  4;1,11,12,2;,
  4;12,13,3,2;,
  4;14,15,5,4;,
  4;15,16,6,5;,
  4;16,17,7,6;,
  4;17,18,8,7;,
  4;18,19,9,8;,
  4;3,13,14,4;,
  4;10,19,29,20;,
  4;11,10,20,21;,
  4;12,11,21,22;,
  4;13,12,22,23;,
  4;24,14,13,23;,
  4;15,14,24,25;,
  4;26,16,15,25;,
  4;29,19,18,28;,
  4;27,17,16,26;,
  4;30,39,39,30;,
  4;31,30,30,31;,
  4;32,31,31,32;,
  4;33,32,32,33;,
  4;34,33,33,34;,
  4;35,34,34,35;,
  4;36,35,35,36;,
  4;37,36,36,37;,
  4;37,38,38,37;,
  4;39,38,38,39;,
  4;40,49,49,40;,
  4;41,40,40,41;,
  4;42,41,41,42;,
  4;43,42,42,43;,
  4;44,43,43,44;,
  4;45,44,44,45;,
  4;46,45,45,46;,
  4;47,46,46,47;,
  4;49,48,48,49;,
  4;76,77,59,50;,
  4;78,76,50,51;,
  4;79,78,51,52;,
  4;80,79,52,53;,
  4;81,80,53,54;,
  4;82,81,54,55;,
  4;83,82,55,56;,
  4;84,83,56,57;,
  4;85,84,57,58;,
  4;77,85,58,59;,
  4;59,86,87,50;,
  4;87,88,51,50;,
  4;88,89,52,51;,
  4;89,90,53,52;,
  4;53,90,91,54;,
  4;91,92,55,54;,
  4;92,93,56,55;,
  4;93,94,57,56;,
  4;94,95,58,57;,
  4;95,86,59,58;,
  4;18,17,27,28;,
  4;48,47,47,48;,
  4;60,60,61,61;,
  4;61,61,62,62;,
  4;62,62,63,63;,
  4;63,63,64,64;,
  4;64,64,65,65;,
  4;65,65,66,66;,
  4;66,66,67,67;,
  4;67,67,68,68;,
  4;68,68,69,69;,
  4;60,69,69,60;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;96,96,96;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;70,75,71;,
  3;98,99,74;,
  3;99,72,74;,
  3;72,73,100;,
  3;73,98,74;,
  3;71,75,101;,
  3;70,102,75;,
  3;101,75,102;;
 }
 MeshTextureCoords {
  120;
  0.375708;0.362649;,
  0.624292;0.362649;,
  0.624292;0.335028;,
  0.375708;0.335028;,
  0.403328;0.335028;,
  0.403328;0.362649;,
  0.430949;0.335028;,
  0.430949;0.362649;,
  0.458569;0.335028;,
  0.458569;0.362649;,
  0.486190;0.335028;,
  0.513810;0.335028;,
  0.513810;0.362649;,
  0.486190;0.362649;,
  0.541431;0.335028;,
  0.541431;0.362649;,
  0.569051;0.335028;,
  0.569051;0.362649;,
  0.596672;0.335028;,
  0.596672;0.362649;,
  0.624292;0.279787;,
  0.375708;0.279787;,
  0.403328;0.279787;,
  0.430949;0.279787;,
  0.458569;0.279787;,
  0.486190;0.279787;,
  0.513810;0.279787;,
  0.541431;0.279787;,
  0.596672;0.279787;,
  0.569051;0.279787;,
  0.624292;0.224546;,
  0.375708;0.224546;,
  0.403328;0.224546;,
  0.430949;0.224546;,
  0.458569;0.224546;,
  0.486190;0.224546;,
  0.513810;0.224546;,
  0.541431;0.224546;,
  0.569051;0.224546;,
  0.596672;0.224546;,
  0.624292;0.169305;,
  0.375708;0.169305;,
  0.403328;0.169305;,
  0.430949;0.169305;,
  0.458569;0.169305;,
  0.486190;0.169305;,
  0.513810;0.169305;,
  0.541431;0.169305;,
  0.569051;0.169305;,
  0.596672;0.169305;,
  0.624292;0.114064;,
  0.375708;0.114064;,
  0.403328;0.114064;,
  0.430949;0.114064;,
  0.458569;0.114064;,
  0.486190;0.114064;,
  0.513810;0.114064;,
  0.541431;0.114064;,
  0.569051;0.114064;,
  0.596672;0.114064;,
  0.624292;0.086443;,
  0.375708;0.086443;,
  0.403328;0.086443;,
  0.430949;0.086443;,
  0.458569;0.086443;,
  0.486190;0.086443;,
  0.513810;0.086443;,
  0.541431;0.086443;,
  0.569051;0.086443;,
  0.596672;0.086443;,
  0.387500;0.753515;,
  0.387500;0.462723;,
  0.412500;0.462723;,
  0.412500;0.753515;,
  0.437500;0.462723;,
  0.437500;0.753515;,
  0.462500;0.462723;,
  0.462500;0.753515;,
  0.487500;0.462723;,
  0.487500;0.753515;,
  0.512500;0.462723;,
  0.512500;0.753515;,
  0.537500;0.462723;,
  0.537500;0.753515;,
  0.562500;0.462723;,
  0.562500;0.753515;,
  0.587500;0.462723;,
  0.587500;0.753515;,
  0.612500;0.462723;,
  0.612500;0.753515;,
  0.373591;0.248091;,
  0.343750;0.156250;,
  0.451716;0.304853;,
  0.548284;0.304853;,
  0.373591;0.064409;,
  0.626409;0.248091;,
  0.451716;0.007647;,
  0.656250;0.156250;,
  0.548284;0.007647;,
  0.626409;0.064408;,
  0.373591;0.751909;,
  0.451716;0.695147;,
  0.343750;0.843750;,
  0.548284;0.695147;,
  0.373591;0.935591;,
  0.626409;0.751908;,
  0.451716;0.992353;,
  0.656250;0.843750;,
  0.548284;0.992353;,
  0.626409;0.935591;,
  0.500000;0.042315;,
  0.500000;0.143720;,
  0.398594;0.143720;,
  0.398594;0.245126;,
  0.449297;0.245126;,
  0.500000;0.447937;,
  0.500000;0.245126;,
  0.550703;0.245126;,
  0.601406;0.245126;,
  0.601406;0.143720;;
 }
}
