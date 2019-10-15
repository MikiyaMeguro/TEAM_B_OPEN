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
 86;
 0.00000;5.85951;-7.61731;,
 0.00000;-2.21950;-10.18793;,
 -7.61731;-1.75781;-7.61731;,
 -6.58379;4.82598;-6.58379;,
 0.00000;5.85951;7.61731;,
 0.00000;6.92888;3.80887;,
 -6.58379;4.82598;6.58379;,
 -3.80887;6.92888;0.00000;,
 -7.61731;5.85951;0.00000;,
 -7.61731;-1.75781;7.61731;,
 0.00000;-2.21950;10.18793;,
 -6.15535;-9.27578;0.00000;,
 0.00000;-10.97398;-0.00000;,
 0.00000;-9.27578;6.15535;,
 -5.32007;-8.44050;5.32007;,
 -7.61731;5.85951;0.00000;,
 -10.18793;-2.21950;0.00000;,
 -7.61731;-1.75781;7.61731;,
 -6.58379;4.82598;6.58379;,
 7.61731;-1.75781;7.61731;,
 10.18793;-2.21950;-0.00000;,
 7.61731;5.85951;0.00000;,
 6.58379;4.82598;6.58379;,
 5.32007;-8.44050;5.32007;,
 6.15535;-9.27578;-0.00000;,
 6.58379;4.82598;6.58379;,
 7.61731;-1.75781;7.61731;,
 7.61731;5.85951;0.00000;,
 3.80887;6.92888;0.00000;,
 7.61731;-1.75781;-7.61731;,
 6.58379;4.82598;-6.58379;,
 0.00000;6.92888;-3.80887;,
 0.00000;-9.27578;-6.15535;,
 -5.32007;-8.44050;-5.32007;,
 5.32007;-8.44050;-5.32007;,
 5.32007;-8.44050;-5.32007;,
 0.00000;-9.27578;-6.15535;,
 -5.32007;-8.44050;-5.32007;,
 -6.15535;-9.27578;0.00000;,
 -5.32007;-8.44050;5.32007;,
 5.32007;-8.44050;5.32007;,
 6.15535;-9.27578;-0.00000;,
 0.00000;5.15379;0.00000;,
 -1.75997;10.56326;-4.17814;,
 -1.82993;10.27259;-4.20578;,
 -3.37482;10.56456;-5.04668;,
 -3.30485;10.85479;-5.01904;,
 -4.09306;10.81679;-0.94153;,
 -2.92651;10.69024;-2.55983;,
 -6.12770;10.93339;-4.88644;,
 -5.35894;11.07807;-2.16940;,
 -4.16303;10.52654;-0.96917;,
 -5.42890;10.78785;-2.19704;,
 -6.19854;10.64014;-4.91408;,
 -2.99648;10.39957;-2.58747;,
 -6.12770;10.93339;-4.88644;,
 -6.19854;10.64014;-4.91408;,
 -5.42890;10.78785;-2.19704;,
 -5.35894;11.07807;-2.16940;,
 -2.69113;9.93313;-0.15678;,
 -0.94239;9.37253;-1.02618;,
 -0.87199;9.66362;-0.99854;,
 -2.62116;10.22335;-0.12914;,
 -2.69113;9.93313;-0.15678;,
 -0.94239;9.37253;-1.02618;,
 -2.62116;10.22335;-0.12914;,
 -0.87199;9.66362;-0.99854;,
 -0.63704;9.70984;-3.00641;,
 -0.56708;10.00007;-2.97877;,
 -1.82993;10.27259;-4.20578;,
 -3.37482;10.56456;-5.04668;,
 -0.63704;9.70984;-3.00641;,
 0.60595;4.65409;-0.68585;,
 -0.69103;4.65409;-0.68585;,
 -1.12551;9.83638;-1.12033;,
 1.04043;9.83638;-1.12033;,
 -1.12551;9.83638;1.04561;,
 1.04043;9.83638;1.04561;,
 -0.69103;4.65409;0.61113;,
 0.60595;4.65409;0.61113;,
 -0.69103;4.65409;-0.68585;,
 0.60595;4.65409;-0.68585;,
 -0.69103;4.65409;0.61113;,
 -1.12551;9.83638;1.04561;,
 0.60595;4.65409;0.61113;,
 1.04043;9.83638;1.04561;;
 
 58;
 4;0,1,2,3;,
 3;4,5,6;,
 3;5,7,6;,
 3;7,8,6;,
 4;9,10,4,6;,
 4;11,12,13,14;,
 4;15,16,17,18;,
 4;19,20,21,22;,
 4;23,13,12,24;,
 4;25,4,10,26;,
 3;27,28,25;,
 3;25,28,4;,
 3;28,5,4;,
 4;29,1,0,30;,
 3;30,0,27;,
 3;27,0,28;,
 3;0,31,28;,
 3;31,0,7;,
 3;0,3,7;,
 3;3,8,7;,
 4;2,16,15,3;,
 4;32,12,11,33;,
 4;24,12,32,34;,
 4;21,20,29,30;,
 4;35,36,1,29;,
 4;2,1,36,37;,
 4;37,38,16,2;,
 4;17,16,38,39;,
 4;13,10,9,14;,
 4;26,10,13,23;,
 4;40,41,20,19;,
 4;29,20,41,35;,
 3;31,7,42;,
 3;28,31,42;,
 3;5,28,42;,
 3;7,5,42;,
 4;43,44,45,46;,
 4;47,48,49,50;,
 4;51,47,50,52;,
 4;53,54,51,52;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 4;63,51,54,64;,
 4;65,47,51,63;,
 4;66,48,47,65;,
 4;67,44,43,68;,
 4;68,43,48,66;,
 4;49,48,43,46;,
 4;45,56,55,46;,
 4;69,54,53,70;,
 4;64,54,69,71;,
 4;61,60,67,68;,
 4;72,73,74,75;,
 4;75,74,76,77;,
 4;77,76,78,79;,
 4;79,78,80,81;,
 4;73,82,83,74;,
 4;84,72,75,85;;
 
 MeshMaterialList {
  1;
  58;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\UV\\Apple_UV.jpg";
   }
  }
 }
 MeshNormals {
  65;
  0.508308;-0.695159;-0.508308;,
  -0.508308;-0.695159;-0.508308;,
  0.678399;0.282046;-0.678399;,
  -0.678399;0.282046;-0.678399;,
  0.493953;0.722533;0.483690;,
  -0.223422;0.948771;0.223422;,
  0.508308;-0.695159;0.508308;,
  -0.508308;-0.695159;0.508308;,
  0.000000;-0.789843;-0.613309;,
  0.000000;-0.789843;0.613309;,
  0.060472;0.783121;0.618922;,
  0.000000;0.254475;-0.967079;,
  0.610807;0.789546;-0.059429;,
  0.000000;1.000000;0.000000;,
  -0.710157;0.704043;0.000000;,
  -0.613309;-0.789843;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.613309;-0.789843;-0.000000;,
  0.701898;-0.121149;-0.701898;,
  0.000000;-0.110251;-0.993904;,
  -0.701898;-0.121149;-0.701898;,
  -0.993904;-0.110251;0.000000;,
  -0.701898;-0.121149;0.701898;,
  0.000000;-0.110251;0.993904;,
  0.701898;-0.121149;0.701898;,
  0.993904;-0.110251;-0.000000;,
  -0.064412;0.997010;-0.042676;,
  0.000000;0.997372;0.072447;,
  0.071465;0.997142;0.024485;,
  -0.031828;0.999458;-0.008385;,
  0.919576;-0.189040;-0.344447;,
  0.223317;0.038686;-0.973978;,
  -0.046142;-0.083691;0.995423;,
  0.153338;0.987833;-0.025948;,
  -0.846076;0.155595;0.509849;,
  0.583523;-0.063519;-0.809609;,
  -0.583506;0.063565;0.809617;,
  0.244144;0.968103;0.056307;,
  0.777812;-0.242934;0.579647;,
  0.223573;0.970966;0.085096;,
  0.125551;0.992005;0.012794;,
  -0.125377;-0.992029;-0.012596;,
  -0.223516;-0.970988;-0.084985;,
  0.000000;-0.083547;-0.996504;,
  0.000000;-0.083547;0.996504;,
  -0.678399;0.282046;0.678399;,
  0.180072;0.967030;-0.180072;,
  0.052471;0.968212;-0.244567;,
  -0.225785;0.951545;-0.208765;,
  -0.244310;-0.968086;-0.055878;,
  -0.153411;-0.987805;0.026591;,
  -0.944830;0.203697;0.256523;,
  -0.331433;-0.933408;-0.137483;,
  -0.318148;-0.935117;-0.156009;,
  0.318096;0.935130;0.156036;,
  0.331191;0.933463;0.137695;,
  0.304837;0.936320;0.174296;,
  0.202719;0.972605;0.113778;,
  0.097477;0.993904;0.051506;,
  -0.043801;0.104702;-0.993539;,
  -0.202434;-0.972640;-0.113982;,
  -0.097048;-0.993933;-0.051752;,
  -0.304696;-0.936337;-0.174453;,
  -0.996504;-0.083547;0.000000;,
  0.996504;-0.083547;-0.000000;;
  58;
  4;11,19,20,3;,
  3;10,29,5;,
  3;29,26,5;,
  3;26,14,5;,
  4;22,23,10,45;,
  4;15,16,9,7;,
  4;14,21,22,45;,
  4;24,25,12,4;,
  4;6,9,16,17;,
  4;4,10,23,24;,
  3;12,28,4;,
  3;4,28,10;,
  3;28,29,10;,
  4;18,19,11,2;,
  3;46,47,12;,
  3;12,47,28;,
  3;47,27,28;,
  3;27,47,26;,
  3;47,48,26;,
  3;48,14,26;,
  4;20,21,14,3;,
  4;8,16,15,1;,
  4;17,16,8,0;,
  4;12,25,18,2;,
  4;0,8,19,18;,
  4;20,19,8,1;,
  4;1,15,21,20;,
  4;22,21,15,7;,
  4;9,23,22,7;,
  4;24,23,9,6;,
  4;6,17,25,24;,
  4;18,25,17,0;,
  3;27,26,13;,
  3;28,27,13;,
  3;29,28,13;,
  3;26,29,13;,
  4;35,35,31,31;,
  4;37,39,40,33;,
  4;36,36,34,34;,
  4;41,42,49,50;,
  4;51,51,34,34;,
  4;32,38,38,32;,
  4;52,49,42,53;,
  4;32,36,36,32;,
  4;54,39,37,55;,
  4;30,35,35,30;,
  4;56,57,39,54;,
  4;40,39,57,58;,
  4;31,59,59,31;,
  4;60,42,41,61;,
  4;53,42,60,62;,
  4;38,38,30,30;,
  4;43,43,43,43;,
  4;13,13,13,13;,
  4;44,44,44,44;,
  4;16,16,16,16;,
  4;63,63,63,63;,
  4;64,64,64,64;;
 }
 MeshTextureCoords {
  86;
  0.210340;0.146850;,
  0.210340;0.092400;,
  0.264790;0.092400;,
  0.264790;0.146850;,
  0.210340;0.255740;,
  0.210340;0.228510;,
  0.264790;0.255740;,
  0.237560;0.201290;,
  0.264790;0.201290;,
  0.264790;0.310180;,
  0.210340;0.310180;,
  0.264790;0.419070;,
  0.210340;0.419070;,
  0.210340;0.364630;,
  0.264790;0.364630;,
  0.319230;0.146850;,
  0.319230;0.092400;,
  0.373670;0.092400;,
  0.373670;0.146850;,
  0.047010;0.092400;,
  0.101450;0.092400;,
  0.101450;0.146850;,
  0.047010;0.146850;,
  0.155900;0.364630;,
  0.155900;0.419070;,
  0.155900;0.255740;,
  0.155900;0.310180;,
  0.155900;0.201290;,
  0.183120;0.201290;,
  0.155900;0.092400;,
  0.155900;0.146850;,
  0.210340;0.174070;,
  0.210340;0.473510;,
  0.264790;0.473510;,
  0.155900;0.473510;,
  0.155900;0.037960;,
  0.210340;0.037960;,
  0.264790;0.037960;,
  0.319230;0.037960;,
  0.373670;0.037960;,
  0.047010;0.037960;,
  0.101450;0.037960;,
  0.210340;0.201290;,
  0.366670;0.765100;,
  0.233340;0.764320;,
  0.233730;0.697660;,
  0.367060;0.698440;,
  0.500000;0.765880;,
  0.433330;0.765490;,
  0.433720;0.698830;,
  0.500390;0.699210;,
  0.633330;0.766660;,
  0.633720;0.699990;,
  0.700390;0.700380;,
  0.700000;0.767050;,
  0.367450;0.631770;,
  0.234120;0.630990;,
  0.234510;0.564320;,
  0.367840;0.565100;,
  0.232170;0.964320;,
  0.232560;0.897650;,
  0.365890;0.898430;,
  0.365500;0.965100;,
  0.632940;0.833320;,
  0.699610;0.833710;,
  0.499610;0.832550;,
  0.432950;0.832160;,
  0.232950;0.830990;,
  0.366280;0.831770;,
  0.766660;0.767440;,
  0.767050;0.700770;,
  0.766270;0.834100;,
  0.699440;0.033200;,
  0.806380;0.033200;,
  0.806380;0.140150;,
  0.699440;0.140150;,
  0.806380;0.247090;,
  0.699440;0.247090;,
  0.806380;0.354030;,
  0.699440;0.354030;,
  0.806380;0.460980;,
  0.699440;0.460980;,
  0.913330;0.033200;,
  0.913330;0.140150;,
  0.592490;0.033200;,
  0.592490;0.140150;;
 }
}
