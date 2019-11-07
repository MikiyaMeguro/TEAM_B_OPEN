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
 124;
 0.00000;0.09759;1.47924;,
 0.00000;1.86627;9.66419;,
 -0.47299;1.96172;9.41042;,
 -0.25860;0.09759;1.19673;,
 0.25860;0.09759;1.19673;,
 0.47299;1.96172;9.41042;,
 0.25860;0.09759;-0.00184;,
 1.16890;0.89741;-0.00832;,
 0.00000;0.09759;-1.47924;,
 0.00000;0.62614;-5.87191;,
 1.16890;0.89741;-5.40937;,
 0.25860;0.09759;-1.19673;,
 -0.25860;0.09759;-1.19673;,
 -1.16890;0.89741;-5.40937;,
 -0.25860;0.09759;0.00956;,
 -1.16890;0.89741;0.04321;,
 0.00000;1.86627;9.66419;,
 0.00000;2.38806;8.39805;,
 -0.53915;2.41193;7.99092;,
 -0.47299;1.96172;9.41042;,
 0.47299;1.96172;9.41042;,
 0.53915;2.41193;7.99091;,
 1.77975;2.61282;-0.01126;,
 0.53915;2.41193;7.99091;,
 0.00000;0.62614;-5.87191;,
 0.00000;2.46476;-8.03529;,
 1.63272;2.46476;-7.31994;,
 1.16890;0.89741;-5.40937;,
 -1.16890;0.89741;-5.40937;,
 -1.63272;2.46476;-7.31994;,
 -1.77975;2.61282;0.05848;,
 -1.63272;2.46476;-7.31994;,
 -0.64560;3.14089;8.98932;,
 0.00000;3.14089;9.63669;,
 0.64560;3.14089;8.98932;,
 0.64560;3.14089;8.98932;,
 0.53915;2.41193;7.99091;,
 1.77975;2.61282;-0.01126;,
 1.77975;3.21550;-0.01126;,
 1.63272;3.36356;-7.31994;,
 1.63272;2.46476;-7.31994;,
 0.00000;2.46476;-8.03529;,
 0.00000;3.36356;-8.03529;,
 -1.63272;2.46476;-7.31994;,
 -1.63272;3.36356;-7.31994;,
 -1.77975;2.61282;0.05848;,
 -1.77975;3.21550;0.05848;,
 0.00000;3.14089;9.63669;,
 0.00000;3.83920;14.68878;,
 -0.63383;3.58963;8.68420;,
 -0.64560;3.14089;8.98932;,
 0.00000;3.83920;14.68878;,
 0.62005;3.53975;8.76958;,
 0.53137;4.13902;8.04830;,
 0.00000;4.31336;8.06661;,
 1.77975;3.21550;-0.01126;,
 1.16890;4.37954;-0.00832;,
 0.64560;3.14089;8.98932;,
 0.53137;4.13902;8.04830;,
 0.62005;3.53975;8.76958;,
 0.00000;3.36356;-8.03529;,
 0.00000;4.62690;-6.16190;,
 1.16890;4.37954;-5.40937;,
 1.63272;3.36356;-7.31994;,
 -1.63272;3.36356;-7.31994;,
 -1.16890;4.37954;-5.40937;,
 0.00000;4.62690;-6.16190;,
 0.00000;3.36356;-8.03529;,
 -1.77975;3.21550;0.05848;,
 -1.16890;4.37954;0.04321;,
 -1.16890;4.37954;-5.40937;,
 -1.63272;3.36356;-7.31994;,
 0.75048;4.96216;3.47303;,
 0.53137;4.13902;8.04830;,
 1.16890;4.37954;-0.00832;,
 0.75048;5.45299;-0.00535;,
 -0.75048;5.45299;-3.47304;,
 -1.16890;4.37954;-5.40937;,
 -1.16890;4.37954;0.04321;,
 -0.75048;5.45299;0.02774;,
 0.00000;4.31336;8.06661;,
 0.00000;5.75156;1.43305;,
 -0.53137;4.13902;8.04830;,
 -0.25860;5.75156;1.15937;,
 -0.75048;4.96216;3.47303;,
 0.25860;5.75156;1.15937;,
 0.25860;5.75156;-0.00179;,
 1.16890;4.37954;-5.40937;,
 0.00000;4.62690;-6.16190;,
 0.75048;5.45299;-3.47304;,
 0.25860;5.75156;-1.15937;,
 0.00000;5.75156;-1.43305;,
 -0.25860;5.75156;-1.15937;,
 -0.25860;5.75156;0.00926;,
 -0.53915;2.41193;7.99092;,
 -0.53915;2.41193;7.99092;,
 -0.64560;3.14089;8.98932;,
 -0.64560;3.14089;8.98932;,
 -0.63383;3.58963;8.68420;,
 -1.77975;3.21550;0.05848;,
 -0.53137;4.13902;8.04830;,
 -1.16890;4.37954;0.04321;,
 1.63272;2.46476;-7.31994;,
 1.63272;3.36356;-7.31994;,
 1.16890;4.37954;-5.40937;,
 1.16890;4.37954;-0.00832;,
 1.77975;3.21550;-0.01126;,
 -0.63383;3.58963;8.68420;,
 0.00000;3.83920;14.68878;,
 0.00000;4.31336;8.06661;,
 -0.53137;4.13902;8.04830;,
 0.62005;3.53975;8.76958;,
 0.00000;3.83920;14.68878;,
 0.00000;3.14089;9.63669;,
 -0.06149;5.43612;-1.95490;,
 0.00000;7.76232;-0.16993;,
 0.00000;7.03897;0.50733;,
 0.00000;6.16315;1.41534;,
 -0.06149;5.46905;2.22785;,
 -0.18859;4.97401;-11.47013;,
 -0.06149;3.55931;-7.37122;,
 0.00000;2.64721;-9.74423;,
 -0.18859;0.82490;-11.20277;,
 -0.06149;1.73198;-7.15961;;
 
 152;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;8,9,10,11;,
 4;12,13,9,8;,
 4;14,15,13,12;,
 4;16,17,18,19;,
 4;20,21,17,16;,
 4;7,22,23,5;,
 4;24,25,26,27;,
 4;28,29,25,24;,
 4;15,30,31,13;,
 4;32,18,17,33;,
 4;33,17,21,34;,
 4;35,36,37,38;,
 4;39,40,41,42;,
 4;42,41,43,44;,
 4;44,43,45,46;,
 4;47,48,49,50;,
 4;51,52,53,54;,
 3;55,56,57;,
 3;56,58,57;,
 3;58,59,57;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 3;80,81,82;,
 3;81,83,82;,
 3;83,84,82;,
 3;72,85,73;,
 3;85,81,73;,
 3;81,80,73;,
 4;85,72,75,86;,
 3;87,88,89;,
 3;89,88,90;,
 3;88,91,90;,
 3;91,88,92;,
 3;88,77,92;,
 3;77,76,92;,
 4;92,76,79,93;,
 3;11,6,8;,
 3;6,4,8;,
 3;4,0,8;,
 3;0,3,8;,
 3;8,3,14;,
 3;14,12,8;,
 3;85,86,81;,
 3;86,90,81;,
 3;90,91,81;,
 3;91,92,81;,
 3;81,92,93;,
 3;93,83,81;,
 4;3,2,15,14;,
 4;2,94,30,15;,
 4;46,45,95,96;,
 3;97,98,99;,
 3;98,100,99;,
 3;100,101,99;,
 4;79,78,82,84;,
 4;93,79,84,83;,
 4;11,10,7,6;,
 4;10,102,22,7;,
 4;38,37,40,39;,
 4;103,104,105,106;,
 4;75,74,87,89;,
 4;86,75,89,90;,
 4;107,108,109,110;,
 4;35,111,112,113;,
 3;114,115,116;,
 3;114,116,117;,
 3;117,118,114;,
 3;119,120,121;,
 3;122,121,123;,
 3;121,120,123;,
 4;3,2,1,0;,
 4;0,1,5,4;,
 4;4,5,7,6;,
 4;11,10,9,8;,
 4;8,9,13,12;,
 4;12,13,15,14;,
 4;19,18,17,16;,
 4;16,17,21,20;,
 4;5,23,22,7;,
 4;27,26,25,24;,
 4;24,25,29,28;,
 4;13,31,30,15;,
 4;33,17,18,32;,
 4;34,21,17,33;,
 4;38,37,36,35;,
 4;42,41,40,39;,
 4;44,43,41,42;,
 4;46,45,43,44;,
 4;50,49,48,47;,
 4;54,53,52,51;,
 3;57,56,55;,
 3;57,58,56;,
 3;57,59,58;,
 4;63,62,61,60;,
 4;67,66,65,64;,
 4;71,70,69,68;,
 4;75,74,73,72;,
 4;79,78,77,76;,
 3;82,81,80;,
 3;82,83,81;,
 3;82,84,83;,
 3;73,85,72;,
 3;73,81,85;,
 3;73,80,81;,
 4;86,75,72,85;,
 3;89,88,87;,
 3;90,88,89;,
 3;90,91,88;,
 3;92,88,91;,
 3;92,77,88;,
 3;92,76,77;,
 4;93,79,76,92;,
 3;8,6,11;,
 3;8,4,6;,
 3;8,0,4;,
 3;8,3,0;,
 3;14,3,8;,
 3;8,12,14;,
 3;81,86,85;,
 3;81,90,86;,
 3;81,91,90;,
 3;81,92,91;,
 3;93,92,81;,
 3;81,83,93;,
 4;14,15,2,3;,
 4;15,30,94,2;,
 4;96,95,45,46;,
 3;99,98,97;,
 3;99,100,98;,
 3;99,101,100;,
 4;84,82,78,79;,
 4;83,84,79,93;,
 4;6,7,10,11;,
 4;7,22,102,10;,
 4;39,40,37,38;,
 4;106,105,104,103;,
 4;89,87,74,75;,
 4;90,89,75,86;,
 4;110,109,108,107;,
 4;113,112,111,35;,
 3;116,115,114;,
 3;117,116,114;,
 3;114,118,117;,
 3;121,120,119;,
 3;123,121,122;,
 3;123,120,121;;
 
 MeshMaterialList {
  1;
  152;
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
    "data\\TEXTURE\\UV\\Fish.jpg";
   }
  }
 }
 MeshNormals {
  159;
  -0.255456;-0.964166;0.071601;,
  0.000000;-0.994432;0.105380;,
  0.255980;-0.964033;0.071511;,
  0.306361;-0.950785;-0.046392;,
  0.000000;-0.999442;-0.033416;,
  -0.306361;-0.950785;-0.046392;,
  -0.730218;-0.668633;0.140397;,
  -0.000000;-0.997282;-0.073681;,
  0.730917;-0.667956;0.139979;,
  0.599809;-0.774888;-0.199443;,
  0.000000;-0.923980;-0.382440;,
  -0.599824;-0.774880;-0.199429;,
  -0.103829;0.933053;0.344429;,
  -0.000001;0.996607;-0.082311;,
  0.103830;0.933053;0.344428;,
  0.822130;-0.326571;-0.466320;,
  0.000000;-0.447566;-0.894251;,
  -0.822167;-0.326562;-0.466259;,
  -0.900419;-0.272133;0.339396;,
  0.000002;-0.842459;0.538761;,
  0.946847;-0.215380;0.238941;,
  0.653604;0.516243;-0.553439;,
  0.000000;0.000000;-1.000000;,
  -0.653627;0.516224;-0.553429;,
  -0.681445;0.707355;0.187836;,
  0.005041;0.951025;0.309072;,
  0.745389;0.647723;0.157643;,
  0.701203;0.676209;-0.225956;,
  -0.039031;0.945137;-0.324334;,
  -0.799021;0.591394;-0.108709;,
  -0.730537;0.674916;0.103948;,
  0.731432;0.674007;0.103542;,
  0.219057;0.953887;-0.205215;,
  -0.890145;0.449321;0.075843;,
  -0.349605;0.929881;0.114446;,
  0.000000;0.996405;0.084723;,
  0.350008;0.929748;0.114294;,
  0.088713;0.992235;-0.087180;,
  0.000000;0.993390;-0.114785;,
  -0.225064;0.969978;-0.092132;,
  -0.366847;-0.930116;0.017531;,
  -0.864191;-0.501350;0.042702;,
  -0.986749;-0.152871;0.054372;,
  -0.976475;0.202230;0.074827;,
  -0.919411;0.391552;0.037020;,
  -0.794138;0.606910;0.031703;,
  -0.293719;0.955795;0.013641;,
  0.367390;-0.929904;0.017421;,
  0.864525;-0.500800;0.042382;,
  0.986807;-0.152681;0.053850;,
  0.978506;0.197585;0.059048;,
  0.934649;0.351680;0.052467;,
  0.794733;0.606148;0.031381;,
  0.294121;0.955673;0.013474;,
  -0.856231;-0.188518;0.480967;,
  -0.915189;0.274798;0.294814;,
  0.553251;0.757785;0.345942;,
  0.999184;-0.039165;-0.009916;,
  0.999774;-0.014524;-0.015513;,
  0.999772;-0.014989;-0.015210;,
  0.998648;-0.051485;-0.007114;,
  0.996169;-0.087445;0.000688;,
  0.998907;-0.046144;0.007425;,
  0.995424;-0.095036;-0.009971;,
  0.999982;-0.004804;0.003597;,
  0.999131;0.040363;0.010376;,
  0.996962;0.077789;-0.004066;,
  0.000000;0.997282;0.073681;,
  0.316851;0.948093;0.026939;,
  -0.317587;0.947842;0.027105;,
  0.883923;-0.384375;0.266337;,
  -0.883637;-0.384603;0.266958;,
  0.000001;-0.996607;0.082311;,
  -0.999802;0.000000;-0.019922;,
  0.879760;0.461379;0.114682;,
  0.972620;-0.129651;0.192873;,
  0.000000;0.879232;-0.476395;,
  0.875574;-0.483049;0.005794;,
  0.890145;-0.449321;-0.075843;,
  0.860262;-0.495793;-0.118910;,
  0.999798;0.000000;-0.020112;,
  0.931721;0.363174;0.000000;,
  -0.535316;0.768296;0.350939;,
  0.838532;-0.237274;0.490474;,
  0.255456;0.964166;-0.071601;,
  0.000000;0.994432;-0.105380;,
  -0.255980;0.964033;-0.071511;,
  -0.864525;0.500800;-0.042382;,
  -0.367390;0.929904;-0.017421;,
  -0.306361;0.950785;0.046392;,
  -0.599809;0.774888;0.199443;,
  0.000000;0.923980;0.382440;,
  0.000000;0.999442;0.033416;,
  0.599824;0.774880;0.199429;,
  0.306361;0.950785;0.046392;,
  0.864191;0.501350;-0.042702;,
  0.366847;0.930116;-0.017531;,
  0.103829;-0.933053;-0.344429;,
  -0.103830;-0.933053;-0.344428;,
  -0.985095;0.137346;-0.103558;,
  -0.883923;0.384375;-0.266337;,
  -0.986807;0.152681;-0.053850;,
  -0.822130;0.326571;0.466320;,
  0.000000;0.447566;0.894251;,
  0.822167;0.326562;0.466259;,
  0.986749;0.152871;-0.054372;,
  -0.000002;0.842459;-0.538761;,
  0.883637;0.384603;-0.266958;,
  0.900419;0.272133;-0.339396;,
  -0.946847;0.215380;-0.238941;,
  -0.978506;-0.197585;-0.059048;,
  0.000000;0.000000;1.000000;,
  -0.653604;-0.516243;0.553439;,
  0.653627;-0.516224;0.553429;,
  0.976475;-0.202230;-0.074827;,
  0.999802;0.000000;0.019922;,
  0.915189;-0.274798;-0.294814;,
  0.856231;0.188518;-0.480967;,
  -0.005041;-0.951025;-0.309072;,
  -0.745389;-0.647723;-0.157643;,
  -0.553251;-0.757785;-0.345942;,
  -0.879760;-0.461379;-0.114682;,
  -0.934649;-0.351680;-0.052467;,
  -0.972620;0.129651;-0.192873;,
  -0.701203;-0.676209;0.225956;,
  0.039031;-0.945137;0.324334;,
  0.000000;-0.879232;0.476395;,
  0.323954;-0.831817;0.450704;,
  0.919411;-0.391552;-0.037020;,
  -0.794733;-0.606148;-0.031381;,
  -0.731432;-0.674007;-0.103542;,
  0.794138;-0.606910;-0.031703;,
  0.681445;-0.707355;-0.187836;,
  -0.000000;-0.996405;-0.084723;,
  0.349605;-0.929881;-0.114446;,
  0.730537;-0.674916;-0.103948;,
  -0.350008;-0.929748;-0.114294;,
  -0.294121;-0.955673;-0.013474;,
  -0.219057;-0.953887;0.205215;,
  -0.088713;-0.992235;0.087180;,
  0.000000;-0.993390;0.114785;,
  0.146394;-0.982635;0.114006;,
  -0.978318;0.008031;0.206951;,
  0.293719;-0.955795;-0.013641;,
  0.984987;0.137583;-0.104266;,
  -0.999798;0.000000;0.020112;,
  -0.931721;-0.363174;0.000000;,
  0.535316;-0.768296;-0.350939;,
  -0.838532;0.237274;-0.490474;,
  -0.999772;0.014989;0.015210;,
  -0.999774;0.014524;0.015513;,
  -0.999184;0.039165;0.009916;,
  -0.998648;0.051485;0.007114;,
  -0.996169;0.087445;-0.000688;,
  -0.999982;0.004804;-0.003597;,
  -0.999131;-0.040363;-0.010376;,
  -0.996962;-0.077789;0.004066;,
  -0.998907;0.046144;-0.007425;,
  -0.995424;0.095036;0.009971;;
  152;
  4;1,7,6,0;,
  4;2,8,7,1;,
  4;47,48,8,2;,
  4;4,10,9,3;,
  4;5,11,10,4;,
  4;40,41,11,5;,
  4;67,13,12,68;,
  4;69,14,13,67;,
  4;48,49,70,8;,
  4;10,16,15,9;,
  4;11,17,16,10;,
  4;41,42,17,11;,
  4;18,71,72,19;,
  4;19,72,70,20;,
  4;20,70,49,50;,
  4;21,15,16,22;,
  4;22,16,17,23;,
  4;73,17,42,43;,
  4;54,54,55,18;,
  4;56,56,26,25;,
  3;50,51,74;,
  3;51,26,20;,
  3;26,75,20;,
  4;76,28,27,21;,
  4;23,29,28,76;,
  4;43,44,29,23;,
  4;31,26,51,52;,
  4;33,29,44,45;,
  3;25,35,24;,
  3;35,34,24;,
  3;34,30,24;,
  3;31,36,26;,
  3;36,35,26;,
  3;35,25,26;,
  4;36,31,52,53;,
  3;27,28,32;,
  3;32,28,37;,
  3;28,38,37;,
  3;38,28,39;,
  3;28,29,39;,
  3;77,78,79;,
  4;39,33,45,46;,
  3;3,47,4;,
  3;47,2,4;,
  3;2,1,4;,
  3;1,0,4;,
  3;4,0,40;,
  3;40,5,4;,
  3;36,53,35;,
  3;53,37,35;,
  3;37,38,35;,
  3;38,39,35;,
  3;35,39,46;,
  3;46,34,35;,
  4;0,6,41,40;,
  4;6,71,42,41;,
  4;43,42,71,18;,
  3;18,55,43;,
  3;55,24,43;,
  3;24,44,43;,
  4;45,44,24,30;,
  4;46,45,30,34;,
  4;3,9,48,47;,
  4;9,15,49,48;,
  4;50,49,15,80;,
  4;21,27,51,50;,
  4;52,51,27,81;,
  4;53,52,32,37;,
  4;55,82,25,24;,
  4;20,75,83,83;,
  3;57,58,59;,
  3;57,59,60;,
  3;60,61,57;,
  3;66,65,64;,
  3;63,64,62;,
  3;64,65,62;,
  4;84,68,67,85;,
  4;85,67,69,86;,
  4;86,69,87,88;,
  4;89,90,91,92;,
  4;92,91,93,94;,
  4;94,93,95,96;,
  4;97,97,72,7;,
  4;7,72,98,98;,
  4;99,100,101,87;,
  4;90,102,103,91;,
  4;91,103,104,93;,
  4;93,104,105,95;,
  4;106,13,107,108;,
  4;109,100,13,106;,
  4;110,101,100,109;,
  4;111,103,102,112;,
  4;113,104,103,111;,
  4;114,105,104,115;,
  4;108,116,117,117;,
  4;118,119,120,120;,
  3;121,122,110;,
  3;109,119,122;,
  3;109,123,119;,
  4;112,124,125,126;,
  4;126,125,127,113;,
  4;113,77,128,114;,
  4;129,122,119,130;,
  4;131,128,77,78;,
  3;132,133,118;,
  3;132,134,133;,
  3;132,135,134;,
  3;119,136,130;,
  3;119,133,136;,
  3;119,118,133;,
  4;137,129,130,136;,
  3;138,125,124;,
  3;139,125,138;,
  3;139,140,125;,
  3;141,125,140;,
  3;141,77,125;,
  3;142,33,29;,
  4;143,131,78,79;,
  3;92,88,89;,
  3;92,86,88;,
  3;92,85,86;,
  3;92,84,85;,
  3;96,84,92;,
  3;92,94,96;,
  3;133,137,136;,
  3;133,139,137;,
  3;133,140,139;,
  3;133,141,140;,
  3;143,141,133;,
  3;133,134,143;,
  4;96,95,68,84;,
  4;95,105,107,144;,
  4;108,107,105,114;,
  3;114,116,108;,
  3;114,132,116;,
  3;114,128,132;,
  4;135,132,128,131;,
  4;134,135,131,143;,
  4;88,87,90,89;,
  4;87,101,102,90;,
  4;145,102,101,110;,
  4;110,122,124,112;,
  4;146,124,122,129;,
  4;139,138,129,137;,
  4;132,118,147,116;,
  4;148,148,123,109;,
  3;149,150,151;,
  3;152,149,151;,
  3;151,153,152;,
  3;154,155,156;,
  3;157,154,158;,
  3;157,155,154;;
 }
 MeshTextureCoords {
  124;
  0.398390;0.378403;,
  0.398390;0.501294;,
  0.298390;0.501294;,
  0.298390;0.378403;,
  0.498390;0.378403;,
  0.498390;0.501294;,
  0.648621;0.378403;,
  0.648621;0.501294;,
  0.898390;0.378403;,
  0.898390;0.501294;,
  0.798390;0.501294;,
  0.798390;0.378403;,
  0.998390;0.378403;,
  0.998390;0.501294;,
  0.645595;0.378403;,
  0.645595;0.501294;,
  0.751714;0.051497;,
  0.751714;0.100493;,
  0.651714;0.100493;,
  0.651714;0.051497;,
  0.851714;0.051497;,
  0.851714;0.100493;,
  0.648621;0.624186;,
  0.498390;0.624186;,
  0.700000;0.382978;,
  0.700000;0.582978;,
  0.600000;0.582978;,
  0.600000;0.382978;,
  0.800000;0.382978;,
  0.800000;0.582978;,
  0.645595;0.624186;,
  0.998390;0.624186;,
  0.651714;0.124991;,
  0.751714;0.124991;,
  0.851714;0.124991;,
  0.300000;0.550000;,
  0.300000;0.450000;,
  0.450231;0.450000;,
  0.450231;0.550000;,
  0.600000;0.550000;,
  0.600000;0.450000;,
  0.700000;0.450000;,
  0.700000;0.550000;,
  0.800000;0.450000;,
  0.800000;0.550000;,
  0.447204;0.450000;,
  0.447204;0.550000;,
  0.296567;0.550000;,
  0.296567;0.662784;,
  0.196567;0.657940;,
  0.196567;0.550000;,
  0.200000;0.735605;,
  0.300000;0.721586;,
  0.300000;0.822821;,
  0.200000;0.822821;,
  -0.436868;0.527135;,
  -0.431011;0.670715;,
  0.195890;0.529279;,
  0.201746;0.672859;,
  0.198782;0.600182;,
  0.700000;0.630737;,
  0.700000;0.830737;,
  0.600000;0.830737;,
  0.600000;0.630737;,
  0.800000;0.625987;,
  0.800000;0.825987;,
  0.700000;0.825987;,
  0.700000;0.625987;,
  0.478769;0.523653;,
  0.416209;0.713617;,
  0.751301;0.823971;,
  0.813861;0.634007;,
  0.300000;0.850000;,
  0.300000;0.750000;,
  0.450231;0.750000;,
  0.450231;0.850000;,
  0.800000;0.850000;,
  0.800000;0.750000;,
  0.447204;0.750000;,
  0.447204;0.850000;,
  0.200000;0.750000;,
  0.200000;0.950000;,
  0.100000;0.750000;,
  0.100000;0.950000;,
  0.100000;0.850000;,
  0.300000;0.950000;,
  0.450231;0.950000;,
  0.600000;0.750000;,
  0.700000;0.750000;,
  0.600000;0.850000;,
  0.600000;0.950000;,
  0.700000;0.950000;,
  0.800000;0.950000;,
  0.447204;0.950000;,
  0.298390;0.624186;,
  0.100000;0.450000;,
  0.100000;0.550000;,
  0.199039;0.530613;,
  0.200089;0.611323;,
  -0.286708;0.525452;,
  0.200984;0.680160;,
  -0.284763;0.675000;,
  0.798390;0.624186;,
  0.658354;0.645929;,
  0.543717;0.809815;,
  0.420992;0.723969;,
  0.535630;0.560084;,
  0.354874;0.718096;,
  0.454874;0.722941;,
  0.454874;0.810157;,
  0.354874;0.810157;,
  0.300000;0.648765;,
  0.200000;0.662784;,
  0.200000;0.550000;,
  0.032668;0.773498;,
  0.198939;0.823379;,
  0.198939;0.889888;,
  0.198939;0.923142;,
  0.032668;0.939769;,
  0.577233;0.919650;,
  0.422767;0.919650;,
  0.577233;0.780631;,
  0.577233;0.765185;,
  0.422767;0.765185;;
 }
}
