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
 102;
 -2.00484;5.35364;1.13203;,
 -2.00484;-0.08615;1.13203;,
 0.00000;-0.08615;2.22092;,
 0.00000;5.35364;2.22092;,
 0.00000;5.35364;2.22092;,
 0.00000;-0.08615;2.22092;,
 2.00483;-0.08615;1.13203;,
 2.00483;5.35364;1.13203;,
 2.00483;5.35364;1.13203;,
 2.00483;-0.08615;1.13203;,
 2.00483;-0.08615;-1.28380;,
 2.00483;5.35364;-1.28380;,
 2.00483;5.35364;-1.28380;,
 2.00483;-0.08615;-1.28380;,
 0.00000;-0.08615;-2.37269;,
 0.00000;5.35364;-2.37269;,
 0.00000;5.35364;-2.37269;,
 0.00000;-0.08615;-2.37269;,
 -2.00486;-0.08615;-1.28380;,
 -2.00486;5.35364;-1.28380;,
 -2.00486;5.35364;-1.28380;,
 -2.00486;-0.08615;-1.28380;,
 -2.00484;-0.08615;1.13203;,
 -2.00484;5.35364;1.13203;,
 2.00483;-0.08615;-1.28380;,
 2.00483;-0.08615;1.13203;,
 0.00000;-0.08615;-2.37269;,
 0.00000;-0.08615;2.22092;,
 -2.00484;-0.08615;1.13203;,
 -2.00486;-0.08615;-1.28380;,
 2.00483;5.35364;1.13203;,
 2.00483;5.35364;-1.28380;,
 0.00000;5.35364;2.22092;,
 0.00000;5.35364;-2.37269;,
 -2.00486;5.35364;-1.28380;,
 -2.00484;5.35364;1.13203;,
 4.39489;22.08751;-2.72529;,
 -4.39489;22.08751;-2.72529;,
 -4.82496;19.62350;-3.53678;,
 4.82496;19.62350;-3.53678;,
 4.82496;22.96652;-2.85280;,
 -4.82496;22.96652;-2.85280;,
 -4.82496;22.76592;-0.48759;,
 4.82496;22.76592;-0.48759;,
 4.82496;22.76592;-0.48759;,
 -4.07665;20.90103;1.93624;,
 4.07665;20.90103;1.93624;,
 3.12052;4.28200;0.01791;,
 3.12052;4.28200;2.66846;,
 3.12052;4.28200;-2.82023;,
 -3.12052;4.28200;2.66846;,
 -3.12052;4.28200;0.01791;,
 -3.12052;4.28200;-2.82023;,
 -4.07665;20.90103;1.93624;,
 -4.82496;22.76592;-0.48759;,
 -3.21220;19.30021;0.49922;,
 -4.07665;20.90103;-1.04464;,
 -4.82496;22.96652;-2.85280;,
 -4.39489;22.08751;-2.72529;,
 -4.82496;19.62350;-3.53678;,
 -4.82496;21.32674;-3.97725;,
 4.82496;21.32674;-3.97725;,
 4.82496;22.96652;-2.85280;,
 4.82496;19.62350;-3.53678;,
 4.39489;22.08751;-2.72529;,
 4.82496;22.76592;-0.48759;,
 4.07665;20.90103;-1.04464;,
 3.21220;19.80013;0.43224;,
 4.07665;20.90103;1.93624;,
 3.12052;4.28200;-2.82023;,
 -3.12052;4.28200;-2.82023;,
 -4.07665;20.90103;-1.04464;,
 4.07665;20.90103;-1.04464;,
 -3.21220;19.30021;0.49922;,
 -3.12052;4.28200;0.01791;,
 -3.12052;4.28200;2.66846;,
 -4.07665;20.90103;1.93624;,
 4.07665;20.90103;1.93624;,
 -4.07665;20.90103;1.93624;,
 -3.12052;4.28200;2.66846;,
 3.12052;4.28200;2.66846;,
 3.12052;4.28200;2.66846;,
 3.12052;4.28200;0.01791;,
 3.21220;19.80013;0.43224;,
 4.07665;20.90103;1.93624;,
 4.82496;21.32674;-3.97725;,
 -4.82496;21.32674;-3.97725;,
 -4.82496;22.96652;-2.85280;,
 4.82496;22.96652;-2.85280;,
 -4.07665;20.90103;-1.04464;,
 -3.12052;4.28200;-2.82023;,
 3.12052;4.28200;0.01791;,
 3.12052;4.28200;-2.82023;,
 4.07665;20.90103;-1.04464;,
 4.82496;19.62350;-3.53678;,
 -4.82496;19.62350;-3.53678;,
 -4.82496;21.32674;-3.97725;,
 4.82496;21.32674;-3.97725;,
 4.07665;20.90103;-1.04464;,
 -4.07665;20.90103;-1.04464;,
 -4.39489;22.08751;-2.72529;,
 4.39489;22.08751;-2.72529;;
 
 84;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 3;24,25,26;,
 3;25,27,26;,
 3;27,28,26;,
 3;28,29,26;,
 3;30,31,32;,
 3;31,33,32;,
 3;33,34,32;,
 3;34,35,32;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,42,45,46;,
 3;47,48,49;,
 3;48,50,49;,
 3;49,50,51;,
 3;51,52,49;,
 3;53,54,55;,
 3;55,54,56;,
 3;54,57,56;,
 3;56,57,58;,
 3;58,57,59;,
 3;57,60,59;,
 3;61,62,63;,
 3;63,62,64;,
 3;62,65,64;,
 3;64,65,66;,
 3;66,65,67;,
 3;65,68,67;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;85,86,87,88;,
 4;74,73,89,90;,
 4;83,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;11,10,9,8;,
 4;15,14,13,12;,
 4;19,18,17,16;,
 4;23,22,21,20;,
 3;26,25,24;,
 3;26,27,25;,
 3;26,28,27;,
 3;26,29,28;,
 3;32,31,30;,
 3;32,33,31;,
 3;32,34,33;,
 3;32,35,34;,
 4;39,38,37,36;,
 4;43,42,41,40;,
 4;46,45,42,44;,
 3;49,48,47;,
 3;49,50,48;,
 3;51,50,49;,
 3;49,52,51;,
 3;55,54,53;,
 3;56,54,55;,
 3;56,57,54;,
 3;58,57,56;,
 3;59,57,58;,
 3;59,60,57;,
 3;63,62,61;,
 3;64,62,63;,
 3;64,65,62;,
 3;66,65,64;,
 3;67,65,66;,
 3;67,68,65;,
 4;72,71,70,69;,
 4;76,75,74,73;,
 4;80,79,78,77;,
 4;84,83,82,81;,
 4;88,87,86,85;,
 4;90,89,73,74;,
 4;93,92,91,83;,
 4;97,96,95,94;,
 4;101,100,99,98;;
 
 MeshMaterialList {
  2;
  84;
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
    "data\\Texture\\UV\\Palette.jpg";
   }
  }
 }
 MeshNormals {
  83;
  -0.477277;0.000000;0.878753;,
  0.000001;0.000000;1.000000;,
  0.477279;0.000000;0.878752;,
  1.000000;0.000000;0.000000;,
  0.000004;0.000000;-1.000000;,
  -0.477272;0.000000;-0.878755;,
  0.000000;0.000000;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.205607;-0.081247;0.975256;,
  -0.205607;-0.081247;0.975256;,
  -0.331557;0.888617;0.316905;,
  0.000000;0.932253;0.361807;,
  0.951626;-0.280961;0.124375;,
  -0.945721;-0.323383;0.032172;,
  0.000000;0.461347;0.887220;,
  0.000000;0.996423;0.084510;,
  -0.971173;-0.238326;0.004828;,
  0.963935;-0.265347;0.020497;,
  -1.000000;0.000000;0.000000;,
  0.301149;-0.250459;0.920098;,
  -0.301149;-0.250459;0.920098;,
  0.477279;0.000000;-0.878752;,
  -1.000000;0.000000;0.000009;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.958505;-0.243018;-0.149030;,
  -0.916749;-0.399441;0.004212;,
  -0.945979;-0.274185;0.173050;,
  -0.878781;-0.452112;-0.152771;,
  0.929850;-0.228890;0.288078;,
  0.901145;-0.433468;-0.006565;,
  0.915431;-0.398690;-0.055065;,
  0.941995;-0.280050;-0.184981;,
  0.000000;0.106236;-0.994341;,
  -0.998807;-0.047146;-0.012718;,
  -0.971414;-0.039735;-0.234043;,
  0.000000;0.044017;0.999031;,
  0.971074;-0.039668;-0.235459;,
  0.998838;-0.048107;-0.002912;,
  0.000000;0.173136;-0.984898;,
  0.306161;0.389535;-0.868636;,
  -0.306161;0.389535;-0.868636;,
  -0.976470;-0.052209;0.209240;,
  0.971745;-0.053904;0.229796;,
  -0.205607;0.081247;-0.975256;,
  0.205607;0.081247;-0.975256;,
  0.000000;-0.816938;-0.576726;,
  -0.000001;0.000000;-1.000000;,
  0.477277;0.000000;-0.878753;,
  -0.477279;0.000000;-0.878752;,
  -0.000004;0.000000;1.000000;,
  -0.477279;0.000000;0.878752;,
  0.477272;0.000000;0.878755;,
  1.000000;0.000000;-0.000009;,
  0.301149;0.250459;-0.920098;,
  -0.301149;0.250459;-0.920098;,
  0.000000;-0.932253;-0.361807;,
  0.000000;-0.996423;-0.084510;,
  0.000000;-0.461347;-0.887220;,
  0.971173;0.238326;-0.004828;,
  0.916749;0.399441;-0.004212;,
  0.958505;0.243018;0.149030;,
  0.945721;0.323383;-0.032172;,
  0.958396;0.278480;0.062652;,
  0.878781;0.452112;0.152771;,
  -0.973512;0.227817;0.019322;,
  -0.915431;0.398690;0.055065;,
  -0.912404;0.407985;-0.032680;,
  -0.951626;0.280961;-0.124375;,
  -0.963935;0.265347;-0.020497;,
  -0.941995;0.280050;0.184981;,
  0.000000;-0.106236;0.994341;,
  0.971414;0.039735;0.234043;,
  0.998807;0.047146;0.012718;,
  0.000000;-0.044017;-0.999031;,
  -0.998838;0.048107;0.002912;,
  -0.971074;0.039668;0.235459;,
  0.000000;-0.565538;0.824722;,
  0.000000;-0.173136;0.984898;,
  0.976470;0.052209;-0.209240;,
  -0.971745;0.053904;-0.229796;,
  0.000000;0.816938;0.576726;;
  84;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;3,3,3,3;,
  4;21,21,4,4;,
  4;4,4,5,5;,
  4;22,22,22,22;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,23,7;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,25,24;,
  4;19,20,9,8;,
  4;15,15,11,10;,
  4;10,11,14,14;,
  3;6,6,6;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;26,27,16;,
  3;16,27,13;,
  3;27,28,13;,
  3;13,28,29;,
  3;20,28,9;,
  3;28,18,18;,
  3;3,30,3;,
  3;8,30,19;,
  3;30,31,32;,
  3;32,31,12;,
  3;12,31,17;,
  3;31,33,17;,
  4;34,34,34,34;,
  4;16,35,36,26;,
  4;14,14,37,37;,
  4;38,39,17,33;,
  4;40,40,41,42;,
  4;35,16,13,43;,
  4;17,39,44,12;,
  4;45,46,40,40;,
  4;47,47,47,47;,
  4;48,48,49,49;,
  4;50,50,48,48;,
  4;18,18,18,18;,
  4;51,51,52,52;,
  4;53,53,51,51;,
  4;54,54,54,54;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,25,24;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,23,7;,
  4;45,46,55,56;,
  4;57,57,58,58;,
  4;59,59,57,57;,
  3;6,6,6;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;60,61,62;,
  3;63,61,60;,
  3;63,64,61;,
  3;65,64,63;,
  3;46,41,55;,
  3;3,3,64;,
  3;18,66,18;,
  3;56,42,45;,
  3;67,68,66;,
  3;69,68,67;,
  3;70,68,69;,
  3;70,71,10;,
  4;72,72,72,72;,
  4;62,73,74,60;,
  4;75,75,59,59;,
  4;71,70,76,77;,
  4;78,78,79,79;,
  4;80,63,60,74;,
  4;69,81,76,70;,
  4;79,79,9,8;,
  4;82,82,82,82;;
 }
 MeshTextureCoords {
  102;
  0.231702;0.804755;,
  0.231702;0.579599;,
  0.171089;0.579833;,
  0.166075;0.809959;,
  0.216993;0.804229;,
  0.216993;0.580423;,
  0.166187;0.581004;,
  0.166187;0.799110;,
  0.162502;0.806097;,
  0.162502;0.579234;,
  0.184775;0.579234;,
  0.184775;0.806097;,
  0.196909;0.805794;,
  0.196909;0.579234;,
  0.222017;0.579234;,
  0.222017;0.804312;,
  0.209882;0.805224;,
  0.209882;0.578939;,
  0.264871;0.580645;,
  0.264871;0.804430;,
  0.241208;0.802712;,
  0.241208;0.580055;,
  0.208193;0.579304;,
  0.208193;0.805687;,
  0.117590;0.580217;,
  0.147352;0.581480;,
  0.116477;0.684592;,
  0.170364;0.583074;,
  0.168117;0.683063;,
  0.142329;0.683693;,
  0.141883;0.802174;,
  0.115451;0.805219;,
  0.166576;0.799875;,
  0.113300;0.701413;,
  0.144567;0.699273;,
  0.164785;0.696256;,
  0.615777;0.147569;,
  0.790872;0.147569;,
  0.790872;0.160021;,
  0.615777;0.160021;,
  0.615890;0.208838;,
  0.793938;0.208838;,
  0.793938;0.223325;,
  0.615890;0.223325;,
  0.615707;0.223325;,
  0.793938;0.262159;,
  0.615707;0.262159;,
  0.093550;0.156338;,
  0.093550;0.035611;,
  0.093550;0.285611;,
  0.343550;0.035611;,
  0.343550;0.156338;,
  0.343550;0.285611;,
  0.967989;0.155634;,
  0.967989;0.163149;,
  0.887989;0.155634;,
  0.802327;0.155634;,
  0.887989;0.163149;,
  0.802327;0.158830;,
  0.802327;0.163149;,
  0.851834;0.163149;,
  0.581886;0.150264;,
  0.545731;0.150264;,
  0.616049;0.150264;,
  0.616049;0.145945;,
  0.437618;0.150264;,
  0.616049;0.140079;,
  0.545731;0.140079;,
  0.437618;0.140079;,
  0.447002;0.465586;,
  0.692492;0.465586;,
  0.692492;0.964080;,
  0.447002;0.964080;,
  0.882718;0.132280;,
  0.882718;0.038548;,
  0.971503;0.038548;,
  0.971503;0.132280;,
  0.731065;0.469679;,
  0.990233;0.470491;,
  0.988676;0.967864;,
  0.729508;0.967053;,
  0.437280;0.039719;,
  0.525817;0.039719;,
  0.525817;0.134463;,
  0.437280;0.134463;,
  0.615890;0.182820;,
  0.793938;0.182820;,
  0.793938;0.207211;,
  0.615890;0.207211;,
  0.792956;0.132280;,
  0.792956;0.038548;,
  0.525817;0.039300;,
  0.616049;0.039719;,
  0.616049;0.134882;,
  0.615890;0.160347;,
  0.793938;0.160347;,
  0.793938;0.187432;,
  0.615890;0.187432;,
  0.616102;0.137475;,
  0.791197;0.137475;,
  0.791197;0.147569;,
  0.616102;0.147569;;
 }
}
